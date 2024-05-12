#pragma once

#include <wx/wx.h>
#include "User.h"
#include "Bank.h"

class MainFrame : public wxFrame
{
	private:

		User* user;
		
		bool hasRequest = false;

		wxPanel* mainPanel;
		wxPanel* topPanel;
		wxPanel* midPanel;
		wxScrolled<wxPanel>* transactionsPanel;
		wxScrolled<wxPanel>* pendingRequestsPanel;
		wxImage* backIcon;

		wxBitmapButton* bellButton;
		wxBitmapButton* bellAlertButton;
		wxBitmapButton* pfpButton;
		wxButton* requestButton;

		//inside Send Money Panel
		wxPanel*		usernameInputPanel;
		wxTextCtrl*		recieverNameBox;
		wxPanel*		amountInputPanel;
		wxPanel*		sendButtonPanel;
		wxButton*		sendButton;
		wxTextCtrl*		amountBox;
		wxStaticText*	amountText;
		wxStaticText*	recieverText;
		wxStaticText*	noRequests;

		//inside Recharge Money Panel
		wxPanel* cardNumberInputPanel;
		wxTextCtrl* cardNumberBox;

		wxPanel* cvvInputPanel;
		wxTextCtrl* cvvBox;

		wxPanel* rechargeButtonPanel;
		wxButton* rechargeButton;

		wxPanel* rechargeAmountInputPanel;
		wxTextCtrl* rechargAmountBox;

		wxStaticText* rechargeAmountText;
		wxStaticText* cvvText;
		wxStaticText* cardNumberText;

		// inside editProfile
		wxStaticText* pfpUsernameText;
		wxStaticText* pfpPasswordText;
		wxStaticText* pfpDisplayNameText;
		wxStaticText* pfpPhoneNumberText;
		wxStaticText* pfpEmailText;
		wxStaticText* textDisplayName;

		wxPanel*	  pfpUsernameInputPanel;
		wxTextCtrl*   pfpUsernameBox;

		wxPanel*	  pfpPasswordInputPanel;
		wxTextCtrl*   pfpPasswordBox;

		wxPanel*	  pfpDisplayNameInputPanel;
		wxTextCtrl*   pfpDisplayNameBox;

		wxPanel*	  pfpPhoneNumberInputPanel;
		wxTextCtrl*   pfpPhoneNumberBox;

		wxPanel*      pfpEmailInputPanel;
		wxTextCtrl*   pfpEmailBox;

		wxPanel*      pfpDoneButtonPanel;
		wxButton*     pfpDoneButton;

		//back buttons
		wxBitmapButton* requestsPanelBackButton;
		wxBitmapButton* transactionsBackButton;
		wxBitmapButton* sendMoneyBackButton;
		wxBitmapButton* requestMoneyBackButton;
		wxBitmapButton* rechargeBalanceBackButton;
		wxBitmapButton* pfpPanelBackButton;

		//inside midPanel
		wxPanel* balanceDisplayPanel;
		wxPanel* sendMoneyPanel;
		wxPanel* requestMoneyPanel;
		wxPanel* transactionButtonPanel;
		wxPanel* rechargeBalancePanel;

		void paintTopPanel();
		void paintMidPanel();

		void repaintBalance();
		void checkRequests();

		void paintSendMoneyPanel();
		void paintRequestMoneypanel();
		void paintTransactionsPanel();
		void paintPendingRequests();
		void paintProfile();
		void paintRechargeBalancePanel();

		//Event Handlers	   
		void onPfpButtonClick(wxCommandEvent& event);
		void onPfpDoneClick(wxCommandEvent& event);
		void onRequestsPanelBackClick(wxCommandEvent& event);
		void onPfpBackButtonClick(wxCommandEvent& event);
		void onRequestMoneyButtonClick(wxCommandEvent& event);
		void onRequestMoneyBackButton(wxCommandEvent& event);
		void onRequestClick(wxCommandEvent& event);
		void onSendMoneyBackButtonClick(wxCommandEvent& event);
		void onRechargeMoneybackButtonClick(wxCommandEvent& event);
		void onRechargeButtonCLick(wxCommandEvent& event);
		void onRechargeBalanceButtonClick(wxCommandEvent& event);
		void onTransacionBackButtonClick(wxCommandEvent& event);
		void onBellButtonClick(wxCommandEvent& event);
		void onSendMoneyClick(wxCommandEvent& event);
		void onTransactionsClick(wxCommandEvent& event);
		void onSendClick(wxCommandEvent& event);
		void onEnterCardNumber(wxFocusEvent& event);
		void onLeaveCardNumber(wxFocusEvent& event);
		void onEnterCvv(wxFocusEvent& event);
		void onLeaveCvv(wxFocusEvent& event);
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