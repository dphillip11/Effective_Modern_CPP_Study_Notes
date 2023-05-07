#include "Exercise.h"

// Item 16: Item 16: Make const member functions thread safe.

namespace Item16 {

	//this class can be const instantiated, we do not want to calculate the roots repeatedly
	class Polynomial {
	public:
		using RootsType = std::vector<double>;
		RootsType roots() const
		{
			//using a lock guard ensures the mutex is released when the lock_guard goes out of scope
			//the mutex ensures only one thread can access the mutable state at any time
			std::lock_guard<std::mutex> g(m); // lock mutex
			if (!rootsAreValid) {
				// if cache not valid compute/store roots
				{}
				rootsAreValid = true;
			}
			return rootVals;
		} // unlock mutex
	private:
		// mutable state allows us to change values of a const object
		//mutexes cannot be copied so Polynomial objects cannot be copied but they can be moved
		mutable std::mutex m;
		mutable bool rootsAreValid{ false };
		mutable RootsType rootVals{};
	};

	class Point { // 2D point
	public:

		double distanceFromOrigin() const noexcept // see Item 14
		{
			++callCount; // atomic increment
			return std::sqrt((x * x) + (y * y));
		}
	private:
		//this mutable atomic allows a const function to change a counter, as an atomic it is an indivisible action which cannot be interrupted by another thread
		//atomics are also move only types
		mutable std::atomic<unsigned> callCount{ 0 };
		double x, y;
	};


	//This is an attempt to use atomics in place of a mutex
	class Widget {
	public:

		auto  expensiveComputation1() const { return 0; }
		auto  expensiveComputation2() const { return 0; }

		int magicValue() const
		{
			if (cacheValid) return cachedValue;
			else {
				auto val1 = expensiveComputation1();
				auto val2 = expensiveComputation2();
				//our expensive computations may be occuring on multiple threads while the cache is still marked invalid
				cachedValue = val1 + val2; // uh oh, part 1
				//if we swap these cache may be marked valid while the cachedValeus have not been updated
				cacheValid = true; // uh oh, part 2
				return cachedValue;
			}
		}
	private:
		mutable std::atomic<bool> cacheValid{ false };
		mutable std::atomic<int> cachedValue;
	};

	//this mutex ensures thread safety
	class Widget2 {
	public:

		auto  expensiveComputation1() const { return 0; }
		auto  expensiveComputation2() const { return 0; }

		int magicValue() const
		{
			std::lock_guard<std::mutex> guard(m); // lock m
			if (cacheValid) return cachedValue;
			else {
				auto val1 = expensiveComputation1();
				auto val2 = expensiveComputation2();
				cachedValue = val1 + val2;
				cacheValid = true;
				return cachedValue;
			}
		} // unlock m

	private:
		mutable std::mutex m;
		mutable int cachedValue; // no longer atomic
		mutable bool cacheValid{ false }; // no longer atomic
	};
}