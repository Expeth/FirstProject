#include "stdafx.h"
#include "qst.h"

void display(question &q) {

	int size = q.count_answers;

	int random;
	for (int i = 0; i < size * 2; i++)
	{
		random = std::rand() % (size + 1);

		for (int j = random; j < size - 1; j++)
		{
			swap(q.answers[j], q.answers[j+1]);
		}
	}
	
	cout << " " << q.info << endl;
	for (int i = 0; i < size; i++)
	{
		cout << " " << i+1 << ". " << q.answers[i].name << endl;
	}
}

void display2(question &q) {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int size = q.count_answers;

	int random;
	for (int i = 0; i < size * 2; i++)
	{
		random = std::rand() % (size + 1);

		for (int j = random; j < size - 1; j++)
		{
			swap(q.answers[j], q.answers[j + 1]);
		}
	}

	cout << " " << q.info << endl;
	for (int i = 0; i < size; i++)
	{
		cout << " " << i + 1 << ". " << q.answers[i].name << "   ";

		if (q.answers[i].iftrue == true)
		{
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
			cout << boolalpha << q.answers[i].iftrue << endl;
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
		}

		else
		{
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 12));
			cout << boolalpha << q.answers[i].iftrue << endl;
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
		}		
	}
}

void new_(question &q, char *title, char *category, char *info)
{
	strcpy_s(q.title, title);
	strcpy_s(q.category, category);
	strcpy_s(q.info, info);
}

void add(question &q, const answer &a)
{
	q.answers[q.count_answers++] = a;
}

void del(question &q, int pos)
{
	for (int i = pos - 1; i < q.count_answers; i++)
	{
		q.answers[i] = q.answers[i + 1];
	}

	q.count_answers--;
}
