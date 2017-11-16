//============================================================================
// Name        : database4.cpp
// Author      : Ganesha Thirumurthi
// Version     :
// Copyright   : 'Copyright of Ganesha'
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <exception>
#include "dbExecute.h"
#include "dbDatabase.h"


pqxx::result executeReturn(const std::string& sql) {
  pqxx::result r;
//  std::cout << r.empty() << " :here";
  try {
	pqxx::connection c("dbname=d977ktitdsgsqp user=qohiknwjuwjacn password=f1ef440e6c254a34c4e638e3dbca1abb9bac8c14acd110309b9955bc8b51af3a host=ec2-50-17-201-204.compute-1.amazonaws.com port=5432 requiressl=1");
    pqxx::work txn(c);
    r = txn.exec(sql);
    txn.commit();
    c.disconnect();
  }
  catch (const std::exception &e) {
    std::cout << "Could not execute SQL statement :" << e.what();
   }
  return r;
}

bool execute(const std::string& sql) {
	return executeReturn(sql).empty();
}




//#include <iostream>
//#include <pqxx/pqxx>
//
//int main(int, char *argv[]) {
//
//  pqxx::connection c("dbname=test1 user=tester");
//  pqxx::work txn(c);
//
//  pqxx::result r = txn.exec(
//    "CREATE TABLE userTest" + txn.quote(argv[1]));
//
//  if (r.size() != 1)
//  {
//    std::cerr
//      << "Expected 1 employee with name " << argv[1] << ", "
//      << "but found " << r.size() << std::endl;
//    return 1;
//  }
//
//  int employee_id = r[0][0].as<int>();
//  std::cout << "Updating employee #" << employee_id << std::endl;
//
//  txn.exec(
//    "UPDATE EMPLOYEE "
//    "SET salary = salary + 1 "
//    "WHERE id = " + txn.quote(employee_id));
//
//  txn.commit();
//}
