#include "stdafx.h"
#include "answ.h"

void new_(answer &a, char *name, bool iftrue)
{
	strcpy_s(a.name, name);
	a.iftrue = iftrue;
}

void display(const answer &a)
{
	cout << a.name << endl;
}