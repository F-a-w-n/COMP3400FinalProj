#include "ExpenseTab.h"
#include "./dbuser.cpp"

ExpenseTab::ExpenseTab(wxWindow* parent)
    : wxPanel(parent) {
    
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    expenseList = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                 wxLC_REPORT | wxLC_HRULES | wxLC_VRULES);

    expenseList->InsertColumn(0, "Resource ID", wxLIST_FORMAT_LEFT, 100);
    expenseList->InsertColumn(1, "Expense ID", wxLIST_FORMAT_LEFT, 100);
    expenseList->InsertColumn(2, "Purpose", wxLIST_FORMAT_LEFT, 150);
    expenseList->InsertColumn(3, "Amount", wxLIST_FORMAT_LEFT, 100);
    expenseList->InsertColumn(4, "Date", wxLIST_FORMAT_LEFT, 120);

    sizer->Add(expenseList, 1, wxEXPAND | wxALL, 10);
    SetSizer(sizer);

    LoadData();
}

void ExpenseTab::LoadData() {
    expenseList->DeleteAllItems();
    std::cout << "[ExpenseTab] Loading expense data..." << std::endl;
    vector<Resource> resources = DBUser::getAllResources();
    std::cout << "[ExpenseTab] Found " << resources.size() << " resources" << std::endl;

    int index = 0;
    for (const auto& resource : resources) {
        vector<Expense> expenses = DBUser::getExpensesByResource(resource.getResourceID());
        std::cout << "  Resource ID " << resource.getResourceID() << ": " << expenses.size() << " expenses" << std::endl;

        for (const auto& e : expenses) {
            expenseList->InsertItem(index, to_string(e.getResourceID()));
            expenseList->SetItem(index, 1, to_string(e.getExpID()));
            expenseList->SetItem(index, 2, e.getPurpose());
            expenseList->SetItem(index, 3, to_string(e.getAmount()));
            expenseList->SetItem(index, 4, e.getDate().toString());
            ++index;
        }
    }
}

