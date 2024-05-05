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
		wxImage* backIcon;

		//inside sendMoneyPanel
		wxPanel*		usernameInputPanel;
		wxTextCtrl*		recieverNameBox;
		wxPanel*		amountInputPanel;
		wxPanel*		sendButtonPanel;
		wxButton*		sendButton;
		wxButton*		requestButton;
		wxTextCtrl*		amountBox;
		wxStaticText*	amountText;
		wxStaticText*	recieverText;

		//back buttons
		wxBitmapButton* transactionsBackButton;
		wxBitmapButton* sendMoneyBackButton;
		wxBitmapButton* requestMoneyBackButton;

		//inside midPanel
		wxPanel* balanceDisplayPanel;
		wxPanel* sendMoneyPanel;
		wxPanel* requestMoneyPanel;
		wxPanel* transactionButtonPanel;
		wxPanel* rechargeBalancePanel;

		void paintTopPanel();
		void paintMidPanel();
		void paintSendMoneyPanel();
		void paintRequestMoneypanel();
		void paintTransactionsPanel();
		void RepaintBalance();
		void paintRequestPanel();

		//Event Handlers
		void onRequestMoneyButtonClick(wxCommandEvent& event);
		void onRequestMoneyBackButton(wxCommandEvent& event);
		void onRequestClick(wxCommandEvent& event);
		void onSendMoneyBackButtonClick(wxCommandEvent& event);
		void onTransacionBackButtonClick(wxCommandEvent& event);
		void onBellButtonClick(wxCommandEvent& event);
		void onSendMoneyClick(wxCommandEvent& event);
		void onTransactionsClick(wxCommandEvent& event);
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