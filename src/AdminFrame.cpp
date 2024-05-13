#include "AdminFrame.h"
#include <wx/wx.h>
#include <wx/image.h>
#include "FileSystemManagement.h"
#include "RoundedPanel.h"
#include "Bank.h"
#include "EditAdminFrame.h"
#include "RegisterFrame.h"

AdminFrame::AdminFrame(Admin* admin) : wxFrame(nullptr, wxID_ANY, "HeisenBank")
{
	wxWindow::SetWindowStyle(wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX);

	this->admin = admin;
	mainPanel = new wxPanel(this);
	mainPanel->SetBackgroundColour(wxColour(0, 125, 141));
	Bind(wxEVT_CLOSE_WINDOW, &AdminFrame::onClose, this);

	paintTopPanel();
	paintMidPanel();
}

void AdminFrame::paintMidPanel()
{
	midPanel = new RoundedPanel(mainPanel, wxID_ANY, wxPoint(35, 130), wxSize(550, 840));

	balanceDisplayPanel = new wxPanel(midPanel, wxID_ANY, wxPoint(0, 40), wxSize(600, 50), wxALIGN_CENTRE_HORIZONTAL);
	balanceDisplayPanel->SetBackgroundColour(wxColour(52, 100, 117));

	wxStaticText* displayBalance = new wxStaticText(balanceDisplayPanel, wxID_ANY, "Balance: Unlimited", wxPoint(130, 7), wxSize(300, -1), wxALIGN_CENTRE_HORIZONTAL);
	displayBalance->SetForegroundColour(*wxWHITE);
	displayBalance->SetBackgroundColour(wxColour(52, 100, 117));
	displayBalance->SetFont(wxFont(wxFontInfo(22).Bold()));

	transactionsMidPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(65, 270), wxSize(190, 280), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	transactionsMidPanel->SetBackgroundColour(*wxWHITE);

	wxStaticText* transactionsText = new wxStaticText(transactionsMidPanel, wxID_ANY, "Transactions", wxPoint(0, 180), wxSize(190, -1), wxALIGN_CENTRE_HORIZONTAL);
	transactionsText->SetBackgroundColour(wxColour(229, 229, 229));
	transactionsText->SetFont(wxFont(wxFontInfo(16).Bold()));

	usersMidPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(295, 270), wxSize(190, 280), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	usersMidPanel->SetBackgroundColour(*wxWHITE);

	wxStaticText* usersText = new wxStaticText(usersMidPanel, wxID_ANY, "Users", wxPoint(0, 180), wxSize(190, -1), wxALIGN_CENTRE_HORIZONTAL);
	usersText->SetBackgroundColour(wxColour(229, 229, 229));
	usersText->SetFont(wxFont(wxFontInfo(16).Bold()));

	wxImage transactionsIcon(wxString("resources\\transactions.png"), wxBITMAP_TYPE_PNG);
	transactionsIcon.Rescale(130, 130, wxIMAGE_QUALITY_HIGH);
	wxBitmap transactionsBitmap(transactionsIcon);

	wxBitmapButton* transactionsButton = new wxBitmapButton(transactionsMidPanel, wxID_ANY, transactionsBitmap, wxPoint(30, 20), wxSize(130, 130), wxBU_AUTODRAW | wxBORDER_NONE);
	transactionsButton->SetBackgroundColour(wxColour(229, 229, 229));

	transactionsButton->Bind(wxEVT_ENTER_WINDOW, &AdminFrame::onHover, this);
	transactionsButton->Bind(wxEVT_LEAVE_WINDOW, &AdminFrame::onLeaveHover, this);
	transactionsButton->Bind(wxEVT_BUTTON, &AdminFrame::onTransactionsClick, this);

	wxImage usersIcon(wxString("resources\\users.png"), wxBITMAP_TYPE_PNG);
	usersIcon.Rescale(130, 130, wxIMAGE_QUALITY_HIGH);

	wxBitmap usersBitmap(usersIcon);
	wxBitmapButton* usersButton = new wxBitmapButton(usersMidPanel, wxID_ANY, usersBitmap, wxPoint(30, 20), wxSize(130, 130), wxBU_AUTODRAW | wxBORDER_NONE);
	usersButton->SetBackgroundColour(wxColour(229, 229, 229));

	usersButton->Bind(wxEVT_ENTER_WINDOW, &AdminFrame::onHover, this);
	usersButton->Bind(wxEVT_LEAVE_WINDOW, &AdminFrame::onLeaveHover, this);
	usersButton->Bind(wxEVT_BUTTON, &AdminFrame::onUsersClick, this);
}
void AdminFrame::paintTopPanel()
{
	topPanel = new wxPanel(mainPanel, wxID_ANY, wxPoint(0, 0), wxSize(620, 110));

	topPanel->SetBackgroundColour(wxColour(52, 100, 117));
	wxPNGHandler* handler = new wxPNGHandler;
	wxImage::AddHandler(handler);

	wxStaticText* textHALLO = new wxStaticText(topPanel, wxID_ANY, "Hey Boss", wxPoint(100, 40), wxSize(420, 80), wxALIGN_CENTRE_HORIZONTAL);
	textHALLO->SetForegroundColour(*wxWHITE);
	textHALLO->SetFont(wxFont(wxFontInfo(20).Bold()));
}

void AdminFrame::paintTransactionsPanel()
{
	transactionsPanel = new wxScrolled<wxPanel>(midPanel, wxID_ANY, wxPoint(0, 90), wxSize(566, 730));
	transactionsPanel->SetScrollRate(0, FromDIP(20));
	transactionsPanel->SetBackgroundColour(*wxWHITE);

	wxImage backIcon(wxString("resources\\back.png"), wxBITMAP_TYPE_PNG);
	backIcon.Rescale(25, 35, wxIMAGE_QUALITY_HIGH);

	wxBitmap backBitmap(backIcon);
	transactionsBackButton = new wxBitmapButton(balanceDisplayPanel, wxID_ANY, backBitmap, wxPoint(40, 8), wxSize(25, 35), wxBU_AUTODRAW | wxBORDER_NONE);
	transactionsBackButton->SetBackgroundColour(wxColour(52, 100, 117));

	transactionsBackButton->Bind(wxEVT_ENTER_WINDOW, &AdminFrame::onHover, this);
	transactionsBackButton->Bind(wxEVT_LEAVE_WINDOW, &AdminFrame::onLeaveHover, this);
	transactionsBackButton->Bind(wxEVT_BUTTON, &AdminFrame::onTransacionBackButtonClick, this);

	wxImage rejectedIcon(wxString("resources\\rejected.png"), wxBITMAP_TYPE_PNG);
	rejectedIcon.Rescale(60, 60, wxIMAGE_QUALITY_HIGH);

	wxImage acceptedIcon(wxString("resources\\accepted.png"), wxBITMAP_TYPE_PNG);
	acceptedIcon.Rescale(60, 60, wxIMAGE_QUALITY_HIGH);

	wxImage pendingIcon(wxString("resources\\pending.png"), wxBITMAP_TYPE_PNG);
	pendingIcon.Rescale(60, 60, wxIMAGE_QUALITY_HIGH);

	/*auto panel = new wxScrolled<wxPanel>(midPanel, wxID_ANY, wxPoint(20, 20), wxSize(500, 600));
	panel->SetBackgroundColour(!wxWHITE);*/

	int pointY = 30;
	int totalScrollHeight = 0;

	auto transactions = Bank::getTransactions()->get();

	for (auto it = transactions.begin(); it != transactions.end(); ++it)
	{
		Transaction* tans = *it;

		wxPanel* transactionDetailsPanel = new RoundedPanel(transactionsPanel, wxID_ANY, wxPoint(35, pointY), wxSize(480, 150), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
		transactionDetailsPanel->SetBackgroundColour(*wxWHITE);

		if (tans->getState() == 1)
		{
			wxBitmap transactionState(rejectedIcon);
			wxBitmapButton* transactionStateHolder = new wxBitmapButton(transactionDetailsPanel, wxID_ANY, transactionState, wxPoint(20, 45), wxSize(60, 60), wxBU_AUTODRAW | wxBORDER_NONE);
			transactionStateHolder->SetBackgroundColour(wxColour(229, 229, 229));

			wxStaticText* stateText = new wxStaticText(transactionDetailsPanel, wxID_ANY, "Request Rejected", wxPoint(8, 8), wxSize(464, -1), wxALIGN_CENTRE_HORIZONTAL);
			stateText->SetBackgroundColour(wxColour(229, 229, 229));
			stateText->SetFont(wxFont(wxFontInfo(16)));
		}
		else if (tans->getState() == 2 || tans->getState() == 3)
		{
			wxBitmap transactionState(acceptedIcon);
			wxBitmapButton* transactionStateHolder = new wxBitmapButton(transactionDetailsPanel, wxID_ANY, transactionState, wxPoint(20, 45), wxSize(60, 60), wxBU_AUTODRAW | wxBORDER_NONE);
			transactionStateHolder->SetBackgroundColour(wxColour(229, 229, 229));

			wxStaticText* stateText = new wxStaticText(transactionDetailsPanel, wxID_ANY, "Transaction Successful", wxPoint(8, 8), wxSize(464, -1), wxALIGN_CENTRE_HORIZONTAL);
			stateText->SetBackgroundColour(wxColour(229, 229, 229));
			stateText->SetFont(wxFont(wxFontInfo(16)));
		}
		else
		{
			wxBitmap transactionState(pendingIcon);
			wxBitmapButton* transactionStateHolder = new wxBitmapButton(transactionDetailsPanel, wxID_ANY, transactionState, wxPoint(20, 45), wxSize(60, 60), wxBU_AUTODRAW | wxBORDER_NONE);
			transactionStateHolder->SetBackgroundColour(wxColour(229, 229, 229));

			wxStaticText* stateText = new wxStaticText(transactionDetailsPanel, wxID_ANY, "Transaction Pending", wxPoint(8, 8), wxSize(464, -1), wxALIGN_CENTRE_HORIZONTAL);
			stateText->SetBackgroundColour(wxColour(229, 229, 229));
			stateText->SetFont(wxFont(wxFontInfo(16)));
		}

		wxStaticText* senderText = new wxStaticText(transactionDetailsPanel, wxID_ANY, tans->getSender()->getUsername() + " => " + tans->getRecipient()->getUsername(), wxPoint(130, 63), wxSize(200, -1), wxALIGN_CENTRE_HORIZONTAL);
		senderText->SetBackgroundColour(wxColour(229, 229, 229));
		senderText->SetFont(wxFont(wxFontInfo(16).Bold()));

		wxStaticText* amountText = new wxStaticText(transactionDetailsPanel, wxID_ANY, to_string(tans->getAmount()).substr(0, to_string(tans->getAmount()).length() - 4) + "EGP", wxPoint(235, 110), wxSize(235, -1), wxALIGN_RIGHT);
		amountText->SetBackgroundColour(wxColour(229, 229, 229));
		amountText->SetForegroundColour(wxColour(0, 125, 141));
		amountText->SetFont(wxFont(wxFontInfo(20).Bold()));

		wxStaticText* transactionIDText = new wxStaticText(transactionDetailsPanel, wxID_ANY, "   #" + to_string(tans->getEpochTime()), wxPoint(5, 120), wxSize(235, -1), wxALIGN_LEFT);
		transactionIDText->SetBackgroundColour(wxColour(229, 229, 229));
		transactionIDText->SetForegroundColour(wxColour(126, 126, 126));
		transactionIDText->SetFont(wxFont(wxFontInfo(12)));

		wxStaticText* transactionTime = new wxStaticText(transactionDetailsPanel, wxID_ANY, tans->getDisplayTime(), wxPoint(150, 120), wxSize(-1, -1), wxALIGN_CENTRE_HORIZONTAL);
		transactionTime->SetBackgroundColour(wxColour(229, 229, 229));
		transactionTime->SetForegroundColour(wxColour(178, 178, 178));
		transactionTime->SetFont(wxFont(wxFontInfo(12)));

		totalScrollHeight += 180;
		pointY += 180;

	}

	transactionsPanel->SetScrollbar(wxVERTICAL, 0, 500, totalScrollHeight, 500);
	transactionsPanel->SetVirtualSize(wxSize(0, totalScrollHeight));

	transactionsMidPanel->Hide();
	usersMidPanel->Hide();
}

void AdminFrame::repaintUsersPanel()
{
	MSWClickButtonIfPossible(usersBackButton);
	paintUsersPanel();
}

void AdminFrame::paintUsersPanel()
{
	
	wxImage backIcon(wxString("resources\\back.png"), wxBITMAP_TYPE_PNG);
	backIcon.Rescale(25, 35, wxIMAGE_QUALITY_HIGH);

	wxBitmap backBitmap(backIcon);
	usersBackButton = new wxBitmapButton(balanceDisplayPanel, wxID_ANY, backBitmap, wxPoint(40, 8), wxSize(25, 35), wxBU_AUTODRAW | wxBORDER_NONE);
	usersBackButton->SetBackgroundColour(wxColour(52, 100, 117));

	usersBackButton->Bind(wxEVT_ENTER_WINDOW, &AdminFrame::onHover, this);
	usersBackButton->Bind(wxEVT_LEAVE_WINDOW, &AdminFrame::onLeaveHover, this);
	usersBackButton->Bind(wxEVT_BUTTON, &AdminFrame::onUsersBackButtonClick, this);

	usersPanel = new wxScrolled<wxPanel>(midPanel, wxID_ANY, wxPoint(0, 90), wxSize(566, 630));
	usersPanel->SetScrollRate(0, FromDIP(20));
	usersPanel->SetBackgroundColour(*wxWHITE);

	addUserPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(-15, 720), wxSize(620, 60), wxALIGN_CENTRE_HORIZONTAL, wxColour(52, 100, 117));
	//addUserPanel->SetBackgroundColour(wxColour(346475));

	wxImage pfpIcon(wxString("resources\\profile.png"), wxBITMAP_TYPE_PNG);
	pfpIcon.Rescale(80, 80, wxIMAGE_QUALITY_HIGH);

	wxImage editIcon(wxString("resources\\editUser.png"), wxBITMAP_TYPE_PNG);
	editIcon.Rescale(40, 40, wxIMAGE_QUALITY_HIGH);

	wxImage deleteIcon(wxString("resources\\deleteUser.png"), wxBITMAP_TYPE_PNG);
	deleteIcon.Rescale(40, 40, wxIMAGE_QUALITY_HIGH);

	wxImage addIcon(wxString("resources\\addUser.png"), wxBITMAP_TYPE_PNG);
	addIcon.Rescale(50, 50, wxIMAGE_QUALITY_HIGH);

		int usersPanelScrollHeight = 0;
		int usersPointY = 30;

		auto users = Bank::getUsers()->getUsers();

		for (auto it = users.begin(); it != users.end(); ++it)
		{
			User* user = *it;

			if (user->getUsername() == "deleteduser" || user->getUsername() == "system")
			{
				continue;
			}
				wxPanel* userDetailsPanel = new RoundedPanel(usersPanel, wxID_ANY, wxPoint(35, usersPointY), wxSize(480, 200), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
				userDetailsPanel->SetBackgroundColour(*wxWHITE);

				wxPanel* editButtonPanel = new RoundedPanel(userDetailsPanel, wxID_ANY, wxPoint(50, 145), wxSize(100, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(0, 125, 141));
				editButtonPanel->SetBackgroundColour(wxColour(229, 229, 229));

				wxPanel* deleteButtonPanel = new RoundedPanel(userDetailsPanel, wxID_ANY, wxPoint(330, 145), wxSize(100, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(0, 125, 141));
				deleteButtonPanel->SetBackgroundColour(wxColour(229, 229, 229));

				wxBitmap editBitmap(editIcon);
				wxBitmapButton* editButton = new wxBitmapButton(editButtonPanel, wxID_ANY, editBitmap, wxPoint(33, 5), wxSize(40, 40), wxBU_AUTODRAW | wxBORDER_NONE);
				editButton->SetBackgroundColour(wxColour(0, 125, 141));

				wxBitmap deleteBitmap(deleteIcon);
				wxBitmapButton* deleteButton = new wxBitmapButton(deleteButtonPanel, wxID_ANY, deleteBitmap, wxPoint(31, 5), wxSize(40, 40), wxBU_AUTODRAW | wxBORDER_NONE);
				deleteButton->SetBackgroundColour(wxColour(0, 125, 141));

				wxBitmap addBitmap(addIcon);
				wxBitmapButton* addButton = new wxBitmapButton(addUserPanel, wxID_ANY, addBitmap, wxPoint(275, 5), wxSize(50, 50), wxBU_AUTODRAW | wxBORDER_NONE);
				addButton->SetBackgroundColour(wxColour(52, 100, 117));

				editButton->Bind(wxEVT_ENTER_WINDOW, &AdminFrame::onHover, this);
				editButton->Bind(wxEVT_LEAVE_WINDOW, &AdminFrame::onLeaveHover, this);
				editButton->Bind
				(
					wxEVT_COMMAND_BUTTON_CLICKED, [=](wxCommandEvent& evt)
					{
						EditAdminFrame* editFrame = new EditAdminFrame(user, this);
						editFrame->SetClientSize(620, 1000);
						editFrame->Center();
						editFrame->Show();
						editFrame->SetIcon(GetIcon());
					}
				);

				deleteButton->Bind(wxEVT_ENTER_WINDOW, &AdminFrame::onHover, this);
				deleteButton->Bind(wxEVT_LEAVE_WINDOW, &AdminFrame::onLeaveHover, this);
				deleteButton->Bind
				(
					wxEVT_COMMAND_BUTTON_CLICKED, [=](wxCommandEvent& evt)
					{
						admin->deleteUser(user);
						repaintUsersPanel();
					}
				);

				addButton->Bind(wxEVT_ENTER_WINDOW, &AdminFrame::onHover, this);
				addButton->Bind(wxEVT_LEAVE_WINDOW, &AdminFrame::onLeaveHover, this);
				addButton->Bind
				(
					wxEVT_COMMAND_BUTTON_CLICKED, [=](wxCommandEvent& evt)
					{
						RegisterFrame* registerFrame = new RegisterFrame(this);
						registerFrame->SetClientSize(620, 1000);
						registerFrame->Center();
						registerFrame->Show();
						registerFrame->SetIcon(GetIcon());

						this->Hide();
					}
				);

				wxBitmap userImage(pfpIcon);
				wxBitmapButton* userImageHolder = new wxBitmapButton(userDetailsPanel, wxID_ANY, userImage, wxPoint(20, 45), wxSize(80, 80), wxBU_AUTODRAW | wxBORDER_NONE);
				userImageHolder->SetBackgroundColour(wxColour(229, 229, 229));

				wxStaticText* stateText = new wxStaticText(userDetailsPanel, wxID_ANY, user->getSuspended() ? "Suspended":"Active", wxPoint(8, 8), wxSize(464, -1), wxALIGN_CENTRE_HORIZONTAL);
				stateText->SetBackgroundColour(wxColour(229, 229, 229));
				stateText->SetFont(wxFont(wxFontInfo(16)));

				wxStaticText* usernameText = new wxStaticText(userDetailsPanel, wxID_ANY, user->getUsername(), wxPoint(150, 80), wxSize(180, -1), wxALIGN_CENTRE_HORIZONTAL);
				usernameText->SetBackgroundColour(wxColour(229, 229, 229));
				usernameText->SetFont(wxFont(wxFontInfo(16).Bold()));

				usersPanelScrollHeight += 270;
				usersPointY += 270;
			
		}

			usersPanel->SetScrollbar(wxVERTICAL, 0, 500, usersPanelScrollHeight, 500);
			usersPanel->SetVirtualSize(wxSize(0, usersPanelScrollHeight));

			transactionsMidPanel->Hide();
			usersMidPanel->Hide();
}


void AdminFrame::onTransacionBackButtonClick(wxCommandEvent& event)
{
	transactionsMidPanel->Show();
	usersMidPanel->Show();

	transactionsPanel->Hide();
	transactionsBackButton->Hide();
}

void AdminFrame::onUsersBackButtonClick(wxCommandEvent& event)
{
	transactionsMidPanel->Show();
	usersMidPanel->Show();

	addUserPanel->Hide();
	usersPanel->Hide();
	usersBackButton->Hide();

}

void AdminFrame::onTransactionsClick(wxCommandEvent& event)
{
	paintTransactionsPanel();
}

void AdminFrame::onUsersClick(wxCommandEvent& event)
{
	paintUsersPanel();
}

void AdminFrame::onHover(wxMouseEvent& event)
{
	SetCursor(wxCursor(wxCURSOR_HAND));
}

void AdminFrame::onLeaveHover(wxMouseEvent& event)
{
	SetCursor(wxCursor(wxCURSOR_ARROW));
}

void AdminFrame::onClose(wxCloseEvent& event)
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