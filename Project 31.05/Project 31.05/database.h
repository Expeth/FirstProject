#pragma once
#include "password.h"

struct database
{
	pass passwords[10];
	int count_passwords = 0;
};

void add(database &d, const pass &p);

void del(database &d, pass &p);

void del(database &d, int pos);

void del(database &d, char *name);

bool search(database &d, pass &p);

void serialize(const database & c, char file[50]);

void deserialize(database &c, char file[50]);

bool if_admin(database &d, pass &p);

void search_student_by_name(database &d, char *name);

void display(database &d);

void save(database &d, pass &p);

void save_results_to_file(database &d, char *path);