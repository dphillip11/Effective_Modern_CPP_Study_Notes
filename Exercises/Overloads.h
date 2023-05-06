#pragma once
# include "Exercise.h"


class Overloads : public Exercise
{
public:
	void Run()
	{

	}

	bool isSevenCheck(int input)
	{
		return input == 7;
	}

	bool isSevenCheck(float input) = delete;

	bool isEightCheck(int input)
	{
		return input == 8;
	}

	template <typename T>
	auto deref(T input)
	{
		return *input;
	}

	int deref(void* input) = delete;

	int deref(std::nullptr_t) = delete;



	void Test()
	{
		assert(isEightCheck(8));
		//implicit conversion causes an enexpected result here
		assert(isEightCheck(8.5));

		//we can use an explicitly deleted overload to fix this
		assert(isSevenCheck(7));
		//this is invalid because of the deleted overload
		//isSevenCheck(7.5f);

		int x = 7;
		assert(deref(&x) == 7);

		//we can use deleted functions to restrict template deductions too
		std::string y = "hello";
		assert(deref(&y) == "hello");

		void* ptr = &y;
		//deleted function
		//assert(deref(ptr) == 0);

		//deleted function
		//deref(nullptr);



	}
};