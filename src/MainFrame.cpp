#include <wx/wx.h>
#include <wx/image.h>
#include "MainFrame.h"
#include "FileSystemManagement.h"
#include "RoundedPanel.h"
#include "ImageButton.h"


MainFrame::MainFrame(User user, const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	mainPanel = new wxPanel(this);
	mainPanel->SetBackgroundColour(wxColour(0, 125, 141));
	this->user = &user;
	Bind(wxEVT_CLOSE_WINDOW, &MainFrame::onClose, this);
	paintTopPanel();
	paintMidPanel();
}

void MainFrame::paintTopPanel()
{
	wxPanel* topPanel = new wxPanel(mainPanel, wxID_ANY, wxPoint(0, 0), wxSize(620, 110));

	topPanel->SetBackgroundColour(wxColour(52, 100, 117));
	wxPNGHandler* handler = new wxPNGHandler;
	wxImage::AddHandler(handler);

	wxStaticText* textHALLO = new wxStaticText(topPanel, wxID_ANY, "Welcome Back", wxPoint(100, 20), wxSize(420, 80), wxALIGN_CENTRE_HORIZONTAL);
	textHALLO->SetForegroundColour(*wxWHITE);
	textHALLO->SetFont(wxFont(wxFontInfo(18)));

	wxStaticText* textDisplayName = new wxStaticText(topPanel, wxID_ANY, (*user).getDisplayName(), wxPoint(100, 55), wxSize(420, 80), wxALIGN_CENTRE_HORIZONTAL);
	textDisplayName->SetForegroundColour(*wxWHITE); // Set text color
	textDisplayName->SetFont(wxFont(wxFontInfo(22).Bold())); // Set font

	wxImage bellIcon(wxString("resources\\bell.png"), wxBITMAP_TYPE_PNG);
	bellIcon.Rescale(80, 80, wxIMAGE_QUALITY_HIGH); // Rescale the image to 60x60
	wxBitmap bellBitmap(bellIcon);
	wxBitmapButton* bellButton = new wxBitmapButton(topPanel, wxID_ANY, bellBitmap, wxPoint(525, 15), wxSize(80, 80), wxBU_AUTODRAW | wxBORDER_NONE);
	bellButton->SetBackgroundColour(wxColour(52, 100, 117));
	bellButton->Bind(wxEVT_BUTTON, &MainFrame::onBellButtonClick, this);

	wxImage pfpIcon(wxT("resources\\profile.png"), wxBITMAP_TYPE_PNG);
	pfpIcon.Rescale(80, 80, wxIMAGE_QUALITY_HIGH); // Rescale the image to 60x60
	wxBitmap pfpBitmap(pfpIcon);
	wxBitmapButton* pfpButton = new wxBitmapButton(topPanel, wxID_ANY, pfpBitmap, wxPoint(15, 15), wxSize(80, 80), wxBU_AUTODRAW | wxBORDER_NONE);
	pfpButton->SetBackgroundColour(wxColour(52, 100, 117));
	pfpButton->Bind(wxEVT_BUTTON, &MainFrame::onBellButtonClick, this);


}
void MainFrame::paintMidPanel()
{
	wxPanel*  midPanel = new RoundedPanel(mainPanel, wxID_ANY, wxPoint(60, 130), wxSize(500, 820), wxALIGN_CENTRE_HORIZONTAL, *wxWHITE);

	wxStaticText* displayBalance = new wxStaticText(midPanel, wxID_ANY, "Balance: " + to_string((*user).getBalance()).substr(0, to_string((*user).getBalance()).find(".") + 2), wxPoint(0, 20), wxSize(500, 30), wxALIGN_CENTRE_HORIZONTAL);
	displayBalance->SetForegroundColour(*wxWHITE);
	displayBalance->SetBackgroundColour(wxColour(52, 100, 117));
	displayBalance->SetFont(wxFont(wxFontInfo(22).Bold()));

	sendMoneyPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(40, 170), wxSize(190, 250), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	sendMoneyPanel->SetBackgroundColour(*wxWHITE);

	requestMoneyPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(270, 170), wxSize(190, 250), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	requestMoneyPanel->SetBackgroundColour(*wxWHITE);

	transactionButtonPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(270, 460), wxSize(190, 250), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	transactionButtonPanel->SetBackgroundColour(*wxWHITE);

	addToBalance = new RoundedPanel(midPanel, wxID_ANY, wxPoint(40, 460), wxSize(190, 250), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	addToBalance->SetBackgroundColour(*wxWHITE);
}
void MainFrame::onBellButtonClick(wxCommandEvent& event)
{	
	printf("HAAALLLLOOOOOOO\n");
}

void MainFrame::onClose(wxCloseEvent& event)
{
	if (wxMessageBox(wxT("Do You want to Close the Application?"),
		wxT("Please confirm"),
		wxICON_QUESTION | wxYES_NO) == wxYES)
	{
		FileSystemManagement::updateData();
		event.Skip();
	}
	
	//event.Skip();
}
