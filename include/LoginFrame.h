#pragma once

#include <wx/wx.h>

class LoginFrame : public wxFrame {
public:
	LoginFrame(const wxString& title);

private:
	wxTextCtrl* usernameTextBox;
	wxTextCtrl* passwordTextBox;
	wxButton* loginButton;
};
