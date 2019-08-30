/*********************************************************************
 * ** Program name: Project 2
 * ** Author: Mikayla Friend
 * ** Date: 2-3-19
 * ** Description: Function implementation file for Penguin class which is a child of the Animal class
 * *********************************************************************/

#include "animal.hpp"
#include "penguin.hpp"

//default contructor
Penguin::Penguin()
{
	age = -1;
	cost = 1000.00;
	numOfBabies = 5;
	foodCost = BASE_FOOD_COST;
	payoff = cost * 0.1;
}

//overloaded assignment operator
Penguin& Penguin::operator=(const Penguin &RHS)
{
	this->age = RHS.age;
	return *this;
}

