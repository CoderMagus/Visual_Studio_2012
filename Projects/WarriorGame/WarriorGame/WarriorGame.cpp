#include "Character.h"
#include <iostream>
#include <string>

// Function prototypes
void displayMenu();
int chSelection();


int main()
{
	// Class objects
	Character fighter;

	using std::cout;
	using std::endl;
	using std::cin;
	using std::string;

	int ch;

	cout << "Welcome to WARRIOR!\tThe game of LIFE or DEATH" << endl;
	displayMenu();
	ch = chSelection();

	switch (ch)
	{
		case 1:
			cout << "you chose the " << endl;
			fighter.getName();
	default:
		break;
	}

	std::cout << ch << std::endl;

	return 0;
}

void displayMenu()
{
	std::cout << "Choose your character on your journey to hell..." << std::endl;
	std::cout << "\n[1] Warrior" << std::endl;
	std::cout << "[2] Slayer" << std::endl;
}

// Character selection from user
int chSelection()
{
	int ch;

	std::cin >> ch;
	// input validation

	return ch;
}

