// invoice-gen.cpp - original code by Carter Buck and Fawn Barisic - generates an invoice for a given customer based on their owed bills

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

// Function to generate invoices.
class CustomerInvoice {
  public:
  static string generateInvoice(int customerID) {
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

      const double interest_rate = 1.1;
      time_t timestamp = time(&timestamp);
      struct tm date = *localtime(&timestamp);
      Date today = *new Date(date.tm_year+1900, date.tm_mon+1, date.tm_mday);

      // Writes customer information to the file.
      outfile << "Invoice for Customer: " << customer.getName() << endl;
      outfile << "Address: " << customer.getAddress() << endl;
      outfile << endl;

      // Writes bill details to the file.
      double totalDue = 0.0;
      for (Bill bill : bills) {
        double dueAmount = bill.getQuantity() * bill.getRate() - bill.getPaidAmount();
        double dueinterest = dueAmount;
        int monthsdue = today.getMonth() - bill.getDate().getMonth();
        monthsdue += (today.getYear() - bill.getDate().getYear()) * 12;
        if (monthsdue > 1) {
          for (int i = 0; i<monthsdue; i++) {
            dueinterest*=interest_rate;
          }
        }
        totalDue += dueinterest;
        dueinterest-=dueAmount;
        if (dueinterest > 0) {
          outfile << "Bill ID: " << bill.getBillID()
            << ", Due Amount: $" << dueAmount
            << ", Due Interest: $" << dueinterest
            << ", Total Due: $" << dueAmount+dueinterest
            << ", Date: " << bill.getDate().toString() << endl;
        } else {
          outfile << "Bill ID: " << bill.getBillID()
            << ", Due Amount: $" << dueAmount
            << ", Total Due: $" << dueAmount
            << ", Date: " << bill.getDate().toString() << endl;
        }
      }

      // Writes the total amounts due to the file.
      outfile << endl;
      outfile << "Total Due: $" << totalDue << endl;

      // Close the output file.
      outfile.close();

      // Displays a message.
      cout << "Invoice generated successfully and saved to " << filename << endl;
      return filename;
      // Catch any runtime errors.
    } catch (const runtime_error& e) {
      cerr << "Error generating invoice: " << e.what() << endl;
      return ""s;
    }
  }
  static bool generateInvoiceEmail(int customerID, string email) {
    string filename = generateInvoice(customerID);
    return MailSend::send_email_with_attachment(email, "Powerplex bill due", "Hello,\n\nWe are sending you this email to remind you of your due electrical bill. Please review the attached bill and send payment at your earliest convenience.\n\nBest regards,\nThe PowerPlex Team", filename);
  }
};