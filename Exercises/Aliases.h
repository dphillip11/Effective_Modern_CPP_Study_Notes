#pragma once
# include "Exercise.h"

class Aliases : public Exercise
{
public:
	void Run()
	{
	}

	void Test()
	{
		//here an alias could be used to force an std::function type
		//but it doesn't provide any great advantage over auto

		using funcIF = std::function<bool(int, float)>;

		auto lessThan = [](int a, float b) {return a < b; };

		auto ptr = &lessThan;

		funcIF lessThan2 = [](int a, float b) {return a < b; };

		auto ptr2 = &lessThan2;

		assert((*ptr)(2.8f, 2.5f) == 1);
		assert((*ptr2)(2.8f, 2.5f) == 1);

	}
};