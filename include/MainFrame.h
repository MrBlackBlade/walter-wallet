#pragma once
#include <wx/wx.h>
#include "User.h"

class MainFrame : public wxFrame
{
	private:

		User* user;

		wxPanel* mainPanel;
		wxPanel* midPanel;

		//inside sendMoneyPanel
		wxPanel*		usernameInputPanel;
		wxTextCtrl*		recieverNameBox;
		wxPanel*		ammountInputPanel;
		wxPanel*		sendButtonPanel;
		wxButton*		sendButton;
		wxTextCtrl*		ammountBox;
		wxStaticText*	ammountText;
		wxStaticText*	recieverText;

		//inside midPanel
		wxPanel* sendMoneyPanel;
		wxPanel* requestMoneyPanel;
		wxPanel* transactionButtonPanel;
		wxPanel* rechargeBalancePanel;

		void paintTopPanel();
		void paintMidPanel();
		void paintSendPanel();

		//Event Handlers
		void onBellButtonClick(wxCommandEvent& event);
		void onSendMoneyClick(wxCommandEvent& event);
		void onSendClick(wxCommandEvent& event);

	public:
		MainFrame(User user, const wxString& title);
};

