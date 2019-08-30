//Header file for Tiger class


#ifndef TIGER_HPP
#define TIGER_HPP
#include "animal.hpp"

class Tiger : public Animal
{
	public:
		Tiger();
		Tiger& operator=(const Tiger &RHS);
};
#endif
