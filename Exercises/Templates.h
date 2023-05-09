
class Templates : public Exercise
{
	class A
	{
	public:
		//our virtual function ensures B and A maintain their respective behaviours
		virtual std::string GetType() const {
			return std::format("This is an object of type: {}", typeid(*this).name());
		}

	};

	class B : public A
	{
	public:
		std::string GetType() const override {
			return std::format("This is an object of type: {}", typeid(*this).name());
		}
	};

	//force an error to display types
	//usage: TD<decltype(variable)> variable_type;
	template<typename T> // declaration only for TD;
	class TD; // TD == "Type Displayer"

public:
	void Run()
	{
	}

	template <typename T>
	void changeInt_by_reference(T& input)
	{
		input++;
	}

	template <typename T>
	void changeInt_by_value(T input)
	{
		input++;
	}

	//this function updates a string reference with the type of the first argument
	template <typename T>
	void checkType(const T& input, std::string& output_string)
	{
		output_string = (typeid(input).name());
	}

	//this function passes an array by reference which means the length is available
	template <typename T>
	int checkArraySize(T& array)
	{
		return sizeof(array);
	}

	//this function is doomed to fail as the array degrades to a pointer to its first value
	template <typename T>
	int checkArraySize_non_reference(T array)
	{
		return sizeof(array);
	}

	//this function uses a universal reference so the leftness, rightness, constness and referenceness are preserved during template deduction
	template <typename T>
	T PerfectForward(T&& input)
	{
		//using forward preserves the type and adornments of the output
		return std::forward<T>(input);
	}


	void Test()
	{
		//check function handles integers
		std::string output;
		int i = 0;
		checkType(i, output);
		assert(output == "int");

		//check auto initialized int
		auto integer = 1;
		checkType(integer, output);
		assert(output == "int");

		//check that brace initialized auto returns int
		auto brace_initialized_integer{ 1 };
		checkType(brace_initialized_integer, output);
		assert(output == "int");

		//check that braced auto returns initializer list
		auto braced_integer = { 1 };
		checkType(braced_integer, output);
		assert(output == "class std::initializer_list<int>");

		//check int rvalue
		checkType(0, output);
		assert(output == "int");

		//check handles custom class
		A a;
		checkType(a, output);
		assert(output == "class Templates::A");

		//check function handles extended class
		B b;
		checkType(b, output);
		assert(output == "class Templates::B");

		A* a_ptr = &b;
		//check if wrong pointer type interferes with type deduction
		checkType(*a_ptr, output);
		assert(output == "class Templates::B");

		//cast b to A type changes output
		checkType((A)b, output);
		assert(output == "class Templates::A");

		//check bool rvalue
		checkType(true, output);
		assert(output == "bool");

		int numbers[] = { 1,2,3,4,5 };
		int size = sizeof(numbers);

		//see that passing an array fails
		assert(checkArraySize_non_reference(numbers) == sizeof(nullptr));

		//see that passing by reference works
		assert(checkArraySize(numbers) == size);

		int x = 10;
		int& ref_x = x;

		//this shows that using a paramType with a reference will pass by reference
		changeInt_by_reference(ref_x);
		assert(ref_x == 11);

		//this shows that even passing a reference type, the value is copied if the paramType does not feature a '&'
		changeInt_by_value(ref_x);
		assert(ref_x == 11);

		//the referenceness of the variable is ignored during type deduction so we have the same result for the non reference int
		changeInt_by_reference(x);
		assert(ref_x == 12);
		changeInt_by_value(x);
		assert(ref_x == 12);

		//overcomes auto type deduction fail by declaring vector explicitly as opposed to a std::initializer_list
		std::vector<int> v;
		auto resetV = [&v](const auto& newValue) { v = newValue; };
		resetV(std::vector<int>{1, 2, 3});
		assert(v[2] == 3);
		//this cannot compile
		//  resetV({1, 2, 3});

		//here we have a modifiable variable and a const reference to it
		float f = 0.5;
		const float& f_ref = f;
		//we assign g and h using auto deduction
		auto g = f_ref;
		decltype(auto) h = f_ref;

		//we can modify g because it has been copied by value as a float
		g = 1;
		//TD<decltype(g)> gType;
		assert(g != f);

		//we can't modify h, it is a compile time error
		//h = 1;
		//TD<decltype(h)> hType;

		//as const references the memory address is preserved
		assert(&h == &f_ref);

		//if we change f, both h and f_ref should change as the const referenceness is preserved
		f = 3.2f;
		assert(f == f_ref && f == h && f_ref == h);
		assert(f != g);

		//if we pass a const value using perfect forwarding, it will return a const value
		const int t = 10;

		//using auto does not capture the constness as captures by value
		auto s = PerfectForward(t);
		assert(&t != &s);
		//TD<decltype(s)> s_Type;

		//using decltype ensures constness is preserved
		decltype(auto) new_s = PerfectForward(t);
		assert(&new_s == &t);
		//TD<decltype(new_s)> new_s_Type;

	}
};

