/*********************************************************************
 * ** Program name: Project2
 * ** Author: Mikayla Friend
 * ** Date: 2-3-19
 * ** Description: Header file for animal class
 * *********************************************************************/

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

const double BASE_FOOD_COST = 10.00;

class Animal
{
	protected:
		int age;
		double cost;
		int numOfBabies;
		double foodCost;
		double payoff;
	public:
		int getAge();
		void setAge(int a);
		double getCost();
		void setCost(double c);
		int getNumOfBabies();
		void setNumOfBabies(int num);
		double getFoodCost();
		void setFoodCost(double c);
		double getPayoff();
		void setPayoff(double pay);
};
#endif
