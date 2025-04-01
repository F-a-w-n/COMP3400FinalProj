// dbtypes.cpp - original code by Fawn Barisic - provides helper classes to store rows for each table of the company database
#include <iostream>
#include <map>
#include <string>

using namespace std;

class Date {
  private:
  int year;
  int month;
  int day;
  
  public: 
  Date() {};

  Date(string s) {
      if (s.compare("NULL")==0) return;
      size_t Dash = s.find('-', 5);
      
      size_t dateEnd = s.find(' ');
      if (dateEnd == string::npos) {
          dateEnd = s.length();
      }
      
      year = stoi(s.substr(0, 4));
      month = stoi(s.substr(5, Dash));
      day = stoi(s.substr(Dash + 1, dateEnd));
  }

  Date(int y, int m, int d) : year(y), month(m), day(d) {}
  
  string toString() {
    return to_string(year) + "-" + to_string(month) + "-" + to_string(day);
  }

  int getYear() { return year; }
  int getMonth() { return month; }
  int getDay() { return day; }
  
  void setYear(int y) { year = y; }
  void setMonth(int m) { month = m; }
  void setDay(int d) { day = d; }
};

class Helper {
  public:
  map<string, string> attr;
  Helper(map<string, string> attr) {
    this->attr = attr;
  }
  int getInt(string key) {
    if (key.compare("NULL") ==0) return 0;
    return stoi(attr.at(key));
  }
  double getDouble(string key) {
    if (key.compare("NULL") ==0) return 0;
    return stod(attr.at(key));
  }
  Date getDate(string key) {
    return *new Date(attr.at(key));
  }
  string getString(string key) {
    return attr.at(key);
  }
};

class Customer : public Helper {
  private:
  int customerID;
  string name;
  string address;
  int regionID;

  public:
  Customer(map<string, string> attr) : Helper(attr) {
    customerID = getInt("customerID");
    name = getString("name");
    address = getString("address");
    regionID = getInt("regionID");
  }
  
  Customer(int id, string n, string addr, int regID) : 
    Helper({{"customerID", to_string(id)}, 
            {"name", n}, 
            {"address", addr}, 
            {"regionID", to_string(regID)}}),
    customerID(id), name(n), address(addr), regionID(regID) {}
  
  int getCustomerID() { return customerID; }
  string getName() { return name; }
  string getAddress() { return address; }
  int getRegionID() { return regionID; }
  
  void setCustomerID(int id) { customerID = id; }
  void setName(string n) { name = n; }
  void setAddress(string addr) { address = addr; }
  void setRegionID(int id) { regionID = id; }
};

class Region : public Helper {
  private:
  int regionID;
  double revenue;
  double production;
  double use;

  public:
  Region(map<string, string> attr) : Helper(attr) {
    regionID = getInt("regionID");
    revenue = getDouble("revenue");
    production = getDouble("production");
    use = getDouble("use");
  }
  
  Region(int id, double rev, double prod, double u) : 
    Helper({{"regionID", to_string(id)}, 
            {"revenue", to_string(rev)}, 
            {"production", to_string(prod)}, 
            {"use", to_string(u)}}),
    regionID(id), revenue(rev), production(prod), use(u) {}
  
  int getRegionID() { return regionID; }
  double getRevenue() { return revenue; }
  double getProduction() { return production; }
  double getUse() { return use; }
  
  void setRegionID(int id) { regionID = id; }
  void setRevenue(double rev) { revenue = rev; }
  void setProduction(double prod) { production = prod; }
  void setUse(double u) { use = u; }
};

class Bill : public Helper {
  private:
  int customerID;
  int billID;
  double quantity;
  double rate;
  double paidAmount;
  Date date;
  Date lastNotified;

  public:
  Bill(map<string, string> attr) : Helper(attr) {
    customerID = getInt("customerID");
    billID = getInt("billID");
    quantity = getDouble("quantity");
    rate = getDouble("rate");
    paidAmount = getDouble("paidAmount");
    date = Helper::getDate("date");
    lastNotified = Helper::getDate("lastNotified");
  }
  
  Bill(int custID, int bID, double qty, double rt, double paid, Date dt, Date lastNot) : 
    Helper({{"customerID", to_string(custID)}, 
            {"billID", to_string(bID)}, 
            {"quantity", to_string(qty)}, 
            {"rate", to_string(rt)}, 
            {"paidAmount", to_string(paid)}, 
            {"date", dt.toString()}, 
            {"lastNotified", lastNot.toString()}}),
    customerID(custID), billID(bID), quantity(qty), rate(rt), 
    paidAmount(paid), date(dt), lastNotified(lastNot) {}
  
  int getCustomerID() { return customerID; }
  int getBillID() { return billID; }
  double getQuantity() { return quantity; }
  double getRate() { return rate; }
  double getPaidAmount() { return paidAmount; }
  Date getDate() { return date; }
  Date getLastNotified() { return lastNotified; }
  
  void setCustomerID(int id) { customerID = id; }
  void setBillID(int id) { billID = id; }
  void setQuantity(double q) { quantity = q; }
  void setRate(double r) { rate = r; }
  void setPaidAmount(double amount) { paidAmount = amount; }
  void setDate(Date d) { date = d; }
  void setLastNotified(Date d) { lastNotified = d; }
};

class Expense : public Helper {
  private:
  int resourceID;
  int expID;
  string purpose;
  double amount;
  Date date;

  public:
  Expense(map<string, string> attr) : Helper(attr) {
    resourceID = getInt("resourceID");
    expID = getInt("expID");
    purpose = getString("purpose");
    amount = getDouble("amount");
    date = Helper::getDate("date");
  }
  
  Expense(int resID, int eID, string purp, double amt, Date dt) : 
    Helper({{"resourceID", to_string(resID)}, 
            {"expID", to_string(eID)}, 
            {"purpose", purp}, 
            {"amount", to_string(amt)}, 
            {"date", dt.toString()}}),
    resourceID(resID), expID(eID), purpose(purp), amount(amt), date(dt) {}
  
  int getResourceID() { return resourceID; }
  int getExpID() { return expID; }
  string getPurpose() { return purpose; }
  double getAmount() { return amount; }
  Date getDate() { return date; }
  
  void setResourceID(int id) { resourceID = id; }
  void setExpID(int id) { expID = id; }
  void setPurpose(string p) { purpose = p; }
  void setAmount(double a) { amount = a; }
  void setDate(Date d) { date = d; }
};

class Footprint : public Helper {
  private:
  int customerID;
  int resourceID;
  double amount;
  double totalcarbon;

  public:
  Footprint(map<string, string> attr) : Helper(attr) {
    customerID = getInt("customerID");
    resourceID = getInt("resourceID");
    amount = getDouble("amount");
    totalcarbon = getDouble("totalCarbon");
  }
  
  Footprint(int custID, int resID, double amt, double totalC) : 
    Helper({{"customerID", to_string(custID)}, 
            {"resourceID", to_string(resID)}, 
            {"amount", to_string(amt)}, 
            {"totalCarbon", to_string(totalC)}}),
    customerID(custID), resourceID(resID), amount(amt), totalcarbon(totalC) {}
  
  int getCustomerID() { return customerID; }
  int getResourceID() { return resourceID; }
  double getAmount() { return amount; }
  double getTotalCarbon() { return totalcarbon; }
  
  void setCustomerID(int id) { customerID = id; }
  void setResourceID(int id) { resourceID = id; }
  void setAmount(double a) { amount = a; }
  void setTotalCarbon(double carbon) { totalcarbon = carbon; }
};

class Resource : public Helper {
  private:
  int resourceID;
  string name;
  double importCost;
  double exportPrice;
  double unitCarbon;

  public:
  Resource(map<string, string> attr) : Helper(attr) {
    resourceID = getInt("resourceID");
    name = getString("name");
    importCost = getDouble("importCost");
    exportPrice = getDouble("exportPrice");
    unitCarbon = getDouble("unitCarbon");
  }
  
  Resource(int id, string nm, double impCost, double expPrice, double unitC) : 
    Helper({{"resourceID", to_string(id)}, 
            {"name", nm}, 
            {"importCost", to_string(impCost)}, 
            {"exportPrice", to_string(expPrice)}, 
            {"unitCarbon", to_string(unitC)}}),
    resourceID(id), name(nm), importCost(impCost), 
    exportPrice(expPrice), unitCarbon(unitC) {}
  
  int getResourceID() { return resourceID; }
  string getName() { return name; }
  double getImportCost() { return importCost; }
  double getExportPrice() { return exportPrice; }
  double getUnitCarbon() { return unitCarbon; }
  
  void setResourceID(int id) { resourceID = id; }
  void setName(string n) { name = n; }
  void setImportCost(double cost) { importCost = cost; }
  void setExportPrice(double price) { exportPrice = price; }
  void setUnitCarbon(double carbon) { unitCarbon = carbon; }
};

class Supply : public Helper {
  private:
  int resourceID;
  int regionID;
  double production; 
  double use;

  public:
  Supply(map<string, string> attr) : Helper(attr) {
    resourceID = getInt("resourceID");
    regionID = getInt("regionID");
    production = getDouble("production");
    use = getDouble("use");
  }
  
  Supply(int resID, int regID, double prod, double u) : 
    Helper({{"resourceID", to_string(resID)}, 
            {"regionID", to_string(regID)}, 
            {"production", to_string(prod)}, 
            {"use", to_string(u)}}),
    resourceID(resID), regionID(regID), production(prod), use(u) {}
  
  int getResourceID() { return resourceID; }
  int getRegionID() { return regionID; }
  double getProduction() { return production; }
  double getUse() { return use; }
  
  void setResourceID(int id) { resourceID = id; }
  void setRegionID(int id) { regionID = id; }
  void setProduction(double prod) { production = prod; }
  void setUse(double u) { use = u; }
};