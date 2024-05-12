
#include "RoundedPanel.h"
#include "EditAdminFrame.h"

EditAdminFrame::EditAdminFrame(User* user, AdminFrame* adminFrame) : wxFrame(nullptr, wxID_ANY, "HeisenBank")
{
	this->user = user;
	this->adminFrame = adminFrame;

	mainPanel = new wxPanel(this);
	mainPanel->SetBackgroundColour(wxColour(0, 125, 141));
	//Bind(wxEVT_CLOSE_WINDOW, &MainFrame::onClose, this);
	paintTopPanel();
	paintMidPanel();
}
void EditAdminFrame::paintTopPanel()
{
	wxPanel* topPanel = new wxPanel(mainPanel, wxID_ANY, wxPoint(0, 0), wxSize(620, 110));

	topPanel->SetBackgroundColour(wxColour(52, 100, 117));
	wxPNGHandler* handler = new wxPNGHandler;
	wxImage::AddHandler(handler);

	wxStaticText* textHALLO = new wxStaticText(topPanel, wxID_ANY, "Hey Boss", wxPoint(22, 40), wxSize(-1, -1));
	textHALLO->SetForegroundColour(*wxWHITE);
	textHALLO->SetFont(wxFont(wxFontInfo(20).Bold()));

}
void EditAdminFrame::paintMidPanel()
{
	midPanel = new RoundedPanel(mainPanel, wxID_ANY, wxPoint(35, 130), wxSize(550, 840));

	wxPanel* joinUsPanel = new wxPanel(midPanel, wxID_ANY, wxPoint(0, 40), wxSize(600, 50), wxALIGN_CENTRE_HORIZONTAL);
	joinUsPanel->SetBackgroundColour(wxColour(52, 100, 117));

	wxStaticText* displayJoinUs = new wxStaticText(joinUsPanel, wxID_ANY, "Edit User", wxPoint(130, 7), wxSize(300, -1), wxALIGN_CENTRE_HORIZONTAL);
	displayJoinUs->SetForegroundColour(*wxWHITE);
	displayJoinUs->SetBackgroundColour(wxColour(52, 100, 117));
	displayJoinUs->SetFont(wxFont(wxFontInfo(22).Bold()));

	usernameInputPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(235, 160), wxSize(240, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	usernameInputPanel->SetBackgroundColour(*wxWHITE);

	displayNameInputPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(235, 240), wxSize(240, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	displayNameInputPanel->SetBackgroundColour(*wxWHITE);

	phoneNumberInputPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(235, 320), wxSize(240, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	phoneNumberInputPanel->SetBackgroundColour(*wxWHITE);

	emailInputPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(235, 400), wxSize(240, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	emailInputPanel->SetBackgroundColour(*wxWHITE);

	initialBalanceInputPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(235, 480), wxSize(240, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	initialBalanceInputPanel->SetBackgroundColour(*wxWHITE);


	usernameBox = new wxTextCtrl(usernameInputPanel, wxID_ANY, user->getUsername(), wxPoint(10, 13), wxSize(220, 30), wxTE_CENTRE | wxBORDER_NONE);
	usernameBox->SetBackgroundColour(wxColour(229, 229, 229));
	usernameBox->SetForegroundColour(*wxBLACK);
	usernameBox->SetFont(wxFont(wxFontInfo(14).Bold()));

	wxStaticText* usernameText = new wxStaticText(midPanel, wxID_ANY, "Username", wxPoint(70, 173), wxSize(-1, -1), wxALIGN_CENTRE_HORIZONTAL);
	usernameText->SetBackgroundColour(*wxWHITE);
	usernameText->SetForegroundColour(*wxBLACK);
	usernameText->SetFont(wxFont(wxFontInfo(14).Bold()));

	usernameBox->Bind(wxEVT_SET_FOCUS, &EditAdminFrame::onEnterUsername, this);
	usernameBox->Bind(wxEVT_KILL_FOCUS, &EditAdminFrame::onLeaveUsername, this);

	displayNameBox = new wxTextCtrl(displayNameInputPanel, wxID_ANY, user->getDisplayName(), wxPoint(10, 13), wxSize(220, 30), wxTE_CENTRE | wxBORDER_NONE);
	displayNameBox->SetBackgroundColour(wxColour(229, 229, 229));
	displayNameBox->SetForegroundColour(*wxBLACK);
	displayNameBox->SetFont(wxFont(wxFontInfo(14).Bold()));

	wxStaticText* displayNameText = new wxStaticText(midPanel, wxID_ANY, "Display Name", wxPoint(70, 253), wxSize(-1, -1), wxALIGN_CENTRE_HORIZONTAL);
	displayNameText->SetBackgroundColour(*wxWHITE);
	displayNameText->SetForegroundColour(*wxBLACK);
	displayNameText->SetFont(wxFont(wxFontInfo(14).Bold()));

	displayNameBox->Bind(wxEVT_SET_FOCUS, &EditAdminFrame::onEnterDisplayName, this);
	displayNameBox->Bind(wxEVT_KILL_FOCUS, &EditAdminFrame::onLeaveDisplayName, this);

	phoneNumberBox = new wxTextCtrl(phoneNumberInputPanel, wxID_ANY, user->getPhoneNumber(), wxPoint(10, 13), wxSize(220, 30), wxTE_CENTRE | wxBORDER_NONE);
	phoneNumberBox->SetBackgroundColour(wxColour(229, 229, 229));
	phoneNumberBox->SetForegroundColour(*wxBLACK);
	phoneNumberBox->SetFont(wxFont(wxFontInfo(14).Bold()));

	wxStaticText* phoneNumberText = new wxStaticText(midPanel, wxID_ANY, "Phone", wxPoint(70, 333), wxSize(-1, -1), wxALIGN_CENTRE_HORIZONTAL);
	phoneNumberText->SetBackgroundColour(*wxWHITE);
	phoneNumberText->SetForegroundColour(*wxBLACK);
	phoneNumberText->SetFont(wxFont(wxFontInfo(14).Bold()));

	phoneNumberBox->Bind(wxEVT_SET_FOCUS, &EditAdminFrame::onEnterPhoneNumber, this);
	phoneNumberBox->Bind(wxEVT_KILL_FOCUS, &EditAdminFrame::onLeavePhoneNumber, this);

	emailBox = new wxTextCtrl(emailInputPanel, wxID_ANY, user->getEmail(), wxPoint(10, 13), wxSize(220, 30), wxTE_CENTRE | wxBORDER_NONE);
	emailBox->SetBackgroundColour(wxColour(229, 229, 229));
	emailBox->SetForegroundColour(*wxBLACK);
	emailBox->SetFont(wxFont(wxFontInfo(14).Bold()));

	wxStaticText* emailText = new wxStaticText(midPanel, wxID_ANY, "Email", wxPoint(70, 413), wxSize(-1, -1), wxALIGN_CENTRE_HORIZONTAL);
	emailText->SetBackgroundColour(*wxWHITE);
	emailText->SetForegroundColour(*wxBLACK);
	emailText->SetFont(wxFont(wxFontInfo(14).Bold()));

	emailBox->Bind(wxEVT_SET_FOCUS, &EditAdminFrame::onEnterEmail, this);
	emailBox->Bind(wxEVT_KILL_FOCUS, &EditAdminFrame::onLeaveEmail, this);

	balanceBox = new wxTextCtrl(initialBalanceInputPanel, wxID_ANY, to_string(user->getBalance()), wxPoint(10, 13), wxSize(220, 30), wxTE_CENTRE | wxBORDER_NONE);
	balanceBox->SetBackgroundColour(wxColour(229, 229, 229));
	balanceBox->SetForegroundColour(*wxBLACK);
	balanceBox->SetFont(wxFont(wxFontInfo(14).Bold()));

	wxStaticText* initBalanceText = new wxStaticText(midPanel, wxID_ANY, "Balance", wxPoint(70, 493), wxSize(-1, -1), wxALIGN_CENTRE_HORIZONTAL);
	initBalanceText->SetBackgroundColour(*wxWHITE);
	initBalanceText->SetForegroundColour(*wxBLACK);
	initBalanceText->SetFont(wxFont(wxFontInfo(14).Bold()));

	balanceBox->Bind(wxEVT_SET_FOCUS, &EditAdminFrame::onEnterInitBalance, this);
	balanceBox->Bind(wxEVT_KILL_FOCUS, &EditAdminFrame::onLeaveInitBalance, this);

	wxPanel* registerButtonPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(185, 660), wxSize(180, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(52, 100, 117));
	registerButtonPanel->SetBackgroundColour(*wxWHITE);

	wxButton* doneButton = new wxButton(registerButtonPanel, wxID_ANY, "Done", wxPoint(10, 5), wxSize(160, 40), wxBORDER_NONE);
	doneButton->SetBackgroundColour(wxColour(52, 100, 117));
	doneButton->SetForegroundColour(*wxWHITE);
	doneButton->SetFont(wxFont(wxFontInfo(18).Bold()));

	doneButton->Bind(wxEVT_BUTTON, &EditAdminFrame::onDoneClick, this);
	doneButton->Bind(wxEVT_ENTER_WINDOW, &EditAdminFrame::onHover, this);
	doneButton->Bind(wxEVT_LEAVE_WINDOW, &EditAdminFrame::onLeaveHover, this);
}

void EditAdminFrame::onEnterUsername(wxFocusEvent& event) {
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->GetValue() == "Username") {
		object->SetForegroundColour(*wxBLACK);
		object->Clear();
	}
	event.Skip(true);
}

void EditAdminFrame::onLeaveUsername(wxFocusEvent& event) {
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->IsEmpty()) {
		object->SetForegroundColour(wxColour(178, 178, 178));
		object->AppendText("Username");
	}

	event.Skip(true);
}

void EditAdminFrame::onEnterPassword(wxFocusEvent& event) {
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->GetValue() == "Password") {
		object->SetForegroundColour(*wxBLACK);
		object->Clear();
	}
	event.Skip(true);
}

void EditAdminFrame::onLeavePassword(wxFocusEvent& event) {
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->IsEmpty()) {
		object->SetForegroundColour(wxColour(178, 178, 178));
		object->AppendText("Password");
	}

	event.Skip(true);
}

void EditAdminFrame::onEnterDisplayName(wxFocusEvent& event)
{
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->GetValue() == "Display Name") {
		object->SetForegroundColour(*wxBLACK);
		object->Clear();
	}
	event.Skip(true);
}

void EditAdminFrame::onLeaveDisplayName(wxFocusEvent& event)
{
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->IsEmpty()) {
		object->SetForegroundColour(wxColour(178, 178, 178));
		object->AppendText("Display Name");
	}

	event.Skip(true);
}

void EditAdminFrame::onEnterPhoneNumber(wxFocusEvent& event)
{
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->GetValue() == "Number") {
		object->SetForegroundColour(*wxBLACK);
		object->Clear();
	}
	event.Skip(true);
}

void EditAdminFrame::onLeavePhoneNumber(wxFocusEvent& event)
{
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->IsEmpty()) {
		object->SetForegroundColour(wxColour(178, 178, 178));
		object->AppendText("Number");
	}

	event.Skip(true);
}

void EditAdminFrame::onEnterEmail(wxFocusEvent& event)
{
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->GetValue() == "Email") {
		object->SetForegroundColour(*wxBLACK);
		object->Clear();
	}
	event.Skip(true);
}

void EditAdminFrame::onLeaveEmail(wxFocusEvent& event)
{
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->IsEmpty()) {
		object->SetForegroundColour(wxColour(178, 178, 178));
		object->AppendText("Email");
	}

	event.Skip(true);
}

void EditAdminFrame::onEnterInitBalance(wxFocusEvent& event)
{
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->GetValue() == "EGP") {
		object->SetForegroundColour(*wxBLACK);
		object->Clear();
	}
	event.Skip(true);
}

void EditAdminFrame::onLeaveInitBalance(wxFocusEvent& event)
{
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->IsEmpty()) {
		object->SetForegroundColour(wxColour(178, 178, 178));
		object->AppendText("EGP");
	}

	event.Skip(true);
}

void EditAdminFrame::onDoneClick(wxCommandEvent& event)
{
	string error = "Invalid form parameters\n\n";

	string username = string(usernameBox->GetValue().mb_str());
	string displayName = string(displayNameBox->GetValue().mb_str());
	string phoneNumber = string(phoneNumberBox->GetValue().mb_str());
	string email = string(emailBox->GetValue().mb_str());
	string balance = string(balanceBox->GetValue().mb_str());

	if
		(
			username == "Username"
			|| displayName == "Display Name"
			|| phoneNumber == "Number"
			|| email == "Email"
			|| balance == "EGP"
			)
	{
		error += "Please fill out all fields\n\n";
		wxMessageBox(error, "Invalid");
	}
	else {
		if
			(
				Validation::usernameValid(username)
				&& Validation::displayNameValid(displayName)
				&& Validation::phoneNumberValidFormat(phoneNumber)
				&& Validation::emailValidFormat(email)
				&& Validation::initialBalanceValid(balance)
				)
		{
			wxMessageBox("User updated successfully");
			Bank::asAdmin()->editUser
			(
				user,
				username,
				user->getPassword(),
				displayName,
				stod(balance),
				phoneNumber,
				email,
				false
			);

			adminFrame->Show();
			this->Close();
		}
		else if
				(
					!Validation::usernameValid(username)
					&& Validation::displayNameValid(displayName)
					&& Validation::passwordValid(user->getPassword())
					&& Validation::phoneNumberValidFormat(phoneNumber)
					&& Validation::emailValidFormat(email)
					&& user->getUsername() == username
				)
		{
			wxMessageBox("User updated successfully");
			Bank::asAdmin()->editUser
			(
				user,
				username,
				displayName,
				stod(balance),
				phoneNumber,
				email,
				false
			);
			
			adminFrame->Show();
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
			if (!Validation::balanceValid(balance)) {
				error += "Balance Invalid:\n";
				error += "Must be a number more than 0\n";
				error += "\n";
			}
			wxMessageBox(error, "Invalid");
		}
	}
	adminFrame->repaintUsersPanel();
}

void EditAdminFrame::onHover(wxMouseEvent& event) {
	SetCursor(wxCursor(wxCURSOR_HAND));
}

void EditAdminFrame::onLeaveHover(wxMouseEvent& event) {
	SetCursor(wxCursor(wxCURSOR_ARROW));
}

void EditAdminFrame::onClose(wxCloseEvent& event)
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
