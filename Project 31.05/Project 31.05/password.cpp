#include "password.h"
#include "stdafx.h"

void new_(pass &p, char *login, char *password, char *name, char *surname, bool if_admin)
{
	strcpy_s(p.login, login);
	strcpy_s(p.password, password);
	strcpy_s(p.name, name);
	strcpy_s(p.surname, surname);
	p.if_admin = if_admin;
}

char *PassInput(char pass[])
{
	int ch = 0;
	string Pass;

	while (true)
	{
		ch = _getch();

		if (ch == 13)
		{
			break;
		}
		else if (ch == 8)
		{
			if (!Pass.empty())
			{
				cout << (char)8 << ' ' << (char)8;

				Pass.erase(Pass.length() - 1);
			}
		}
		else
		{
			cout << '*';
			Pass = Pass + (char)ch;
		}
	}

	for (int i = 0; i != Pass.length(); i++)
	{
		pass[i] = Pass[i];
	}

	pass[Pass.length()] = '\0';

	return pass;
}

void add(pass &p, result &r)
{
	p.results[p.count_results++] = r;
}

void del(pass &p, int pos)
{
	for (int i = pos - 1; i < p.count_results; i++)
	{
		swap(p.results[i], p.results[i + 1]);
	}

	p.count_results--;
}

void display_results(pass &p, HANDLE hConsole)
{
	for (int i = 0; i < p.count_results; i++)
	{
		cout << " " << i + 1 << ". ";
		display(p.results[i], hConsole);
	}
}

void display_students(pass & p)
{
	cout << p.name << " " << p.surname;
}

void display(pass & p)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 14));
	cout << "\t\t\t Student: " << p.name << " " << p.surname << endl;
	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));

	cout << " Login: " << p.login << endl;
	cout << " Password: " << p.password << endl;
	cout << " Admin: ";
	if (p.if_admin == true)
	{
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
		cout << boolalpha << p.if_admin << endl;
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
	}

	else
	{
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 12));
		cout << boolalpha << p.if_admin << endl;
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
	}
	cout << " Results count: " << p.count_results << "\n\n";

	for (int j = 0; j < p.count_results; j++)
	{
		cout << " " << j + 1 << ". ";
		display(p.results[j], hConsole);
	}
	cout << endl;

	cout << " Messages count: " << p.count_messages << "\n\n";

	for (int  i = 0; i < p.count_messages; i++)
	{
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
		cout << "\t\t\t\t Message #" << i + 1 << endl;
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
		
		display(p.messages[i]);

		cout << endl;
	}
}

void add(pass &p, message &m)
{
	p.messages[p.count_messages++] = m;
}

void del_message(pass &p, int pos)
{
	for (int i = pos - 1; i < p.count_messages; i++)
	{
		swap(p.messages[i], p.messages[i + 1]);
	}

	p.count_messages--;
}