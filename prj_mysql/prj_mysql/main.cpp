#include <iostream>
using namespace std;

#include <windows.h>  
#include "stdio.h"   
 
#include <iostream>
#include <string>
#include "mysql.h"  
#pragma comment(lib, "libmysql")
#pragma comment(lib, "mysqlclient")
using namespace std;

MYSQL *connection, mysql;
MYSQL_ROW row;

MYSQL_RES* mysql_perform_query(MYSQL *connection, char *sql_query)
{
	if (mysql_query(connection, sql_query))
	{
		printf("MySQL query error : %s\n", mysql_error(connection));
		exit(1);
	}
	return mysql_use_result(connection);
}

int getScoreFromDatabase(int userID, int gameID, bool isHost) {
	MYSQL_RES *result;
	string str = "SELECT pointA, pointB FROM Game WHERE gameID = " + to_string(gameID) + " ;";
	int tmp = -1;
	result = mysql_perform_query(connection, (char *)str.c_str());
	while ((row = mysql_fetch_row(result)) != NULL) {
		//printf("%s %s\n", row[0], row[1]);
		if (isHost)
			tmp = stoi(row[0]);
		else
			tmp = stoi(row[1]);
	}
	mysql_free_result(result);
	return tmp;
}

int updateScoreToDatabase(int userID, int gameID, int newScore, bool isHost) {
	string str = "";
	if (isHost)
		str = "UPDATE Game SET pointA = " + to_string(newScore) + " WHERE gameID = " + to_string(gameID) + " ;";
	else 
		str = "UPDATE Game SET pointB = " + to_string(newScore) + " WHERE gameID = " + to_string(gameID) + " ;";
	MYSQL_RES *result;
	result = mysql_perform_query(connection, (char *)str.c_str());
	mysql_free_result(result);
	return 0;
}

int displayGameTable(int gameID) {
	MYSQL_RES *result;
	string str = "SELECT U1.userName, pointA, U2.userName, pointB FROM Game, Users U1, Users U2 WHERE Game.gameID=" + to_string(gameID) + " AND U1.userID=Game.userAID AND U2.userID=Game.userBID;";
	result = mysql_perform_query(connection, (char *)str.c_str());
	printf("MySQL Tables in mysql database:\n");
	while ((row = mysql_fetch_row(result)) != NULL)
		printf("%s %s %s %s\n", row[0], row[1], row[2], row[3]);
	mysql_free_result(result);
	return 0;
}

int main()
{
	int a;
	mysql_init(&mysql);
	connection = mysql_real_connect(&mysql, "localhost", "root", "root", "CS201Proj", 0, 0, 0);
	//connection = mysql_real_connect(&mysql, "172.20.10.5", "root", "root", "CS201Proj", 0, 0, 0);
	if (connection == NULL)
		cout << mysql_error(&mysql) << endl;
	
	//result = mysql_perform_query(connection, (char*)"SELECT U1.userName, pointA, U2.userName, pointB FROM Game, Users U1, Users U2 WHERE Game.gameID=1 AND U1.userID=Game.userAID AND U2.userID=Game.userBID;");
	//result = mysql_perform_query(connection, (char*)"SELECT * FROM Users;");
	
	

	cout << "pause" << endl;
	
	displayGameTable(1);
	
	cout<< getScoreFromDatabase(1, 1, true) << endl;
	updateScoreToDatabase(1, 1, 77, true);
	displayGameTable(1);
	cin >> a;


	// clean up the database link 
	mysql_close(connection);
	// clean up the database result set 
	

	return 0;
}