/*********************************************************************
 * ** Program name: Project 2
 * ** Author: Mikayla Friend
 * ** Date: 1-3-19
 * ** Description: Function implementation file for Tiger class which is a child of Animal class.
 * *********************************************************************/

#include "tiger.hpp"
//default constructor
Tiger::Tiger()
{
	age = -1;
	cost = 10000.00;
	numOfBabies = 1;
	foodCost = BASE_FOOD_COST * 5.0;
	payoff = cost * 0.2;
}

//overloaded assignment operator
Tiger& Tiger::operator=(const Tiger &RHS)
{
	this->age = RHS.age;
	return *this;
}
