#include "stdafx.h"
#include "manager.h"

void add(manager &m, const test &t)
{
	m.tests[m.count_tests++] = t;
}

void del(manager &m, int pos)
{
	for (int i = pos-1; i < m.count_tests; i++)
	{
		swap(m.tests[i], m.tests[i + 1]);
	}

	m.count_tests--;
}

void display(manager &m)
{
	for (int i = 0; i < m.count_tests; i++)
	{
		cout << " " << i + 1 << ". " << m.tests[i].title << "  (" << m.tests[i].count_questions << " questions)" << endl;
	}	
}

void serialize(const manager & c, char file[50])
{
	ofstream f;

	f.open(file, ios::out | ios::binary);

	f.write((char*)&c, sizeof(manager));

	f.close();
}

void deserialize(manager &c, char file[50])
{
	ifstream f;
	f.open(file, ios::in | ios::binary);

	f.read((char*)&c, sizeof(manager));

	f.close();

}