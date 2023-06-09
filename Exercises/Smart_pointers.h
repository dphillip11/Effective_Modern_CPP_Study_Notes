
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
		//the unique ptr carries its deleter, the shared pointer carries a reference to its control block where the deleter resides
		bool deleter1Called = false;
		bool deleter2Called = false;
		//we will add some capture data to bloat the uptr size
		std::vector<int> bloat = { 1,2,3,4,5,6,7,8,9,10 };
		//pass the bloat by value to increase bloat
		auto deleterFunction1 = [&deleter1Called, bloat](int*) {deleter1Called = true;};
		//the size of the sptr will be unaffected as the capture data will be stored in a referenced control block
		auto deleterFunction2 = [&deleter2Called, bloat](int*) {deleter2Called = true;};

		//this is the syntax for adding a deleter to a unique ptr, notice the type contains the deleter and the function is passed as an argument
		std::unique_ptr<int, decltype(deleterFunction1)> uptr(new int{ 1 }, deleterFunction1);

		//a shared ptr type does not contain the deleter, 
		std::shared_ptr<int> sptr(new int{ 1 }, deleterFunction2);

		auto sptr2 = sptr;

		//the capture data bloats the uptr but not the sptr
		assert(sizeof(uptr) > sizeof(sptr));

		//destructors call their respective deleters
		uptr.reset();
		assert(deleter1Called);

		//shared deleter is only called when reference count is zero
		sptr.reset();
		assert(!deleter2Called);
		sptr2.reset();
		assert(deleter2Called);

		//reset deleters
		deleter1Called = false;
		deleter2Called = false;

		//as shared pointers have the same type and size regardless of their deleters, they may be stored in containers and each may reference a unique deleter
		std::vector<std::shared_ptr<int>> sptrs;
		sptrs.push_back(std::shared_ptr<int>{new int(5), deleterFunction1});
		sptrs.push_back(std::shared_ptr<int>{new int(7), deleterFunction2});

		//now both deleters will be called when the vector is cleared
		sptrs.clear();
		assert(deleter1Called);
		assert(deleter2Called);

		auto sptr3 = std::make_shared<int>(2);
		//we can create a weak ptr that references a shared resource
		std::weak_ptr<int> wptr1 = sptr3;
		//it does not affect the count
		assert(sptr3.use_count() == 1);
		//we can convert it to a shared ptr when we choose
		auto sptr4 = wptr1.lock();
		//thus increasing the count
		assert(sptr3.use_count() == 2);
		//if the resource is deleted, we can check via the weak ptr .expired() functions
		assert(!wptr1.expired());
		sptr3.reset();
		sptr4.reset();
		assert(wptr1.expired());
		//if we lock a void pointer it will return a nullptr
		auto sptr5 = wptr1.lock();
		assert(sptr5 == nullptr);
		//alternatively we can throw a bad_weak_ptr error by using the shared pointer constructor
		//std::shared_ptr<int> sptr6(wptr1);

		//the weak count based on the number of weak pointer references controls the lifetime of the contriol block
		//this way we can pass references to shared resources and check their validity without undefined behaviour
		//as such weak pointers cannot be dereferenced directly
		//*wptr1






	}
};