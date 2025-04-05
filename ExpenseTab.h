#ifndef EXPENSE_TAB_H
#define EXPENSE_TAB_H

#include <wx/wx.h>
#include <wx/listctrl.h>

class ExpenseTab : public wxPanel {
public:
    ExpenseTab(wxWindow* parent);
    void LoadData();

private:
    wxListCtrl* expenseList;
};

#endif
