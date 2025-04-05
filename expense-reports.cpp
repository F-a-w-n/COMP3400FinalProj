// expensereports.cpp - original code by Carter Buck and Fawn Barisic - generates a file with an expense report for a given resource
#include <iostream>
#include <fstream>
#include <string>
#include "./dbuser.cpp"
#include "./mailsend.cpp"

using namespace std;

class ExpenseReport {
    public:
    // Function to generate expense reports.
    static string generateExpenseReport() {
        try {
            // Retrieves all resources from the database.
            vector<Resource> resources = DBUser::getAllResources();

            // Creates a filename for the TXT output.
            string filename = "ExpenseReport.txt";

            // Opens the file for writing.
            ofstream outfile(filename);

            // Checks if the file was successfully opened.
            if (!outfile.is_open()) {
                throw runtime_error("Failed to open file for writing");
            }

            // Loops through each resource and writes its expenses to the file.
            for (Resource resource : resources) {
                // Retrieves expenses for the current resource.
                vector<Expense> expenses = DBUser::getExpensesByResource(resource.getResourceID());

                // Writes the resource name to the file.
                outfile << "Expense Report for Resource: " << resource.getName() << endl;

                // Calculates the total expenses for the resource.
                double totalExpenses = 0.0;
                for (Expense expense : expenses) {
                    outfile << "Expense ID: " << expense.getExpID()
                            << ", Purpose: " << expense.getPurpose()
                            << ", Amount: $" << expense.getAmount()
                            << ", Date: " << expense.getDate().toString() << endl;
                    totalExpenses += expense.getAmount();
                }

                // Writes the total expenses to the file.
                outfile << "Total Expenses for Resource (" << resource.getName() << "): $" << totalExpenses << endl;
                outfile << endl;
            }

            // Close the output file.
            outfile.close();

            // Displays a message.
            cout << "Expense report generated successfully and saved to " << filename << endl;
            return filename;
        // Catch any runtime errors.
        } catch (const runtime_error& e) {
            cerr << "Error generating expense report: " << e.what() << endl;
            return ""s;
        }
    }

    static bool emailExpenseReport(string email) {
        string filename = generateExpenseReport();
        return MailSend::send_email_with_attachment(email, "Powerplex expense report", "Hello,\n\nWe are sending you this email to inform you of the operating expenses involved in energy generation. Please review the attached report at your earliest convenience.\n\nBest regards,\nThe PowerPlex Team", filename);
    }
};