
class Noexcept : public Exercise
{
public:
	MyType() noexcept {
		std::cout << "MyType default constructor called.\n";
	}

	MyType(const MyType& other) noexcept(false) {
		std::cout << "MyType copy constructor called.\n";
		if (other.val == 0) {
			throw std::runtime_error("Cannot copy a MyType object with a value of zero.");
		}
		val = other.val;
	}

	int getVal() const noexcept {
		return val;
	}

private:
	int val = 0;
};

void run() {
	MyType a; // default constructor, no-throw
	MyType b{ a }; // copy constructor, potentially throws
	std::cout << "a.getVal(): " << a.getVal() << "\n"; // no-throw
	std::cout << "b.getVal(): " << b.getVal() << "\n"; // potentially throws
}

	};