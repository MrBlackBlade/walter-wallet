#include <wx/wx.h>
#include <wx/image.h>
#include "MainFrame.h"
#include "FileSystemManagement.h"
#include "RoundedPanel.h"
#include "Bank.h"

MainFrame::MainFrame(User* user, const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	mainPanel = new wxPanel(this);
	mainPanel->SetBackgroundColour(wxColour(0, 125, 141));
	this->user = user;
	Bind(wxEVT_CLOSE_WINDOW, &MainFrame::onClose, this);
	paintTopPanel();
	paintMidPanel();
}

//panels
void MainFrame::paintTopPanel()
{
	topPanel = new wxPanel(mainPanel, wxID_ANY, wxPoint(0, 0), wxSize(620, 110));

	topPanel->SetBackgroundColour(wxColour(52, 100, 117));
	wxPNGHandler* handler = new wxPNGHandler;
	wxImage::AddHandler(handler);

	wxStaticText* textHALLO = new wxStaticText(topPanel, wxID_ANY, "Welcome Back", wxPoint(100, 20), wxSize(420, 80), wxALIGN_CENTRE_HORIZONTAL);
	textHALLO->SetForegroundColour(*wxWHITE);
	textHALLO->SetFont(wxFont(wxFontInfo(18)));

	wxStaticText* textDisplayName = new wxStaticText(topPanel, wxID_ANY, (*user).getDisplayName(), wxPoint(100, 55), wxSize(420, 80), wxALIGN_CENTRE_HORIZONTAL);
	textDisplayName->SetForegroundColour(*wxWHITE); // Set text color
	textDisplayName->SetFont(wxFont(wxFontInfo(22).Bold())); // Set font



	
	/*if (hasRequest == true)
	{
		wxBitmap bellBitmap(bellAlertIcon);
		bellButton = new wxBitmapButton(topPanel, wxID_ANY, bellBitmap, wxPoint(525, 15), wxSize(80, 80), wxBU_AUTODRAW | wxBORDER_NONE);
		bellButton->SetBackgroundColour(wxColour(52, 100, 117));
		bellButton->Bind(wxEVT_BUTTON, &MainFrame::onBellButtonClick, this);
	}
	else
	{
		wxBitmap bellBitmap(bellIcon);
		bellButton = new wxBitmapButton(topPanel, wxID_ANY, bellBitmap, wxPoint(525, 15), wxSize(80, 80), wxBU_AUTODRAW | wxBORDER_NONE);
		bellButton->SetBackgroundColour(wxColour(52, 100, 117));
		bellButton->Bind(wxEVT_BUTTON, &MainFrame::onBellButtonClick, this);
	}*/
	
	wxImage pfpIcon(wxT("resources\\profile.png"), wxBITMAP_TYPE_PNG);
	pfpIcon.Rescale(80, 80, wxIMAGE_QUALITY_HIGH); // Rescale the image to 60x60
	wxBitmap pfpBitmap(pfpIcon);
	pfpButton = new wxBitmapButton(topPanel, wxID_ANY, pfpBitmap, wxPoint(15, 15), wxSize(80, 80), wxBU_AUTODRAW | wxBORDER_NONE);
	pfpButton->SetBackgroundColour(wxColour(52, 100, 117));
	pfpButton->Bind(wxEVT_BUTTON, &MainFrame::onBellButtonClick, this);



	pfpButton->Bind(wxEVT_ENTER_WINDOW, &MainFrame::onHover, this);
	pfpButton->Bind(wxEVT_LEAVE_WINDOW, &MainFrame::onLeaveHover, this);

	checkRequests();

}
void MainFrame::paintMidPanel()
{
	midPanel = new RoundedPanel(mainPanel, wxID_ANY, wxPoint(35, 130), wxSize(550, 840));

	balanceDisplayPanel = new wxPanel(midPanel, wxID_ANY, wxPoint(0, 40), wxSize(600, 50), wxALIGN_CENTRE_HORIZONTAL);
	balanceDisplayPanel->SetBackgroundColour(wxColour(52, 100, 117));

	repaintBalance();

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
	requestMoneyButton->Bind(wxEVT_BUTTON, &MainFrame::onRequestMoneyButtonClick, this);

	transactionButton->Bind(wxEVT_ENTER_WINDOW, &MainFrame::onHover, this);
	transactionButton->Bind(wxEVT_LEAVE_WINDOW, &MainFrame::onLeaveHover, this);
	transactionButton->Bind(wxEVT_BUTTON, &MainFrame::onTransactionsClick, this);

	rechargeButton->Bind(wxEVT_ENTER_WINDOW, &MainFrame::onHover, this);
	rechargeButton->Bind(wxEVT_LEAVE_WINDOW, &MainFrame::onLeaveHover, this);

}
void MainFrame::paintSendMoneyPanel()
{
	wxImage backIcon(wxString("resources\\back.png"), wxBITMAP_TYPE_PNG);
	backIcon.Rescale(25, 35, wxIMAGE_QUALITY_HIGH);

	wxBitmap backBitmap(backIcon);
	sendMoneyBackButton = new wxBitmapButton(balanceDisplayPanel, wxID_ANY, backBitmap, wxPoint(40, 8), wxSize(25, 35), wxBU_AUTODRAW | wxBORDER_NONE);
	sendMoneyBackButton->SetBackgroundColour(wxColour(52, 100, 117));

	sendMoneyBackButton->Bind(wxEVT_BUTTON, &MainFrame::onSendMoneyBackButtonClick, this);
	sendMoneyBackButton->Bind(wxEVT_ENTER_WINDOW, &MainFrame::onHover, this);
	sendMoneyBackButton->Bind(wxEVT_LEAVE_WINDOW, &MainFrame::onLeaveHover, this);

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
void MainFrame::paintRequestMoneypanel()
{
	wxImage backIcon(wxString("resources\\back.png"), wxBITMAP_TYPE_PNG);
	backIcon.Rescale(25, 35, wxIMAGE_QUALITY_HIGH);

	wxBitmap backBitmap(backIcon);
	requestMoneyBackButton = new wxBitmapButton(balanceDisplayPanel, wxID_ANY, backBitmap, wxPoint(40, 8), wxSize(25, 35), wxBU_AUTODRAW | wxBORDER_NONE);
	requestMoneyBackButton->SetBackgroundColour(wxColour(52, 100, 117));

	requestMoneyBackButton->Bind(wxEVT_BUTTON, &MainFrame::onRequestMoneyBackButton, this);
	requestMoneyBackButton->Bind(wxEVT_ENTER_WINDOW, &MainFrame::onHover, this);
	requestMoneyBackButton->Bind(wxEVT_LEAVE_WINDOW, &MainFrame::onLeaveHover, this);

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

	requestButton = new wxButton(sendButtonPanel, wxID_ANY, "Reqeust", wxPoint(10, 5), wxSize(160, 40), wxBORDER_NONE);
	requestButton->SetBackgroundColour(wxColour(52, 100, 117));
	requestButton->SetForegroundColour(*wxWHITE);
	requestButton->SetFont(wxFont(wxFontInfo(18).Bold()));

	requestButton->Bind(wxEVT_BUTTON, &MainFrame::onRequestClick, this);
	requestButton->Bind(wxEVT_ENTER_WINDOW, &MainFrame::onHover, this);
	requestButton->Bind(wxEVT_LEAVE_WINDOW, &MainFrame::onLeaveHover, this);

	sendMoneyPanel->Hide();
	requestMoneyPanel->Hide();
	transactionButtonPanel->Hide();
	rechargeBalancePanel->Hide();
}
void MainFrame::repaintBalance()
{
	wxStaticText* displayBalance = new wxStaticText(balanceDisplayPanel, wxID_ANY, "Balance: " + to_string((*user).getBalance()).substr(0, to_string((*user).getBalance()).length()-4), wxPoint(130, 7), wxSize(300, -1), wxALIGN_CENTRE_HORIZONTAL);
	displayBalance->SetForegroundColour(*wxWHITE);
	displayBalance->SetBackgroundColour(wxColour(52, 100, 117));
	displayBalance->SetFont(wxFont(wxFontInfo(22).Bold()));
}
void MainFrame::paintTransactionsPanel()
{
	transactionsPanel = new wxScrolled<wxPanel>(midPanel, wxID_ANY, wxPoint(0, 90), wxSize(566, 730));
	transactionsPanel->SetScrollRate(0, FromDIP(20));
	transactionsPanel->SetBackgroundColour(*wxWHITE);
	//auto sizer = new wxBoxSizer(wxVERTICAL);

	wxImage backIcon(wxString("resources\\back.png"), wxBITMAP_TYPE_PNG);
	backIcon.Rescale(25, 35, wxIMAGE_QUALITY_HIGH);

	wxBitmap backBitmap(backIcon);
	transactionsBackButton = new wxBitmapButton(balanceDisplayPanel, wxID_ANY, backBitmap, wxPoint(40, 8), wxSize(25, 35), wxBU_AUTODRAW | wxBORDER_NONE);
	transactionsBackButton->SetBackgroundColour(wxColour(52, 100, 117));

	transactionsBackButton->Bind(wxEVT_BUTTON, &MainFrame::onTransacionBackButtonClick, this);
	transactionsBackButton->Bind(wxEVT_ENTER_WINDOW, &MainFrame::onHover, this);
	transactionsBackButton->Bind(wxEVT_LEAVE_WINDOW, &MainFrame::onLeaveHover, this);

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

	auto transactions = Bank::getTransactions()->get(user);

	for (auto it = transactions.rbegin(); it != transactions.rend(); ++it)
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

		wxStaticText* senderText = new wxStaticText(transactionDetailsPanel, wxID_ANY, tans->getSender()->getUsername()+" => "+tans->getRecipient()->getUsername(), wxPoint(130, 63), wxSize(200, -1), wxALIGN_CENTRE_HORIZONTAL);
		senderText->SetBackgroundColour(wxColour(229, 229, 229));
		senderText->SetFont(wxFont(wxFontInfo(16).Bold()));

		wxStaticText* amountText = new wxStaticText(transactionDetailsPanel, wxID_ANY,to_string(tans->getAmount()).substr(0, to_string(tans->getAmount()).length() - 4) + "EGP", wxPoint(235, 110), wxSize(235, -1), wxALIGN_RIGHT);
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

		totalScrollHeight += 180;
		pointY += 180;

	}

	transactionsPanel->SetScrollbar(wxVERTICAL, 0, 500, totalScrollHeight, 500);
	transactionsPanel->SetVirtualSize(wxSize(0, totalScrollHeight));

	sendMoneyPanel->Hide();
	requestMoneyPanel->Hide();
	transactionButtonPanel->Hide();
	rechargeBalancePanel->Hide();
	
}
void MainFrame::paintPendingRequests()
{
	sendMoneyPanel->Hide();
	requestMoneyPanel->Hide();
	transactionButtonPanel->Hide();
	rechargeBalancePanel->Hide();

	//bellButton->Unbind(wxEVT_BUTTON, &MainFrame::onBellButtonClick, this);
	//bellAlertButton->Unbind(wxEVT_BUTTON, &MainFrame::onBellButtonClick, this);
	pendingRequestsPanel = new wxScrolled<wxPanel>(midPanel, wxID_ANY, wxPoint(0, 90), wxSize(566, 730));
	pendingRequestsPanel->SetScrollRate(0, FromDIP(20));
	pendingRequestsPanel->SetBackgroundColour(*wxWHITE);
	//auto sizer = new wxBoxSizer(wxVERTICAL);

	wxImage backIcon(wxString("resources\\back.png"), wxBITMAP_TYPE_PNG);
	backIcon.Rescale(25, 35, wxIMAGE_QUALITY_HIGH);

	wxBitmap backBitmap(backIcon);
	requestsPanelBackButton = new wxBitmapButton(balanceDisplayPanel, wxID_ANY, backBitmap, wxPoint(40, 8), wxSize(25, 35), wxBU_AUTODRAW | wxBORDER_NONE);
	requestsPanelBackButton->SetBackgroundColour(wxColour(52, 100, 117));

	requestsPanelBackButton->Bind(wxEVT_BUTTON, &MainFrame::onRequestsPanelBackClick, this);
	requestsPanelBackButton->Bind(wxEVT_ENTER_WINDOW, &MainFrame::onHover, this);
	requestsPanelBackButton->Bind(wxEVT_LEAVE_WINDOW, &MainFrame::onLeaveHover, this);

	wxImage rejectedIcon(wxString("resources\\rejected.png"), wxBITMAP_TYPE_PNG);
	rejectedIcon.Rescale(60, 60, wxIMAGE_QUALITY_HIGH);

	wxImage acceptedIcon(wxString("resources\\accepted.png"), wxBITMAP_TYPE_PNG);
	acceptedIcon.Rescale(60, 60, wxIMAGE_QUALITY_HIGH);

	wxImage pendingIcon(wxString("resources\\pending.png"), wxBITMAP_TYPE_PNG);
	pendingIcon.Rescale(60, 60, wxIMAGE_QUALITY_HIGH);

	/*auto panel = new wxScrolled<wxPanel>(midPanel, wxID_ANY, wxPoint(20, 20), wxSize(500, 600));
	panel->SetBackgroundColour(!wxWHITE);*/
	if (hasRequest == true)
	{
		int requestPanelScrollHeight = 0;
		int requestPointY = 30;

		auto transactions = Bank::getTransactions()->get(user);

		for (auto it = transactions.rbegin(); it != transactions.rend(); ++it)
		{
			Transaction* tans = *it;

			if (tans->getState() == TransactionState::pendingRequest and tans->getSender() == user)
			{
				wxPanel* requestDetailsPanel = new RoundedPanel(pendingRequestsPanel, wxID_ANY, wxPoint(35, requestPointY), wxSize(480, 220), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
				requestDetailsPanel->SetBackgroundColour(*wxWHITE);

				wxPanel* acceptButtonPanel = new RoundedPanel(requestDetailsPanel, wxID_ANY, wxPoint(50, 165), wxSize(100, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(0, 125, 141));
				acceptButtonPanel->SetBackgroundColour(wxColour(229, 229, 229));

				wxPanel* rejectButtonPanel = new RoundedPanel(requestDetailsPanel, wxID_ANY, wxPoint(330, 165), wxSize(100, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(0, 125, 141));
				rejectButtonPanel->SetBackgroundColour(wxColour(229, 229, 229));

				wxBitmap acceptBitmap(acceptedIcon);
				wxBitmapButton* acceptButton = new wxBitmapButton(acceptButtonPanel, wxID_ANY, acceptBitmap, wxPoint(30, 5), wxSize(40, 40), wxBU_AUTODRAW | wxBORDER_NONE);
				acceptButton->SetBackgroundColour(wxColour(0, 125, 141));

				acceptButton->Bind(wxEVT_ENTER_WINDOW, &MainFrame::onHover, this);
				acceptButton->Bind(wxEVT_LEAVE_WINDOW, &MainFrame::onLeaveHover, this);
				acceptButton->Bind
				(
					wxEVT_COMMAND_BUTTON_CLICKED, [=](wxCommandEvent& evt)
					{
						user->acceptRequest(tans);
						repaintBalance();
						MSWClickButtonIfPossible(requestsPanelBackButton);
						paintPendingRequests();
					}
				);

				wxBitmap rejectBitmap(rejectedIcon);
				wxBitmapButton* rejectedButton = new wxBitmapButton(rejectButtonPanel, wxID_ANY, rejectBitmap, wxPoint(30, 5), wxSize(40, 40), wxBU_AUTODRAW | wxBORDER_NONE);
				rejectedButton->SetBackgroundColour(wxColour(0, 125, 141));

				rejectedButton->Bind(wxEVT_ENTER_WINDOW, &MainFrame::onHover, this);
				rejectedButton->Bind(wxEVT_LEAVE_WINDOW, &MainFrame::onLeaveHover, this);
				rejectedButton->Bind
				(
					wxEVT_COMMAND_BUTTON_CLICKED, [=](wxCommandEvent& evt)
					{
						user->rejectRequest(tans);
						MSWClickButtonIfPossible(requestsPanelBackButton);
						paintPendingRequests();
					}
				);

				wxBitmap transactionState(pendingIcon);
				wxBitmapButton* transactionStateHolder = new wxBitmapButton(requestDetailsPanel, wxID_ANY, transactionState, wxPoint(20, 45), wxSize(60, 60), wxBU_AUTODRAW | wxBORDER_NONE);
				transactionStateHolder->SetBackgroundColour(wxColour(229, 229, 229));

				wxStaticText* stateText = new wxStaticText(requestDetailsPanel, wxID_ANY, "Request Pending", wxPoint(8, 8), wxSize(464, -1), wxALIGN_CENTRE_HORIZONTAL);
				stateText->SetBackgroundColour(wxColour(229, 229, 229));
				stateText->SetFont(wxFont(wxFontInfo(16)));

				wxStaticText* senderText = new wxStaticText(requestDetailsPanel, wxID_ANY, tans->getSender()->getUsername() + " => " + tans->getRecipient()->getUsername(), wxPoint(130, 63), wxSize(200, -1), wxALIGN_CENTRE_HORIZONTAL);
				senderText->SetBackgroundColour(wxColour(229, 229, 229));
				senderText->SetFont(wxFont(wxFontInfo(16).Bold()));

				wxStaticText* amountText = new wxStaticText(requestDetailsPanel, wxID_ANY, to_string(tans->getAmount()).substr(0, to_string(tans->getAmount()).length() - 4) + "EGP", wxPoint(235, 110), wxSize(235, -1), wxALIGN_RIGHT);
				amountText->SetBackgroundColour(wxColour(229, 229, 229));
				amountText->SetForegroundColour(wxColour(0, 125, 141));
				amountText->SetFont(wxFont(wxFontInfo(20).Bold()));

				wxStaticText* transactionIDText = new wxStaticText(requestDetailsPanel, wxID_ANY, "   #" + to_string(tans->getEpochTime()), wxPoint(5, 120), wxSize(235, -1), wxALIGN_LEFT);
				transactionIDText->SetBackgroundColour(wxColour(229, 229, 229));
				transactionIDText->SetForegroundColour(wxColour(126, 126, 126));
				transactionIDText->SetFont(wxFont(wxFontInfo(12)));

				wxStaticText* transactionTime = new wxStaticText(requestDetailsPanel, wxID_ANY, tans->getDisplayTime(), wxPoint(168, 180), wxSize(-1, -1), wxALIGN_CENTRE_HORIZONTAL);
				transactionTime->SetBackgroundColour(wxColour(229, 229, 229));
				transactionTime->SetForegroundColour(wxColour(178, 178, 178));
				transactionTime->SetFont(wxFont(wxFontInfo(12)));

				requestPanelScrollHeight += 310;
				requestPointY += 280;
			}
		}

		pendingRequestsPanel->SetScrollbar(wxVERTICAL, 0, 500, requestPanelScrollHeight, 500);
		pendingRequestsPanel->SetVirtualSize(wxSize(0, requestPanelScrollHeight));
	}
	else
	{
		noRequests = new wxStaticText(pendingRequestsPanel, wxID_ANY, "You Don't Have Any Requests.", wxPoint(0, 280), wxSize(550, -1), wxALIGN_CENTRE_HORIZONTAL);
		noRequests->SetBackgroundColour(*wxWHITE);
		noRequests->SetFont(wxFont(wxFontInfo(22)));
	}
	

}

void MainFrame::checkRequests()
{
	hasRequest = false;
	for (Transaction* tans : Bank::getTransactions()->get(user))
	{
		if (tans->getState() == TransactionState::pendingRequest and tans->getSender() == user)
		{
			hasRequest = true;
		}
	}

	cout << hasRequest << endl;

	wxImage bellAlertIcon(wxString("resources\\bellAlert.png"), wxBITMAP_TYPE_PNG);
	bellAlertIcon.Rescale(80, 80, wxIMAGE_QUALITY_HIGH);
	wxBitmap bellAlertBitmap(bellAlertIcon);
	wxImage bellIcon(wxString("resources\\bell.png"), wxBITMAP_TYPE_PNG);
	bellIcon.Rescale(80, 80, wxIMAGE_QUALITY_HIGH);
	wxBitmap bellBitmap(bellIcon);

	bellButton =  new wxBitmapButton(topPanel, wxID_ANY, wxNullBitmap, wxPoint(525, 15), wxSize(80, 80), wxBU_AUTODRAW | wxBORDER_NONE);
	bellButton->SetBackgroundColour(wxColour(52, 100, 117));
	bellButton->Bind(wxEVT_ENTER_WINDOW, &MainFrame::onHover, this);
	bellButton->Bind(wxEVT_LEAVE_WINDOW, &MainFrame::onLeaveHover, this);
	bellButton->Bind(wxEVT_BUTTON, &MainFrame::onBellButtonClick, this);

	bellButton->SetBitmap(wxNullBitmap);
	if (hasRequest == true)
	{
		bellButton->SetBitmap(bellAlertBitmap);
	}
	else
	{
		bellButton->SetBitmap(bellBitmap);
	}
	bellButton->Hide();
	bellButton->Show();
}

//functions buttons

void MainFrame::onBellButtonClick(wxCommandEvent& event)
{	
	paintPendingRequests();

	printf("HAAALLLLOOOOOOO\n");
}

void MainFrame::onSendMoneyClick(wxCommandEvent& event)
{
	paintSendMoneyPanel();
}

void MainFrame::onSendClick(wxCommandEvent& event)
{
	wxString recieverString((recieverNameBox->GetValue()));
	wxString amountString((amountBox->GetValue()));

	string reciever = string(recieverString.mb_str());
	string amount = string(amountString.mb_str());

	if (stod(amount) > 0 and stod(amount) < 999999 and stod(amount) <= user->getBalance())
	{

		user->sendMoney(&Bank::getUsers()->at(reciever), stod(amount));
		repaintBalance();

		sendMoneyPanel->Show();
		requestMoneyPanel->Show();
		transactionButtonPanel->Show();
		rechargeBalancePanel->Show();

		sendMoneyBackButton->Hide();
		usernameInputPanel->Hide();
		recieverNameBox->Hide();
		amountInputPanel->Hide();
		sendButtonPanel->Hide();
		sendButton->Hide();
		amountBox->Hide();
		amountText->Hide();
		recieverText->Hide();

	}
	else
	{
		wxMessageBox("Please enter a valid amount", "Error", wxICON_ERROR | wxOK, this);
	}
}

void MainFrame::onTransactionsClick(wxCommandEvent& event)
{
	paintTransactionsPanel();
}

void MainFrame::onRequestMoneyButtonClick(wxCommandEvent& event)
{
	paintRequestMoneypanel();
}

void MainFrame::onRequestClick(wxCommandEvent& event)
{
	wxString recieverString((recieverNameBox->GetValue()));
	wxString amountString((amountBox->GetValue()));

	string reciever = string(recieverString.mb_str());
	string amount = string(amountString.mb_str());

	if (stod(amount) < 100000)
	{
		user->requestMoney(&Bank::getUsers()->at(reciever), stod(amount));

		sendMoneyPanel->Show();
		requestMoneyPanel->Show();
		transactionButtonPanel->Show();
		rechargeBalancePanel->Show();

		requestMoneyBackButton->Hide();
		usernameInputPanel->Hide();
		recieverNameBox->Hide();
		amountInputPanel->Hide();
		sendButtonPanel->Hide();
		requestButton->Hide();
		amountBox->Hide();
		amountText->Hide();
		recieverText->Hide();

	}
	else
	{
		wxMessageBox("It's not your mother's money, is it ?", "Error", wxICON_ERROR | wxOK, this);
	}
	printf("yay");
}

//back buttons
void MainFrame::onTransacionBackButtonClick(wxCommandEvent& event)
{

	transactionsPanel->Hide();
	transactionsBackButton->Hide();
	
	sendMoneyPanel->Show();
	requestMoneyPanel->Show();
	transactionButtonPanel->Show();
	rechargeBalancePanel->Show();
}

void MainFrame::onSendMoneyBackButtonClick(wxCommandEvent& event)
{
	sendMoneyPanel->Show();
	requestMoneyPanel->Show();
	transactionButtonPanel->Show();
	rechargeBalancePanel->Show();

	sendMoneyBackButton->Hide();
	usernameInputPanel->Hide();
	recieverNameBox->Hide();
	amountInputPanel->Hide();
	sendButtonPanel->Hide();
	sendButton->Hide();
	amountBox->Hide();
	amountText->Hide();
	recieverText->Hide();

}

void MainFrame::onRequestMoneyBackButton(wxCommandEvent& event)
{
	sendMoneyPanel->Show();
	requestMoneyPanel->Show();
	transactionButtonPanel->Show();
	rechargeBalancePanel->Show();

	requestMoneyBackButton->Hide();
	usernameInputPanel->Hide();
	recieverNameBox->Hide();
	amountInputPanel->Hide();
	sendButtonPanel->Hide();
	requestButton->Hide();
	amountBox->Hide();
	amountText->Hide();
	recieverText->Hide();
}

void MainFrame::onRequestsPanelBackClick(wxCommandEvent& event)
{
	checkRequests();
	//bellButton->Bind(wxEVT_BUTTON, &MainFrame::onBellButtonClick, this);
	//bellAlertButton->Bind(wxEVT_BUTTON, &MainFrame::onBellButtonClick, this);
	//noRequests->Hide();
	pendingRequestsPanel->Hide();
	requestsPanelBackButton->Hide();

	sendMoneyPanel->Show();
	requestMoneyPanel->Show();
	transactionButtonPanel->Show();
	rechargeBalancePanel->Show();
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
