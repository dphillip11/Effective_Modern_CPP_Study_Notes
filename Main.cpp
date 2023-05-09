// standard library includes, pre-compiled-header
#include "pch.h"
// log statements
#include "Utils.h"
#define Log(x) Utils::Log(x)
// exercise base class
#include "Exercise.h"
// exercises
#include "Templates.h"
#include "Const.h"
#include "Vectors.h"
#include "Lambdas.h"
#include "Auto.h"
#include "BracedInitializers.h"
#include "Aliases.h"
#include "Inheritance.h"
#include "Overloads.h"
#include "Mutexes.h"
#include "Smart_pointers.h"
#include "Constructors.h"
#include "UniversalReferences.h"

int main()
{
	//instantiates exercises, the exercise constructor adds them to the static Exercise::exercises vector
	Templates t;
	Const c;
	Vectors v;
	Lambdas l;
	Auto a;
	BracedInitializers b;
	Aliases a2;
	Inheritance i;
	Overloads o;
	Mutexes M;
	Smart_pointers sp;
	Constructors co;
	UniversalRefVsRvalueRef UR;

	//calls static function
	Exercise::RunExercises();

}