#include "stdafx.h"
#include "result.h"

void new_(result &r, char *name_of_test, char *date, double grade)
{
	strcpy_s(r.name_of_test, name_of_test);
	strcpy_s(r.date, date);
	r.grade = grade;
}

void display(result &r, HANDLE hConsole)
{
	cout << r.name_of_test << "  -  ";

	if (r.grade < 50)
	{
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 12));
		cout << r.grade << "/100 (must be retaken)";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));	
	}

	else
	{
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
		cout << r.grade << "/100";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
	}

	cout << ". Date: " << r.date << endl;
}