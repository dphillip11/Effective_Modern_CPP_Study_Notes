#include "pch.h"

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