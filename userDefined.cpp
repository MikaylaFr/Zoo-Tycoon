/*********************************************************************
 * ** Program name: Project 2
 * ** Author: Mikayla Friend
 * ** Date: 2-3-19
 * ** Description: Function for UserDefined class which is a child of Animal class. User will define animal type for the object.
 * *********************************************************************/

#include "userDefined.hpp"
#include "animal.hpp"
//default constructor
UserDefined::UserDefined()
{
	age = -1;
}

//overloaded assignment operator
UserDefined& UserDefined::operator=(const UserDefined &RHS)
{
	this->age = RHS.age;
	this->cost = RHS.cost;
	this->numOfBabies = RHS.numOfBabies;
	this->foodCost = RHS.foodCost;
	this->payoff = RHS.payoff;
	return *this;
}
