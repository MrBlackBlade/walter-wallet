#pragma once
#include <wx/wx.h>
#include "User.h"

class MainFrame : public wxFrame
{
	private:

		User* user;

		wxPanel* mainPanel;
		wxPanel* sendMoneyPanel;
		wxPanel* requestMoneyPanel;
		wxPanel* transactionButtonPanel;
		wxPanel* rechargeBalancePanel;

		void paintTopPanel();
		void paintMidPanel();

		//Event Handlers
		void onBellButtonClick(wxCommandEvent& event);

	public:
		MainFrame(User user, const wxString& title);
};

