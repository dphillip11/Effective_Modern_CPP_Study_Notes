#pragma once
# include "Exercise.h"


class Inheritance : public Exercise
{
	enum class FUNCTION {
		BASE_FUNCTION,
		DERIVED_FUNCTION,
		BASE_DESTRUCTOR,
		DERIVED_DESTRUCTOR
	};

	//shared pointer to a map type to track which functions have been called
	using mapEB =
		std::shared_ptr<std::map<Inheritance::FUNCTION, bool>>;

	static mapEB getEmptyMap()
	{
		mapEB map = std::make_shared<std::map<Inheritance::FUNCTION, bool>>();
		(*map)[FUNCTION::BASE_FUNCTION] = false;
		(*map)[FUNCTION::DERIVED_FUNCTION] = false;
		(*map)[FUNCTION::BASE_DESTRUCTOR] = false;
		(*map)[FUNCTION::DERIVED_DESTRUCTOR] = false;
		return map;
	}	

	//A and B correctly delegate function calls based on the instantiated class due to virtual declarations and override declaration
	class A {
	public:
		mapEB _map;
		A(mapEB& map) : _map(map) {};
		//this is the same name as function in B, but accepts const int, a possible mistake
		virtual void f() {
			(*_map)[FUNCTION::BASE_FUNCTION] = true;
		}

		virtual ~A() {
			(*_map)[FUNCTION::BASE_DESTRUCTOR] = true;
		}
	};

	class B : public A {
	public:
		B(mapEB& map) : A(map) {};

		void f() override{
			(*_map)[FUNCTION::DERIVED_FUNCTION] = true;
		}

		~B() {
			(*_map)[FUNCTION::DERIVED_DESTRUCTOR] = true;
		}
	};

	//C and D are more haphazard and can produce unexpected behaviour
	class C {
	public:
		mapEB _map;

		C(mapEB map) : _map(map) {};

		~C() {
			(*_map)[FUNCTION::BASE_DESTRUCTOR] = true;
		}

		virtual void f(int) {
			(*_map)[FUNCTION::BASE_FUNCTION] = true;
		}
	};

	class D : public C {
	public:

		D(mapEB map) : C(map) {};

		~D() {
			(*_map)[FUNCTION::DERIVED_DESTRUCTOR] = true;
		}

		//using override here ensures correct overriding of the virtual function in the base class
		//void f(int&) override{
		void f(int&) {
			(*_map)[FUNCTION::DERIVED_FUNCTION] = true;
		}
	};



public:
	void Run()
	{
	}



	void Test()
	{
		mapEB map = Inheritance::getEmptyMap();
		//scoped declaration to invoke destructor
		if (true)
		{
			B b(map);
		}
		//using a virtual destructor, the derived and base destructors are both called
		assert((*map)[FUNCTION::BASE_DESTRUCTOR] == true && (*map)[FUNCTION::DERIVED_DESTRUCTOR] == true);

		map = Inheritance::getEmptyMap();

		//even using an A type pointer will call the B destructor
		if (true)
		{
			std::unique_ptr<A> ptr = std::make_unique<B>(map);
		}
		assert((*map)[FUNCTION::BASE_DESTRUCTOR] == true && (*map)[FUNCTION::DERIVED_DESTRUCTOR] == true);

		map = Inheritance::getEmptyMap();

		if (true)
		{
			std::unique_ptr<A> ptr = std::make_unique<B>(map);
			//even calling the A destructor explicitly will call the B destructor
			ptr->~A();
			assert((*map)[FUNCTION::BASE_DESTRUCTOR] == true && (*map)[FUNCTION::DERIVED_DESTRUCTOR] == true);
		}

		map = Inheritance::getEmptyMap();
			
		//scoped declaration to invoke destructor
		if (true)
		{
			std::unique_ptr<C> ptr = std::make_unique<D>(map);
		}
		//no virtual destructor means ~D() is not called
		assert((*map)[FUNCTION::BASE_DESTRUCTOR] == true && (*map)[FUNCTION::DERIVED_DESTRUCTOR] == false);

		map = Inheritance::getEmptyMap();
		std::unique_ptr<C> d = std::make_unique<D>(map);

		//here the virtual declaration fails because of a slight difference in the parameters, referenceness and constness can cause unexpected delegation
		int x = 1;
		d->f(x);
		assert((*map)[FUNCTION::BASE_FUNCTION] == true && (*map)[FUNCTION::DERIVED_FUNCTION] == false);
	}
};