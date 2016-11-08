#include <iostream> // for console output
#include <iomanip> // to format output
#include <string> // for creating a string variable
#include <cstdlib> // for srand random function
#include <ctime> // to call the time() function for random
#include <fstream> // File input/output header
#include <sstream> // String stream
#include <Windows.h> // Needed to display colors and call Sleep
#include <cctype> // For toupper


// Function prototypes
void displayWelcome(std::string);
void displayMenu();
int getSelection();
void displayQuestions();
int getQuestions();
int specifyQuestions();
int randomQuestions();
void addition(int, int);
void subtraction(int, int);
void multiplication(int, int);
void division(int, int);
int getAnswer();
//void saveFile(ofstream &outFile);
void clearScreen();



int main()
{

	// Create a handle to the computer screen
	HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);

	// Using declerations for cout, cin, and endl
	using std::cout;
	using std::cin;
	using std::endl;
	std::string name,
				setColor,
				saveResults;
	std::stringstream output;
	int num1, 
		num2, 
		answer,
		count = 1,
		numberOfQuestions = 0,
		selection = 0,
		selectColor = 0;

	// Define file stream object
	std::ofstream outFile;
	// Open the file
	outFile.open("D:\\test.txt");
	


	cout << "Enter your name: ";
		getline(std::cin, name); // Reads entire line of input\

	cout << '\n' << name << ",\nWould you like to set the color, y or n (Default is White)? ";
	cin >> setColor;

	if (setColor == "Y" || setColor == "y") {
		cout << "1. Blue" << endl;
		cout << "2. Green" << endl;
		cout << "3. Aqua" << endl;
		cout << "4. Red" << endl;
		cout << "5. Purple" << endl;
		cout << "6. Yellow" << endl;
		cout << "7. Bright White" << endl;
		cin >> selectColor;
	}
	else if (setColor == "N" || setColor == "n")
		SetConsoleTextAttribute (screen, 7);

	switch (selectColor) {
		case 1: SetConsoleTextAttribute (screen, 1);
			break;
		case 2: SetConsoleTextAttribute (screen, 2);
			break;
		case 3: SetConsoleTextAttribute (screen, 3);
			break;
		case 4: SetConsoleTextAttribute (screen, 4);
			break;
		case 5: SetConsoleTextAttribute (screen, 5);
			break;
		case 6: SetConsoleTextAttribute (screen, 6);
			break;
		case 7: SetConsoleTextAttribute (screen, 15);
	}

	displayWelcome(name);
	
	// Initialize random seed
	srand( time(0) );


	do {
		if (count > 1)
			clearScreen();

		displayMenu();
		selection = getSelection();
		if (selection == 5)
			break;

		displayQuestions();
		numberOfQuestions = getQuestions();
		switch (numberOfQuestions) {
			case 1: numberOfQuestions = 5;
				break;
			case 2: numberOfQuestions = 10;
				break;
			case 3: numberOfQuestions = 15;
				break;
			case 4: numberOfQuestions = 20;
				break;
			case 5: numberOfQuestions = specifyQuestions();
				break;
			case 6: numberOfQuestions = randomQuestions();
				break;
			case 7: std::cout << "Not ready" << std::endl;
				break;
		}

		for (int count = 1; count <= numberOfQuestions; count++) {
			num1 = rand() % 50 + 1;
			num2 = rand() % 50 + 1;

			// call swap function if num2 is bigger
			if (num1 < num2)
				std::swap(num1, num2);

			// Depending on selection, do that Math problem
			switch (selection) {
				case 1: addition(num1, num2);
					break;
				case 2: subtraction(num1, num2);
					break;
				case 3: multiplication(num1, num2);
					break;
				case 4: division(num1, num2);
					break;
			}
		
		} // For loop for number of questions

		if (selection != 5) 
			cout << '\n' << name << " you have " << " Correct.\n" << endl;


		// Ask user to save to file or no
		cout << "/nSave results, y or n?" << endl;
		cin >> saveResults;
		// Write score to file if user decides
		if (saveResults == "yes" || saveResults == "Yes" || saveResults == "y" || saveResults == "Y")
			outFile << output;

			// Prepare all questions if correct or wrong, for output
			/*output << num1 << " + " << num2 << " = " << answer 
					 << ((num1 + num2 == answer) ? " Correct" : " Wrong") << endl;*/
		
		count++;
	} while (selection != 5);

		// Close the file
		outFile.close();

	/*if (selection != 5) {
		cout << '\n' << name << " you have " << " Correct.\n" << endl;*/

	if (selection == 5)
		cout << "\nThank you for taking the Math Quiz!\nGoodbye " << name << endl;

	// Set screen color back to default
	SetConsoleTextAttribute (screen, 7);

	return 0;
}

void displayWelcome(std::string name)
{
	// Clear the screen
	clearScreen();
	std::cout << "\nProgram by: Capet\tVersion 1.0" << std::endl;
	std::cout << "++++++++++++++++++++++++++++++++++++" << std::endl; //Sleep(500);
	std::cout << "|                                  |" << std::endl; //Sleep(500);
	std::cout << "|            " << name << "               |" << std::endl; //Sleep(500);
	std::cout << "|    WELCOME TO THE MATH QUIZ!     |" << std::endl; //Sleep(500);
	std::cout << "++++++++++++++++++++++++++++++++++++" << std::endl; //Sleep(500);
}

void displayMenu()
{
	std::cout << "\nMake your Math Quiz selection: " << std::endl;
	std::cout << "[1] (+) Addition" << std::endl;
	std::cout << "[2] (-) Subtraction" << std::endl;
	std::cout << "[3] (*) Multiplication" << std::endl;
	std::cout << "[4] (/) Division" << std::endl;
	std::cout << "[5] Quit the Math Quiz" << std::endl;
}

int getSelection()
{
	int selection = 0;

	std::cin >> selection;

	while ((selection < 1) || (selection > 5)) {
		std::cout << "!!ERROR!!" << std::endl;
		displayMenu();
		std::cin >> selection;
	}

	return selection;
}

void displayQuestions()
{
	std::cout << "Select how many questions you want on the Math Quiz" << std::endl;
	std::cout << "[1] 5" << std::endl;
	std::cout << "[2] 10" << std::endl;
	std::cout << "[3] 15" << std::endl;
	std::cout << "[4] 20" << std::endl;
	std::cout << "[5] Specify how many you want (Min = 1, Max = 20)" << std::endl;
	std::cout << "[6] Randomly generate number of questions" << std::endl;
	std::cout << "[7] Go back to the Math Quiz selection window" << std::endl;
}

int getQuestions()
{
	int questions = 0;
	std::cin >> questions;

	while ((questions < 1) || (questions > 7)) {
		std::cout << "!!ERROR!!" << std::endl;
		displayQuestions();
		std::cin >> questions;
	}

	return questions;
}

int specifyQuestions()
{
	int questions = 0;

	std::cout << "How many would you like?  ";
	std::cin >> questions;

	while (questions < 1 || questions > 20) {
		std::cout << "That is not in the range.  Select from 1-20 questions." << std::endl;
		std::cout << "How many would you like?  ";
		std::cin >> questions;
	}

	return questions;
}

int randomQuestions()
{
	int questions = rand() % 20 + 1;
	
	return questions;
}

void addition(int num1, int num2)
{
	int answer = 0;

	// Output the problem
	std::cout << '\n' << std::setw(4) << num1 << std::endl; 
	std::cout << "+" << std::setw(3) << num2 << std::endl;
	std::cout << "-----" << std::endl;
	getAnswer();
}

void subtraction(int num1, int num2)
{
	// Output the problem
	std::cout << '\n' << std::setw(4) << num1 << std::endl; 
	std::cout << "-" << std::setw(3) << num2 << std::endl;
	std::cout << "-----" << std::endl;
	getAnswer();
}

void multiplication(int num1, int num2)
{
	// Output the problem
	std::cout << '\n' << std::setw(4) << num1 << std::endl; 
	std::cout << "*" << std::setw(3) << num2 << std::endl;
	std::cout << "-----" << std::endl;
	getAnswer();
}

void division(int divisor, int dividend)
{
	int multiplier;

	divisor = rand() % 30 + 1;
	multiplier = rand() % 20 + 1;
	dividend = divisor * multiplier;

	// Output the problem
	std::cout << '\n' << "  _____" << std::endl;
	std::cout << std::setw(2) << divisor << ")" << dividend << std::endl;
	getAnswer();
}

int getAnswer()
{
	int answer;
	std::cin >> answer;

	// Some exception handling
	return answer;
}

/*void saveFile(ofstream &outFile)
{
	
}*/

void clearScreen()
{

  HANDLE                     hStdOut;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD                      count;
  DWORD                      cellCount;
  COORD                      homeCoords = { 0, 0 };

  hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
  if (hStdOut == INVALID_HANDLE_VALUE) return;

  /* Get the number of cells in the current buffer */
  if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
  cellCount = csbi.dwSize.X *csbi.dwSize.Y;

  /* Fill the entire buffer with spaces */
  if (!FillConsoleOutputCharacter(
    hStdOut,
    (TCHAR) ' ',
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Fill the entire buffer with the current colors and attributes */
  if (!FillConsoleOutputAttribute(
    hStdOut,
    csbi.wAttributes,
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Move the cursor home */
  SetConsoleCursorPosition( hStdOut, homeCoords );
  }