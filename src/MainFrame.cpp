#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/image.h>

MainFrame::MainFrame(User user, const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	wxPanel* mainPanel = new wxPanel(this);
	wxPanel* topPanel = new wxPanel(mainPanel, wxID_ANY, wxPoint(0, 0), wxSize(720, 150));

	topPanel->SetBackgroundColour(wxColour(52, 100, 117));
	//wxPNGHandler* handler = new wxPNGHandler;
	//wxImage::AddHandler(handler);
	//wxStaticBitmap* image;
	//image = new wxStaticBitmap(topPanel, wxID_ANY, wxBitmap("resources\\topPanel.png", wxBITMAP_TYPE_PNG));
	//image->SetSize(wxSize(720, 150));


	wxStaticText* textHALLO = new wxStaticText(topPanel, wxID_ANY, "Welcome Back", wxPoint(20, 20));
	textHALLO->SetForegroundColour(*wxWHITE); // Set text color
	//staticText->SetBackgroundColour(wxColour(52, 100, 117));
	textHALLO->SetFont(wxFont(wxFontInfo(12))); // Set font
	wxStaticText* textDisplayName = new wxStaticText(topPanel, wxID_ANY, user.getDisplayName(), wxPoint(20, 40));
	textDisplayName->SetForegroundColour(*wxWHITE); // Set text color
	//staticText->SetBackgroundColour(wxColour(52, 100, 117));
	textDisplayName->SetFont(wxFont(wxFontInfo(20).Bold())); // Set font

	//wxButton* button = new wxButton(mainPanel, wxID_ANY, "Button", wxPoint(150, 50), wxSize(100, 50));
}
