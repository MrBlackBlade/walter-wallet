#pragma once
#include <wx/wx.h>
#include "User.h"

class MainFrame : public wxFrame
{
	private:

		User* user;

		wxPanel* mainPanel;
		wxPanel* midPanel;

		void paintTopPanel();

		//Event Handlers
		void onBellButtonClick(wxCommandEvent& event);

	public:
		MainFrame(User user, const wxString& title);
};

