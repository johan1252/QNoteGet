#include "createTable.h"

int main(int, char *argv[]) {
	pqxx::connection c("dbname=d977ktitdsgsqp user=qohiknwjuwjacn password=f1ef440e6c254a34c4e638e3dbca1abb9bac8c14acd110309b9955bc8b51af3a host=ec2-50-17-201-204.compute-1.amazonaws.com port=5432 requiressl=1");
	std::string sql = "CREATE TABLE TESTMAYTHA("  \
		      "ID INT PRIMARY KEY     NOT NULL," \
		      "NAME           TEXT    NOT NULL," \
		      "PASSWORD       TEXT     NOT NULL);";

	createTable(c, sql);
	c.disconnect();
}
