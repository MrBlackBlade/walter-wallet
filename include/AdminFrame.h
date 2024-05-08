#pragma once

#include <wx/wx.h>
#include "User.h"
#include "Bank.h"

class AdminFrame : public wxFrame
{
	private:

		Admin* admin;

		wxPanel* mainPanel;
		wxPanel* topPanel;
		wxPanel* midPanel;

		wxPanel* balanceDisplayPanel;
		wxPanel* transactionsMidPanel;
		wxPanel* usersMidPanel;
		wxPanel* addUserPanel;

		wxPanel* userDisplayPanel;
		wxScrolled<wxPanel>* transactionsPanel;
		wxScrolled<wxPanel>* usersPanel;
		wxImage* backIcon;

		wxBitmapButton* transactionsBackButton;
		wxBitmapButton* usersBackButton;

		//Events
		void paintTopPanel();
		void paintMidPanel();
		void paintTransactionsPanel();
		void paintUsersPanel();

		void onUsersClick(wxCommandEvent& event);
		void onTransacionBackButtonClick(wxCommandEvent& event);
		void onUsersBackButtonClick(wxCommandEvent& event);
		void onTransactionsClick(wxCommandEvent& event);
		void onHover(wxMouseEvent& event);
		void onLeaveHover(wxMouseEvent& event);
		void onClose(wxCloseEvent& event);

	public:
		void repaintUsersPanel();
		AdminFrame(Admin* admin);
};

