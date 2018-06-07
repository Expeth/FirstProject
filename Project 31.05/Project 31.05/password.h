#pragma once
#include "result.h"
#include "message.h"

struct pass
{
	char name[20];
	char surname[20];
	char login[100];
	char password[100];
	result results[20];
	int count_results = 0;
	bool if_admin = false;
	message messages[10];
	int count_messages = 0;
};

void new_(pass &p, char *login, char *password, char *name, char *surname, bool if_admin);

char *PassInput(char pass[]);

void add(pass &p, result &r);

void del(pass &p, int pos);

void display_results(pass &p, HANDLE hConsole);

void display_students(pass &p);

void display(pass &p);

void add(pass &p, message &m);

void del_message(pass &p, int pos);
