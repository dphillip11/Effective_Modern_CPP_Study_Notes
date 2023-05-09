
class constructor {

public:
	//we can forward declare enum classes to clean up our headers
	enum class CTOR;

	//the type of an enum becomes the enum class and is strongly typed as opposed to behaving as an int
	enum class CTOR {
		DEFAULT,
		INTEGER,
		INITIALIZER_LIST,
		FLOAT,
		LONG
	};

	//using an enum class here allows us to use the same names for variables within the constructor class
	int INITIALIZER_LIST = 0;

	CTOR constructor_used;

	constructor() {
		constructor_used = CTOR::DEFAULT;
	}
	constructor(int f1, bool f2)
	{
		constructor_used = CTOR::INTEGER;
	}
	//this constructor would be used in the absence of the better suited parameter types
	constructor(float f1, float f2)
	{
		constructor_used = CTOR::FLOAT;
	}
	//this will be used  despite the ill fitting parameter types due to the conformity with the initializer list type
	constructor(std::initializer_list<float> array)
	{
		constructor_used = CTOR::INITIALIZER_LIST;
	}
	constructor(long f1, long f2)
	{
		constructor_used = CTOR::LONG;
	}

};

class BracedInitializers : public Exercise
{
public:
	void Run()
	{

	}

	void Test()
	{
		//braces here are fine, they can also be omitted and the default constructor will be called
		constructor a1{};
		assert(a1.constructor_used == constructor::CTOR::DEFAULT);

		//wrapping this in parentheses or an extra set of braces however will invoke the initializer list constructor despite the lack of arguments
		constructor a({});
		assert(a.constructor_used == constructor::CTOR::INITIALIZER_LIST);

		//this shows how braced initialization prefers initializer lists
		constructor a2(2, true);
		assert(a2.constructor_used == constructor::CTOR::INTEGER);

		//in this case, the int value and bool are converted to floats to satisfy the initializer list constructor
		constructor a3{ 2, true };
		assert(a3.constructor_used == constructor::CTOR::INITIALIZER_LIST);

		//the arguments will even be narrow in this case
		constructor a4{ (long)1, long(2) };
		assert(a4.constructor_used == constructor::CTOR::INITIALIZER_LIST);

		long l1 = 1;
		long l2 = 2;
		//this wont even compile because of narrowing despite a better constructor being defined
		  //constructor a5{ l1, l2 };

		//this will work due to the change of parentheses
		constructor a5(l1, l2);
		assert(a5.constructor_used == constructor::CTOR::LONG);

		//Avoid implementing a constructor for initializer lists as it could cause incorrect usage

		//std::vector has a curious usage of braced vs non-braced initialization
		std::vector<int> new_vector{ 5, 6 };
		assert(new_vector.size() == 2);

		//the constructor also accepts the arguments size and value
		std::vector<int> new_vector2(5, 6);
		assert(new_vector2.size() == 5);

		//we can compare enum class CTOR types
		assert(constructor::CTOR::INTEGER < constructor::CTOR::FLOAT);

		//but we can no longer compare enums to int if using the class keyword
		  //assert(constructor::CTOR::INTEGER < 5);

		//we can however type cast them if we really want to
		assert(static_cast<int>(constructor::CTOR::INTEGER) < 5);


	}
};