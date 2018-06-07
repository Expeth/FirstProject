#pragma once
#include "test.h"

struct manager {

	int count_tests = 0;
	test tests[10];
};

void add(manager &m, const test &t);

void del(manager &m, int pos);

void display(manager &m);

void serialize(const manager & c, char file[50]);

void deserialize(manager &c, char file[50]);