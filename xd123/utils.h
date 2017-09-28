#pragma once

#include <iostream>
#include <vector>
#include <windows.h>
#include <string>

#include "defs.h"
#include "Date.h"

using namespace std;

/** \fn
*	Function that clears the console. Uses Windows system functions and variables.
*/
void clearScreen();

/** \fn
*	Function that reads an integer from min to max range.
*	Reads from the console an integer that must be from min to max range, displaying a message before reading it.
*	@param min The minimum unsigned short integer to be read.
*	@param max The maximum unsigned short integer to be read.
*	@param msg Empty string by default. Message displayed before reading the values.
*	@param width 0 by default. Width to leave in the console before displaying the message.
*	@return Returns an unsigned short integer. The one specified by the user if within range; if not, attempts to read again.
*/
unsigned short int getUnsignedShortInt(unsigned short int min, unsigned short int max, string msg = "", size_t width = 0);

/** \fn
*	Function that changes the color of the output buffer. Default color is white (15).
*	Color codes are: 1-blue, 2-green, 3-cyan, 4-red, 5-magenta, 6-brown, 7-lightgray, 8-darkgray, 9-lightblue, 10-lightgreen, 11-lightcyan, 12-lightred, 13-lightmagenta, 14-yellow, 15-white.
*	@param color Unsigned integer representing the number of the color which the output will have.
*/
void setcolor(unsigned int color);

/** \fn
*	Function that reads a generic value (template).
*	@param msg String defaulted to empty that is displayed.
*	@param width Width used to format the message.
*	@return Returns a value.
*/
template <class numT>
numT getValue(string msg, size_t msg_width) {
	string dummy; numT input;
	bool fail = false; // fail flag
	while (true)
	{
		setcolor(14);  cout << TAB << setw(msg_width) << msg; setcolor(15); cin >> input;

		if (cin.fail()) {
			fail = true;
			cin.clear();
		}

		getline(cin, dummy);
		if (dummy.empty())
			return input;
		else fail = true;

		if (fail)
		{
			setcolor(12); cout << "Invalid input.\a\n\n"; setcolor(15);
		}
	}
}


/** \fn
*	Function that tests if a file name is valid.
*	@param file String name of the file.
*	@return Returns a boolean, true if the file name is valid.
*/
bool validFile(const string file);

/** \fn
*	Function that convers a char to upper case. If already in upper case, remains the same.
*	@param c Char to be set to upper case.
*	@return Returns the uppercase char.
*/
char toUpper(char c);

/** \fn
*	Function that trims a string.
*/
void trim(string &value);

/** \fn
*	Function that displays a string as a title.
*	@param title String with the title.
*	@param out By default, its cout. Output stream to send the title.
*/
void showTitle(string title, ostream& out = cout);

/** \fn
*	Function that checks if a date is between 2 other dates.
*	@param msg By default set to empty string. Message to be displayed before reading the date.
*	@return Returns a Date object.
*/
Date getDate(string msg = "");



