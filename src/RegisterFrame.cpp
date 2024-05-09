#include "RegisterFrame.h"
#include "RoundedPanel.h"

RegisterFrame::RegisterFrame(LoginFrame* loginFrame, const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	this->loginFrame = loginFrame;

	mainPanel = new wxPanel(this);
	mainPanel->SetBackgroundColour(wxColour(0, 125, 141));
	//Bind(wxEVT_CLOSE_WINDOW, &MainFrame::onClose, this);
	paintTopPanel();
	paintMidPanel();
}
void RegisterFrame::paintTopPanel()
{
	wxPanel* topPanel = new wxPanel(mainPanel, wxID_ANY, wxPoint(0, 0), wxSize(620, 110));

	topPanel->SetBackgroundColour(wxColour(52, 100, 117));
	wxPNGHandler* handler = new wxPNGHandler;
	wxImage::AddHandler(handler);

	wxStaticText* textHALLO = new wxStaticText(topPanel, wxID_ANY, "You got the Money and We got the Business", wxPoint(22, 40), wxSize(-1, -1));
	textHALLO->SetForegroundColour(*wxWHITE);
	textHALLO->SetFont(wxFont(wxFontInfo(20).Bold()));

}
void RegisterFrame::paintMidPanel()
{
	midPanel = new RoundedPanel(mainPanel, wxID_ANY, wxPoint(35, 130), wxSize(550, 840));

	wxPanel* joinUsPanel = new wxPanel(midPanel, wxID_ANY, wxPoint(0, 40), wxSize(600, 50), wxALIGN_CENTRE_HORIZONTAL);
	joinUsPanel->SetBackgroundColour(wxColour(52, 100, 117));

	wxStaticText* displayJoinUs = new wxStaticText(joinUsPanel, wxID_ANY, "Join Us", wxPoint(130, 7), wxSize(300, -1), wxALIGN_CENTRE_HORIZONTAL);
	displayJoinUs->SetForegroundColour(*wxWHITE);
	displayJoinUs->SetBackgroundColour(wxColour(52, 100, 117));
	displayJoinUs->SetFont(wxFont(wxFontInfo(22).Bold()));

	usernameInputPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(235, 160), wxSize(240, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	usernameInputPanel->SetBackgroundColour(*wxWHITE);

	passwordInputPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(235, 240), wxSize(240, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	passwordInputPanel->SetBackgroundColour(*wxWHITE);

	displayNameInputPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(235, 320), wxSize(240, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	displayNameInputPanel->SetBackgroundColour(*wxWHITE);

	phoneNumberInputPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(235, 400), wxSize(240, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	phoneNumberInputPanel->SetBackgroundColour(*wxWHITE);

	emailInputPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(235, 480), wxSize(240, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	emailInputPanel->SetBackgroundColour(*wxWHITE);

	initialBalanceInputPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(235, 560), wxSize(240, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	initialBalanceInputPanel->SetBackgroundColour(*wxWHITE);


	usernameBox = new wxTextCtrl(usernameInputPanel, wxID_ANY, "Username", wxPoint(10, 13), wxSize(220, 30), wxTE_CENTRE | wxBORDER_NONE);
	usernameBox->SetBackgroundColour(wxColour(229, 229, 229));
	usernameBox->SetForegroundColour(wxColour(178, 178, 178));
	usernameBox->SetFont(wxFont(wxFontInfo(14).Bold()));

	wxStaticText* usernameText = new wxStaticText(midPanel, wxID_ANY, "Unique", wxPoint(70, 173), wxSize(-1, -1), wxALIGN_CENTRE_HORIZONTAL);
	usernameText->SetBackgroundColour(*wxWHITE);
	usernameText->SetForegroundColour(*wxBLACK);
	usernameText->SetFont(wxFont(wxFontInfo(14).Bold()));

	usernameBox->Bind(wxEVT_SET_FOCUS, &RegisterFrame::onEnterUsername, this);
	usernameBox->Bind(wxEVT_KILL_FOCUS, &RegisterFrame::onLeaveUsername, this);

	passwordBox = new wxTextCtrl(passwordInputPanel, wxID_ANY, "Password", wxPoint(10, 13), wxSize(220, 30), wxTE_CENTRE | wxBORDER_NONE);
	passwordBox->SetBackgroundColour(wxColour(229, 229, 229));
	passwordBox->SetForegroundColour(wxColour(178, 178, 178));
	passwordBox->SetFont(wxFont(wxFontInfo(14).Bold()));

	wxStaticText* passwordText = new wxStaticText(midPanel, wxID_ANY, "Secured", wxPoint(70, 253), wxSize(-1, -1), wxALIGN_CENTRE_HORIZONTAL);
	passwordText->SetBackgroundColour(*wxWHITE);
	passwordText->SetForegroundColour(*wxBLACK);
	passwordText->SetFont(wxFont(wxFontInfo(14).Bold()));

	passwordBox->Bind(wxEVT_SET_FOCUS, &RegisterFrame::onEnterPassword, this);
	passwordBox->Bind(wxEVT_KILL_FOCUS, &RegisterFrame::onLeavePassword, this);

	displayNameBox = new wxTextCtrl(displayNameInputPanel, wxID_ANY, "Display Name", wxPoint(10, 13), wxSize(220, 30), wxTE_CENTRE | wxBORDER_NONE);
	displayNameBox->SetBackgroundColour(wxColour(229, 229, 229));
	displayNameBox->SetForegroundColour(wxColour(178, 178, 178));
	displayNameBox->SetFont(wxFont(wxFontInfo(14).Bold()));

	wxStaticText* displayNameText = new wxStaticText(midPanel, wxID_ANY, "Say your name", wxPoint(70, 333), wxSize(-1, -1), wxALIGN_CENTRE_HORIZONTAL);
	displayNameText->SetBackgroundColour(*wxWHITE);
	displayNameText->SetForegroundColour(*wxBLACK);
	displayNameText->SetFont(wxFont(wxFontInfo(14).Bold()));

	displayNameBox->Bind(wxEVT_SET_FOCUS, &RegisterFrame::onEnterDisplayName, this);
	displayNameBox->Bind(wxEVT_KILL_FOCUS, &RegisterFrame::onLeaveDisplayName, this);

	phoneNumberBox = new wxTextCtrl(phoneNumberInputPanel, wxID_ANY, "Number", wxPoint(10, 13), wxSize(220, 30), wxTE_CENTRE | wxBORDER_NONE);
	phoneNumberBox->SetBackgroundColour(wxColour(229, 229, 229));
	phoneNumberBox->SetForegroundColour(wxColour(178, 178, 178));
	phoneNumberBox->SetFont(wxFont(wxFontInfo(14).Bold()));

	wxStaticText* phoneNumberText = new wxStaticText(midPanel, wxID_ANY, "Phone", wxPoint(70, 413), wxSize(-1, -1), wxALIGN_CENTRE_HORIZONTAL);
	phoneNumberText->SetBackgroundColour(*wxWHITE);
	phoneNumberText->SetForegroundColour(*wxBLACK);
	phoneNumberText->SetFont(wxFont(wxFontInfo(14).Bold()));

	phoneNumberBox->Bind(wxEVT_SET_FOCUS, &RegisterFrame::onEnterPhoneNumber, this);
	phoneNumberBox->Bind(wxEVT_KILL_FOCUS, &RegisterFrame::onLeavePhoneNumber, this);

	emailBox = new wxTextCtrl(emailInputPanel, wxID_ANY, "Email", wxPoint(10, 13), wxSize(220, 30), wxTE_CENTRE | wxBORDER_NONE);
	emailBox->SetBackgroundColour(wxColour(229, 229, 229));
	emailBox->SetForegroundColour(wxColour(178, 178, 178));
	emailBox->SetFont(wxFont(wxFontInfo(14).Bold()));

	wxStaticText* emailText = new wxStaticText(midPanel, wxID_ANY, "Contact", wxPoint(70, 493), wxSize(-1, -1), wxALIGN_CENTRE_HORIZONTAL);
	emailText->SetBackgroundColour(*wxWHITE);
	emailText->SetForegroundColour(*wxBLACK);
	emailText->SetFont(wxFont(wxFontInfo(14).Bold()));

	emailBox->Bind(wxEVT_SET_FOCUS, &RegisterFrame::onEnterEmail, this);
	emailBox->Bind(wxEVT_KILL_FOCUS, &RegisterFrame::onLeaveEmail, this);

	initialBalanceBox = new wxTextCtrl(initialBalanceInputPanel, wxID_ANY, "EGP", wxPoint(10, 13), wxSize(220, 30), wxTE_CENTRE | wxBORDER_NONE);
	initialBalanceBox->SetBackgroundColour(wxColour(229, 229, 229));
	initialBalanceBox->SetForegroundColour(wxColour(178, 178, 178));
	initialBalanceBox->SetFont(wxFont(wxFontInfo(14).Bold()));

	wxStaticText* initBalanceText = new wxStaticText(midPanel, wxID_ANY, "Initial Balance", wxPoint(70, 573), wxSize(-1, -1), wxALIGN_CENTRE_HORIZONTAL);
	initBalanceText->SetBackgroundColour(*wxWHITE);
	initBalanceText->SetForegroundColour(*wxBLACK);
	initBalanceText->SetFont(wxFont(wxFontInfo(14).Bold()));

	initialBalanceBox->Bind(wxEVT_SET_FOCUS, &RegisterFrame::onEnterInitBalance, this);
	initialBalanceBox->Bind(wxEVT_KILL_FOCUS, &RegisterFrame::onLeaveInitBalance, this);

	wxPanel* registerButtonPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(185, 660), wxSize(180, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(52, 100, 117));
	registerButtonPanel->SetBackgroundColour(*wxWHITE);

	wxButton* registerButton = new wxButton(registerButtonPanel, wxID_ANY, "Register", wxPoint(10, 5), wxSize(160, 40), wxBORDER_NONE);
	registerButton->SetBackgroundColour(wxColour(52, 100, 117));
	registerButton->SetForegroundColour(*wxWHITE);
	registerButton->SetFont(wxFont(wxFontInfo(18).Bold()));

	registerButton->Bind(wxEVT_BUTTON, &RegisterFrame::onRegisterClick, this);
	registerButton->Bind(wxEVT_ENTER_WINDOW, &RegisterFrame::onHover, this);
	registerButton->Bind(wxEVT_LEAVE_WINDOW, &RegisterFrame::onLeaveHover, this);
}

void RegisterFrame::onEnterUsername(wxFocusEvent& event) {
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->GetValue() == "Username") {
		object->SetForegroundColour(*wxBLACK);
		object->Clear();
	}
	event.Skip(true);
}

void RegisterFrame::onLeaveUsername(wxFocusEvent& event) {
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->IsEmpty()) {
		object->SetForegroundColour(wxColour(178, 178, 178));
		object->AppendText("Username");
	}

	event.Skip(true);
}

void RegisterFrame::onEnterPassword(wxFocusEvent& event) {
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->GetValue() == "Password") {
		object->SetForegroundColour(*wxBLACK);
		object->Clear();
	}
	event.Skip(true);
}

void RegisterFrame::onLeavePassword(wxFocusEvent& event) {
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->IsEmpty()) {
		object->SetForegroundColour(wxColour(178, 178, 178));
		object->AppendText("Password");
	}

	event.Skip(true);
}

void RegisterFrame::onEnterDisplayName(wxFocusEvent& event)
{
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->GetValue() == "Display Name") {
		object->SetForegroundColour(*wxBLACK);
		object->Clear();
	}
	event.Skip(true);
}

void RegisterFrame::onLeaveDisplayName(wxFocusEvent& event)
{
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->IsEmpty()) {
		object->SetForegroundColour(wxColour(178, 178, 178));
		object->AppendText("Display Name");
	}

	event.Skip(true);
}

void RegisterFrame::onEnterPhoneNumber(wxFocusEvent& event)
{
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->GetValue() == "Number") {
		object->SetForegroundColour(*wxBLACK);
		object->Clear();
	}
	event.Skip(true);
}

void RegisterFrame::onLeavePhoneNumber(wxFocusEvent& event)
{
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->IsEmpty()) {
		object->SetForegroundColour(wxColour(178, 178, 178));
		object->AppendText("Number");
	}

	event.Skip(true);
}

void RegisterFrame::onEnterEmail(wxFocusEvent& event)
{
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->GetValue() == "Email") {
		object->SetForegroundColour(*wxBLACK);
		object->Clear();
	}
	event.Skip(true);
}

void RegisterFrame::onLeaveEmail(wxFocusEvent& event)
{
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->IsEmpty()) {
		object->SetForegroundColour(wxColour(178, 178, 178));
		object->AppendText("Email");
	}

	event.Skip(true);
}

void RegisterFrame::onEnterInitBalance(wxFocusEvent& event)
{
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->GetValue() == "EGP") {
		object->SetForegroundColour(*wxBLACK);
		object->Clear();
	}
	event.Skip(true);
}

void RegisterFrame::onLeaveInitBalance(wxFocusEvent& event)
{
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->IsEmpty()) {
		object->SetForegroundColour(wxColour(178, 178, 178));
		object->AppendText("EGP");
	}

	event.Skip(true);
}

void RegisterFrame::onRegisterClick(wxCommandEvent& event)
{
	string error = "Invalid form parameters\n\n";

	string username = string(usernameBox->GetValue().mb_str());
	string password = string(passwordBox->GetValue().mb_str());
	string displayName = string(displayNameBox->GetValue().mb_str());
	string phoneNumber = string(phoneNumberBox->GetValue().mb_str());
	string email = string(emailBox->GetValue().mb_str());
	string initialBalance = string(initialBalanceBox->GetValue().mb_str());

	if
		(
			username == "Username"
			|| password == "Password"
			|| displayName == "Display Name"
			|| phoneNumber == "Number"
			|| email == "Email"
			|| initialBalance == "EGP"
		)
	{
		error += "Please fill out all fields\n\n";
		wxMessageBox(error, "Invalid");
	}
	else {
		if
			(
				Validation::usernameValid(username)
				&& Validation::passwordValid(password)
				&& Validation::displayNameValid(displayName)
				&& Validation::phoneNumberValidFormat(phoneNumber)
				&& Validation::emailValidFormat(email)
				&& Validation::initialBalanceValid(initialBalance)
				)
		{
			wxMessageBox("trsh");
			Bank::asAdmin()->addUser
			(
				username,
				password,
				displayName,
				stod(initialBalance),
				phoneNumber,
				email,
				false
			);
			MainFrame* mainFrame = new MainFrame(Bank::getUsers()->getUser(username), "Heisenbank");
			mainFrame->SetClientSize(620, 1000);
			mainFrame->Center();
			mainFrame->Show();
			mainFrame->SetIcon(this->GetIcon());
			//this->Hide();
			this->Close();
		}
		else
		{
			if (!Validation::usernameValid(username)) {
				error += "Username Invalid:\n";
				if (!Validation::usernameAvailable(username)) {
					error += "User already exists.\n";
				}
				if (!Validation::usernameValidLength(username)) {
					error += "Length must be 3-16 characters.\n";
				}
				if (!Validation::usernameValidCharacterSet(username)) {
					error += "Only charecters [Aa-Zz], digits[0-9] and [_-] are allowed\n";
				}
				error += "\n";
			}
			if (!Validation::passwordValid(password)) {
				error += "Password Invalid:\n";
				if (!Validation::passwordValidLength(password)) {
					error += "Length must be 8-32 characters.\n";
				}
				if (!Validation::passwordValidCase(password)) {
					error += "Must contain at least one uppercase and one lowercase character.\n";
				}
				if (!Validation::passwordContainsNumbers(password)) {
					error += "Must contain at least one number.\n";
				}
				if (!Validation::passwordContainsSpecialCharacters(password)) {
					error += "Must contain at least one special character.\n";
				}
				if (!Validation::passwordValidCharacterSet(password)) {
					error += "Only charecters [Aa-Zz], digits[0-9] and [~!@#$%^&*:;()<>_-] are allowed\n";
				}
				error += "\n";
			}
			if (!Validation::displayNameValid(displayName)) {
				error += "Display Name Invalid:\n";
				error += "Only charecters [Aa-Zz] are allowed\n";
				error += "\n";
			}
			if (!Validation::phoneNumberValidFormat(phoneNumber)) {
				error += "Phone Number Invalid:\n";
				error += "Must be 11 digits in the format: 01XXXXXXXXX \n";
				error += "\n";
			}
			if (!Validation::emailValidFormat(email)) {
				error += "Email Invalid:\n";
				error += "Must be in the format: example@example.example \n";
				error += "\n";
			}
			if (!Validation::initialBalanceValid(initialBalance)) {
				error += "Initial Balance Invalid:\n";
				error += "Must be a number between 0-50000\n";
				error += "\n";
			}
			wxMessageBox(error, "Invalid");
		}
	}
}

void RegisterFrame::onHover(wxMouseEvent& event) {
	SetCursor(wxCursor(wxCURSOR_HAND));
}

void RegisterFrame::onLeaveHover(wxMouseEvent& event) {
	SetCursor(wxCursor(wxCURSOR_ARROW));
}

void RegisterFrame::onClose(wxCloseEvent& event)
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
