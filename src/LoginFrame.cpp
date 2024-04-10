#include "LoginFrame.h"

LoginFrame::LoginFrame(const wxString & title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition) {

    wxPanel* panel = new wxPanel(this, wxID_ANY);
    panel->SetBackgroundColour(wxColour(240, 240, 240));

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* usernameLabel = new wxStaticText(panel, wxID_ANY, wxT("Username:"));
    usernameTextBox = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);

    wxStaticText* passwordLabel = new wxStaticText(panel, wxID_ANY, wxT("Password:"));
    passwordTextBox = new wxTextCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD | wxTE_PROCESS_ENTER);

    loginButton = new wxButton(panel, wxID_ANY, wxT("Login"));
    loginButton->SetBackgroundColour(wxColour(50, 150, 255));
    loginButton->SetForegroundColour(*wxWHITE);

    mainSizer->Add(usernameLabel, 0, wxALL | wxEXPAND, 5);
    mainSizer->Add(usernameTextBox, 0, wxALL | wxEXPAND, 5);
    mainSizer->Add(passwordLabel, 0, wxALL | wxEXPAND, 5);
    mainSizer->Add(passwordTextBox, 0, wxALL | wxEXPAND, 5);
    mainSizer->Add(loginButton, 0, wxALL | wxALIGN_CENTER, 5);

    panel->SetSizer(mainSizer);
    mainSizer->Fit(this);
}
