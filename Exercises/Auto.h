#pragma once
# include "Exercise.h"

class boolContainer {
private:
	std::vector<bool> _bool_values{ true, false, true, false, false, false, true, true };

public:
	auto GetBools()
	{
		return _bool_values;
	}
	void TestBool(auto bool_value, int position)
	{
		assert(bool_value == _bool_values[position]);
	}
};

class Auto: public Exercise 
{
public:
	void Run()
	{
		
	}

	//returns a lambda function for comparing two variables using <
	auto GetFunction()
	{
		//a closure is defined here as an auto variable, taking two auto variables, the return type is not defined
		auto smaller =
			[](auto a, auto b) {return a < b;};
		return smaller;
	}

	//returns an std::function for comparing two variables using <
	template <typename T1, typename T2>
	std::function<bool(T1, T2)> GetFunction2()
	{
		//a closure is defined here using the template types
		std::function<bool(T1, T2)> smaller =
			[](T1 a, T2 b) {return a < b;};
		return smaller;
	}

	void Test()
	{
		//the function is corectly passed and functions correctly for integers and floats
		auto function = GetFunction();
		assert(function(9, 6) == false);
		assert(function(3, 6) == true);
		assert(function(3.1, 3.3) == true);
		assert(function(3.3, 3.1) == false);

		//function2 requires the types to be declared
		auto function2 = GetFunction2<int,int>();

		//this works for ints but fails for floats
		//assert(function2(9, 6) == false);
		//assert(function2(3.1, 3.3) == false);

		//we can however change the parameters
		auto function3 = GetFunction2<float, float>();
		assert(function3(3.1f, 3.3f) == true);

		//we could also truncate the first by treating it as an int and keep the decimal places for the second if we so wish
		//GetFunction2 may be somewhat more flexible, but GetFunction is easy to read, write and use
		//std::functions are more bloated than lambdas if performance is a concern
		auto function_type = typeid(decltype(function)).name();
		auto function_type2 = typeid(decltype(function2)).name();
		auto function_type3 = typeid(decltype(function3)).name();

		// this highlights an unexpected type deduction
		boolContainer bc;
		int index = 2;
		//here we can see response one has a std::vecto<bool>::reference type, a proxy to the boolean value in the vector
		auto response1 = bc.GetBools()[index];
		//using the response may cause undefined behaviour as the type is not the expected one
		  //bc.TestBool(response1, index);
		  
		//we can explicitly show we intend to recieve a bool using the static cast
		auto response2 = static_cast<bool>(bc.GetBools()[index]);
		//we can then use the bool value
		bc.TestBool(response2, index);
		//or use explicit declaration of our variable
		bool response3 = static_cast<bool>(bc.GetBools()[index]);
		//we can then use the bool value
		bc.TestBool(response3, index);
		
		//this highlights a problem caused by incorrect implicit declaration
		std::unordered_map<std::string, int> m{ {"frst", 1}, {"secd", 2}, {"thrd", 3}, {"frth", 4}, {"ffth", 5} };

		//create an empty pointer to a pair
		const std::pair<std::string, int>* address = nullptr;

		for (const std::pair<std::string, int>& p : m)
		{
			//update the pointer if it is empty
			if (address == nullptr)
				address = &p;
			//this shows that the address is not changing for each value, the pair is being copied to a new location where it can be accessed
			//this is because the pair has a a type pair<const string, int> but is being accessed as a non const string
			else
				assert(address == &p);
		}
		//the dereferenced pointer will be undefined after the loop, the dereferenced key will not have a string of length 4
		//assert(address->first.length() != 4);
		const std::pair<const std::string, int>* address2 = nullptr;

		for (const auto& p : m)
		{
			//the address for each element is different, notice the pointer type includes the const string
			assert(&p != address2);
			address2 = &p;
		}
		//the address is still valid and may be dereferenced
		//assert(address2->first.length() == 4);



		
	}
};