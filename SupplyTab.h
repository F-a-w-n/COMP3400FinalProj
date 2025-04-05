#ifndef SUPPLY_TAB_H
#define SUPPLY_TAB_H

#include <wx/wx.h>
#include <wx/listctrl.h>

class SupplyTab : public wxPanel {
public:
    SupplyTab(wxWindow* parent);
    void LoadData();

private:
    wxListCtrl* supplyList;
};

#endif
