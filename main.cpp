#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
using namespace std;

// DB login details
char HOST[] = "localhost";
char USER[] = "root";
char PASS[] = "root";

int main()
{
	MYSQL *obj; // MySQL Object
	int custid, phone;
	char checkin[11];
	char checkout[11];
	char name[20];
	char roomtype[10];
	bool ProgramIsOpened = true;
	int answer;
	char *consult;
	char *sentence;
	string sentence_aux; // Append data into table
	
	// Setting up Connection
	
	if (!(obj = mysql_init(0)))
	{
		cout << "Error: MySQL object cannot be created\n";
	}
	else
	{
		if (!mysql_real_connect(obj, HOST, USER, PASS, "vaman", 3306, NULL, 0))
		{
			cout << "Error: Some database info is wrong or do not exist\n";
			cout << mysql_error(obj) << "\n";
		}
		else
		{
			cout << "Logged in. \n";
			while (ProgramIsOpened)
			{
				cout << "Enter custid and phone no : ";
				cin >> custid;
				cin >> phone;
				cin.ignore(100, '\n'); //  Clean the buffer
				cout << "Enter name : ";
				cin.getline(name, 20, '\n'); // Cin >> name does not read spaces, hence we use getline()
				cout << "Check-in and Check-out dates : ";
				cin.getline(checkin, 11, '\n');
				cin.getline(checkout, 11, '\n');
				cout << "Enter Room-type : ";
				cin.getline(name, 10, '\n');
				cin.ignore(100, '\n');
				cout << "\n";
				
				// Set the update
				
				sentence_aux = "INSERT INTO HOTEL(custid, name, phone, checkin, checkout, roomtype) VALUES('%d','%s','%d','%s','%s','%s')";
				sentence = new char[sentence_aux.length() + 1];
				strcpy(sentence, sentence_aux.c_str());
				consult = new char[strlen(sentence) + sizeof(int) + strlen(name) + sizeof(int) + strlen(checkin) + strlen(checkout) + strlen(roomtype)];
				sprintf(consult, sentence, custid, name, phone, checkin, checkout, roomtype);
				
				// Connect to DB
				
				if (mysql_ping(obj))
				{
					cout << "Error: Impossible to connect \n";
					cout << mysql_error(obj) << "\n";
				}
				
				if (mysql_query(obj, consult))
				{
					cout << "Error: " << mysql_error(obj) << "\n";
					rewind(stdin);
					getchar();
				}
				else
				{
					cout << "Details added \n";
				}
				mysql_store_result(obj);
				cout << "Add more? (1 y / 0 n) \n";
				cin >> answer;
				cin.ignore(100, '\n');
				if (answer == 0)
				{
					ProgramIsOpened = false;
				}
				cout << "\n";
			}
		}
	}
}
