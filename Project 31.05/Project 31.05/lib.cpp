#include "stdafx.h"
#include "lib.h"

void main_screen_user(HANDLE hConsole, manager &m, pass &pass_, database &db)
{
	// to choose something
	int choise;
	int choise2;
	char choise3;

	// to create new pass
	char new_pass[100];
	char new_pass2[100];
	int num;

	// time
	SYSTEMTIME st;

	do {
		// menu
		system("cls");

		save(db, pass_);
		cout << "\t\t\tGlad to see you, " << pass_.name << " " << pass_.surname << "!\n\n";
		cout << "\t\t============================================\n";
		cout << "\t\tKnowledge testing system\n";
		cout << "\t\t============================================\n";
		cout << "           		1. View all avaible tests\n";
		cout << "           		2. Start test\n";
		cout << "           		3. View test results\n";
		cout << "           		4. Send message\n";
		cout << "           		5. My messages"; if (pass_.count_messages > 0){ SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 14)); cout << "   " << pass_.count_messages << " new!"; SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15)); }
		cout << "\n           		6. Delete message\n";
		cout << "           		7. Change password\n";
		cout << "           		8. Exit\n";
		cout << "\t\t============================================\n";
		cout << "\t\t         To go back always enter '0' \n\n";

		cout << " Answer: ";
		cin >> choise;

		// just deserialize functions
		deserialize(db, "passwords.data");
		deserialize(m, "info.dat");
		
		switch (choise)
		{
		case 1:
		{
			if (m.count_tests == 0)
			{
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
				cout << "\n There isn't any available test for you!" << endl;
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));

				cout << "\n\n Press any key to continue";
				_getch();
				break;
			}

			// display a list of tests
			cout << "\n All available tests for you: \n";
			display(m);

			// pause
			cout << "\n Press any key to continue";
			_getch();
		}
		break;

		case 2:
		{
			if (m.count_tests == 0)
			{
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
				cout << "\n There isn't any available test for you!" << endl;
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));

				cout << "\n\n Press any key to continue";
				_getch();
				break;
			}

			// display a list of tests
			cout << "\n Choose the test: \n";
			display(m);
			cout << "\n Answer: ";
			cin >> choise2;

			// to go back
			if (choise2 == 0)
			{
				cout << "\n Press any key to continue";
				_getch();
				break;
			}

			// function to start test
			start_test(m.tests[choise2 - 1], pass_);

			// save results
			del(db, pass_);
			add(db, pass_);
			serialize(db, "passwords.data");

			// pause
			cout << "\n\n Press any key to continue";
			_getch();
		}
		break;

		case 3:
		{
			// display results
			cout << "\n Test results for student " << pass_.name << " " << pass_.surname << ":\n";

			// display func.
			display_results(pass_, hConsole);

			// pause
			cout << "\n Press any key to continue";
			_getch();
		}
		break;

		case 5:
		{
			if (pass_.count_messages == 0)
			{
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
				cout << "\n You don't have any message!" << endl;
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));

				cout << "\n\n Press any key to continue";
				_getch();
				break;
			}

			cout << "\n Your messages: \n";

			// display messages
			for (int i = 0; i < pass_.count_messages; i++)
			{
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
				cout << "\t\t\t\t Message #" << i + 1 << endl;
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));

				// display function
				display(pass_.messages[i]);
				cout << endl;
			}

			cout << "\n\n Press any key to continue";
			_getch();
		}
		break;

		case 4:
		{
			cout << "\n Choose the student to send message: \n";

			// display a list of students
			for (int i = 0; i < db.count_passwords; i++)
			{
				cout << " " << i + 1 << ". ";
				// function to display student
				display_students(db.passwords[i]);
				cout << endl;
			}

			int sm;
			cout << "\n Answer: ";
			cin >> sm;

			// to go back
			if (sm == 0)
			{
				cout << "\n Press any key to continue";
				_getch();
				break;
			}

			message message_;
			cout << "\n Enter a title of your message: ";
			cin.ignore();
			cin.getline(message_.title, 20);

			cout << " Enter a body of your message: ";
			cin.getline(message_.text, 50);

			// get time
			GetSystemTime(&st);

			char date[20];
			char time[20];
			sprintf_s(date, "%d.%d.%d", st.wDay, st.wMonth, st.wYear);
			sprintf_s(time, "%d:%d:%d", st.wHour+3, st.wMinute, st.wSecond);

			strcpy_s(message_.date, date);
			strcpy_s(message_.time, time);
			strcpy_s(message_.sender, pass_.name);
			strcat_s(message_.sender, " ");
			strcat_s(message_.sender, pass_.surname);

			// add message to student
			add(db.passwords[sm - 1], message_);
			serialize(db, "passwords.data");

			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
			cout << "\n\n Your message has been sent to " << db.passwords[sm - 1].name << " " << db.passwords[sm - 1].surname << endl;
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));

			cout << "\n\n Press any key to continue";
			_getch();
		}
		break;

		case 6:
		{
			if (pass_.count_messages == 0)
			{
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
				cout << "\n You don't have any message!" << endl;
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));

				cout << "\n\n Press any key to continue";
				_getch();
				break;
			}

			cout << "\n Choose the message to delete: \n";

			// display messages
			for (int i = 0; i < pass_.count_messages; i++)
			{
				cout << " " << i + 1 << ". " << pass_.messages[i].title << ". From " << pass_.messages[i].sender << " (" << pass_.messages[i].date << ")" << endl;
			}
			cout << "\n Answer: ";
			int mtd;
			cin >> mtd;

			del(db, pass_);
			del_message(pass_, mtd);
			add(db, pass_);
			serialize(db, "passwords.data");

			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
			cout << "\n\n Message has been deleted!" << endl;
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));

			cout << "\n\n Press any key to continue";
			_getch();
		}
		break;

		case 7:
		{
			cin.ignore();
			do
			{
				// change password
				cout << "\n Enter new password: ";
				cin.getline(new_pass, 20);
				
				// re-enter password
				cout << " Re-enter new password: ";
				cin.getline(new_pass2, 20);

				if (strcmp(new_pass, new_pass2) != 0)
				{
					SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 12));
					cout << "\n Your passwords do not match. Please try again." << endl;
					SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
				}

			} while (strcmp(new_pass, new_pass2) != 0);

			cout << "\n Change password? (y/n) - ";
			cin >> choise3;

			if (choise3 != 'y')
			{
				break;
			}

			// save new pass
			del(db, pass_);
			strcpy_s(pass_.password, new_pass);
			add(db, pass_);
			serialize(db, "passwords.data");

			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
			cout << "\n\n Password changed!" << endl;
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));

			// pause
			cout << "\n Press any key to continue";
			_getch();
		}
		break;

		default:
			break;
		}


	} while (choise != 8);
}

void main_screen_admin(HANDLE hConsole, manager &m, pass &pass_, database &db)
{
	// to choose something
	int choise;
	int choise2;
	int choise3;
	int choise4;
	int choise5;

	// to create new pass
	char new_pass[20];
	int num;

	// to add new answers, tests, passes etc.
	answer a;
	test t;
	pass p;
	question q;

	// time
	SYSTEMTIME st;

	do {
		system("cls");

		save(db, pass_);
		cout << "\t\t\tYou have been logged in as admin!\n\n";
		cout << "\t\t===================================================\n";
		cout << "\t\tKnowledge testing system | Admin menu\n";
		cout << "\t\t===================================================\n";
		cout << "\t\t\t\t1. View test\n";
		cout << "\t\t\t\t2. View all tests\n";
		cout << "\t\t\t\t3. Modify test\n";
		cout << "\t\t\t\t4. Delete test\n";
		cout << "\t\t\t\t5. Create new test\n";
		cout << "\t\t\t\t6. View student result\n";
		cout << "\t\t\t\t7. View all results\n";
		cout << "\t\t\t\t8. Delete result\n";
		cout << "\t\t\t\t9. View list of students\n";
		cout << "\t\t\t       10. Search student by name\n";
		cout << "\t\t\t       11. Add new student\n";
		cout << "\t\t\t       12. Delete student\n";
		cout << "\t\t\t       13. Modify student\n";
		cout << "\t\t\t       14. View DataBase\n";
		cout << "\t\t\t       15. My messages"; if (pass_.count_messages > 0) { SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 14)); cout << "   " << pass_.count_messages << " new!"; SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15)); }
		cout << "\n\t\t\t       16. Send message\n";
		cout << "\t\t\t       17. Delete message\n";
		cout << "\t\t\t       18. Exit\n";
		cout << "\t\t===================================================\n";
		cout << "\t\t         To go back always enter '0' \n\n";

		cout << " Answer: ";
		cin >> choise;

		deserialize(db, "passwords.data");
		deserialize(m, "info.dat");

		switch (choise)
		{
		case 1:
		{
			if (m.count_tests == 0)
			{
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
				cout << "\n There isn't any available test!" << endl;
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));

				cout << "\n\n Press any key to continue";
				_getch();
				break;
			}

			// display tests
			cout << "\n Choose the number of test to view: \n";
			display(m);

			// scan answer
			cout << "\n Answer: ";
			cin >> choise2;

			// to go back
			if (choise2 == 0)
			{
				cout << "\n Press any key to continue";
				_getch();
				break;
			}

			// display questions from choisen test
			display(m.tests[choise2 - 1]);

			cout << " Press any key to continue";
			_getch();
		}
		break;

		case 2:
		{
			if (m.count_tests == 0)
			{
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
				cout << "\n There isn't any available test!" << endl;
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));

				cout << "\n\n Press any key to continue";
				_getch();
				break;
			}

			// display questions from all tests
			for (int i = 0; i < m.count_tests; i++)
			{
				// display name of test
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 14));
				cout << "\t\t\t Test: " << m.tests[i].title << endl;
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));

				// display all questions of test
				display(m.tests[i]);
			}

			cout << " Press any key to continue";
			_getch();
		}
		break;

		case 3:
		{
			if (m.count_tests == 0)
			{
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
				cout << "\n There isn't any available test!" << endl;
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));

				cout << "\n\n Press any key to continue";
				_getch();
				break;
			}

			// display the tests
			cout << "\n Choose the number of test to view: \n";
			display(m);

			// scan answers
			cout << "\n Answer: ";
			cin >> choise2;

			// to go back
			if (choise2 == 0)
			{
				cout << "\n Press any key to continue";
				_getch();
				break;
			}

			cout << " Enter the number of question: ";
			cin >> choise3;

			// display choisen question
			cout << endl;
			display(m.tests[choise2 - 1].questions[choise3 - 1]);
			cout << endl;

			// modify menu
			cout << " What do you want to do? \n";
			cout << " 1. Delete answer \n";
			cout << " 2. Add answer \n";
			cout << " 3. Change the answer name \n";
			cout << " 4. Delete question \n";
			cout << " 5. Add question \n";
			cout << " 6. Change the question name\n";
			cout << "\n Answer: ";
			cin >> choise4;

			switch (choise4)
			{
			case 1:
			{
				cout << " Enter the number of answer: ";
				cin >> choise5;

				// delete answer
				del(m.tests[choise2 - 1].questions[choise3 - 1], choise5);

				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
				cout << "\n\n Answer deleted!";
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
			}
			break;

			case 2:
			{
				// add new answer
				cout << " Enter the name of answer: ";
				cin.ignore();
				cin.getline(a.name, 100);

				cout << " Is that answer right? (y/n) - ";
				char vibor01;
				cin >> vibor01;

				a.iftrue = false;
				if (vibor01 == 'y')
				{
					a.iftrue = true;
				}

				// add function
				add(m.tests[choise2 - 1].questions[choise3 - 1], a);

				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
				cout << "\n\n Answer added!";
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
			}
			break;

			case 3:
			{
				cout << " Enter the number of answer: ";
				cin >> choise5;

				cout << " Enter new answer name: ";
				cin.ignore();
				cin.getline(m.tests[choise2 - 1].questions[choise3 - 1].answers[choise5 - 1].name, 100);

				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
				cout << "\n\n Answer name changed!";
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
			}
			break;

			case 4:
			{
				// delete answer
				del(m.tests[choise2 - 1], choise3);

				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
				cout << "\n\n Question deleted!";
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
			}
			break;

			case 5:
			{
				question q1;

				// enter cat. and question
				cout << "\n Enter the subject of the question: ";
				cin.ignore();
				cin.getline(q1.category, 50);

				cout << " Enter the question: ";
				cin.getline(q1.info, 100);

				add(m.tests[choise2 - 1], q1);

				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
				cout << "\n\n Question added!";
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
			}
			break;

			case 6:
			{
				//cout << " Enter the number of question: ";
				//cin >> choise5;

				cout << " Enter new question name: ";
				cin.ignore();
				cin.getline(m.tests[choise2 - 1].questions[choise3 - 1].info, 100);

				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
				cout << "\n\n Question name changed!";
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
			}
			break;

			default:
				break;
			}
			serialize(m, "info.dat");

			cout << "\n Press any key to continue";
			_getch();
		}
		break;

		case 4:
		{
			if (m.count_tests == 0)
			{
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
				cout << "\n There isn't any available test!" << endl;
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));

				cout << "\n\n Press any key to continue";
				_getch();
				break;
			}

			// display the tests
			cout << "\n Choose the number of test to delete: \n";
			display(m);

			// scan answer
			cout << "\n Answer: ";
			cin >> choise2;

			// to go back
			if (choise2 == 0)
			{
				cout << "\n Press any key to continue";
				_getch();
				break;
			}

			// del function
			del(m, choise2);
			serialize(m, "info.dat");

			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
			cout << "\n Test deleted" << endl;
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));

			cout << "\n\n Press any key to continue";
			_getch();
		}
		break;

		case 5:
		{
			// enter title and cat. of test
			cout << "\n Enter the name of the test: ";
			cin.ignore();
			cin.getline(t.title, 100);

			// to go back
			if (t.title[0] == '0')
			{
				cout << "\n Press any key to continue";
				_getch();
				break;
			}

			cout << " Enter the subject of the test: ";
			cin.getline(t.category, 50);

			cout << "\n Add question? (y/n) - ";
			char vibor;
			cin >> vibor;

			do
			{
				if (vibor == 'y')
				{
					question q1;

					// enter cat. and question
					cout << "\n Enter the subject of the question: ";
					cin.ignore();
					cin.getline(q1.category, 50);

					cout << " Enter the question: ";
					cin.getline(q1.info, 100);

					cout << "\n Add answers? (y/n) - ";
					cin >> vibor;

					if (vibor == 'y')
					{
						do
						{
							// enter answers
							cout << "\n Enter the name of the answer: ";
							cin.ignore();
							cin.getline(a.name, 100);

							cout << "\n Is the answer correct? (y/n) - ";
							cin >> vibor;

							if (vibor == 'y')
							{
								a.iftrue = true;
							}

							add(q1, a);
							a.iftrue = false;

							cout << "\n Continue to add the answers? (y/n) - ";
							cin >> vibor;

						} while (vibor == 'y');
					}

					add(t, q1);
				}

				cout << "\n Continue to add the questions? (y/n) - ";
				cin >> vibor;

			} while (vibor == 'y');

			add(m, t);
			serialize(m, "info.dat");

			cout << "\n\n Press any key to continue";
			_getch();
		}
		break;

		case 6:
		{
			// display a list of students
			cout << endl;
			for (int i = 0; i < db.count_passwords; i++)
			{
				cout << " " << i + 1 << ". ";
				display_students(db.passwords[i]);
				cout << endl;
			}

			cout << "\n Choose the number of the student: ";
			cin >> choise3;

			// to go back
			if (choise3 == 0)
			{
				cout << "\n Press any key to continue";
				_getch();
				break;
			}

			// display grades of choisen student
			for (int i = 0; i < db.passwords[choise3 - 1].count_results; i++)
			{
				cout << " " << i + 1 << ". ";
				display(db.passwords[choise3 - 1].results[i], hConsole);
			}
			
			cout << "\n\n Press any key to continue";
			_getch();
		}
		break;

		case 7:
		{
			cout << endl;
			for (int i = 0; i < db.count_passwords; i++)
			{
				// name and surname of student
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 14));
				cout << "\n\t\t\t Student: " << db.passwords[i].name << " " << db.passwords[i].surname << "\n";
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));

				// if student doesn't have any result
				if (db.passwords[i].count_results == 0)
				{
					cout << " No results!" << endl;
					continue;
				}

				// display student's results
				for (int j = 0; j < db.passwords[i].count_results; j++)
				{
					cout << " " << j + 1 << ". ";
					display(db.passwords[i].results[j], hConsole);
				}
			}

			char yn;
			cout << "\n Save results to file? (y/n) - ";
			cin >> yn;

			if (yn == 'y')
			{
				cout << "\n Enter the path to file: ";
				cin.ignore();
				char path[50];
				cin.getline(path, 50);

				save_results_to_file(db, path);

				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
				cout << "\n\n Results have been saved to file.";
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
			}

			cout << "\n\n Press any key to continue";
			_getch();
		}
		break;

		case 8:
		{
			// display a list of students
			cout << endl;
			for (int i = 0; i < db.count_passwords; i++)
			{
				cout << " " << i + 1 << ". ";
				display_students(db.passwords[i]);
				cout << endl;
			}

			cout << "\n Choose the number of the student: ";
			cin >> choise3;

			// to go back
			if (choise3 == 0)
			{
				cout << "\n Press any key to continue";
				_getch();
				break;
			}

			// display the grades
			for (int i = 0; i < db.passwords[choise3 - 1].count_results; i++)
			{
				cout << " " << i + 1 << ". ";
				display(db.passwords[choise3 - 1].results[i], hConsole);
			}

			cout << "\n Choose the number of the grade: ";
			int choise_grade;
			cin >> choise_grade;
			
			// del function
			del(db.passwords[choise3 - 1], choise_grade);

			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
			cout << "\n\n Grade deleted!";
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
			serialize(db, "passwords.data");

			cout << "\n\n Press any key to continue";
			_getch();
		}
		break;

		case 9:
		{
			// display a list of students

			cout << endl << " A list of students: " << endl;
			for (int i = 0; i < db.count_passwords; i++)
			{
				cout << " " << i + 1 << ". ";
				// function to display student
				display_students(db.passwords[i]);
				cout << endl;
			}

			cout << "\n\n Press any key to continue";
			_getch();
		}
		break;

		case 10:
		{
			// search student by name

			cout << "\n Enter the name or surname of student you want to search: ";
			char name_student[20];
			cin.ignore();
			cin.getline(name_student, 20);

			// to go back
			if (name_student[0] == '0')
			{
				cout << "\n Press any key to continue";
				_getch();
				break;
			}

			// search function
			search_student_by_name(db, name_student);

			cout << "\n\n Press any key to continue";
			_getch();
		}
		break;

		case 11:
		{
			// add new student

			cout << "\n Enter student name: ";
			char name_new_student[20];
			cin.ignore();
			cin.getline(name_new_student, 20);

			// to go back
			if (name_new_student[0] == '0')
			{
				cout << "\n Press any key to continue";
				_getch();
				break;
			}

			cout << " Enter student surname: ";
			char surname_new_student[20];
			cin.getline(surname_new_student, 20);

			cout << " Enter login of student to sign in: ";
			char login_new_student[100];
			cin.getline(login_new_student, 100);

			cout << " Enter password of student to sign in: ";
			char pass_new_student[100];
			cin.getline(pass_new_student, 100);

			// create new student
			new_(p, login_new_student, pass_new_student, name_new_student, surname_new_student, false);

			// add student to database
			add(db, p);

			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
			cout << "\n\n New student has been added to data base!\n\n";
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
			serialize(db, "passwords.data");

			cout << " Press any key to continue";
			_getch();
		}
		break;

		case 12:
		{
			// display a list of students
			cout << "\n Choose the student to delete: " << endl;
			for (int i = 0; i < db.count_passwords; i++)
			{
				cout << " " << i + 1 << ". ";
				// function to display student
				display_students(db.passwords[i]);
				cout << endl;
			}
			cout << "\n Answer: ";
			cin >> choise4;

			// to go back
			if (choise4 == 0)
			{
				cout << "\n Press any key to continue";
				_getch();
				break;
			}

			// del function
			del(db, choise4);

			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
			cout << "\n\n Student has been deleted from data base!\n\n";
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
			serialize(db, "passwords.data");

			cout << " Press any key to continue";
			_getch();
		}
		break;

		case 13:
		{
			// display a list of students
			cout << "\n Choose the student to modify: " << endl;
			for (int i = 0; i < db.count_passwords; i++)
			{
				cout << " " << i + 1 << ". ";
				display_students(db.passwords[i]);
				cout << endl;
			}

			cout << "\n Answer: ";
			cin >> choise4;

			// to go back
			if (choise4 == 0)
			{
				cout << "\n Press any key to continue";
				_getch();
				break;
			}

			cout << "\n What do you want to change? \n";
			cout << " 1. Name \n";
			cout << " 2. Surname \n\n";
			cout << " Answer: ";
			cin >> choise5;

			p = db.passwords[choise4 - 1];
			del(db, db.passwords[choise4 - 1]);
			if (choise5 == 1)
			{
				cout << "\n Enter new name: ";
				cin.ignore();
				cin.getline(p.name, 20);
			}
			else if (choise5 == 2)
			{
				cout << "\n Enter new surname: ";
				cin.ignore();
				cin.getline(p.surname, 20);
			}
			add(db, p);

			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
			cout << "\n\n Student has been modified\n\n";
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
			serialize(db, "passwords.data");

			cout << " Press any key to continue";
			_getch();
		}
		break;

		case 14:
		{
			// display data base

			cout << "\n Data Base: \n\n";
			display(db);

			cout << "\n Press any key to continue";
			_getch();
		}
		break;

		case 15:
		{
			if (pass_.count_messages == 0)
			{
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
				cout << "\n You don't have any message!" << endl;
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));

				cout << "\n\n Press any key to continue";
				_getch();
				break;
			}

			cout << "\n Your messages: \n";

			// display messages
			for (int i = 0; i < pass_.count_messages; i++)
			{
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
				cout << "\t\t\t\t Message #" << i + 1 << endl;
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));

				// display function
				display(pass_.messages[i]);
				cout << endl;
			}

			cout << "\n\n Press any key to continue";
			_getch();
		}
		break;

		case 16:
		{
			cout << "\n Choose the student to send message: \n";

			// display a list of students
			for (int i = 0; i < db.count_passwords; i++)
			{
				cout << " " << i + 1 << ". ";
				// function to display student
				display_students(db.passwords[i]);
				cout << endl;
			}

			int sm;
			cout << "\n Answer: ";
			cin >> sm;

			// to go back
			if (sm == 0)
			{
				cout << "\n Press any key to continue";
				_getch();
				break;
			}

			message message_;
			cout << "\n Enter a title of your message: ";
			cin.ignore();
			cin.getline(message_.title, 20);

			cout << " Enter a body of your message: ";
			cin.getline(message_.text, 50);

			// get time
			GetSystemTime(&st);

			char date[20];
			char time[20];
			sprintf_s(date, "%d.%d.%d", st.wDay, st.wMonth, st.wYear);
			sprintf_s(time, "%d:%d:%d", st.wHour+3, st.wMinute, st.wSecond);

			strcpy_s(message_.date, date);
			strcpy_s(message_.time, time);
			strcpy_s(message_.sender, pass_.name);
			strcat_s(message_.sender, " ");
			strcat_s(message_.sender, pass_.surname);

			// add message to student
			add(db.passwords[sm - 1], message_);
			serialize(db, "passwords.data");

			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
			cout << "\n\n Message has been sent to " << db.passwords[sm - 1].name << " " << db.passwords[sm - 1].surname << endl;
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));

			cout << "\n\n Press any key to continue";
			_getch();
		}
		break;

		case 17:
		{
			if (pass_.count_messages == 0)
			{
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
				cout << "\n You don't have any message!" << endl;
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));

				cout << "\n\n Press any key to continue";
				_getch();
				break;
			}

			cout << "\n Choose the message to delete: \n";

			// display messages
			for (int i = 0; i < pass_.count_messages; i++)
			{
				cout << " " << i + 1 << ". " << pass_.messages[i].title << ". From " << pass_.messages[i].sender << " (" << pass_.messages[i].date << ")" << endl;
			}
			cout << "\n Answer: ";
			int mtd;
			cin >> mtd;

			del(db, pass_);
			del_message(pass_, mtd);
			add(db, pass_);
			serialize(db, "passwords.data");

			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
			cout << "\n\n Message has been deleted!" << endl;
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));

			cout << "\n\n Press any key to continue";
			_getch();
		}
		break;

		}

	} while (choise != 18);
}