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

int main()
{
	//instantiates exercises, the exercise constructor adds them to the static Exercise::exercises vector
	//this is similar to the observer pattern but with automatic subscription
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

	//calls static function
	Exercise::RunExercises();

}