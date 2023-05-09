
namespace Utils
{
	//accepts types with defined behaviour for <<
	template <typename T>
	void Log(T input)
	{
		std::cout << input << std::endl;
	}

	//accepts brace initialized lists
	template <typename T>
	void Log(const std::initializer_list<T>& input)
	{
		for (T item : input)
		{
			std::cout << item << ", ";
		}
		std::cout << std::endl;
	}

	//accepts vectors
	template <typename T>
	void Log(const std::vector<T>& input)
	{
		for (T item : input)
		{
			std::cout << item << ", ";
		}
		std::cout << std::endl;
	}
}

