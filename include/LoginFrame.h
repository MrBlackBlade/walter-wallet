#pragma once

#include <wx/wx.h>
#include "User.h"
#include "Bank.h"

class LoginFrame : public wxFrame {
	private:

		User* user;

		wxPanel* mainPanel;
		wxPanel* midPanel;

		wxPanel* usernameInputPanel;
		wxTextCtrl* usernameBox;

		wxPanel* passwordInputPanel;
		wxTextCtrl* passwordBox;

		//Event handlers

		void onEnterUsername(wxFocusEvent& event);
		void onLeaveUsername(wxFocusEvent& event);

		void onEnterPassword(wxFocusEvent& event);
		void onLeavePassword(wxFocusEvent& event);

		void onLoginClick(wxCommandEvent& event);
		void onRegisterClick(wxCommandEvent& event);

		void onHover(wxMouseEvent& event);
		void onLeaveHover(wxMouseEvent& event);
		void onClose(wxCloseEvent& event);

		void paintTopPanel();
		void paintMidPanel();

	public:

		LoginFrame();

};
