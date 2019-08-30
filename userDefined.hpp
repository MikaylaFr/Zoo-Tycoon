//Header file for userDefined class

#ifndef USERDEFINED_HPP
#define USERDEFINED_HPP
#include "animal.hpp"

class UserDefined : public Animal
{
	public:
		UserDefined();
		UserDefined& operator=(const UserDefined &RHS);
};
#endif
