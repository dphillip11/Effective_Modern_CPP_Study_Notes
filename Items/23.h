//"Item23: Understand std::move and std::forward."

namespace Item23 {

	class MyType {
	public:
		MyType() = default;
		MyType(const MyType&) {
			std::cout << "Copy constructor called.\n";
		}
		MyType(MyType&&) noexcept {
			std::cout << "Move constructor called.\n";
		}
	};

	void processMyType(MyType&& myType) {
		// Do something with myType.
	}

	void run() {
		std::vector<MyType> v1;
		MyType myType;

		v1.push_back(std::move(myType)); // Move myType into the vector.

		processMyType(std::move(myType)); // Move myType into the function.
	}

} // namespace Item23