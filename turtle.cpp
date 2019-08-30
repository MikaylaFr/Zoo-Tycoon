/*********************************************************************
 * ** Program name: Project 2
 * ** Author: Mikayla Friend
 * ** Date: 2-3-19
 * ** Description: Function implementation file for Turtle class which is a child of Animal class.
 * *********************************************************************/

#include "animal.hpp"
#include "turtle.hpp"
//default constructor
Turtle::Turtle()
{
	age = -1;
	cost = 100.00;
	numOfBabies = 10;
	foodCost = BASE_FOOD_COST * 0.5;
	payoff = cost * 0.05;
}

//overloaded assignment operator
Turtle& Turtle::operator=(const Turtle &RHS)
{
	this->age = RHS.age;
	return *this;
}
