// invoice-gen.cpp - original code by Carter Buck and Fawn Barisic - generates an invoice for a given customer based on their owed bills

#include <iostream>
#include <fstream>
#include <string>
#include "./dbuser.cpp"

// Function to generate invoices.
void generateInvoice(int customerID) {
    try {
        // Retrieves customer information from the database.
        Customer customer = DBUser::getCustomer(customerID);

        // Retrieves billing information for the customer.
        vector<Bill> bills = DBUser::getBillsByCustomer(customerID);

        // Creates a filename for the TXT output.
        string filename = "Invoice_Customer_" + to_string(customerID) + ".txt";

        // Opens the file for writing.
        ofstream outfile(filename);

        // Checks if the file was successfully opened.
        if (!outfile.is_open()) {
            throw runtime_error("Failed to open file for writing");
        }

        // Writes customer information to the file.
        outfile << "Invoice for Customer: " << customer.getName() << endl;
        outfile << "Address: " << customer.getAddress() << endl;
        outfile << endl;

        // Writes bill details to the file.
        double totalDue = 0.0;
        for (Bill bill : bills) {
            double dueAmount = bill.getQuantity() * bill.getRate() - bill.getPaidAmount();
            totalDue += dueAmount;
            outfile << "Bill ID: " << bill.getBillID()
                    << ", Due Amount: $" << dueAmount
                    << ", Date: " << bill.getDate().toString() << endl;
        }

        // Writes the total amounts due to the file.
        outfile << endl;
        outfile << "Total Due: $" << totalDue << endl;

        // Close the output file.
        outfile.close();

        // Displays a message.
        cout << "Invoice generated successfully and saved to " << filename << endl;

    // Catch any runtime errors.
    } catch (const runtime_error& e) {
        cerr << "Error generating invoice: " << e.what() << endl;
    }
}