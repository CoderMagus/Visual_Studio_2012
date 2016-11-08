//#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
using std::string;

class Character
{

private:
	string name,
		   attributes,
		   chSelection;

public:
	void setName(string);
	void setAttributes(string);
	string charactSelection();
	string getName();
	string getAttributes();
};

#endif
