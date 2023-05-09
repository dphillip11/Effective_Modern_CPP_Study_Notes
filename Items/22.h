// Item 22: When using the Pimpl Idiom, define special member functions in the implementation file.
//pimpl(pointer to implementation) idiom can reduce compile time by reducing the need to compile dependencies in the header file.

namespace Item21 {

	//in header .h file
	class PIMPL_class {
	public:
		PIMPL_class();
		//forward declaration of dtor as will not accept incomplete type for unique_ptr
		~PIMPL_class();
		//forward declaration of move operations
		PIMPL_class(PIMPL_class&& rhs);
		PIMPL_class& operator=(PIMPL_class&& rhs);
		//forward declarations of copy operations
		PIMPL_class(const PIMPL_class& rhs);
		PIMPL_class& operator=(const PIMPL_class& rhs);

	private:
		//forward declaration of implementation struct containing elements that may requre additional headers <vector> <map> etc
		struct impl;
		//using a shared_ptr alleviates the need to redefine default operations
		std::unique_ptr<impl> _impl;
	};

	//in .cpp implementation file
	//include headers

	struct PIMPL_class::impl {
		//data members that reuqire additional headers
		std::map<std::string, std::vector<int>> map;
	};

	//assign ownership of impl class
	PIMPL_class::PIMPL_class() :_impl(std::make_unique<impl>()) {}

	//now impl struct is complete we can assign the default dtor
	PIMPL_class::~PIMPL_class() = default;

	//we probably wish to do the same for move
	PIMPL_class::PIMPL_class(PIMPL_class&& rhs) = default;
	PIMPL_class& PIMPL_class::operator=(PIMPL_class&& rhs) = default;

	//and ensure deep copying
	PIMPL_class::PIMPL_class(const PIMPL_class& rhs) // copy ctor
		: _impl(std::make_unique<impl>(*rhs._impl)) {}

	PIMPL_class& PIMPL_class::operator=(const PIMPL_class& rhs) // copy operator=
	{
		*_impl = *rhs._impl;
		return *this;
	}

}