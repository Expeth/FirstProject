#pragma once

struct message
{
	char title[20];
	char text[50];
	char date[10];
	char time[20];
	char sender[50];
};

void new_(message &m, char *title, char *text, char *date, char *sender, char *time);

void display(message &m);