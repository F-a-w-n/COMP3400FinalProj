// database.cpp - original code by Fawn Barisic - directly interfaces with SQLite database through custom string commands
#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include <vector>
#include <map> 
#include <string>

using namespace std;

class Database {
  private:
  public:

  static int callback(void* res, int argc, char **argv, char **azColName) {
    map<string, string> current;
    vector<map<string, string>> * results = static_cast<vector<map<string, string>>*>(res);
    for(int i = 0; i<argc; i++) {
      current.insert(make_pair((string)azColName[i], (string)(argv[i] ? argv[i] : "NULL")));
    }
    results->push_back(current);
    return 0;
  }

  static vector<map<string, string>> runCommand(char *sql) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc = sqlite3_open("test.db", &db);
    
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return *new vector<map<string, string>>;
    }

    /*
    sql = "CREATE TABLE COMPANY("  \
        "ID INT PRIMARY KEY     NOT NULL," \
        "NAME           TEXT    NOT NULL," \
        "AGE            INT     NOT NULL," \
        "ADDRESS        CHAR(50)," \
        "SALARY         REAL );";
    */

    vector<map<string, string>> results;

    rc = sqlite3_exec(db, sql, callback, &results, &zErrMsg);

    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
    return results;
  }
};

/*
int main() {
  Database::runCommand(" CREATE TABLE REGION( regionID INT NOT NULL, revenue DOUBLE, production DOUBLE, use DOUBLE, PRIMARY KEY (regionID) );");
  Database::runCommand(" CREATE TABLE CUSTOMER( customerID INT NOT NULL, name VARCHAR(20), address VARCHAR(30), regionID INT, PRIMARY KEY (customerID), FOREIGN KEY (regionID) REFERENCES REGION(regionID) );");
  Database::runCommand(" CREATE TABLE RESOURCE( resourceID INT NOT NULL, name VARCHAR(15), importCost DOUBLE, exportPrice DOUBLE, unitCarbon DOUBLE, PRIMARY KEY (resourceID) );");
  Database::runCommand(" CREATE TABLE BILL( customerID INT NOT NULL, billID INT NOT NULL, quantity DOUBLE, rate DOUBLE, paidAmount DOUBLE, date VARCHAR(10), lastNotified VARCHAR(10), PRIMARY KEY (customerID, billID), FOREIGN KEY (customerID) REFERENCES CUSTOMER(customerID) );");
  Database::runCommand(" CREATE TABLE EXPENSE( resourceID INT NOT NULL, expID INT NOT NULL, purpose VARCHAR(30), amount DOUBLE, date VARCHAR(10), PRIMARY KEY (resourceID, expID), FOREIGN KEY (resourceID) REFERENCES RESOURCE(resourceID) );");
  Database::runCommand(" CREATE TABLE FOOTPRINT( customerID INT NOT NULL, resourceID INT NOT NULL, amount DOUBLE, totalCarbon DOUBLE, PRIMARY KEY (customerID, resourceID), FOREIGN KEY (customerID) REFERENCES CUSTOMER(customerID), FOREIGN KEY (resourceID) REFERENCES RESOURCE(resourceID));");
  Database::runCommand(" CREATE TABLE SUPPLY( resourceID INT NOT NULL, regionID INT NOT NULL, production DOUBLE, use DOUBLE, PRIMARY KEY (resourceID, regionID), FOREIGN KEY (resourceID) REFERENCES RESOURCE(resourceID), FOREIGN KEY (regionID) REFERENCES REGION(regionID));");
  return 0;
}
*/