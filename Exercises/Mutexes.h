# include "Exercise.h"


class Mutexes : public Exercise
{
public:
	void Run()
	{

	}

	class CachedObject {
	public:
		void CalculateValue() const
		{
			cachedValue = 32;
		}

		int GetValue() const
		{
			//our mutex stops concurrent threads proceeding to calculate or requesting cached value
			std::lock_guard<std::mutex>g(m);
			if (!cacheIsValid)
			{

				CalculateValue();
				cacheIsValid = true;
			}
			return cachedValue;
		}

	private:
		mutable std::mutex m;
		mutable int cachedValue{ 0 };
		mutable bool cacheIsValid{ false };

	};

	void Test()
	{
		const CachedObject CO;
		//cannot be copied
		//CachedObject CO2 = CO;

		int value = CO.GetValue();
		assert(value == 32);

	}
};