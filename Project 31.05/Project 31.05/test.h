#pragma once
#include "qst.h"
#include "password.h"

struct test
{
	char title[50];
	char category[30];
	int count_questions = 0;
	question questions[20];
};

void new_(test &t, char *title, char *category);

void add(test &t, const question &q);

void del(test &t, int pos);

void display(test &t);

void start_test(test &t, pass &pass_);