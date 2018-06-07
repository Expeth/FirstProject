// Project 31.05.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "lib.h"

int main()
{
	// set code page 1251
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	// handle of console for use color text
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	srand(time(0));

	// user's pass and login
	pass pass_;

	// database with all passes and logins
	database db;
	deserialize(db, "passwords.data");

	// manager of tests
	manager m;
	deserialize(m, "info.dat");

	// Log screen.
	do
	{
		system("cls");

		cout << "\t\t\t  ==========Welcome==========\n\n";
		cout << "\t\t\t=====Please login to system=====\n\n\n\n";

		cout << " Login: ";
		cin.getline(pass_.login, 100);

		cout << " Password: ";
		PassInput(pass_.password);

		// if pass incorrect
		if (search(db, pass_) == false)
		{
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 12));
			cout << "\n\n\n Password or login is incorrect!";
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));

			// pause
			cout << "\n Press any key to continue";
			_getch();
		}

	} while (search(db, pass_) == false);

	// user
	if (if_admin(db, pass_) == false)
	{
		main_screen_user(hConsole, m, pass_, db);
	}

	// admin
	else
	{
		main_screen_admin(hConsole, m, pass_, db);
	}

	cout << "\n\n\n";
	//system("pause");
    return 0;
}

