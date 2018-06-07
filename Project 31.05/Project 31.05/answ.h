#pragma once

struct answer
{
	char name[100];
	bool iftrue = false;
};

void new_(answer &a, char *name, bool iftrue);

void display(const answer &a);
