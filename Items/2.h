#include "Exercise.h"
// Item 2: Understand auto type deduction.
class Item2
{
	// auto type deduction is template type deduction, therefore the cases are the same
		// Case 1: The type specifier is a pointer or reference, but not a universal reference.
		// Case 2 : The type specifier is a universal reference.
		// Case 3 : The type specifier is neither a pointer nor a reference.

	template<typename T>
	void f(T param) {}

	template<typename T> // conceptual template for
	void const_f(const T param) {}

	template<typename T> // conceptual template for
	void ref_f(const T& param) {}

	void someFunc(int, double) {} // someFunc is a function, type is void(int, double)

	void Test()
	{
		auto x = 27;			// case 3 (x is neither ptr nor reference)
		const auto cx = x;		// case 3 (cx isn't either)
		const auto& rx = x;		// case 1 (rx is a non-universal ref.)

		auto&& uref1 = x;		// x is int and lvalue, so uref1's type is int&
		auto&& uref2 = cx;		// cx is const int and lvalue, so uref2's type is const int&
		auto&& uref3 = 27;		// 27 is int and rvalue, so uref3's type is int&&

		const char name[] = "R. N. Briggs";			// name's type is const char[13]
		auto arr1 = name;							// arr1's type is const char*
		auto& arr2 = name;							// arr2's type is const char (&)[13]

		auto func1 = someFunc;			// func1's type is void (*)(int, double)
		auto& func2 = someFunc;			// func2's type is void (&)(int, double)

		auto x1 = 27;	// type is int, value is 27
		auto x2(27);	// type is int, value is 27

		auto x3 = { 27 };	//type is std::initializer_list<int>, value is { 27 }
		auto x4{ 27 };	// type is int, value is 27

		auto x5 = { 1, 2, 3.0 }; // error! can't deduce T for std::initializer_list<T>

	}
};