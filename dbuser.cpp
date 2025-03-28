// dbuser.cpp - original code by Fawn Barisic - provides functions to create, delete, access, and change values in the company database 
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "./database.cpp"
#include "./dbtypes.cpp"

using namespace std;

class DBUser {
public:
  // Customer CRUD operations
  static Customer getCustomer(int customerID) {
      string comstr = "SELECT * FROM CUSTOMER WHERE customerID = " + to_string(customerID) + ";";
      char* com = (char*)comstr.c_str();
      vector<map<string,string>> data = Database::runCommand(com);
      if(data.empty()) throw runtime_error("Customer not found");
      return Customer(data.at(0));
  }

  static vector<Customer> getAllCustomers() {
      string comstr = "SELECT * FROM CUSTOMER;";
      char* com = (char*)comstr.c_str();
      vector<map<string,string>> data = Database::runCommand(com);
      vector<Customer> customers;
      for(auto& row : data) {
          customers.emplace_back(row);
      }
      return customers;
  }

  static bool createCustomer(Customer *customer) {
      string comstr = "INSERT INTO CUSTOMER VALUES (" +
                      to_string(customer->getCustomerID()) + ", '" +
                      customer->getName() + "', '" +
                      customer->getAddress() + "', " +
                      to_string(customer->getRegionID()) + ");";
      char* com = (char*)comstr.c_str();
      Database::runCommand(com);
      return true;
  }

  static bool updateCustomer(Customer *customer) {
      string comstr = "UPDATE CUSTOMER SET " +
                      string("name = '") + customer->getName() + "', " +
                      "address = '" + customer->getAddress() + "', " +
                      "regionID = " + to_string(customer->getRegionID()) + " " +
                      "WHERE customerID = " + to_string(customer->getCustomerID()) + ";";
      char* com = (char*)comstr.c_str();
      Database::runCommand(com);
      return true;
  }

  static bool deleteCustomer(int customerID) {
      string comstr = "DELETE FROM CUSTOMER WHERE customerID = " + to_string(customerID) + ";";
      char* com = (char*)comstr.c_str();
      Database::runCommand(com);
      return true;
  }

  // Region CRUD operations
  static Region getRegion(int regionID) {
      string comstr = "SELECT * FROM REGION WHERE regionID = " + to_string(regionID) + ";";
      char* com = (char*)comstr.c_str();
      vector<map<string,string>> data = Database::runCommand(com);
      if(data.empty()) throw runtime_error("Region not found");
      return Region(data.at(0));
  }

  static vector<Region> getAllRegions() {
      string comstr = "SELECT * FROM REGION;";
      char* com = (char*)comstr.c_str();
      vector<map<string,string>> data = Database::runCommand(com);
      vector<Region> regions;
      for(auto& row : data) {
          regions.emplace_back(row);
      }
      return regions;
  }

  static bool createRegion(Region *region) {
      string comstr = "INSERT INTO REGION VALUES (" +
                      to_string(region->getRegionID()) + ", " +
                      to_string(region->getRevenue()) + ", " +
                      to_string(region->getProduction()) + ", " +
                      to_string(region->getUse()) + ");";
      char* com = (char*)comstr.c_str();
      Database::runCommand(com);
      return true;
  }

  static bool updateRegion(Region *region) {
      string comstr = "UPDATE REGION SET " +
                      "revenue = "s + to_string(region->getRevenue()) + ", " +
                      "production = " + to_string(region->getProduction()) + ", " +
                      "use = " + to_string(region->getUse()) + " " +
                      "WHERE regionID = " + to_string(region->getRegionID()) + ";";
      char* com = (char*)comstr.c_str();
      Database::runCommand(com);
      return true;
  }

  static bool deleteRegion(int regionID) {
        string comstr = "DELETE FROM REGION WHERE regionID = " + to_string(regionID) + ";";
        char* com = (char*)comstr.c_str();
        Database::runCommand(com);
        return true;
    }

  // Bill CRUD operations
  static Bill getBill(int billID) {
      string comstr = "SELECT * FROM BILL WHERE billID = " + to_string(billID) + ";";
      char* com = (char*)comstr.c_str();
      vector<map<string,string>> data = Database::runCommand(com);
      if(data.empty()) throw runtime_error("Bill not found");
      return Bill(data.at(0));
  }

  static vector<Bill> getBillsByCustomer(int customerID) {
      string comstr = "SELECT * FROM BILL WHERE customerID = " + to_string(customerID) + ";";
      char* com = (char*)comstr.c_str();
      vector<map<string,string>> data = Database::runCommand(com);
      vector<Bill> bills;
      for(auto& row : data) {
          bills.emplace_back(row);
      }
      return bills;
  }

  static bool createBill(Bill *bill) {
      string comstr = "INSERT INTO BILL VALUES (" +
                      to_string(bill->getCustomerID()) + ", " +
                      to_string(bill->getBillID()) + ", " +
                      to_string(bill->getQuantity()) + ", " +
                      to_string(bill->getRate()) + ", " +
                      to_string(bill->getPaidAmount()) + ", '" +
                      bill->getDate().toString() + "', '" +
                      bill->getLastNotified().toString() + "');";
      char* com = (char*)comstr.c_str();
      Database::runCommand(com);
      return true;
  }

  static bool updateBill(Bill *bill) {
      string comstr = "UPDATE BILL SET " +
                      "customerID = "s + to_string(bill->getCustomerID()) + ", " +
                      "quantity = " + to_string(bill->getQuantity()) + ", " +
                      "rate = " + to_string(bill->getRate()) + ", " +
                      "paidAmount = " + to_string(bill->getPaidAmount()) + ", " +
                      "date = '" + bill->getDate().toString() + "', " +
                      "lastNotified = '" + bill->getLastNotified().toString() + "' " +
                      "WHERE billID = " + to_string(bill->getBillID()) + ";";
      char* com = (char*)comstr.c_str();
      Database::runCommand(com);
      return true;
  }

  static bool deleteBill(int billID) {
      string comstr = "DELETE FROM BILL WHERE billID = " + to_string(billID) + ";";
      char* com = (char*)comstr.c_str();
      Database::runCommand(com);
      return true;
  }

  static vector<Bill> getAllBills() {
    string comstr = "SELECT * FROM BILL;";
    char* com = (char*)comstr.c_str();
    vector<map<string,string>> data = Database::runCommand(com);
    vector<Bill> bills;
    for(auto& row : data) {
        bills.emplace_back(row);
    }
    return bills;
  }

  // Expense CRUD operations
  static Expense getExpense(int expID) {
      string comstr = "SELECT * FROM EXPENSE WHERE expID = " + to_string(expID) + ";";
      char* com = (char*)comstr.c_str();
      vector<map<string,string>> data = Database::runCommand(com);
      if(data.empty()) throw runtime_error("Expense not found");
      return Expense(data.at(0));
  }

  static vector<Expense> getExpensesByResource(int resourceID) {
      string comstr = "SELECT * FROM EXPENSE WHERE resourceID = " + to_string(resourceID) + ";";
      char* com = (char*)comstr.c_str();
      vector<map<string,string>> data = Database::runCommand(com);
      vector<Expense> expenses;
      for(auto& row : data) {
          expenses.emplace_back(row);
      }
      return expenses;
  }

  static bool createExpense(Expense *expense) {
      string comstr = "INSERT INTO EXPENSE VALUES (" +
                      to_string(expense->getResourceID()) + ", " +
                      to_string(expense->getExpID()) + ", '" +
                      expense->getPurpose() + "', " +
                      to_string(expense->getAmount()) + ", '" +
                      expense->getDate().toString() + "');";
      char* com = (char*)comstr.c_str();
      Database::runCommand(com);
      return true;
  }

  static bool updateExpense(Expense *expense) {
      string comstr = "UPDATE EXPENSE SET " +
                      "resourceID = "s + to_string(expense->getResourceID()) + ", " +
                      "purpose = '" + expense->getPurpose() + "', " +
                      "amount = " + to_string(expense->getAmount()) + ", " +
                      "date = '" + expense->getDate().toString() + "' " +
                      "WHERE expID = " + to_string(expense->getExpID()) + ";";
      char* com = (char*)comstr.c_str();
      Database::runCommand(com);
      return true;
  }

  static bool deleteExpense(int expID) {
      string comstr = "DELETE FROM EXPENSE WHERE expID = " + to_string(expID) + ";";
      char* com = (char*)comstr.c_str();
      Database::runCommand(com);
      return true;
  }

  static vector<Expense> getAllExpenses() {
    string comstr = "SELECT * FROM EXPENSE;";
    char* com = (char*)comstr.c_str();
    vector<map<string,string>> data = Database::runCommand(com);
    vector<Expense> expenses;
    for(auto& row : data) {
        expenses.emplace_back(row);
    }
    return expenses;
  }

  // Footprint CRUD operations
  static Footprint getFootprint(int customerID, int resourceID) {
      string comstr = "SELECT * FROM FOOTPRINT WHERE customerID = " + to_string(customerID) + 
                      " AND resourceID = " + to_string(resourceID) + ";";
      char* com = (char*)comstr.c_str();
      vector<map<string,string>> data = Database::runCommand(com);
      if(data.empty()) throw runtime_error("Footprint not found");
      return Footprint(data.at(0));
  }

  static vector<Footprint> getFootprintsByCustomer(int customerID) {
      string comstr = "SELECT * FROM FOOTPRINT WHERE customerID = " + to_string(customerID) + ";";
      char* com = (char*)comstr.c_str();
      vector<map<string,string>> data = Database::runCommand(com);
      vector<Footprint> footprints;
      for(auto& row : data) {
          footprints.emplace_back(row);
      }
      return footprints;
  }

  static bool createFootprint(Footprint *footprint) {
      string comstr = "INSERT INTO FOOTPRINT VALUES (" +
                      to_string(footprint->getCustomerID()) + ", " +
                      to_string(footprint->getResourceID()) + ", " +
                      to_string(footprint->getAmount()) + ", " +
                      to_string(footprint->getTotalCarbon()) + ");";
      char* com = (char*)comstr.c_str();
      Database::runCommand(com);
      return true;
  }

  static bool updateFootprint(Footprint *footprint) {
      string comstr = "UPDATE FOOTPRINT SET " +
                      "amount = "s + to_string(footprint->getAmount()) + ", " +
                      "totalcarbon = " + to_string(footprint->getTotalCarbon()) + " " +
                      "WHERE customerID = " + to_string(footprint->getCustomerID()) + 
                      " AND resourceID = " + to_string(footprint->getResourceID()) + ";";
      char* com = (char*)comstr.c_str();
      Database::runCommand(com);
      return true;
  }

  static bool deleteFootprint(int customerID, int resourceID) {
      string comstr = "DELETE FROM FOOTPRINT WHERE customerID = " + to_string(customerID) + 
                      " AND resourceID = " + to_string(resourceID) + ";";
      char* com = (char*)comstr.c_str();
      Database::runCommand(com);
      return true;
  }
  
  static vector<Footprint> getAllFootprints() {
    string comstr = "SELECT * FROM FOOTPRINT;";
    char* com = (char*)comstr.c_str();
    vector<map<string,string>> data = Database::runCommand(com);
    vector<Footprint> footprints;
    for(auto& row : data) {
        footprints.emplace_back(row);
    }
    return footprints;
  }

  // Resource CRUD operations
  static Resource getResource(int resourceID) {
      string comstr = "SELECT * FROM RESOURCE WHERE resourceID = " + to_string(resourceID) + ";";
      char* com = (char*)comstr.c_str();
      vector<map<string,string>> data = Database::runCommand(com);
      if(data.empty()) throw runtime_error("Resource not found");
      return Resource(data.at(0));
  }

  static vector<Resource> getAllResources() {
      string comstr = "SELECT * FROM RESOURCE;";
      char* com = (char*)comstr.c_str();
      vector<map<string,string>> data = Database::runCommand(com);
      vector<Resource> resources;
      for(auto& row : data) {
          resources.emplace_back(row);
      }
      return resources;
  }

  static bool createResource(Resource *resource) {
      string comstr = "INSERT INTO RESOURCE VALUES (" +
                      to_string(resource->getResourceID()) + ", '" +
                      resource->getName() + "', " +
                      to_string(resource->getImportCost()) + ", " +
                      to_string(resource->getExportPrice()) + ", " +
                      to_string(resource->getUnitCarbon()) + ");";
      char* com = (char*)comstr.c_str();
      Database::runCommand(com);
      return true;
  }

  static bool updateResource(Resource *resource) {
      string comstr = "UPDATE RESOURCE SET " +
                      "name = '"s + resource->getName() + "', " +
                      "importCost = " + to_string(resource->getImportCost()) + ", " +
                      "exportPrice = " + to_string(resource->getExportPrice()) + ", " +
                      "unitCarbon = " + to_string(resource->getUnitCarbon()) + " " +
                      "WHERE resourceID = " + to_string(resource->getResourceID()) + ";";
      char* com = (char*)comstr.c_str();
      Database::runCommand(com);
      return true;
  }

  static bool deleteResource(int resourceID) {
      string comstr = "DELETE FROM RESOURCE WHERE resourceID = " + to_string(resourceID) + ";";
      char* com = (char*)comstr.c_str();
      Database::runCommand(com);
      return true;
  }

  // Supply CRUD operations
  static Supply getSupply(int resourceID, int regionID) {
      string comstr = "SELECT * FROM SUPPLY WHERE resourceID = " + to_string(resourceID) + 
                      " AND regionID = " + to_string(regionID) + ";";
      char* com = (char*)comstr.c_str();
      vector<map<string,string>> data = Database::runCommand(com);
      if(data.empty()) throw runtime_error("Supply not found");
      return Supply(data.at(0));
  }

  static vector<Supply> getSuppliesByRegion(int regionID) {
      string comstr = "SELECT * FROM SUPPLY WHERE regionID = " + to_string(regionID) + ";";
      char* com = (char*)comstr.c_str();
      vector<map<string,string>> data = Database::runCommand(com);
      vector<Supply> supplies;
      for(auto& row : data) {
          supplies.emplace_back(row);
      }
      return supplies;
  }

  static bool createSupply(Supply *supply) {
      string comstr = "INSERT INTO SUPPLY VALUES (" +
                      to_string(supply->getResourceID()) + ", " +
                      to_string(supply->getRegionID()) + ", " +
                      to_string(supply->getProduction()) + ", " +
                      to_string(supply->getUse()) + ");";
      char* com = (char*)comstr.c_str();
      Database::runCommand(com);
      return true;
  }

  static bool updateSupply(Supply *supply) {
      string comstr = "UPDATE SUPPLY SET " +
                      "production = "s + to_string(supply->getProduction()) + ", " +
                      "use = " + to_string(supply->getUse()) + " " +
                      "WHERE resourceID = " + to_string(supply->getResourceID()) + 
                      " AND regionID = " + to_string(supply->getRegionID()) + ";";
      char* com = (char*)comstr.c_str();
      Database::runCommand(com);
      return true;
  }

  static bool deleteSupply(int resourceID, int regionID) {
      string comstr = "DELETE FROM SUPPLY WHERE resourceID = " + to_string(resourceID) + 
                      " AND regionID = " + to_string(regionID) + ";";
      char* com = (char*)comstr.c_str();
      Database::runCommand(com);
      return true;
  }
  static vector<Supply> getAllSupplies() {
    string comstr = "SELECT * FROM SUPPLY;";
    char* com = (char*)comstr.c_str();
    vector<map<string,string>> data = Database::runCommand(com);
    vector<Supply> supplies;
    for(auto& row : data) {
        supplies.emplace_back(row);
    }
    return supplies;
}
};

int main(int argc, char *argv[]) {
  /*
  DBUser::createRegion(new Region(2, 1500.00, 220.5, 199.2));
  DBUser::createCustomer(new Customer(2, "Gusbert", "456 7th blvd.", 2));
  DBUser::createBill(new Bill(2, 1, 18.1, 8.0, 80.50, *new Date(2024, 12, 10), *new Date(2025, 1, 10)));
  DBUser::createResource(new Resource(2, "solar", 12.25, 10.00, 0.25));
  DBUser::createExpense(new Expense(2, 1, "panel dusting service", 500.25, *new Date(2025, 2, 15)));
  DBUser::createFootprint(new Footprint(2, 2, 10, 2.5));
  DBUser::createSupply(new Supply(2, 2, 150.76, 125.34));
  */

  for (Customer c : DBUser::getAllCustomers()) {
    for(auto const& p : c.attr) {
      cout << p.first << "=" << p.second << endl;
    }
    cout << endl;
  }
  cout << endl;
  for (Region c : DBUser::getAllRegions()) {
    for(auto const& p : c.attr) {
      cout << p.first << "=" << p.second << endl;
    }
    cout << endl;
  }
  cout << endl;
  for (Bill c : DBUser::getAllBills()) {
    for(auto const& p : c.attr) {
      cout << p.first << "=" << p.second << endl;
    }
    cout << endl;
  }
  cout << endl;
  for (Resource c : DBUser::getAllResources()) {
    for(auto const& p : c.attr) {
      cout << p.first << "=" << p.second << endl;
    }
    cout << endl;
  }
  cout << endl;
  for (Expense c : DBUser::getAllExpenses()) {
    for(auto const& p : c.attr) {
      cout << p.first << "=" << p.second << endl;
    }
    cout << endl;
  }
  cout << endl;
  for (Footprint c : DBUser::getAllFootprints()) {
    for(auto const& p : c.attr) {
      cout << p.first << "=" << p.second << endl;
    }
    cout << endl;
  }
  cout << endl;
  for (Supply c : DBUser::getAllSupplies()) {
    for(auto const& p : c.attr) {
      cout << p.first << "=" << p.second << endl;
    }
    cout << endl;
  }
  return 0;
}