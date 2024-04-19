#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/image.h>

MainFrame::MainFrame(User user, const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	wxPanel* mainPanel = new wxPanel(this);
	wxPanel* topPanel = new wxPanel(mainPanel, wxID_ANY,wxPoint(0, 0), wxSize(720, 150));

	topPanel->SetBackgroundColour(wxColour(52, 100, 117));

    wxIcon topImage(wxT("resources\\WalterWalletGUI.ico"), wxBITMAP_TYPE_ICO);

    if (topImage.IsOk()) {
        // Create a static bitmap from the image
        wxStaticBitmap* staticBitmap = new wxStaticBitmap(topPanel, wxID_ANY, wxBitmap(topImage));

        // Optionally, you can set the size of the bitmap+
        staticBitmap->SetSize(wxSize(720, 150));

    }

	wxStaticText* staticText = new wxStaticText(topPanel, wxID_ANY, user.getDisplayName());
	staticText->SetForegroundColour(*wxBLACK); // Set text color
	staticText->SetFont(wxFont(wxFontInfo(12).Bold())); // Set font

	//wxButton* button = new wxButton(mainPanel, wxID_ANY, "Button", wxPoint(150, 50), wxSize(100, 50));
}
