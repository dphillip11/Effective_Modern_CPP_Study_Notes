// Item__: Understand template type deduction
class Item1
{
	// Case 1: ParamType is a Reference or Pointer, but not a Universal Reference
		//	param is a reference
		template<typename T>
		void f(T& param) {}
		// param is a const reference
		template<typename T>
		void const_f(const T& param) {}
		// param is a pointer
		template<typename T>
		void ptr_f(T* param) {} 

	// Case 2:: ParamType is a Universal Reference
		template<typename T>
		void g(T&& param); 

	// Case 3: ParamType is Neither a Pointer nor a Reference
		// param is passed by value
		template<typename T>
		void h(T param) {}


	void Test()
	{
		int x = 27; // x is an int
		const int cx = x; // cx is a const int
		const int& rx = x; // rx is a reference to x as a const int
		const int* px = &x; // px is a const pointer to x

		//hover to see param type deduction
		f(x);	// T is int, param's type is int&
		f(cx);	// T is const int, param's type is const int&
		f(rx);	// T is const int, param's type is const int&

		const_f(x); // T is int, param's type is const int&
		const_f(cx); // T is int, param's type is const int&
		const_f(rx); // T is int, param's type is const int&

		ptr_f(&x);	// T is int, param's type is int*
		ptr_f(px);	// T is const int, param's type is const int*

		g(x);	// x is lvalue, so T is int&, param's type is also int&
		g(cx);	// cx is lvalue, so T is const int&, param's type is also const int&
		g(rx);	// rx is lvalue, so T is const int&, param's type is also const int&
		g(27);	// 27 is rvalue, so T is int, param's type is therefore int&&

		h(x); // T's and param's types are both int
		h(cx); // T's and param's types are again both int
		h(rx); // T's and param's types are still both int

		const char* const ptr = "Fun with pointers"; // ptr is const pointer to const object
		h(ptr); //the pointer value is copied and is non const but the referenced string is still const
	}
};