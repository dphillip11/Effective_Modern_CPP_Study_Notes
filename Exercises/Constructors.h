
class Constructors : public Exercise
{
public:
	void Run()
	{

	}

	enum class ops {
		move_constructor,
		move_assignment,
		copy_constructor,
		copy_assignment,
		constructor
	};


	class MyClass {
	private:
		int _value{ 0 };
	public:
		//map to track functions called
		static std::map<ops, int> operator_log;

		MyClass(int value) : _value(value) {
			++operator_log[ops::constructor];
		}

		// copy constructor
		MyClass(const MyClass& other) : _value(other._value) {
			++operator_log[ops::copy_constructor];
		}

		// copy assignment operator
		MyClass& operator=(const MyClass& other) {
			_value = other._value;
			++operator_log[ops::copy_assignment];
			return *this;
		}

		// move constructor
		MyClass(MyClass&& other) noexcept {
			_value = std::move(other._value);
			++operator_log[ops::move_constructor];
		}

		// move assignment operator
		MyClass& operator=(MyClass&& other) noexcept {
			if (this != &other)
			{
				_value = std::move(other._value);
				++operator_log[ops::move_assignment];
			}
			return *this;
		}
	};

	void Test()
	{
		// create an instance of MyClass
		MyClass a(42);
		assert(MyClass::operator_log[ops::constructor] == 1);

		// call the copy constructor
		MyClass b(a);
		assert(MyClass::operator_log[ops::copy_constructor] == 1);

		// call the copy assignment operator
		b = a;
		assert(MyClass::operator_log[ops::copy_assignment] == 1);

		// call the move constructor
		MyClass d(std::move(a));
		assert(MyClass::operator_log[ops::move_constructor] == 1);

		// call the move assignment operator
		b = std::move(d);
		assert(MyClass::operator_log[ops::move_assignment] == 1);
	}
};

std::map<Constructors::ops, int> Constructors::MyClass::operator_log = {};