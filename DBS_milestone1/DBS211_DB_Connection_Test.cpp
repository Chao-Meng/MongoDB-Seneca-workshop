#include <iostream>
#include <occi.h>

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;

int main(void){
	//OCCI Variables
	Environment* env = nullptr;
	Connection* conn = nullptr;
	//User Variables
	string str;
	string usr = "db_cmeng14";
	string pass = "m]9fGu]0Sw";
	string srv = "myoracle12c.senecacollege.ca:1521/oracle12c";

	try {
		env = Environment::createEnvironment(Environment::DEFAULT);
		conn = env->createConnection(usr, pass, srv);
		cout << "Connection is Successful!" << endl;
		env->terminateConnection(conn);
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ":" << sqlExcp.getMessage();
	}
	return 0;
}