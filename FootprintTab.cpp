#include "FootprintTab.h"
#include "./dbuser.cpp"  // access to DBUser and Footprint

FootprintTab::FootprintTab(wxWindow* parent)
    : wxPanel(parent) {
    
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    footprintList = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                   wxLC_REPORT | wxLC_HRULES | wxLC_VRULES);

    footprintList->InsertColumn(0, "Customer ID", wxLIST_FORMAT_LEFT, 100);
    footprintList->InsertColumn(1, "Resource ID", wxLIST_FORMAT_LEFT, 100);
    footprintList->InsertColumn(2, "Amount", wxLIST_FORMAT_LEFT, 100);
    footprintList->InsertColumn(3, "Total Carbon", wxLIST_FORMAT_LEFT, 120);

    sizer->Add(footprintList, 1, wxEXPAND | wxALL, 10);
    SetSizer(sizer);

    LoadData();
}

void FootprintTab::LoadData() {
    footprintList->DeleteAllItems();
    std::cout << "[FootprintTab] Loading footprint data..." << std::endl;
    vector<Footprint> footprints = DBUser::getAllFootprints();
    std::cout << "[FootprintTab] Fetched " << footprints.size() << " footprints" << std::endl;

    for (int i = 0; i < footprints.size(); ++i) {
        footprintList->InsertItem(i, to_string(footprints[i].getCustomerID()));
        footprintList->SetItem(i, 1, to_string(footprints[i].getResourceID()));
        footprintList->SetItem(i, 2, to_string(footprints[i].getAmount()));
        footprintList->SetItem(i, 3, to_string(footprints[i].getTotalCarbon()));
    }
}

