#ifndef FOOTPRINT_TAB_H
#define FOOTPRINT_TAB_H

#include <wx/wx.h>
#include <wx/listctrl.h>

class FootprintTab : public wxPanel {
public:
    FootprintTab(wxWindow* parent);
    void LoadData();

private:
    wxListCtrl* footprintList;
};

#endif
