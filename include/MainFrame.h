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
		wxPanel* addToBalance;

		void paintTopPanel();
		void paintMidPanel();

		//Event Handlers
		void onBellButtonClick(wxCommandEvent& event);
		void onClose(wxCloseEvent& event);

	public:
		MainFrame(User user, const wxString& title);
};

