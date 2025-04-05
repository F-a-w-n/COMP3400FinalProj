#include "CustomerTab.h"
#include "./invoice-gen.cpp"

CustomerTab::CustomerTab(wxWindow* parent)
    : wxPanel(parent) {
    
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    customerList = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                  wxLC_REPORT | wxLC_HRULES | wxLC_VRULES);

    customerList->InsertColumn(0, "ID", wxLIST_FORMAT_LEFT, 50);
    customerList->InsertColumn(1, "Name", wxLIST_FORMAT_LEFT, 150);
    customerList->InsertColumn(2, "Address", wxLIST_FORMAT_LEFT, 200);
    customerList->InsertColumn(3, "Region", wxLIST_FORMAT_LEFT, 80);

    sizer->Add(customerList, 1, wxEXPAND | wxALL, 10);

    // Add the "Send Email" button
    wxButton* sendBtn = new wxButton(this, wxID_ANY, "Send Reminder Email");
    sizer->Add(sendBtn, 0, wxALIGN_RIGHT | wxALL, 10);
    sendBtn->Bind(wxEVT_BUTTON, &CustomerTab::OnSendEmail, this); 

    SetSizer(sizer);
    LoadData();
}

void CustomerTab::LoadData() {
    customerList->DeleteAllItems();
    std::cout << "[CustomerTab] Loading customer data..." << std::endl;
    vector<Customer> customers = DBUser::getAllCustomers();
    std::cout << "[CustomerTab] Fetched " << customers.size() << " customers" << std::endl;

    for (int i = 0; i < customers.size(); ++i) {
        customerList->InsertItem(i, to_string(customers[i].getCustomerID()));
        customerList->SetItem(i, 1, customers[i].getName());
        customerList->SetItem(i, 2, customers[i].getAddress());
        customerList->SetItem(i, 3, to_string(customers[i].getRegionID()));
    }
}


// Define the event handler
void CustomerTab::OnSendEmail(wxCommandEvent&) {
    long selected = customerList->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    long id;
    if (selected == -1) {
        wxMessageBox("Please select a customer first.");
        return;
    }

    wxString name = customerList->GetItemText(selected);
    name.ToLong(&id);
    std::string email = "karim32@uwindsor.ca";

    bool success = CustomerInvoice::generateInvoiceEmail((int)id, email);

    if (success)
        wxMessageBox("Email sent successfully!");
    else
        wxMessageBox("Failed to send email.");
}
