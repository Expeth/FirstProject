#pragma once
#include "answ.h"

struct question
{
	char title[20];
	char category[20];
	char info[100];
	answer answers[5];
	int count_answers = 0;
};

void new_(question &q, char *title, char *category, char *info);

void display(question &q);

void display2(question &q);

void add(question &q, const answer &a);

void del(question &q, int pos);
