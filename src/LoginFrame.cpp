#include "LoginFrame.h"
#include "RoundedPanel.h"
#include "RegisterFrame.h"
#include "AdminFrame.h"
#include "SHA256.h"

LoginFrame::LoginFrame() : wxFrame(nullptr, wxID_ANY, "HeisenBank")
{
	wxWindow::SetWindowStyle(wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX);
	mainPanel = new wxPanel(this);
	mainPanel->SetBackgroundColour(wxColour(0, 125, 141));

	
	paintTopPanel();
	paintMidPanel();
}

void LoginFrame::paintTopPanel()
{
	wxPanel* topPanel = new wxPanel(mainPanel, wxID_ANY, wxPoint(0, 0), wxSize(620, 110));

	topPanel->SetBackgroundColour(wxColour(52, 100, 117));
	wxPNGHandler* handler = new wxPNGHandler;
	wxImage::AddHandler(handler);

	wxStaticText* textHALLO = new wxStaticText(topPanel, wxID_ANY, "Welcome To HeisenBank", wxPoint(0, 40), wxSize(620, -1), wxALIGN_CENTRE_HORIZONTAL);
	textHALLO->SetForegroundColour(*wxWHITE);
	textHALLO->SetFont(wxFont(wxFontInfo(20).Bold()));
}

void LoginFrame::paintMidPanel()
{
	midPanel = new RoundedPanel(mainPanel, wxID_ANY, wxPoint(35, 130), wxSize(550, 840));

	wxPanel* sloganPanel = new wxPanel(midPanel, wxID_ANY, wxPoint(0, 40), wxSize(600, 50), wxALIGN_CENTRE_HORIZONTAL);
	sloganPanel->SetBackgroundColour(wxColour(52, 100, 117));

	wxStaticText* displaySlogan = new wxStaticText(sloganPanel, wxID_ANY, "Deals at your fingertips", wxPoint(130, 7), wxSize(300, -1), wxALIGN_CENTRE_HORIZONTAL);
	displaySlogan->SetForegroundColour(*wxWHITE);
	displaySlogan->SetBackgroundColour(wxColour(52, 100, 117));
	displaySlogan->SetFont(wxFont(wxFontInfo(22).Bold()));

	usernameInputPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(235, 160), wxSize(240, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	usernameInputPanel->SetBackgroundColour(*wxWHITE);

	passwordInputPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(235, 280), wxSize(240, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	passwordInputPanel->SetBackgroundColour(*wxWHITE);

	usernameBox = new wxTextCtrl(usernameInputPanel, wxID_ANY, "Heisenberg", wxPoint(10, 13), wxSize(220, 30), wxTE_CENTRE | wxBORDER_NONE);
	usernameBox->SetBackgroundColour(wxColour(229, 229, 229));
	usernameBox->SetForegroundColour(wxColour(178, 178, 178));
	usernameBox->SetFont(wxFont(wxFontInfo(14).Bold()));

	wxStaticText* usernameText = new wxStaticText(midPanel, wxID_ANY, "Username", wxPoint(70, 173), wxSize(-1, -1), wxALIGN_CENTRE_HORIZONTAL);
	usernameText->SetBackgroundColour(*wxWHITE);
	usernameText->SetForegroundColour(*wxBLACK);
	usernameText->SetFont(wxFont(wxFontInfo(14).Bold()));

	usernameBox->Bind(wxEVT_SET_FOCUS, &LoginFrame::onEnterUsername, this);
	usernameBox->Bind(wxEVT_KILL_FOCUS, &LoginFrame::onLeaveUsername, this);

	passwordBox = new wxTextCtrl(passwordInputPanel, wxID_ANY, "Password", wxPoint(10, 13), wxSize(220, 30), wxTE_CENTRE | wxBORDER_NONE | wxTE_PASSWORD);
	passwordBox->SetBackgroundColour(wxColour(229, 229, 229));
	passwordBox->SetForegroundColour(wxColour(178, 178, 178));
	passwordBox->SetFont(wxFont(wxFontInfo(14).Bold()));

	passwordBox->Bind(wxEVT_SET_FOCUS, &LoginFrame::onEnterPassword, this);
	passwordBox->Bind(wxEVT_KILL_FOCUS, &LoginFrame::onLeavePassword, this);

	wxStaticText* passwordText = new wxStaticText(midPanel, wxID_ANY, "Password", wxPoint(70, 303), wxSize(-1, -1), wxALIGN_CENTRE_HORIZONTAL);
	passwordText->SetBackgroundColour(*wxWHITE);
	passwordText->SetForegroundColour(*wxBLACK);
	passwordText->SetFont(wxFont(wxFontInfo(14).Bold()));

	wxPanel* sendButtonPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(185, 400), wxSize(180, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(52, 100, 117));
	sendButtonPanel->SetBackgroundColour(*wxWHITE);

	wxStaticText* noAccountText = new wxStaticText(midPanel, wxID_ANY, "Don't have an account ? Register below", wxPoint(0, 550), wxSize(550, -1), wxALIGN_CENTRE_HORIZONTAL);
	noAccountText->SetBackgroundColour(*wxWHITE);
	noAccountText->SetForegroundColour(*wxBLACK);
	noAccountText->SetFont(wxFont(wxFontInfo(14)));

	wxPanel* registerButtonPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(185, 600), wxSize(180, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(52, 100, 117));
	registerButtonPanel->SetBackgroundColour(*wxWHITE);

	wxButton* loginButton = new wxButton(sendButtonPanel, wxID_ANY, "Login", wxPoint(10, 5), wxSize(160, 40), wxBORDER_NONE);
	loginButton->SetBackgroundColour(wxColour(52, 100, 117));
	loginButton->SetForegroundColour(*wxWHITE);
	loginButton->SetFont(wxFont(wxFontInfo(18).Bold()));

	loginButton->Bind(wxEVT_BUTTON, &LoginFrame::onLoginClick, this);
	loginButton->Bind(wxEVT_ENTER_WINDOW, &LoginFrame::onHover, this);
	loginButton->Bind(wxEVT_LEAVE_WINDOW, &LoginFrame::onLeaveHover, this);

	wxButton* registerButton = new wxButton(registerButtonPanel, wxID_ANY, "Register", wxPoint(10, 5), wxSize(160, 40), wxBORDER_NONE);
	registerButton->SetBackgroundColour(wxColour(52, 100, 117));
	registerButton->SetForegroundColour(*wxWHITE);
	registerButton->SetFont(wxFont(wxFontInfo(18).Bold()));

	registerButton->Bind(wxEVT_BUTTON, &LoginFrame::onRegisterClick, this);
	registerButton->Bind(wxEVT_ENTER_WINDOW, &LoginFrame::onHover, this);
	registerButton->Bind(wxEVT_LEAVE_WINDOW, &LoginFrame::onLeaveHover, this);

}

void LoginFrame::onEnterUsername(wxFocusEvent& event) {
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->GetValue() == "Heisenberg") {
		object->SetForegroundColour(*wxBLACK);
		object->Clear();
	}
	event.Skip(true);
}

void LoginFrame::onLeaveUsername(wxFocusEvent& event) {
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->IsEmpty()) {
		object->SetForegroundColour(wxColour(178, 178, 178));
		object->AppendText("Heisenberg");
	}

	event.Skip(true);
}

void LoginFrame::onEnterPassword(wxFocusEvent& event) {
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->GetValue() == "Password") {
		object->SetForegroundColour(*wxBLACK);
		object->Clear();
	}
	event.Skip(true);
}

void LoginFrame::onLeavePassword(wxFocusEvent& event) {
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->IsEmpty()) {
		object->SetForegroundColour(wxColour(178, 178, 178));
		object->AppendText("Password");
	}

	event.Skip(true);
}

void LoginFrame::onHover(wxMouseEvent& event) {
	SetCursor(wxCursor(wxCURSOR_HAND));
}

void LoginFrame::onLeaveHover(wxMouseEvent& event) {
	SetCursor(wxCursor(wxCURSOR_ARROW));
}

void LoginFrame::onClose(wxCloseEvent& event)
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

void LoginFrame::onLoginClick(wxCommandEvent& event)
{
	string username = string(usernameBox->GetValue().mb_str());
	string password = string(passwordBox->GetValue().mb_str());
	
	if (!Validation::usernameAvailable(username)) {
		if (Validation::userExists(username))
		{
			if (Bank::getUsers()->getUser(username)->getPassword() == SHA256::toSHA256(password)) {
				MainFrame* mainFrame = new MainFrame(Bank::getUsers()->getUser(username));
				mainFrame->SetClientSize(620, 1000);
				mainFrame->Center();
				mainFrame->Show();
				mainFrame->SetIcon(GetIcon());
				this->Destroy();
			}
			else {
				wxMessageBox("Username or password incorrect", "Error", wxICON_ERROR | wxOK);
			}
		}
		else if (Validation::adminExists(username))
		{
			if (Bank::getUsers()->getAdmin(username)->getPassword() == SHA256::toSHA256(password)) {
				AdminFrame* adminFrame = new AdminFrame(Bank::getUsers()->getAdmin(username));
				adminFrame->SetClientSize(620, 1000);
				adminFrame->Center();
				adminFrame->Show();
				adminFrame->SetIcon(GetIcon());
				this->Destroy();
			}
			else {
				wxMessageBox("Username or password incorrect", "Error", wxICON_ERROR | wxOK);
			}
		}
	}
	else {
		wxMessageBox("User does not exist", "Error", wxICON_ERROR | wxOK);
	}
}

void LoginFrame::onRegisterClick(wxCommandEvent& event)
{
	//wxIcon icon(wxT("resources\\walterWallet.ico"), wxBITMAP_TYPE_ICO);

	RegisterFrame* registerFrame = new RegisterFrame(this);
	registerFrame->SetClientSize(620, 1000);
	registerFrame->Center();
	registerFrame->Show();
	registerFrame->SetIcon(GetIcon());

	this->Hide();
}