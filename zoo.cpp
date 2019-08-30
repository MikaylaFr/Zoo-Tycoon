/*********************************************************************
 * ** Program name: Project 2
 * ** Author: Mikayla Friend
 * ** Date: 2-3-19
 * ** Description: Function impelentation file for zoo class. All game play happens in this class. 
 * *********************************************************************/

#include "zoo.hpp"
#include "tiger.hpp"
#include "menu.hpp"
#include "penguin.hpp"
#include "turtle.hpp"
#include "userDefined.hpp"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include<string>
using std::string;
#include<vector>
using std::vector;

//Deconstructor. Deallocates memory to prevent leaks.
Zoo::~Zoo()
{
	for (int i=0; i<arySize; i++)
	{	delete [] animal[i];}

	delete [] animal;
	
	animal=NULL;
}

//Map of game play, is only function called main. Calls member function in correct order.
int Zoo::playGame()
{
	Menu menu;

	srand((unsigned)time(NULL)); //random generator seed.

	cout << "Welcome: Two extra credit features have been added.\n\n" << endl;
	cout << " ZOO" << endl;
	cout << "TYCOON\n\n" << endl;
		
	day = 1; //Holds how many days have passed.
	int feed;

	beginningPrompt(); //Prompts user for information before game starts.
	buyAnimals(); //Let user buy additional animals before game starts.
	
	loop=true;
	bool game = true;//loop control
	while(game)
	{
		bonus = 0;
		displayStats(); //display variables
		
		for(int i=0; i<arySize; i++) //Increase age by one for all owned animals
		{	for(int j=0; j<animalNumOf[i]; j++)
			{
				animal[i][j].setAge(animal[i][j].getAge() + 1);
			}
		}
		feed = feedCost(); //choose feed type
		randomEvent(feed); //pass feed type to choose random event	
		calcProfit(); //calculate profit
		
		cout << "Account Balance: $" << bank << endl;
		
		if(bank <= 0) //if bank is 0, quits program
		{
			cout << "\n\nGame over! Your zoo has gone bankrupt!" << endl;
			return 0;
		}
		else
		{
			buyAnimals(); //buy animals at end of day
			if(menu.end() == false) //give user option to exit program
				return 0;
		}

		day++;	
	}

	return 0;
}

//calculates the total revenue at the end of the day
void Zoo::calcProfit()
{
	int profit=0; //reset profit
	
	for(int i=0; i<arySize; i++) //adds up all payoffs from all animals
	{	profit = profit + animal[i][0].getPayoff();}
	
	bank = bank + profit + bonus; //adds all revenue for the day to bank

	cout << "\nYou made $" << profit+bonus << " in profits today!\n" << endl;
}

//if a sickness event happens chooses random animal, checks if there any animals of chosen animal and if not nothing happens
void Zoo::sicknessEvent()
{
	
	int randAnimal = (rand() % arySize); //Choose random animal
		
	if(animalNumOf[randAnimal] > 0) //if there are more than 0 of chosen animal
	{	animalNumOf[randAnimal] = animalNumOf[randAnimal] - 1; //Subtract from variable holding amount of animal in zoo
		if(randAnimal == 0) //prints which animal is chosen
			cout << "\nA Tiger";
		else if(randAnimal == 1)
			cout << "\nA Penguin";
		else if(randAnimal == 2)
			cout << "\nA Turtle";
		else if(randAnimal == 3)
			cout << "\nA " << userAnimalName;

		cout << " passed away from disease" << endl;
	}
	else //if no animals of chosen animals, nothing happens
		nothingEvent();
}

//if a boom event is chosen, checks if any tigers and adds up bonus, if not nothing happens
bool Zoo::boomEvent()
{
	if(animalNumOf[0] > 0)
	{	int i = 1;
		while(i <= animalNumOf[0]) //add up bonus
		{	bonus = bonus + ((rand()%250) + 251);
			i++;
		}
		cout << "\nThere was a boom in attendance for the Tiger attraction today. You made $" << bonus << " extra today" << endl;
		return true;
	}
	else
		return false;
}

//if baby event is chosen, creates an array that contains animals that have an adult in zoo, if none nothing happens
bool Zoo::babyEvent()
{
	int randBaby;
	vector<int> baby;
	for(int i=0; i<arySize; i++) //adds to vector if adult in zoo
	{
		for(int j=0; j<animalNumOf[i]; j++)
		{
			if(animal[i][j].getAge() > 2 && animalNumOf[i] > 0)
			{
				baby.push_back(i);
				j=animalNumOf[i];//quit loop
			}
		}
	}
	
	
	if(baby.size() == 0) //if no adults, nothing happens
		return false;
	else //if there are adults
	{	int num = rand() % baby.size();
		randBaby = baby[num]; //choose an animal
		
		addAnimal(randBaby + 1, 0, animal[randBaby][0].getNumOfBabies()); //call addAnimal to add baby to array
		cout << "\nA ";
		if(randBaby == 0) //prints which animal is chosen
			cout << "Tiger ";
		else if(randBaby==1)
			cout << "Penguin ";
		else if(randBaby==2)
			cout << "Turtle ";
		else if(randBaby==3)
			cout << userAnimalName << " ";

		cout << "had " << animal[randBaby][0].getNumOfBabies() << " babies today." << endl;
		return true;
	}
	return true;
}

//if nothing happens
void Zoo::nothingEvent()
{
	cout << "Just a regular day at the zoo" << endl;
}

//chooses random event. Creates event based on what food type is chosen. Chooses an event and calls the event function
void Zoo::randomEvent(int food)
{
	vector<int> event;
	switch(food) //creates vector based on food type
	{
		case 1:	event = {1,1,1,1,2,2,3,3,4,4};
			break;
		case 2: event = {1,1,2,2,3,3,4,4};
			break;
		case 3: event = {1,2,2,3,3,4,4};
			break;
	}
	
	int num = (rand() % 4) + 1; //randomly choose event
	
	switch(num) //call chosen event
	{
		case 1: sicknessEvent();
			break;
		case 2: if(boomEvent() == false)
			{	nothingEvent();}
			break;
		case 3: if(babyEvent() == false)
			{	nothingEvent();}
			break;
		case 4: nothingEvent();
			break;
	}
}		


//prompts user for which food type they want to purchase for the day. Returns int based on choice, includes input validation. Subtracts chosen 
//food type from bank.
int Zoo::feedCost()
{
	string input;
	while(loop) //loop for input validation
	{	cout << "\n\nWhat type of feed would you like to buy today?" << endl;
		cout << "(1) Cheap" << endl;
		cout << "(2) Generic" << endl;
		cout << "(3) Premium" << endl;
		getline(cin, input);
		
		if(input[0] == '1' && input.length() == 1) //subtracts food type cost for each animal
		{
			for(int i=0; i<arySize; i++)
			{	
				bank = bank - ((animal[i][0].getFoodCost() * .5) * animalNumOf[i]);
			}
			return 1;
		}
		else if(input[0] == '2' && input.length() == 1)
		{
			for(int i=0; i<arySize; i++)
			{
				bank = bank - (animal[i][0].getFoodCost() * animalNumOf[i]);
			}
			return 2;
		}
		else if(input[0] == '3' && input.length() == 1)
		{
			for(int i=0; i<arySize; i++)
			{
				bank = bank - ((animal[i][0].getFoodCost() * 2) * animalNumOf[i]);
			}
			return 3;
		}
		else
			cout << "Invalid input, please choose one of the menu options\n" << endl;
	}
	return 0;
}


//Displays how much in bank and zoo contents
void Zoo::displayStats()
{
	cout << string(60, '=') << endl;
	cout << "Day " << day << endl;
	cout << "Account Balance: $" << bank << endl;
	cout << "\nYour zoo has: " << endl;
	cout << animalNumOf[0] << " Tigers" << endl;
	cout << animalNumOf[1] << " Penguins" << endl;
	cout << animalNumOf[2] << " Turtles" << endl;
	if(arySize == 4)
		cout << animalNumOf[3] << " " << userAnimalName << "s" << endl;
}

//First prompt for game. Creates new animal if user chooses to do so. Initializes bank variable. Intializes 2D array
bool Zoo::beginningPrompt()
{
	string input = " ";
	Menu menu;
	loop = true;
	cout << "Lets Begin:\n" << endl;
	bank = 100000.00;
	cout << "Account Balance: $" << bank << endl;
	cout << "You will be able to buy Tiger's, Penguin's, Turtles. \nWould you like to create an animal?" << endl;
	while(loop) //determine pointer array size based off answer
	{
		cout << "(1) Yes, create a new animal" << "\n(2) No, continue" << endl;
		getline(cin, input);
		if(input[0] == '1' && input.length() == 1)
		{       loop = false;
			arySize = 4;					
		}
		else if(input[0] == '2' && input.length() == 1)
		{
			loop=false;
			arySize = 3;
		}
		else
			cout << "Invalid input." << endl;
	}
	loop = true;
	
	animal = new Animal*[arySize];//Intialize 2d array with each object
	for(int i=0; i<arySize; i++)
	{
		if(i==0)
		{	animal[i] = new Tiger[10];
			animalArySize[0] = 10;}
		else if(i==1)
		{	animal[i] = new Penguin[10];
			animalArySize[1] = 10;}
		else if(i==2)
		{	animal[i] = new Turtle[10];
			animalArySize[2] = 10;}
		else if(i==3)
		{	animal[i] = new UserDefined[10];
			animalArySize[3] = 10;}
	}
	
	if(arySize == 4) //reprompt user for each trait of user created animal
	{
		string name;
		cout << "What is the name of your new animal?" << endl; //name
		getline(cin, name);
		userAnimalName = menu.validateName(name);
			
		cout << "How much does each " << userAnimalName << " cost?" << endl; //cost
		while(loop)
		{	cout << "$";
			getline(cin, input);
			animal[3][0].setCost(menu.validateDoub(input));

			if(animal[3][0].getCost() > 88900)
				cout << "Please keep cost under $88,900" << endl;
			else
				loop = false;
		}
		loop = true;
		
		cout << "How many babies does a " << userAnimalName << " have at once?" << endl; //num of babies
		while(loop)
		{
			getline(cin, input);
			animal[3][0].setNumOfBabies(menu.validateInt(input));

			if(animal[3][0].getNumOfBabies() > 18)
				cout << "Please keep number of babies under 18" << endl;
			else 
				loop = false;
		}
		loop = true;

		cout << "How much does it cost to feed one " << userAnimalName << " daily?" << endl; //food cost
		while(loop)
		{
			cout << "$";
			getline(cin, input);
			animal[3][0].setFoodCost(menu.validateDoub(input));

			if(animal[3][0].getFoodCost() > 50000)
				cout << "Please keep food cost under 5000" << endl;
			else
				loop = false;
		}
		loop = true;

		cout << "What is the daily profit of owning one " << userAnimalName << "?" << endl; //payoff
		while(loop)
		{
			cout << "$";
			getline(cin, input);
			animal[3][0].setPayoff(menu.validateDoub(input));

			if(animal[3][0].getPayoff() > animal[3][0].getCost())
				cout << "The daily profit can not be more than the cost" << endl;
			else
				loop=false;
		}
	}

	for(int i=0; i<arySize; i++) //buy one animal on behalf of user, sets age of animal
	{
		animal[i][0].setAge(1);
		bank = bank - animal[i][0].getCost();
	}
	
	for(int i=0; i<arySize; i++) //animals age is 1
	{
		animalNumOf[i] = 1;
	}
	
	cout << "\nYour zoo must have at least one of each animal. Your account balance is now $" << bank << endl;
	
	return true;
}


//prompt user if they want to buy an animal and how many of animal
bool Zoo::buyAnimals()
{
	loop = true;
	Menu menu;
	string input;
	while(loop) //input validation loop for buying extra animals
	{
		cout << "Would you like to buy additional animals?" << endl;
		cout << "(1) Yes\n(2) No, continue" << endl;
		getline(cin, input);

		if(input[0] == '1' && input.length() == 1)
			loop = false;
		else if(input[0] == '2' && input.length() == 1)
			return true;
		else
			cout << "Invalid input" << endl;
	}
	
	loop = true;
	while(loop) //add animals loop
	{
		cout << "\n\nAccount Balance: $" << bank << endl;
		cout << "Your zoo currently has: "<< endl;
		cout << animalNumOf[0] << " Tigers" << endl;
		cout << animalNumOf[1] << " Penguins" << endl;
		cout << animalNumOf[2] << " Turtles" << endl;
		if(arySize == 4)
		{	cout << animalNumOf[3] << " " << userAnimalName << "s" << endl;}
		
		cout << "\nChoose an animal to buy\n" << endl;
		
		cout << "(1) Tiger    $" << animal[0][0].getCost() << endl;
		cout << "(2) Penguin    $" << animal[1][0].getCost() << endl;
		cout << "(3) Turtle    $" << animal[2][0].getCost() << endl;
		if(arySize == 4)
		{
			cout << "(4) " << userAnimalName << "    $" << animal[3][0].getCost() << endl;
		}
		cout << "(C) Continue" << endl;
		getline(cin, input);
			
		if((input[0] == 'C' || input[0] == 'c') && input.length() == 1)//exit loop
		{	return true;}
		else if(input.length() != 1)
		{	cout << "Invalid input, please choose one of the menu options." << endl;}
		else if(input[0] == '1' || input[0] == '2' || input[0] == '3' || (input[0] == '4' && arySize == 4))
		{	int choice = menu.validateInt(input);
		
			cout << "How many would you like to buy?" << endl;
			getline(cin, input);
			int many = menu.validateInt(input);
			if((animalNumOf[choice-1] + many) > (animalArySize[choice-1] * 2))
			{	cout << "Your zoo enclosure of that animal can only hold " << animalArySize[choice-1] * 2 << " at the moment." << endl;
				cout << "The enclosure will grow over time" << endl;
			}
			else if((bank - (animal[choice-1][0].getCost() * many) < 0))
				cout << "\nYou dont have enough money" << endl;
			else
				addAnimal(choice, 3, many);				
		}
		else
			cout << "Invalid input, please choose one of the menu options." << endl;
			
	}
	
	return true;
}

//resizes array if array is too small to accomadate all objects, sets age based if they animals are bought or born.
void Zoo::addAnimal(int animType, int newAnim, int howMany)
{
	if((animalNumOf[animType - 1] + howMany) > animalArySize[animType - 1]) //if need to resize array
	{
		int newArySize = animalArySize[animType-1] * 2;//calculate how large array needs to be
	
		if(animType == 1)
		{	temp = new Tiger[newArySize];} //create new array
		else if(animType == 2)
		{	temp = new Penguin[newArySize];}
		else if(animType == 3)
		{	temp = new Turtle[newArySize];}
		else if(animType == 4)
		{	temp = new UserDefined[newArySize];}
		
		
		for(int i=0; i<animalNumOf[animType-1]; i++) //copy old array to new array
		{
			temp[i] = animal[animType - 1][i];
		}
			
		delete [] animal[animType-1]; // delete old array
		
		animal[animType-1] = temp; //swap pointers
		
		temp = NULL;

		animalArySize[animType-1] = newArySize; //change array size variable
	}
	
	for(int i = animalNumOf[animType - 1]; i < (animalNumOf[animType-1] + howMany); i++)
	{	switch(newAnim)
		{	case 1: animal[animType-1][i].setAge(0); //if born
				break;
			case 2: animal[animType-1][i].setAge(3); //if bought
				break;
			case 3: animal[animType-1][i].setAge(1); //if bought at begining
				break;
		}
	}

	animalNumOf[animType-1] = animalNumOf[animType-1] + howMany;
	if(newAnim != 0)
		bank = bank - (animal[animType-1][0].getCost() * howMany);
}



			
		
	




