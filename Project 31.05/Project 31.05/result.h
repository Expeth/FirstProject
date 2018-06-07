#pragma once

struct result
{
	char name_of_test[50];
	char date[20];
	double grade;
};

void new_(result &r, char *name_of_test, char *date, double grade);

void display(result &r, HANDLE hConsole);