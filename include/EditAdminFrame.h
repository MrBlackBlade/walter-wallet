#pragma once

#include <wx/wx.h>
#include "User.h"
#include "Bank.h"
#include "Validation.h"
#include "MainFrame.h"
#include "LoginFrame.h"
#include "AdminFrame.h"

class EditAdminFrame : public wxFrame
{
private:

	User* user;
	AdminFrame* adminFrame;


	wxPanel* mainPanel;
	wxPanel* midPanel;

	wxPanel* usernameInputPanel;
	wxTextCtrl* usernameBox;

	wxPanel* passwordInputPanel;
	wxTextCtrl* passwordBox;

	wxPanel* displayNameInputPanel;
	wxTextCtrl* displayNameBox;

	wxPanel* phoneNumberInputPanel;
	wxTextCtrl* phoneNumberBox;

	wxPanel* emailInputPanel;
	wxTextCtrl* emailBox;

	wxPanel* initialBalanceInputPanel;
	wxTextCtrl* balanceBox;

	wxPanel* registerButtonPanel;
	wxButton* registerButton;

	wxRadioBox* suspendCheck;

	//Event Handlers
	void onEnterUsername(wxFocusEvent& event);
	void onLeaveUsername(wxFocusEvent& event);

	void onEnterPassword(wxFocusEvent& event);
	void onLeavePassword(wxFocusEvent& event);

	void onEnterDisplayName(wxFocusEvent& event);
	void onLeaveDisplayName(wxFocusEvent& event);

	void onEnterPhoneNumber(wxFocusEvent& event);
	void onLeavePhoneNumber(wxFocusEvent& event);

	void onEnterEmail(wxFocusEvent& event);
	void onLeaveEmail(wxFocusEvent& event);

	void onEnterInitBalance(wxFocusEvent& event);
	void onLeaveInitBalance(wxFocusEvent& event);

	void onDoneClick(wxCommandEvent& event);

	void onHover(wxMouseEvent& event);
	void onLeaveHover(wxMouseEvent& event);
	void onClose(wxCloseEvent& event);

	void paintTopPanel();
	void paintMidPanel();

public:
	EditAdminFrame(User* user, AdminFrame* adminFrame);
};

