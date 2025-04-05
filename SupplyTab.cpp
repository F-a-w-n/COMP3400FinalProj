#include "SupplyTab.h"
#include "./dbuser.cpp"

SupplyTab::SupplyTab(wxWindow* parent)
    : wxPanel(parent) {
    
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    supplyList = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                wxLC_REPORT | wxLC_HRULES | wxLC_VRULES);

    supplyList->InsertColumn(0, "Resource ID", wxLIST_FORMAT_LEFT, 100);
    supplyList->InsertColumn(1, "Region ID", wxLIST_FORMAT_LEFT, 100);
    supplyList->InsertColumn(2, "Production", wxLIST_FORMAT_LEFT, 120);
    supplyList->InsertColumn(3, "Use", wxLIST_FORMAT_LEFT, 100);

    sizer->Add(supplyList, 1, wxEXPAND | wxALL, 10);
    SetSizer(sizer);

    LoadData();
}

void SupplyTab::LoadData() {
    supplyList->DeleteAllItems();
    std::cout << "[SupplyTab] Loading supply data..." << std::endl;
    vector<Supply> supplies = DBUser::getAllSupplies();
    std::cout << "[SupplyTab] Fetched " << supplies.size() << " supplies" << std::endl;

    for (int i = 0; i < supplies.size(); ++i) {
        supplyList->InsertItem(i, to_string(supplies[i].getResourceID()));
        supplyList->SetItem(i, 1, to_string(supplies[i].getRegionID()));
        supplyList->SetItem(i, 2, to_string(supplies[i].getProduction()));
        supplyList->SetItem(i, 3, to_string(supplies[i].getUse()));
    }
}

