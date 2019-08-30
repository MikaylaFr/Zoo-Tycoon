//header file for zoo class

#ifndef ZOO_HPP
#define ZOO_HPP
#include "animal.hpp"
#include <string>

class Zoo
{
	private:
		bool loop;
		double bank;
		double bonus;
		int arySize;
		int day;
		Animal **animal;
		Animal *temp;
		std::string userAnimalName;
		int animalArySize[4];
		int animalNumOf[4];
	public:
		~Zoo();
		int playGame();
		bool beginningPrompt();
		void addAnimal(int animType, int newAnim, int howMany);
		void displayStats();
		int feedCost();
		void randomEvent(int food);
		void sicknessEvent();
		bool boomEvent();
		bool babyEvent();
		void nothingEvent();
		bool buyAnimals();
		void calcProfit();
};
#endif


