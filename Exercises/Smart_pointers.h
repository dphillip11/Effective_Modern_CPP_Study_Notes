#pragma once
# include "Exercise.h"


class Smart_pointers : public Exercise
{
public:
	void Run()
	{
	}

	class ptr_container {
	private:
		std::unique_ptr<int> _contained_ptr;
	public:
		ptr_container(auto& ptr) { _contained_ptr = std::move(ptr); }
		auto& get_ptr() { return _contained_ptr; }
	};

	void Test()
	{
		//unique pointer is assigned
		auto int_ptr = std::make_unique<int>(31);

		//copy constructor is deleted
		//auto int_ptr2 = int_ptr;

		//constructor moves pointer
		ptr_container new_container{ int_ptr };

		//old pointer is nulled as the unique ptr keeps only one reference
		assert(int_ptr == nullptr);

		//new pointer is valid
		assert(*new_container.get_ptr() == 31);

		auto new_ptr = std::make_unique<int>(25);
		//we can however move a unique pointer to a shared pointer
		std::shared_ptr<int> new_ptr2 = std::move(new_ptr);
		//then we can copy it
		auto copy_ptr = new_ptr2;
		//both pointers are intact
		assert(*new_ptr2 == *copy_ptr && *copy_ptr == 25);
		//our reference count is correct also as our unique pointer is nullified
		assert(new_ptr2.use_count() == 2);


		//shared pointers keep count
		std::shared_ptr<int> s_ptr1 = std::make_shared<int>(42);

		if (true)
		{
			//this pointer is scoped to this if statement
			auto ptr2 = s_ptr1;
			assert(s_ptr1.use_count() == 2);
		}

		// reference count is updated
		assert(s_ptr1.use_count() == 1);

		auto ptr2 = std::move(s_ptr1);

		//move operation nullifies old pointer, count is unchanged
		assert(s_ptr1 == nullptr);
		assert(ptr2.use_count() == 1);

		//things go wrong if you convert raw pointers to shared as a new reference block is created even if the pointer is the same
		/*int* rawPtr = new int(42); // create a raw pointer
		std::shared_ptr<int> sharedPtr(rawPtr); // create a shared pointer from the raw pointer

		// create two reference blocks for the same pointer
		std::shared_ptr<int> block1(sharedPtr);
		std::shared_ptr<int> block2(sharedPtr);

		// accessing the value through any of the shared pointers is safe
		std::cout << *sharedPtr << '\n'; // outputs 42

		// however, deleting the pointer through any of the shared pointers leads to undefined behavior
		delete sharedPtr.get(); // undefined behavior*/

		//both shared and unique pointers may be given custom deleter functions but their implementation is different, 
		//the unique ptr carries its deleter, the shared pointer carries a reference to its reference block where the deleter resides

		bool deleter1Called = false;
		bool deleter2Called = false;
		auto deleterFunction1 = [&deleter1Called](int*) {deleter1Called = true;};
		auto deleterFunction2 = [&deleter2Called](int*) {Log("2 called"); deleter2Called = true;};

		//this is the syntax for adding a deleter to a unique ptr, notice the type contains the deleter and the function is passed as an argument
		std::unique_ptr<int, decltype(deleterFunction1)> uptr(new int{ 1 }, deleterFunction1);

		//a shared ptr type does not contain the deleter, 
		std::shared_ptr<int> sptr(new int{ 1 }, deleterFunction2);

		std::cout << "uptr size: " << sizeof(uptr) << "\n" << "sptr size: " << sizeof(sptr);
		//assert(sizeof(uptr) > sizeof(sptr));

		uptr.reset();
		assert(deleter1Called);

		sptr.reset();
		assert(deleter2Called);








	}
};