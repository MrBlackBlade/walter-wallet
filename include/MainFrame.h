#pragma once
#include <wx/wx.h>
#include "User.h"

class MainFrame : public wxFrame
{
	public:
		MainFrame(User user, const wxString& title);

		void onBellButtonClick(wxCommandEvent& event);
};

