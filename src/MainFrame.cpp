#include <wx/wx.h>
#include <wx/image.h>
#include "MainFrame.h"
#include "FileSystemManagement.h"
#include "RoundedPanel.h"
#include "ImageButton.h"


MainFrame::MainFrame(User* user, const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	mainPanel = new wxPanel(this);
	mainPanel->SetBackgroundColour(wxColour(0, 125, 141));
	this->user = user;
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

	bellButton->Bind(wxEVT_ENTER_WINDOW, &MainFrame::onHover, this);
	bellButton->Bind(wxEVT_LEAVE_WINDOW, &MainFrame::onLeaveHover, this);

	pfpButton->Bind(wxEVT_ENTER_WINDOW, &MainFrame::onHover, this);
	pfpButton->Bind(wxEVT_LEAVE_WINDOW, &MainFrame::onLeaveHover, this);


}
void MainFrame::paintMidPanel()
{
	midPanel = new RoundedPanel(mainPanel, wxID_ANY, wxPoint(35, 130), wxSize(550, 820), wxALIGN_CENTRE_HORIZONTAL, *wxWHITE);

	wxStaticText* displayBalance = new wxStaticText(midPanel, wxID_ANY, "Balance: " + to_string((*user).getBalance()).substr(0, to_string((*user).getBalance()).find(".") + 2), wxPoint(0, 40), wxSize(550, 30), wxALIGN_CENTRE_HORIZONTAL);
	displayBalance->SetForegroundColour(*wxWHITE);
	displayBalance->SetBackgroundColour(wxColour(52, 100, 117));
	displayBalance->SetFont(wxFont(wxFontInfo(22).Bold()));

	sendMoneyPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(65, 170), wxSize(190, 250), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	sendMoneyPanel->SetBackgroundColour(*wxWHITE);
	wxStaticText* sendMoneyText = new wxStaticText(sendMoneyPanel, wxID_ANY, "Send\nMoney", wxPoint(0, 180), wxSize(190, -1), wxALIGN_CENTRE_HORIZONTAL);
	sendMoneyText->SetBackgroundColour(wxColour(229, 229, 229));
	sendMoneyText->SetFont(wxFont(wxFontInfo(16).Bold()));

	requestMoneyPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(295, 170), wxSize(190, 250), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	requestMoneyPanel->SetBackgroundColour(*wxWHITE);
	wxStaticText* requestMoneyText = new wxStaticText(requestMoneyPanel, wxID_ANY, "Request\nMoney", wxPoint(0, 180), wxSize(190, -1), wxALIGN_CENTRE_HORIZONTAL);
	requestMoneyText->SetBackgroundColour(wxColour(229, 229, 229));
	requestMoneyText->SetFont(wxFont(wxFontInfo(16).Bold()));

	transactionButtonPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(65, 460), wxSize(190, 250), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	transactionButtonPanel->SetBackgroundColour(*wxWHITE);
	wxStaticText* transactionsText = new wxStaticText(transactionButtonPanel, wxID_ANY, "Transaction\nHistory", wxPoint(0, 180), wxSize(190, -1), wxALIGN_CENTRE_HORIZONTAL);
	transactionsText->SetBackgroundColour(wxColour(229, 229, 229));
	transactionsText->SetFont(wxFont(wxFontInfo(16).Bold()));

	rechargeBalancePanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(295, 460), wxSize(190, 250), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	rechargeBalancePanel->SetBackgroundColour(*wxWHITE);
	wxStaticText* rechargeBalanceText = new wxStaticText(rechargeBalancePanel, wxID_ANY, "Recharge\nBalance", wxPoint(0, 180), wxSize(190, -1), wxALIGN_CENTRE_HORIZONTAL);
	rechargeBalanceText->SetBackgroundColour(wxColour(229, 229, 229));
	rechargeBalanceText->SetFont(wxFont(wxFontInfo(16).Bold()));

	wxImage sendMoneyIcon(wxString("resources\\sendMoney.png"), wxBITMAP_TYPE_PNG);
	sendMoneyIcon.Rescale(130, 130, wxIMAGE_QUALITY_HIGH);
	wxBitmap sendMoneyBitmap(sendMoneyIcon);
	wxBitmapButton* sendMoneyButton = new wxBitmapButton(sendMoneyPanel, wxID_ANY, sendMoneyBitmap, wxPoint(30, 20), wxSize(130, 130), wxBU_AUTODRAW | wxBORDER_NONE);
	sendMoneyButton->SetBackgroundColour(wxColour(229, 229, 229));
	sendMoneyButton->Bind(wxEVT_BUTTON, &MainFrame::onSendMoneyClick, this);

	wxImage requestMoneyIcon(wxString("resources\\requestMoney.png"), wxBITMAP_TYPE_PNG);
	requestMoneyIcon.Rescale(130, 130, wxIMAGE_QUALITY_HIGH);
	wxBitmap requestMoneyBitmap(requestMoneyIcon);
	wxBitmapButton* requestMoneyButton = new wxBitmapButton(requestMoneyPanel, wxID_ANY, requestMoneyBitmap, wxPoint(30, 20), wxSize(130, 130), wxBU_AUTODRAW | wxBORDER_NONE);
	requestMoneyButton->SetBackgroundColour(wxColour(229, 229, 229));
	requestMoneyButton->Bind(wxEVT_BUTTON, &MainFrame::onBellButtonClick, this);

	wxImage transactionsIcon(wxString("resources\\transactions.png"), wxBITMAP_TYPE_PNG);
	transactionsIcon.Rescale(130, 130, wxIMAGE_QUALITY_HIGH);
	wxBitmap transactionBitmap(transactionsIcon);
	wxBitmapButton* transactionButton = new wxBitmapButton(transactionButtonPanel, wxID_ANY, transactionBitmap, wxPoint(42, 20), wxSize(130, 130), wxBU_AUTODRAW | wxBORDER_NONE);
	transactionButton->SetBackgroundColour(wxColour(229, 229, 229));
	transactionButton->Bind(wxEVT_BUTTON, &MainFrame::onBellButtonClick, this);

	wxImage rechargeIcon(wxString("resources\\rechargeMoney.png"), wxBITMAP_TYPE_PNG);
	rechargeIcon.Rescale(130, 130, wxIMAGE_QUALITY_HIGH);
	wxBitmap rechargeBitmap(rechargeIcon);
	wxBitmapButton* rechargeButton = new wxBitmapButton(rechargeBalancePanel, wxID_ANY, rechargeBitmap, wxPoint(30, 20), wxSize(130, 130), wxBU_AUTODRAW | wxBORDER_NONE);
	rechargeButton->SetBackgroundColour(wxColour(229, 229, 229));
	rechargeButton->Bind(wxEVT_BUTTON, &MainFrame::onBellButtonClick, this);

	sendMoneyButton->Bind(wxEVT_ENTER_WINDOW, &MainFrame::onHover, this);
	sendMoneyButton->Bind(wxEVT_LEAVE_WINDOW, &MainFrame::onLeaveHover, this);

	requestMoneyButton->Bind(wxEVT_ENTER_WINDOW, &MainFrame::onHover, this);
	requestMoneyButton->Bind(wxEVT_LEAVE_WINDOW, &MainFrame::onLeaveHover, this);

	transactionButton->Bind(wxEVT_ENTER_WINDOW, &MainFrame::onHover, this);
	transactionButton->Bind(wxEVT_LEAVE_WINDOW, &MainFrame::onLeaveHover, this);

	rechargeButton->Bind(wxEVT_ENTER_WINDOW, &MainFrame::onHover, this);
	rechargeButton->Bind(wxEVT_LEAVE_WINDOW, &MainFrame::onLeaveHover, this);
		

}
void MainFrame::paintSendPanel()
{
	usernameInputPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(215, 200), wxSize(240, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	usernameInputPanel->SetBackgroundColour(*wxWHITE);

	recieverNameBox = new wxTextCtrl(usernameInputPanel, wxID_ANY, "Username", wxPoint(10, 13), wxSize(220, 30), wxTE_CENTRE | wxBORDER_NONE);
	recieverNameBox->SetBackgroundColour(wxColour(229, 229, 229));
	recieverNameBox->SetForegroundColour(wxColour(178, 178, 178));
	recieverNameBox->SetFont(wxFont(wxFontInfo(14).Bold()));

	recieverNameBox->Bind(wxEVT_SET_FOCUS, &MainFrame::onEnterUsername, this);
	recieverNameBox->Bind(wxEVT_KILL_FOCUS, &MainFrame::onLeaveUsername, this);

	amountInputPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(215, 400), wxSize(240, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	amountInputPanel->SetBackgroundColour(*wxWHITE);

	recieverText = new wxStaticText(midPanel, wxID_ANY, "Reciever's", wxPoint(70, 213), wxSize(-1, -1), wxALIGN_CENTRE_HORIZONTAL);
	recieverText->SetBackgroundColour(*wxWHITE);
	recieverText->SetForegroundColour(*wxBLACK);
	recieverText->SetFont(wxFont(wxFontInfo(14).Bold()));

	amountBox = new wxTextCtrl(amountInputPanel, wxID_ANY, "EGP", wxPoint(10, 13), wxSize(220, 30), wxTE_CENTRE | wxBORDER_NONE);
	amountBox->SetBackgroundColour(wxColour(229, 229, 229));
	amountBox->SetForegroundColour(wxColour(178, 178, 178));
	amountBox->SetFont(wxFont(wxFontInfo(14).Bold()));

	amountBox->Bind(wxEVT_SET_FOCUS, &MainFrame::onEnterAmount, this);
	amountBox->Bind(wxEVT_KILL_FOCUS, &MainFrame::onLeaveAmount, this);

	amountText = new wxStaticText(midPanel, wxID_ANY, "Amount", wxPoint(70, 413), wxSize(-1, -1), wxALIGN_CENTRE_HORIZONTAL);
	amountText->SetBackgroundColour(*wxWHITE);
	amountText->SetForegroundColour(*wxBLACK);
	amountText->SetFont(wxFont(wxFontInfo(14).Bold()));

	sendButtonPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(185, 600), wxSize(180, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(52, 100, 117));
	sendButtonPanel->SetBackgroundColour(*wxWHITE);

	sendButton = new wxButton(sendButtonPanel, wxID_ANY, "Send", wxPoint(10, 5), wxSize(160, 40), wxBORDER_NONE);
	sendButton->SetBackgroundColour(wxColour(52, 100, 117));
	sendButton->SetForegroundColour(*wxWHITE);
	sendButton->SetFont(wxFont(wxFontInfo(18).Bold()));
	sendButton->Bind(wxEVT_BUTTON, &MainFrame::onSendClick, this);

	sendButton->Bind(wxEVT_ENTER_WINDOW, &MainFrame::onHover, this);
	sendButton->Bind(wxEVT_LEAVE_WINDOW, &MainFrame::onLeaveHover, this);

	sendMoneyPanel->Hide();
	requestMoneyPanel->Hide();
	transactionButtonPanel->Hide();
	rechargeBalancePanel->Hide();
}
void MainFrame::paintTransactionsPanel()
{
	wxImage rejectedIcon(wxString("resources\\rejected.png"), wxBITMAP_TYPE_PNG);
	rejectedIcon.Rescale(60, 60, wxIMAGE_QUALITY_HIGH);

	wxImage acceptedIcon(wxString("resources\\accepted.png"), wxBITMAP_TYPE_PNG);
	acceptedIcon.Rescale(60, 60, wxIMAGE_QUALITY_HIGH);

	wxImage pendingIcon(wxString("resources\\pending.png"), wxBITMAP_TYPE_PNG);
	pendingIcon.Rescale(60, 60, wxIMAGE_QUALITY_HIGH);
	
	int pointY = 150;

	for (Transaction* tans : Bank::getTransactions()->get(&Bank::getUsers()->at(user->getUsername())))
	{

		wxPanel* transactionDetailsPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(35, pointY), wxSize(480, 150), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
		transactionDetailsPanel->SetBackgroundColour(*wxWHITE);

		if (tans->getFlag() == -1)
		{
			wxBitmap transactionState(rejectedIcon);
			wxStaticBitmap* transactionStateHolder = new wxStaticBitmap(transactionDetailsPanel, wxID_ANY, transactionState, wxPoint(20, 45), wxSize(60, 60), wxBU_AUTODRAW | wxBORDER_NONE);
			transactionStateHolder->SetBackgroundColour(wxColour(229, 229, 229));

			wxStaticText* stateText = new wxStaticText(transactionDetailsPanel, wxID_ANY, "Request Rejected", wxPoint(8, 8), wxSize(464, -1), wxALIGN_CENTRE_HORIZONTAL);
			stateText->SetBackgroundColour(wxColour(229, 229, 229));
			stateText->SetFont(wxFont(wxFontInfo(16)));
		}
		else if (tans->getFlag() == 1)
		{
			wxBitmap transactionState(acceptedIcon);
			wxStaticBitmap* transactionStateHolder = new wxStaticBitmap(transactionDetailsPanel, wxID_ANY, transactionState, wxPoint(20, 45), wxSize(70, 60), wxBU_AUTODRAW | wxBORDER_NONE);
			transactionStateHolder->SetBackgroundColour(wxColour(229, 229, 229));

			wxStaticText* stateText = new wxStaticText(transactionDetailsPanel, wxID_ANY, "Transaction Successful", wxPoint(8, 8), wxSize(464, -1), wxALIGN_CENTRE_HORIZONTAL);
			stateText->SetBackgroundColour(wxColour(229, 229, 229));
			stateText->SetFont(wxFont(wxFontInfo(16)));
		}
		else
		{
			wxBitmap transactionState(pendingIcon);
			wxStaticBitmap* transactionStateHolder = new wxStaticBitmap(transactionDetailsPanel, wxID_ANY, transactionState, wxPoint(20, 45), wxSize(60, 60), wxBU_AUTODRAW | wxBORDER_NONE);
			transactionStateHolder->SetBackgroundColour(wxColour(229, 229, 229));

			wxStaticText* stateText = new wxStaticText(transactionDetailsPanel, wxID_ANY, "Transaction Pending", wxPoint(8, 8), wxSize(464, -1), wxALIGN_CENTRE_HORIZONTAL);
			stateText->SetBackgroundColour(wxColour(229, 229, 229));
			stateText->SetFont(wxFont(wxFontInfo(16)));
		}

		wxStaticText* senderText = new wxStaticText(transactionDetailsPanel, wxID_ANY, tans->getSender()->getUsername()+" => "+tans->getReciever()->getUsername(), wxPoint(100, 63), wxSize(200, -1), wxALIGN_CENTRE_HORIZONTAL);
		senderText->SetBackgroundColour(wxColour(229, 229, 229));
		senderText->SetFont(wxFont(wxFontInfo(16).Bold()));

		wxStaticText* amountText = new wxStaticText(transactionDetailsPanel, wxID_ANY,to_string(tans->getAmount()).substr(0, to_string((*user).getBalance()).find(".") + 2) + "EGP", wxPoint(235, 110), wxSize(235, -1), wxALIGN_RIGHT);
		amountText->SetBackgroundColour(wxColour(229, 229, 229));
		amountText->SetForegroundColour(wxColour(0, 125, 141));
		amountText->SetFont(wxFont(wxFontInfo(20).Bold()));

		wxStaticText* transactionIDText = new wxStaticText(transactionDetailsPanel, wxID_ANY,"   #" + to_string(tans->getEpochTime()), wxPoint(5, 120), wxSize(235, -1), wxALIGN_LEFT);
		transactionIDText->SetBackgroundColour(wxColour(229, 229, 229));
		transactionIDText->SetForegroundColour(wxColour(126, 126, 126));
		transactionIDText->SetFont(wxFont(wxFontInfo(12)));

		wxStaticText* transactionTime = new wxStaticText(transactionDetailsPanel, wxID_ANY, tans->getDisplayTime(), wxPoint(350, 180), wxSize(-1, -1), wxALIGN_CENTRE_HORIZONTAL);
		transactionTime->SetBackgroundColour(wxColour(229, 229, 229));
		transactionTime->SetForegroundColour(wxColour(178, 178, 178));
		transactionTime->SetFont(wxFont(wxFontInfo(12)));

		pointY += 180;
	}

	sendMoneyPanel->Hide();
	requestMoneyPanel->Hide();
	transactionButtonPanel->Hide();
	rechargeBalancePanel->Hide();
	
}

void MainFrame::onBellButtonClick(wxCommandEvent& event)
{	
	printf("HAAALLLLOOOOOOO\n");
	paintTransactionsPanel();
	
}

void MainFrame::onSendMoneyClick(wxCommandEvent& event)
{
	paintSendPanel();
}

void MainFrame::onSendClick(wxCommandEvent& event)
{
	printf("\nAuthentication to be done later\n");

	sendMoneyPanel->Show();
	requestMoneyPanel->Show();
	transactionButtonPanel->Show();
	rechargeBalancePanel->Show();

	usernameInputPanel->Hide();
	recieverNameBox->Hide();
	amountInputPanel->Hide();
	sendButtonPanel->Hide();
	sendButton->Hide();
	amountBox->Hide();
	amountText->Hide();
	recieverText->Hide();

}

//copious amounts of suffering

void MainFrame::onEnterUsername(wxFocusEvent& event) {
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->GetValue() == "Username") {
		object->SetForegroundColour(*wxBLACK);
		object->Clear();
	}
	event.Skip(true);
}

void MainFrame::onLeaveUsername(wxFocusEvent& event) {
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->IsEmpty()) {
		object->SetForegroundColour(wxColour(178, 178, 178));
		object->AppendText("Username");
	}

	event.Skip(true);
}

void MainFrame::onEnterAmount(wxFocusEvent& event) {
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->GetValue() == "EGP") {
		object->SetForegroundColour(*wxBLACK);
		object->Clear();
	}
	event.Skip(true);
}

void MainFrame::onLeaveAmount(wxFocusEvent& event) {
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->IsEmpty()) {
		object->SetForegroundColour(wxColour(178, 178, 178));
		object->AppendText("EGP");
	}

	event.Skip(true);
}

void MainFrame::onHover(wxMouseEvent& event) {
	SetCursor(wxCursor(wxCURSOR_HAND));
}

void MainFrame::onLeaveHover(wxMouseEvent& event) {
	SetCursor(wxCursor(wxCURSOR_ARROW));
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
