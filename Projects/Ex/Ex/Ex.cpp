#include <iostream>
#include <iomanip>
#include <string>
using namespace std;


int main()
{
	const int NUM_EMPLOYEES = 6;
	int hours[NUM_EMPLOYEES];
	int count;

	cout << "Enter the hours worked by " << NUM_EMPLOYEES << " employees: ";
	for (count = 0; count < NUM_EMPLOYEES; count++)
		cin >> hours[count];

	cout << "The hours you entered are: ";
	for (count = 0; count <	NUM_EMPLOYEES; count++)
		cout << " " << hours[count];

	cout << endl;

	return 0;
}