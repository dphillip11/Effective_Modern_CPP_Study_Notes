#pragma once
# include "Exercise.h"

class Lambdas: public Exercise 
{
public:
	void Run()
	{
		//example of basic lambda function
		auto sum = [](double a, double b) { return a + b; };

		auto result = sum(9.0, 11.3);

	}	

	void Test()
	{
		int x = 5;
		//capture by value
		auto lambda_val = [x]() { return x;};
		//capture by reference
		auto lambda_ref = [&x]() {return x;};
		x = 10;
		//lambda_val returns captured value
		assert(lambda_val() == 5);
		//lambda_ref returns the new value of the referenced variable
		assert(lambda_ref() == 10);
	}
};