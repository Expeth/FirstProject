#include "stdafx.h"
#include "message.h"

void new_(message &m, char *title, char *text, char *date, char *sender, char *time)
{
	strcpy_s(m.title, title);
	strcpy_s(m.text, text);
	strcpy_s(m.date, date);
	strcpy_s(m.sender, sender);
	strcpy_s(m.time, time);
}

void display(message &m)
{
	cout << " Message from " << m.sender << ". Date: " << m.date << " | " << m.time << endl;
	cout << " " << m.title << endl;
	cout << " " << m.text << "\n\n";
}