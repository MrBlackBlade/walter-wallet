#pragma once
#include <wx/wx.h>
#include "User.h"
#include "Bank.h"

class MainFrame : public wxFrame
{
	private:

		User* user;

		wxPanel* mainPanel;
		wxPanel* midPanel;
		wxScrolled<wxPanel>* transactionsPanel;

		//inside sendMoneyPanel
		wxPanel*		usernameInputPanel;
		wxTextCtrl*		recieverNameBox;
		wxPanel*		amountInputPanel;
		wxPanel*		sendButtonPanel;
		wxButton*		sendButton;
		wxTextCtrl*		amountBox;
		wxStaticText*	amountText;
		wxStaticText*	recieverText;

		//inside midPanel
		wxPanel* sendMoneyPanel;
		wxPanel* requestMoneyPanel;
		wxPanel* transactionButtonPanel;
		wxPanel* rechargeBalancePanel;

		void paintTopPanel();
		void paintMidPanel();
		void paintSendPanel();
		void paintTransactionsPanel();

		//Event Handlers
		void onBellButtonClick(wxCommandEvent& event);
		void onSendMoneyClick(wxCommandEvent& event);
		void onSendClick(wxCommandEvent& event);
		void onEnterUsername(wxFocusEvent& event);
		void onLeaveUsername(wxFocusEvent& event);
		void onEnterAmount(wxFocusEvent& event);
		void onLeaveAmount(wxFocusEvent& event);
		void onHover(wxMouseEvent& event);
		void onLeaveHover(wxMouseEvent& event);
		void onClose(wxCloseEvent& event);

	public:
		MainFrame(User* user, const wxString& title);
};

