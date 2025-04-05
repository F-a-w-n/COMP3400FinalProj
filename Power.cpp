// cd /e/Documents/UWindsor\ Docs/COMP\ 3400\ -\ Adv\ Object\ Oriented\ Using\ C++/Project

#include <wx/wx.h>
#include <wx/notebook.h>
#include "CustomerTab.h"
#include "FootprintTab.h"
#include "SupplyTab.h"
#include "ExpenseTab.h"

// Theme colours
wxColour darkBg(30, 33, 36);
wxColour accent(0, 174, 239);
wxColour lightText(230, 230, 230);

// ────────────────────────────────
// Login Frame
class LoginFrame : public wxFrame {
public:
    LoginFrame() : wxFrame(nullptr, wxID_ANY, "Login Page", wxDefaultPosition, wxSize(400, 300)) {
        wxPanel* panel = new wxPanel(this);
        panel->SetBackgroundColour(darkBg);
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

        wxStaticText* title = new wxStaticText(panel, wxID_ANY, "WELCOME TO");
        title->SetFont(wxFontInfo(25).Bold());
        title->SetForegroundColour(accent);
        sizer->Add(title, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 40);

        wxBitmap logoBitmap("PowerplexLogo.png", wxBITMAP_TYPE_PNG);
        if (!logoBitmap.IsOk()) {
            wxMessageBox("Failed to load PowerplexLogo.png", "Image Error", wxOK | wxICON_ERROR);
        }
        
        wxBitmapButton* logoBtn = new wxBitmapButton(panel, wxID_ANY, logoBitmap);
        logoBtn->SetMinSize(wxSize(180, 180)); 
        logoBtn->SetBackgroundColour(darkBg);
        logoBtn->SetWindowStyle(wxBORDER_NONE);
        logoBtn->SetCursor(wxCursor(wxCURSOR_HAND)); 
        logoBtn->Bind(wxEVT_BUTTON, &LoginFrame::OnLogin, this);
        sizer->Add(logoBtn, 0, wxALIGN_CENTER | wxALL, 10);

        panel->SetSizer(sizer);
    }

    void OnLogin(wxCommandEvent&);
};

// ────────────────────────────────
// Main Menu Frame
class MainMenuFrame : public wxFrame {
public:
    MainMenuFrame() : wxFrame(nullptr, wxID_ANY, "PowerPlex - Main Menu", wxDefaultPosition, wxSize(500, 400)) {
        wxPanel* panel = new wxPanel(this);
        panel->SetBackgroundColour(darkBg);
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

        wxStaticText* title = new wxStaticText(panel, wxID_ANY, "Choose Energy Type");
        title->SetFont(wxFontInfo(16).Bold());
        title->SetForegroundColour(lightText);
        sizer->Add(title, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 20);

        wxString energyTypes[] = { "Crude Oil", "Solar", "Nuclear", "Natural Gas" };
        for (auto& type : energyTypes) {
            wxButton* btn = new wxButton(panel, wxID_ANY, type);
            btn->SetMinSize(wxSize(220, 40));
            btn->SetFont(wxFontInfo(11));
            btn->SetBackgroundColour(accent);
            btn->SetForegroundColour(*wxWHITE);
            btn->Bind(wxEVT_BUTTON, &MainMenuFrame::OnEnergyButton, this);
            sizer->Add(btn, 0, wxALIGN_CENTER | wxALL, 10);
        }

        panel->SetSizer(sizer);
    }

    void OnEnergyButton(wxCommandEvent&);
};

// ────────────────────────────────
// Info Page Frame with Tabs    
class InfoPageFrame : public wxFrame {  
public:
    InfoPageFrame(const wxString& resource)
        : wxFrame(nullptr, wxID_ANY, resource + " Info", wxDefaultPosition, wxSize(800, 600)) {
        
        wxPanel* panel = new wxPanel(this);
        panel->SetBackgroundColour(darkBg);
        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

        wxNotebook* notebook = new wxNotebook(panel, wxID_ANY);
        notebook->AddPage(new CustomerTab(notebook), "Customer Details and Billing");
        notebook->AddPage(new FootprintTab(notebook), "Customer Footprints");
        notebook->AddPage(new SupplyTab(notebook), "Energy Use and Supply Tracker");
        notebook->AddPage(new ExpenseTab(notebook), "Expense Reports");

        wxButton* backBtn = new wxButton(panel, wxID_ANY, "Back to Main Menu");
        backBtn->SetMinSize(wxSize(180, 35));
        backBtn->SetFont(wxFontInfo(11));
        backBtn->SetBackgroundColour(wxColour(80, 80, 80));
        backBtn->SetForegroundColour(lightText);

        mainSizer->Add(notebook, 1, wxEXPAND | wxALL, 10);
        mainSizer->Add(backBtn, 0, wxALIGN_CENTER | wxBOTTOM, 15);
        panel->SetSizer(mainSizer);

        backBtn->Bind(wxEVT_BUTTON, &InfoPageFrame::OnBack, this);
    }

private:
    void OnBack(wxCommandEvent&) {
        MainMenuFrame* menu = new MainMenuFrame();
        menu->Show();
        this->Close();
    }
};

// ────────────────────────────────
// Event Handlers
void LoginFrame::OnLogin(wxCommandEvent&) {
    MainMenuFrame* menu = new MainMenuFrame();
    menu->Show();
    this->Close();
}

void MainMenuFrame::OnEnergyButton(wxCommandEvent& event) {
    wxString label = dynamic_cast<wxButton*>(event.GetEventObject())->GetLabel();
    InfoPageFrame* info = new InfoPageFrame(label);
    info->Show();
    this->Close();
}

// ────────────────────────────────
// wxApp Entry Point
class MyApp : public wxApp {
public:
    bool OnInit() override {
        wxInitAllImageHandlers();
        std::cout << "GUI launched. Showing main window..." << std::endl;
        LoginFrame* login = new LoginFrame();
        login->Show();
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
