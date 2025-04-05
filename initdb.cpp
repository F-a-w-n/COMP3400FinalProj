#include "database.cpp"

int main() {
    // Create tables if they don't exist
    Database::runCommand("CREATE TABLE IF NOT EXISTS REGION( regionID INT NOT NULL, revenue DOUBLE, production DOUBLE, use DOUBLE, PRIMARY KEY (regionID) );");
    Database::runCommand("CREATE TABLE IF NOT EXISTS CUSTOMER( customerID INT NOT NULL, name VARCHAR(20), address VARCHAR(30), regionID INT, PRIMARY KEY (customerID), FOREIGN KEY (regionID) REFERENCES REGION(regionID) );");
    Database::runCommand("CREATE TABLE IF NOT EXISTS RESOURCE( resourceID INT NOT NULL, name VARCHAR(15), importCost DOUBLE, exportPrice DOUBLE, unitCarbon DOUBLE, PRIMARY KEY (resourceID) );");
    Database::runCommand("CREATE TABLE IF NOT EXISTS BILL( customerID INT NOT NULL, billID INT NOT NULL, quantity DOUBLE, rate DOUBLE, paidAmount DOUBLE, date VARCHAR(10), lastNotified VARCHAR(10), PRIMARY KEY (customerID, billID), FOREIGN KEY (customerID) REFERENCES CUSTOMER(customerID) );");
    Database::runCommand("CREATE TABLE IF NOT EXISTS EXPENSE( resourceID INT NOT NULL, expID INT NOT NULL, purpose VARCHAR(30), amount DOUBLE, date VARCHAR(10), PRIMARY KEY (resourceID, expID), FOREIGN KEY (resourceID) REFERENCES RESOURCE(resourceID) );");
    Database::runCommand("CREATE TABLE IF NOT EXISTS FOOTPRINT( customerID INT NOT NULL, resourceID INT NOT NULL, amount DOUBLE, totalCarbon DOUBLE, PRIMARY KEY (customerID, resourceID), FOREIGN KEY (customerID) REFERENCES CUSTOMER(customerID), FOREIGN KEY (resourceID) REFERENCES RESOURCE(resourceID));");
    Database::runCommand("CREATE TABLE IF NOT EXISTS SUPPLY( resourceID INT NOT NULL, regionID INT NOT NULL, production DOUBLE, use DOUBLE, PRIMARY KEY (resourceID, regionID), FOREIGN KEY (resourceID) REFERENCES RESOURCE(resourceID), FOREIGN KEY (regionID) REFERENCES REGION(regionID));");

    // Seed with test data
    Database::runCommand("INSERT OR IGNORE INTO REGION VALUES (1, 150000.0, 80000.0, 75000.0);");
    Database::runCommand("INSERT OR IGNORE INTO CUSTOMER VALUES (1, 'Jane Doe', '42 Windy Way', 1);");
    Database::runCommand("INSERT OR IGNORE INTO RESOURCE VALUES (1, 'Solar', 200.0, 300.0, 0.01);");
    Database::runCommand("INSERT OR IGNORE INTO BILL VALUES (1, 1, 100.0, 2.5, 50.0, '2024-01-01', '2024-03-01');");
    Database::runCommand("INSERT OR IGNORE INTO EXPENSE VALUES (1, 1, 'Import', 1200.0, '2024-02-15');");
    Database::runCommand("INSERT OR IGNORE INTO FOOTPRINT VALUES (1, 1, 500.0, 5.0);");
    Database::runCommand("INSERT OR IGNORE INTO SUPPLY VALUES (1, 1, 100000.0, 95000.0);");

    printf("✅ Database initialized and seeded.\n");
    return 0;
}
