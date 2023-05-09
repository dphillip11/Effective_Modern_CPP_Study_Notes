
class Vectors : public Exercise
{
public:
	void Run()
	{
	}

	void pushZeroesToVector(std::vector<int>& vector, int n)
	{
		for (int i = 0; i < n; i++)
		{
			vector.push_back(0);
		}
	}

	void Test()
	{
		//show that vectors must be reallocated as they grow
		std::vector<int> numbers;
		numbers.push_back(0);
		int* initialAddress = &numbers[0];
		pushZeroesToVector(numbers, 100);
		int* currentAddress = &numbers[0];
		assert(currentAddress != initialAddress);

		//use reserve to avoid this
		numbers.clear();
		numbers.reserve(1000);
		numbers.push_back(0);
		initialAddress = &numbers[0];
		pushZeroesToVector(numbers, 800);
		currentAddress = &numbers[0];
		assert(currentAddress == initialAddress);

		// this shows that when the vector is reallocated the iterator is invalidated
		//you might expect that if the vector has 800 zeroes, when iterated you should have 1600 elements but instead the size is equal to the previous capacity + 1 as the iterator is valid unitl the first push beyond capacity
		numbers.clear();
		//this will populate the vector with zeroes until the vector has size 800
		numbers.resize(800, 0);
		//we add a 1 to the vector for every zero we read
		for (auto number : numbers)
		{
			if (number == 0)
			{
				numbers.push_back(1);
			}
		}
		//notice this issue does not flag an error when the iterator is invalidated
		int n = (int)numbers.size();
		assert(n == 1001);
	}
};