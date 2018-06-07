#include "stdafx.h"
#include "test.h"

void new_(test & t, char * title, char * category)
{
	strcpy_s(t.title, title);
	strcpy_s(t.category, category);
}

void add(test & t, const question & q)
{
	t.questions[t.count_questions++] = q;
}

void del(test & t, int pos)
{
	for (int i = pos - 1; i < t.count_questions; i++)
	{
		t.questions[i] = t.questions[i + 1];
	}

	t.count_questions--;
}

void display(test & t)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < t.count_questions; i++)
	{
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
		cout << "\t\t\t Question #" << i + 1 << endl;
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
		display2(t.questions[i]);
		cout << endl;
	}

	cout << endl << endl;
}

void start_test(test & t, pass &pass_)
{
	HWND hWnd = GetForegroundWindow();
	EnableWindow(hWnd, false);

	int size = t.count_questions;
	double score = 0;
	short choise;

	short *rand = new short[size];

	for (int i = 0; i < size; i++)
	{
		rand[i] = i;
	}

	int random;

	for (int i = 0; i < size * 2; i++)
	{
		random = std::rand() % (size + 1);

		for (int j = random; j < size - 1; j++)
		{
			swap(rand[j], rand[j + 1]);
		}
	}

	for (int i = 0; i < size; i++)
	{
		system("cls");

		cout << "\n\tTest: " << t.title << endl;
		cout << "\tCategory: " << t.category << endl;
		cout << "\tStudent name: " << pass_.name << " " << pass_.surname << endl;
		cout << "\tQuestion: " << i + 1 << "/" << size << "\n\n";

		display(t.questions[rand[i]]);

		cout << "\n Answer: ";
		cin >> choise;

		if (t.questions[rand[i]].answers[choise-1].iftrue == true)
		{
			score += (float)100 / size;
		}
	}
	delete[] rand;

	SYSTEMTIME st;
	GetSystemTime(&st);

	char date[20];
	sprintf_s(date, "%d.%d.%d", st.wDay, st.wMonth, st.wYear);

	result r;
	new_(r, t.title, date, (double)score);
	add(pass_, r);

	EnableWindow(hWnd, true);
	cout << "\n The test is over. Check your mark at 'Test results'.";
}
