#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/image.h>

MainFrame::MainFrame(User user, const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	wxPanel* mainPanel = new wxPanel(this);
	wxPanel* topPanel = new wxPanel(mainPanel, wxID_ANY, wxPoint(0, 0), wxSize(720, 110));

	topPanel->SetBackgroundColour(wxColour(52, 100, 117));
	wxPNGHandler* handler = new wxPNGHandler;
	wxImage::AddHandler(handler);

	wxStaticText* textHALLO = new wxStaticText(topPanel, wxID_ANY, "AMERICA YA !", wxPoint(100, 20), wxSize(520,80),wxALIGN_CENTRE_HORIZONTAL);
	textHALLO->SetForegroundColour(*wxWHITE); 
	textHALLO->SetFont(wxFont(wxFontInfo(18)));

	wxStaticText* textDisplayName = new wxStaticText(topPanel, wxID_ANY, user.getDisplayName(), wxPoint(100, 55), wxSize(520, 80),wxALIGN_CENTRE_HORIZONTAL);
	textDisplayName->SetForegroundColour(*wxWHITE); // Set text color
	textDisplayName->SetFont(wxFont(wxFontInfo(22).Bold())); // Set font

	wxImage pfpIcon(wxT("resources\\profile.png"), wxBITMAP_TYPE_PNG);
	pfpIcon.Rescale(80, 80, wxIMAGE_QUALITY_HIGH); // Rescale the image to 60x60
	wxBitmap pfpBitmap(pfpIcon);
	wxStaticBitmap* displayedPfp;
	//displayedPfp = new wxStaticBitmap(topPanel, wxID_ANY, pfpBitMap, wxPoint(15, 15), wxSize(80, 80)); // Display the rescaled image

	wxImage bellIcon(wxT("resources\\bell.png"), wxBITMAP_TYPE_PNG);
	bellIcon.Rescale(80, 80, wxIMAGE_QUALITY_HIGH); // Rescale the image to 60x60
	wxBitmap bellBitmap(bellIcon);
	wxStaticBitmap* displayedBell;

	//displayedBell = new wxStaticBitmap(topPanel, wxID_ANY, bellBitmap, wxPoint(625, 15), wxSize(80, 80)); // Display the rescaled image

	wxBitmapButton* bellButton = new wxBitmapButton(topPanel, wxID_ANY, bellBitmap, wxPoint(625, 15), wxSize(80, 80), wxBU_AUTODRAW | wxBORDER_NONE);
	bellButton->SetBackgroundColour(wxColour(52, 100, 117));

	bellButton->Bind(wxEVT_BUTTON, &MainFrame::onBellButtonClick, this);

	wxBitmapButton* pfpButton = new wxBitmapButton(topPanel, wxID_ANY, pfpBitmap, wxPoint(15, 15), wxSize(80, 80), wxBU_AUTODRAW | wxBORDER_NONE);
	pfpButton->SetBackgroundColour(wxColour(52, 100, 117));

	pfpButton->Bind(wxEVT_BUTTON, &MainFrame::onBellButtonClick, this);
}

void MainFrame::onBellButtonClick(wxCommandEvent& event)
{
	printf("HAAALLLLOOOOOOO\n");
}
