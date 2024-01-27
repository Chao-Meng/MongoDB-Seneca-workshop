/*
	==================================================
	Milestone 1:
	==================================================
	Name   :Chao Meng
	ID     :128438215
	Email  :cmeng14@myseneca.ca
	Section:ZDD
	Group Number:1
	Date   :03/18/2022
*/
/*I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.*/
#include <iostream>
#include <occi.h>
#include <string>
#define  _CRT_SECURE_NO_WARNINGS
using oracle::occi::Environment;
using oracle::occi::Connection;

using namespace oracle::occi;
using namespace std;
int main(void) {
	//OCCI Variables
	Environment* env = nullptr;
	Connection* conn = nullptr;
	//User Variables
	string str;
	string usr = "dbs211_221zd23";
	string pass = "31859841";
	string srv = "myoracle12c.senecacollege.ca:1521/oracle12c";

	try {
		env = Environment::createEnvironment(Environment::DEFAULT);
		conn = env->createConnection(usr, pass, srv);
		cout << "Connection is Successful! Group 1" << endl;
		cout << "Members name: Chao Meng, MANPREET SINGH, Satneet Kaur, Simaranpreet Kaur, Rupinderjit Kaur" << endl;

		Statement* stmt = conn->createStatement();
		ResultSet* rs = stmt->executeQuery("SELECT officecode, city, state, country, postalcode FROM offices ORDER BY officecode");


		cout << "The company offices are:" << endl;
		cout << "#  City            State          Country          Postal Code" << endl;

		while (rs->next()) {
			int count = rs->getInt(1);
			string city = rs->getString(2);
			string state = rs->getString(3);
			string country = rs->getString(4);
			string pc = rs->getString(5);
			cout << count << "  ";
			cout.width(16);
			cout << std::left << city;
			cout.fill(' ');
			cout.width(15);
			cout << std::left << state;
			cout.fill(' ');
			cout.width(17);
			cout << std::left << country;
			cout.fill(' ');
			cout << pc << endl;
		}

		string val = {};
		int count = 0;
		cout << "Input the employeeNumber need to be searched: ";
		cin >> val;
		bool isInt = true;
		//transfer the input string to int if it is int.
		int iVal = atoi(val.c_str());
		//check if the input value is integer via ASCII code
		for (size_t i = 0; i < val.length(); i++) {
			if (val[i] < '0' || val[i] >'9') {
				isInt = false;
			}
		}
		//if the input is valid integer, query the number in database
		if (isInt) {
			if (iVal > 0 || iVal < 9999) {
				char query[250];
				sprintf_s(query, "SELECT employeeNumber,lastName,firstName,email,officecode FROM employees WHERE employeeNumber = %d", iVal);
				ResultSet* rss = stmt->executeQuery(query);
				cout << "employeeNumber  lastName       firstName      email                              officecode" << endl;
				while (rss->next()) {
					int employeeNumber = rss->getInt(1);
					string lastName = rss->getString(2);
					string firstName = rss->getString(3);
					string email = rss->getString(4);
					int officeCode = rss->getInt(5);
					cout.width(14);
					cout << std::right << employeeNumber << "  ";
					cout.width(15);
					cout << std::left << lastName;
					cout.fill(' ');
					cout.width(15);
					cout << std::left << firstName;
					cout.fill(' ');
					cout.width(35);
					cout << std::left << email;
					cout.fill(' ');
					cout << officeCode << endl;
					count++;
				}
			}
			else {
				cout << "Error: wrong employeeNumber!!";
			}
		}
		else {
			cout << "Error:Invalid Integer!!" << endl;
		}
		cout << "The inquiry has been completed, thanks!" << endl;
		//if the result is null, it means there is no this employeeNumber in the database
		if (count == 0) {
			cout << "Error, employeeNumber does not exit!!";
		}
		conn->terminateStatement(stmt);
		env->terminateConnection(conn);
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ":" << sqlExcp.getMessage();
	}
	return 0;
}