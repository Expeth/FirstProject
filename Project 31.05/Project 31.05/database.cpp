#include "stdafx.h"
#include "database.h"

void add(database &d, const pass &p)
{
	d.passwords[d.count_passwords++] = p;
}

void del(database &d, pass &p)
{
	int pos;

	for (int i = 0; i < d.count_passwords; i++)
	{
		if (strcmp(d.passwords[i].login, p.login) == 0 && strcmp(d.passwords[i].password, p.password) == 0)
		{
			pos = i;
		}
	}

	for (int i = pos; i < d.count_passwords; i++)
	{
		swap(d.passwords[i], d.passwords[i + 1]);
	}

	d.count_passwords--;
}

void del(database & d, int pos)
{
	for (int i = pos - 1; i < d.count_passwords; i++)
	{
		swap(d.passwords[i], d.passwords[i + 1]);
	}

	d.count_passwords--;
}

void del(database & d, char * name)
{

}

bool search(database &d, pass &p)
{
	bool confirm = false;

	for (int i = 0; i < d.count_passwords; i++)
	{
		if (strcmp(d.passwords[i].login, p.login) == 0 && strcmp(d.passwords[i].password, p.password) == 0)
		{
			confirm = true;
			p = d.passwords[i];
			break;
		}
	}

	return confirm;
}

bool if_admin(database &d, pass &p)
{
	bool confirm = false;

	for (int i = 0; i < d.count_passwords; i++)
	{
		if (strcmp(d.passwords[i].login, p.login) == 0 && strcmp(d.passwords[i].password, p.password) == 0)
		{
			if (d.passwords[i].if_admin == true)
			{
				confirm = true;
			}
		}
	}

	return confirm;
}

void search_student_by_name(database & d, char * name)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char y = 'n';

	for (int i = 0; i < d.count_passwords; i++)
	{
		if (strcmp(d.passwords[i].name, name) == 0 || strcmp(d.passwords[i].surname, name) == 0)
		{
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 14));		
			cout << "\n ";
			display_students(d.passwords[i]);
			cout << "\n";
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));

			y = 'y';

			for (int j = 0; j < d.passwords[i].count_results; j++)
			{
				cout << " " << j + 1 << ". ";
				display(d.passwords[i].results[j], hConsole);
			}

			break;
		}
	}

	if (y == 'n')
	{
		cout << " No matches!\n";
	}
}

void display(database & d)
{
	for (int i = 0; i < d.count_passwords; i++)
	{
		display(d.passwords[i]);
	}
}

void save(database & d, pass & p)
{
	for (int i = 0; i < d.count_passwords; i++)
	{
		if (strcmp(d.passwords[i].login, p.login) == 0 && strcmp(d.passwords[i].password, p.password) == 0)
		{
			p = d.passwords[i];
			break;
		}
	}
}

void save_results_to_file(database & d, char * path)
{
	ofstream f;
	f.open(path, ios::ate);

	int count = 1;
	for (int i = 0; i < d.count_passwords; i++)
	{
		for (int j = 0; j < d.passwords[i].count_results; j++)
		{
			f << count++ << ". " << d.passwords[i].name << " " << d.passwords[i].surname << ". " << d.passwords[i].results[j].name_of_test;
			f << " - " << d.passwords[i].results[j].grade << "/100. Date: " << d.passwords[i].results[j].date << endl;
		}
	}

	f.close();
}

void serialize(const database & c, char file[50])
{
	ofstream f;

	f.open(file, ios::out | ios::binary);

	f.write((char*)&c, sizeof(database));

	f.close();
}

void deserialize(database &c, char file[50])
{
	ifstream f;

	f.open(file, ios::in | ios::binary);

	f.read((char*)&c, sizeof(database));

	f.close();
}