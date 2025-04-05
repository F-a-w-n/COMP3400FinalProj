#ifndef CUSTOMERTAB_H
#define CUSTOMERTAB_H

#include <wx/wx.h>
#include <wx/listctrl.h>

class CustomerTab : public wxPanel {
public:
    CustomerTab(wxWindow* parent);

private:
    wxListCtrl* customerList;

    void LoadData();
    void OnSendEmail(wxCommandEvent&); 
};

#endif
