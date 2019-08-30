//Header file for penguin class


#ifndef PENGUIN_HPP
#define PENGUIN_HPP
#include "animal.hpp"

class Penguin : public Animal
{
	public:
		Penguin();
		Penguin& operator=(const Penguin &RHS);
};
#endif
