/*********************************************************************
 * ** Program name: Project 2
 * ** Author: Mikayla Friend
 * ** Date: 2-3-19
 * ** Description: Function implementation file for Animal class. Will serve as parent class for Tiger, Penguin
 * Turtle, and UserDefined. Hold values of an Animal.
 * *********************************************************************/

#include "animal.hpp"

int Animal::getAge()
{
	return age;
}


void Animal::setAge(int a)
{
	age = a;
}


double Animal::getCost()
{
	return cost;
}


void Animal::setCost(double c)
{
	cost = c;
}


int Animal::getNumOfBabies()
{
	return numOfBabies;
}


void Animal::setNumOfBabies(int num)
{
	numOfBabies = num;
}


double Animal::getFoodCost()
{
	return foodCost;
}


void Animal::setFoodCost(double c)
{
	foodCost = c;
}


double Animal::getPayoff()
{
	return payoff;
}


void Animal::setPayoff(double pay)
{
	payoff = pay;
}



