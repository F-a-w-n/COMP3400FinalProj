// imp-exp-expenses.cpp - original code by Carter Buck and Fawn Barisic - generates a file containing the expense details related with importing and exporting energy resources

#include <iostream>
#include <fstream>
#include <string>
#include "./dbuser.cpp"
#include "./mailsend.cpp"

using namespace std;

class ImportExport {
    public:
    // Function to calculate import/export expenses.
    static string calculateImportExportExpenses(int resourceID) {
        try {
            // Retrieves resource information from the database.
            Resource resource = DBUser::getResource(resourceID);

            // Retrieves expense information for the resource from the database.
            vector<Expense> expenses = DBUser::getExpensesByResource(resourceID);

            // Creates a filename for the TXT output.
            string filename = "ImportExport_Resource_" + to_string(resourceID) + ".txt";

            // Opens the file for writing.
            ofstream outfile(filename);

            // Checks if the file was successfully opened.
            if (!outfile.is_open()) {
                throw runtime_error("Failed to open file for writing");
            }

            // Writes resource details to the file.
            outfile << "Expense Report for Resource: " << resource.getName() << endl;
            outfile << endl;

            // Calculates total import and export expenses.
            double totalImportCost = 0.0, totalExportRevenue = 0.0;
            for (Expense expense : expenses) {
                if (expense.getPurpose() == "Import") {
                    totalImportCost += expense.getAmount();
                } else if (expense.getPurpose() == "Export") {
                    totalExportRevenue += expense.getAmount();
                }
            }

            // Writes import and export totals to the file.
            outfile << "Total Import Cost: $" << totalImportCost << endl;
            outfile << "Total Export Revenue: $" << totalExportRevenue << endl;

            // Close the output file.
            outfile.close();

            // Displays a message.
            cout << "Import/Export expenses report generated successfully and saved to " << filename << endl;
            return filename;
        // Catch any runtime errors.
        } catch (const runtime_error& e) {
            cerr << "Error generating import/export expenses report: " << e.what() << endl;
            return ""s;
        }
    }

    static bool calculateImportExportEmail(int resourceID, string email) {
        string filename = calculateImportExportExpenses(resourceID);
        return MailSend::send_email_with_attachment(email, "Powerplex Import/Export Report", "Hello,\n\nWe are sending you this email to inform you of current expenses related to importing and exporting energy products. Please review the attached report at your earliest convenience.\n\nBest regards,\nThe PowerPlex Team", filename);
    }
};