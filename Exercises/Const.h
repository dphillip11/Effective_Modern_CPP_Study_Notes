
# include "Exercise.h"

class Const : public Exercise
{
public:
	void Run()
	{
	}

	void modifyConstValue(int* input)
	{
		*input = 5;
	}

	//this object has a number of constexpr functions which means that given constexpr arguments they can be performed at compile time producing constexpr results
	class CompileTimeObject
	{
	private:
		int _ID{ 0 };
		float _weight{ 0.0f };
		//string view allows strings to behave as constexpr
		std::string_view _name{ "Noname" };
	public:
		constexpr CompileTimeObject(int ID, float weight, auto name) noexcept
			: _ID(ID), _weight(weight), _name(name) {}
		constexpr auto GetID() const noexcept { return _ID; }
		constexpr auto GetWeight() const noexcept { return _weight; }
		constexpr auto GetName() const noexcept { return _name; }
	};

	// constexpr functions cannot use I/O statements as they will not compile
	// if a function is likely to require I/O statements for debugging, you may want to omit constexpr
	/*constexpr int add(int x, int y) {
		std::cout << "Adding " << x << " and " << y << std::endl;
		return x + y;
	}*/


	//this is a generic find and insert function using const interators
	template<typename C, typename V>
	void findAndInsert(C& container, // in container, find
		const V& targetVal, // first occurrence
		const V& insertVal) // of targetVal, then
	{ // insert insertVal
		using std::cbegin; // there
		using std::cend;
		auto it = std::find(cbegin(container), // non-member cbegin
			cend(container), // non-member cend
			targetVal);
		container.insert(it, insertVal);
	}

	//class with const member function
	class MyClass {
	public:
		//modifies the state
		void setValue(int value) { m_value = value; }
		//doesn't modify state of object, const safe
		int getValue() const { return m_value; } // const member function
	private:
		int m_value{ 0 };
	};

	void Test()
	{
		constexpr auto string = "new_name";

		// this object can be constructed at compile time
		constexpr CompileTimeObject CTO(5, 8.8f, string);
		assert(CTO.GetName() == "new_name");
		// furthermore we can allocate fixed arrays based on its constexpr functions at compile time
		int array[CTO.GetID()];

		// this will fail depending on the compiler, g++ enforces const-ness, gcc does not
		const int x = 1;
		int* x_ptr = const_cast<int*>(&x);
		modifyConstValue(x_ptr);
		assert(x == 1);

		//we can use const iterator values using cbegin and cend
		std::vector<int> values;
		auto it = std::find(values.cbegin(), values.cend(), 1983);// use cbegin
		values.insert(it, 1998);

		findAndInsert(values, 1998, 1983);

		// we are not allowed to change existing values using the const iterator
		/*for (auto it = std::cbegin(values); it != std::cend(values); ++it) {
			(*it)++;
		}*/

		const MyClass obj;
		//obj.setValue(42); // compile error: can't modify a const object
		int value = obj.getValue(); // okay: const member function can be called on a const object
	}
};