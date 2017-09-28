#include <fstream>
#include <iomanip>
#include "utils.h"

// Clears the screen
void clearScreen() {
	COORD upperLeftCorner = { 0,0 };
	DWORD charsWritten;
	DWORD conSize;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO  csbi;

	GetConsoleScreenBufferInfo(hCon, &csbi);
	conSize = csbi.dwSize.X * csbi.dwSize.Y;

	// fill with spaces
	FillConsoleOutputCharacter(hCon, TEXT(' '), conSize, upperLeftCorner, &charsWritten);
	GetConsoleScreenBufferInfo(hCon, &csbi);
	FillConsoleOutputAttribute(hCon, csbi.wAttributes, conSize, upperLeftCorner, &charsWritten);

	// cursor to upper left corner
	SetConsoleCursorPosition(hCon, upperLeftCorner);
}

// Repeatedly asks the user for input until a valid integer in range [min, max] is given
unsigned short int getUnsignedShortInt(unsigned short int min, unsigned short int max, string msg, size_t msg_width)
{
	string dummy; unsigned short int input;
	bool fail = false; // fail flag

	while (true)
	{
		setcolor(14);  cout << TAB << setw(msg_width) << msg; setcolor(15); cin >> input;

		if (cin.fail())
		{
			fail = true;
			cin.clear();
		}

		getline(cin, dummy); trim(dummy);
		if (dummy.empty())
		{
			if (input >= min && input <= max)
				return input;
			else
			{
				setcolor(12); cout << "Input must be an integer between " << min << " and " << max << ".\a\n\n"; setcolor(15);
			}

		}
		else fail = true;

		if (fail)
		{
			setcolor(12); cout << "Invalid input.\a\n\n"; setcolor(15);
		}


	}

}

Date getDate(string msg) {
	unsigned short int day, month, year;
	size_t width = 7;	//width para formatar a mensagem

	cout << msg << endl;
	year = getValue<unsigned short int>("Year: ", width);
	month = getUnsignedShortInt(1, 12, "Month: ", width);

	if (month == 2)
		day = getUnsignedShortInt(1, 29, "Day: ", width);
	else
		day = getUnsignedShortInt(1, 31, "Day: ", width);

	return Date(day, month, year);
}

bool validFile(const string file) {
	ifstream input;
	input.open(file);
	return input.is_open();
}

// Converts character to uppercase
char toUpper(char c) {
	if ('A' <= c && c <= 'Z')
		return c;
	else if ('a' <= c && c <= 'z')
		return c + 'A' - 'a';
	return c;
}

// Converts string to uppercase
string toUpper(string s) {
	for (char c : s)
		c = toUpper(c);

	return s;
}

//trims desired char (whitespace by default) in the begin and end of the string, aswell as setting any in between words sequence of the char to 1 char only
void trim(string &s) {
	char c = ' ';

	while (s.find('\t') != string::npos)
		s.erase(s.find('\t'), 1);


	for (unsigned i = 0; i < s.size(); i++)
	{
		if (s[i] == c && s[i + 1] == c)
		{
			s.erase(s.begin() + i);
			i--;
		}
	}

	s.erase(0, s.find_first_not_of(c));
	s.erase(s.find_last_not_of(c) + 1, string::npos);
}

/*
COLOR CODES:
1   blue
2   green
3   cyan
4   red
5   magenta
6   brown
7   lightgray
8   darkgray
9   lightblue
10  lightgreen
11  lightcyan
12  lightred
13  lightmagenta
14  yellow
15  white
*/
void setcolor(unsigned int color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, color);
}

void showTitle(string title, ostream& out) {
	setcolor(10);
	out << endl
		<< TAB_BIG << string(title.size() + 6, '*') << endl
		<< TAB_BIG << "** " << title << " **" << endl
		<< TAB_BIG << string(title.size() + 6, '*')
		<< endl << endl;
	setcolor(15);
}