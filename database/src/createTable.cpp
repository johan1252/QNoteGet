//============================================================================
// Name        : database4.cpp
// Author      : Ganesha Thirumurthi
// Version     :
// Copyright   : 'Copyright of Ganesha'
// Description : Hello World in C++, Ansi-style
//============================================================================

//#include <iostream>
//using namespace std;
//
//int main() {
//	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
//	return 0;
//}
#include "createTable.h"
#include <exception>
#include <iostream>


bool createTable(pqxx::connection& c,const std::string& sql) {
  try {
    pqxx::work txn(c);
    pqxx::result r = txn.exec(sql);
    txn.commit();
  }
  catch (const std::exception &e) {
    std::cout << "Could not create table :" << e.what();
    return false;
   }
  return true;
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
