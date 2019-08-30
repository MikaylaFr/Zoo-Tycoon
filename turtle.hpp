//Header file for Turtle class

#include "animal.hpp"
#ifndef TURTLE_HPP
#define TURTLE_HPP

class Turtle : public Animal
{
	public:
		Turtle();
		Turtle& operator=(const Turtle &RHS);
};
#endif

