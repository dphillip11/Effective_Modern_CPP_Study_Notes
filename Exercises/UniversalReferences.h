

class UniversalRefVsRvalueRef : public Exercise {
public:
	class MyType {
	public:
		MyType(int val) : value{ val } {}
		MyType(MyType&& other) noexcept : value{ std::exchange(other.value, 0) } {}
		int getValue() const { return value; }
	private:
		int value;
	};

	void Run() override {
		MyType a{ 5 };
		std::cout << "Before move:\n";
		printValueType(a);

		// Pass a universal reference to a function
		f(std::forward<MyType>(a));

		// Check that 'a' has been moved from
		std::cout << "After move:\n";
		printValueType(a);
	}

	void Test() override {
		MyType a{ 5 };
		MyType b{ std::move(a) };
		assert(a.getValue() == 0);
		assert(b.getValue() == 5);
	}

private:
	// Define a function that takes a universal reference
	template <typename U>
	void f(U&& arg) {
		std::cout << "f called with arg of type ";
		printValueType(arg);

		// Pass 'arg' to another function that takes an rvalue reference
		g(std::forward<U>(arg));
	}

	// Define a function that takes an rvalue reference
	template <typename U>
	void g(U&& arg) {
		std::cout << "g called with arg of type ";
		printValueType(arg);

		// Move 'arg' to a new object
		MyType newObj{ std::move(arg) };
	}

	// Helper function to print the type of a variable
	template <typename U>
	void printValueType(const U& arg) {
		std::cout << typeid(arg).name() << '\n';
	}
};

