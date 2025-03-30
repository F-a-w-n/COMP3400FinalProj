// sales-and-billing.cpp - original code by Carter Buck and Fawn Barisic - generates a Final Project - Mar 30, 2025

#include <iostream>
#include <fstream>
#include <string>
#include "./dbuser.cpp"

using namespace std;

// Function to calculate sales and billing info.
void calculateSalesAndBillingTXT(int resourceID) {
    try {
        // Retrieves resource information from the database.
        Resource resource = DBUser::getResource(resourceID);

        vector<Region> regions = DBUser::getAllRegions();

        // Creates a filename for the TXT output.
        string filename = "SalesBilling_Resource_" + to_string(resourceID) + ".txt";

        // Opens the file for writing.
        ofstream outfile(filename);

        // Checks if the file was successfully opened.
        if (!outfile.is_open()) {
            throw runtime_error("Failed to open file for writing");
        }

        // Writes resource name to the file.
        outfile << "Sales and Billing Report for Resource: " << resource.getName() << endl;
        outfile << endl;

        // Calculates and writes sales revenue for each bill.
        double totalSalesRevenue = 0.0;
        for (Region region : regions) {
            Supply s = DBUser::getSupply(resourceID, region.getRegionID());
            double revenue = s.getUse() * resource.getExportPrice();
            totalSalesRevenue += revenue;
            outfile << "Region ID: " << region.getRegionID()
                    << ", Quantity: " << s.getUse()
                    << ", Rate: $" << resource.getExportPrice()
                    << ", Revenue: $" << revenue << endl;
        }

        // Writes total sales revenue to the file.
        outfile << endl;
        outfile << "Total Sales Revenue for Resource (" << resource.getName() << "): $" << totalSalesRevenue << endl;

        // Close the output file.
        outfile.close();

        // Displays a message.
        cout << "Sales and billing report generated successfully and saved to " << filename << endl;

    // Catch any runtime errors.
    } catch (const runtime_error& e) {
        cerr << "Error generating sales and billing report: " << e.what() << endl;
    }
}
