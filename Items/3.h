#include "Exercise.h"
// Item 3: Understand decltype.
class Item3
{
	class Widget {};

	bool f(const Widget& w) {};	// decltype(w) is const Widget&
	// decltype(f) is bool(const Widget&)

	template<typename T> // simplified version of std::vector
	class vector {
	public:
		T& operator[](std::size_t index) {};
	};

	template<typename Container, typename Index>
	//using decltype(auto) here ensures referenceness is maintained
	decltype(auto) authAndAccess(Container&& c, Index i)
	{
		authenticateUser();
		return std::forward<Container>(c)[i];
		//we don't want to be handed a copy of the container as we wish to update the value it holds
	}

	void Test()
	{
		const int i = 0;	// decltype(i) is const int

		struct Point {
			int x, y;	// decltype(Point::x) is int
		};				// decltype(Point::y) is int

		Widget w;		// decltype(w) is Widget
		if (f(w)) {}		// decltype(f(w)) is bool

		vector<int> v; // decltype(v) is vector<int>

		if (v[0] == 0) {} // decltype(v[0]) is int&

		int j = 0; // decltype(j) is int

		// int and const int have different types when using decltype
		auto sameType = std::is_same_v<decltype(i), decltype(j)>;
		assert(!sameType);
	}
};