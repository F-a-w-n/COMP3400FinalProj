// textUI.cpp - original code by Fawn Barisic - a text based UI as an alternative to the graphical user interface
#include <iostream>
#include <stdio.h>
#include <string>

#include "./dbuser.cpp"
#include "./mailsend.cpp"
#include "./expense-reports.cpp"
#include "./imp-exp-expenses.cpp"
#include "./invoice-gen.cpp"
#include "./sales-and-billing.cpp"

using namespace std;

class UserMethods {
  public:
  static int promptForID(string idname) {
    cout << "Please enter the " << idname << endl;
    int id;
    cin >> id;
    return id;
  }
  static string promptForEmail() {
    cout << "Please enter the email to send this document to"<< endl;
    string email;
    cin >> email;
    return email;
  }

  static void outputCustomerFootprint(int customerID) {
    vector<Footprint> footprints = DBUser::getFootprintsByCustomer(customerID);
    cout << "Footprints for customer ID " << customerID << endl;
    for (Footprint f : footprints) {
      fprintf(stdout, "Footprint for %s: \n\tTotal amount: %d kwh\n\tTotal Carbon: %dg\n\n", DBUser::getResource(f.getResourceID()).getName().c_str(), f.getAmount(), f.getTotalCarbon());
    }
  }

  static void outputResourceDetails(int resourceID) {
    Resource r = DBUser::getResource(resourceID);
    fprintf(stdout, "Details for resource %s:\n\tImport Cost: $%.2f/kwh\n\tExport Price: $%.2f/kwh\n\tCarbon per kwh: %f\n", r.getName().c_str(), r.getImportCost(), r.getExportPrice(), r.getUnitCarbon());
  }

  static void outputCustomerDetails(int customerID) {
    Customer c = DBUser::getCustomer(customerID);
    fprintf(stdout, "Customer ID %d: %s\n\tAddress: %s\n\tRegion: %d\n", c.getCustomerID(), c.getName().c_str(), c.getAddress().c_str(), c.getRegionID());
  }

  static void outputTotalSales(int regionID) {
    Region r = DBUser::getRegion(regionID);
    fprintf(stdout, "Sales for region %d:\n\tTotal revenue: $%.2f\n\tTotal production: %f\n\tTotal use: %f\n", r.getRegionID(), r.getRevenue(), r.getProduction(), r.getUse());
  }

  static void outputCustomerBills(int customerID) {
    vector<Bill> bills = DBUser::getBillsByCustomer(customerID);
    cout << "Bills for customer ID " << customerID << endl;
    for (Bill b : bills) {
      fprintf(stdout, "bill ID %d: \n\tQuantity: %fkwh\n\tRate: $%.2f\n\tCurrently Paid: $%.2f\n\tDate due: %s\n\tLast Notified: %s\n", b.getBillID(), b.getQuantity(), b.getRate(), b.getPaidAmount(), b.getDate().toString().c_str(), b.getLastNotified().toString().c_str());
    }
  }

  static void outputResourceExpenses(int resourceID) {
    vector<Expense> expenses = DBUser::getExpensesByResource(resourceID);
    cout << "Expenses for resource ID " << resourceID << endl;
    for (Expense e : expenses) {
      fprintf(stdout, "%s: $%.2f - %s\n", e.getPurpose().c_str(), e.getAmount(), e.getDate().toString().c_str());
    }
  }

  static void outputRegionSupplies(int regionID) {
    vector<Supply> supplies = DBUser::getSuppliesByRegion(regionID);
    cout << "Resource supplies for region ID " << regionID << endl;
    for (Supply s : supplies) {
      fprintf(stdout, "Resource ID %d: Production - %f, use - %f\n", s.getResourceID(), s.getProduction(), s.getUse());
    }
  }

  static void listCustomers() {
    vector<Customer> customers = DBUser::getAllCustomers();
    for (Customer c : customers) {
      outputCustomerDetails(c.getCustomerID());
    }
  }

  static void listRegions() {
    vector<Region> regions = DBUser::getAllRegions();
    for (Region r : regions) {
      outputTotalSales(r.getRegionID());
    }
  }

  static void listBills() {
    vector<Customer> customers = DBUser::getAllCustomers();
    for (Customer c : customers) {
      outputCustomerBills(c.getCustomerID());
    }
  }

  static void listExpenses() {
    vector<Resource> resources = DBUser::getAllResources();
    for (Resource r : resources) {
      outputResourceExpenses(r.getResourceID());
    }
  }

  static void listFootprints() {
    vector<Customer> customers = DBUser::getAllCustomers();
    for (Customer c : customers) {
      outputCustomerFootprint(c.getCustomerID());
    }
  }

  static void listResources() {
    vector<Resource> resources = DBUser::getAllResources();
    for (Resource r : resources) {
      outputResourceDetails(r.getResourceID());
    }
  }

  static void listSupplies() {
    vector<Region> regions = DBUser::getAllRegions();
    for(Region r : regions) {
      outputRegionSupplies(r.getRegionID());
    }
  }

  static int getIntInput(const string& prompt) {
    int value;
    cout << prompt;
    cin >> value;
    return value;
  }

  static double getDoubleInput(const string& prompt) {
    double value;
    cout << prompt;
    cin >> value;
    return value;
  }

  // Helper function to get string input
  static string getStringInput(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
  }
  
  static void makeCustomer() {
    cout << "Enter customer details:" << endl;
    int customerID = getIntInput("Customer ID: ");
    getchar();
    string name = getStringInput("Name: ");
    string address = getStringInput("Address: ");
    int regionID = getIntInput("Region ID: ");
    
    Customer customer({{"customerID", to_string(customerID)}, 
                      {"name", name}, 
                      {"address", address}, 
                      {"regionID", to_string(regionID)}});
    DBUser::createCustomer(&customer);
  }

  static void makeRegion() {
    cout << "Enter region details:" << endl;
    int regionID = getIntInput("Region ID: ");
    double revenue = getDoubleInput("Revenue: ");
    double production = getDoubleInput("Production: ");
    double use = getDoubleInput("Use: ");
    
    Region region({{"regionID", to_string(regionID)}, 
                  {"revenue", to_string(revenue)}, 
                  {"production", to_string(production)}, 
                  {"use", to_string(use)}});
    DBUser::createRegion(&region);
  }

  static void makeBill() {
    cout << "Enter bill details:" << endl;
    int customerID = getIntInput("Customer ID: ");
    int billID = getIntInput("Bill ID: ");
    double quantity = getDoubleInput("Quantity: ");
    double rate = getDoubleInput("Rate: ");
    double paidAmount = getDoubleInput("Paid Amount: ");
    getchar();
    Date date = *new Date(getStringInput("Bill Date: "));
    Date lastNotified = *new Date(getStringInput("Last Notified Date: "));
    
    Bill bill({{"customerID", to_string(customerID)}, 
              {"billID", to_string(billID)}, 
              {"quantity", to_string(quantity)}, 
              {"rate", to_string(rate)}, 
              {"paidAmount", to_string(paidAmount)}, 
              {"date", date.toString()}, 
              {"lastNotified", lastNotified.toString()}});
    DBUser::createBill(&bill);
  }

  static void makeExpense() {
    cout << "Enter expense details:" << endl;
    int resourceID = getIntInput("Resource ID: ");
    int expID = getIntInput("Expense ID: ");
    getchar();
    string purpose = getStringInput("Purpose: ");
    double amount = getDoubleInput("Amount: ");
    getchar();
    Date date = *new Date(getStringInput("Expense Date: "));
    
    Expense expense({{"resourceID", to_string(resourceID)}, 
                    {"expID", to_string(expID)}, 
                    {"purpose", purpose}, 
                    {"amount", to_string(amount)}, 
                    {"date", date.toString()}});
    DBUser::createExpense(&expense);
  }

  static void makeResource() {
    cout << "Enter resource details:" << endl;
    int resourceID = getIntInput("Resource ID: ");
    getchar();
    string name = getStringInput("Name: ");
    double importCost = getDoubleInput("Import Cost: ");
    double exportPrice = getDoubleInput("Export Price: ");
    double unitCarbon = getDoubleInput("Unit Carbon: ");
    
    Resource resource({{"resourceID", to_string(resourceID)}, 
                      {"name", name}, 
                      {"importCost", to_string(importCost)}, 
                      {"exportPrice", to_string(exportPrice)}, 
                      {"unitCarbon", to_string(unitCarbon)}});
    DBUser::createResource(&resource);
  }

  static void makeFootprint() {
    cout << "Enter carbon footprint details:" << endl;
    int customerID = getIntInput("Customer ID: ");
    int resourceID = getIntInput("Resource ID: ");
    double amount = getDoubleInput("Amount: ");
    double totalcarbon = getDoubleInput("Total Carbon: ");
    
    Footprint footprint({{"customerID", to_string(customerID)}, 
                        {"resourceID", to_string(resourceID)}, 
                        {"amount", to_string(amount)}, 
                        {"totalCarbon", to_string(totalcarbon)}});
    DBUser::createFootprint(&footprint);
  }

  static void makeSupply() {
    cout << "Enter supply details:" << endl;
    int resourceID = getIntInput("Resource ID: ");
    int regionID = getIntInput("Region ID: ");
    double production = getDoubleInput("Production: ");
    double use = getDoubleInput("Use: ");
    
    Supply supply({{"resourceID", to_string(resourceID)}, 
                  {"regionID", to_string(regionID)}, 
                  {"production", to_string(production)}, 
                  {"use", to_string(use)}});
    DBUser::createSupply(&supply);
  }

  static void optionPrompt() {
    cout << "1) customer footprint" << endl;
    cout << "2) resource details" << endl;
    cout << "3) customer details" << endl;
    cout << "4) total sales" << endl;
    cout << "5) customer bills" << endl;
    cout << "6) expenses by resource" << endl;
    cout << "7) supplies by region" << endl;
    cout << "8) customers list" << endl;
    cout << "9) region list" << endl;
    cout << "10) bills list" << endl;
    cout << "11) expenses list" << endl;
    cout << "12) footprint list" << endl;
    cout << "13) resource list" << endl;
    cout << "14) supply list" << endl;
    cout << "15) expense report" << endl;
    cout << "16) email expense report" << endl;
    cout << "17) import/export report" << endl;
    cout << "18) email import/export report" << endl;
    cout << "19) customer invoice" << endl;
    cout << "20) email customer invoice" << endl;
    cout << "21) sales report" << endl;
    cout << "22) email sales report" << endl;
    cout << "23) make new customer" << endl;
    cout << "24) make new region" << endl;
    cout << "25) make new bill" << endl;
    cout << "26) make new expense" << endl;
    cout << "27) make new resource" << endl;
    cout << "28) make new footprint" << endl;
    cout << "29) make new supply" << endl;
  
    cout << "-1) exit" << endl;
  }
};

int main() {
  int option;
  while (1) {
    UserMethods::optionPrompt();
    cin >> option;
    switch (option) {
      case -1:
        return 0;
      case 1:
        UserMethods::outputCustomerFootprint(UserMethods::promptForID("Customer ID"));
      break;
      case 2:
        UserMethods::outputResourceDetails(UserMethods::promptForID("Resource ID"));
        break;
      case 3:
        UserMethods::outputCustomerDetails(UserMethods::promptForID("Customer ID"));
        break;
      case 4:
        UserMethods::outputTotalSales(UserMethods::promptForID("Region ID"));
        break;
      case 5:
        UserMethods::outputCustomerBills(UserMethods::promptForID("customer ID"));
        break;
      case 6:
        UserMethods::outputResourceExpenses(UserMethods::promptForID("Resource ID"));
        break;
      case 7:
        UserMethods::outputRegionSupplies(UserMethods::promptForID("Region ID"));
        break;
      case 8:
        UserMethods::listCustomers();
        break;
      case 9:
        UserMethods::listRegions();
        break;
      case 10:
        UserMethods::listBills();
        break;
      case 11:
        UserMethods::listExpenses();
        break;
      case 12:
        UserMethods::listFootprints();
        break;
      case 13:
        UserMethods::listResources();
        break;
      case 14:
        UserMethods::listSupplies();
        break;
      case 15:
        ExpenseReport::generateExpenseReport();
        break;
      case 16:
        ExpenseReport::emailExpenseReport(UserMethods::promptForEmail());
        break;
      case 17:
        ImportExport::calculateImportExportExpenses(UserMethods::promptForID("Resource ID"));
        break;
      case 18:
        ImportExport::calculateImportExportEmail(UserMethods::promptForID("Resource ID"), UserMethods::promptForEmail());
        break;
      case 19:
        CustomerInvoice::generateInvoice(UserMethods::promptForID("Customer ID"));
        break;
      case 20:
        CustomerInvoice::generateInvoiceEmail(UserMethods::promptForID("Customer ID"), UserMethods::promptForEmail());
        break;
      case 21:
        SalesReport::calculateSalesBilling(UserMethods::promptForID("Resource ID"));
        break;
      case 22:
        SalesReport::calculateSalesBillingEmail(UserMethods::promptForID("Resource ID"), UserMethods::promptForEmail());
        break;
      case 23:
        UserMethods::makeCustomer();
        break;
      case 24:
        UserMethods::makeRegion();
        break;
      case 25:
        UserMethods::makeBill();
        break;
      case 26:
        UserMethods::makeExpense();
        break;
      case 27:
        UserMethods::makeResource();
        break;
      case 28:
        UserMethods::makeFootprint();
        break;
      case 29:
        UserMethods::makeSupply();
        break;
      default:
        cout << "Invalid option selected" << endl;
    }
    cin.get();cin.get();
  }
}