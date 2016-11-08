#ifndef CHARRANGE_H
#define CHARRANGE_H


class CharRange
{
	private:
		char input; // User input
		char lower; // Lowest valid character
		char upper; // Highest valid character

	public:
		CharRange(char, char);
		char getChar();
};
#endif
