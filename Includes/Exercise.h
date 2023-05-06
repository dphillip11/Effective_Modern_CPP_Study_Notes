#pragma once
#include "Utils.h"
#include <string>
#include <cassert>
#include <vector>
#include <format>
#include <array>
#include <functional>
#include <map>


//Macro for saving us from writing Utils:: alot
#define Log(x) Utils::Log(x);

class Exercise {

private:
	static std::vector<Exercise*> exercises;

public:
	
	virtual void Run() = 0;
	virtual void Test() = 0;

	Exercise() {
		exercises.push_back(this);
	}

	static void RunExercises()
	{
		for (auto exercise : exercises)
		{
			exercise->Run();
			exercise->Test();
		}
	}
};

std::vector<Exercise*> Exercise::exercises;