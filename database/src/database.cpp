#include "createTable.h"

int main(int, char *argv[]) {
	pqxx::connection c("dbname=test1 user=tester");
	std::string sql = "CREATE TABLE USERS("  \
		      "ID INT PRIMARY KEY     NOT NULL," \
		      "NAME           TEXT    NOT NULL," \
		      "PASSWORD       TEXT     NOT NULL);";

	createTable(c, sql);
	c.disconnect();
}
