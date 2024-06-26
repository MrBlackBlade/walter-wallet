#include <wx/wx.h>
#include <wx/image.h>
#include "MainFrame.h"
#include "FileSystemManagement.h"
#include "RoundedPanel.h"
#include "Bank.h"
#include "Validation.h"
#include "SHA256.h"

MainFrame::MainFrame(User* user) : wxFrame(nullptr, wxID_ANY, "Heisenbank")
{
	wxWindow::SetWindowStyle(wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX);
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

	textDisplayName = new wxStaticText(topPanel, wxID_ANY, (*user).getDisplayName(), wxPoint(100, 55), wxSize(420, 80), wxALIGN_CENTRE_HORIZONTAL);
	textDisplayName->SetForegroundColour(*wxWHITE); // Set text color
	textDisplayName->SetFont(wxFont(wxFontInfo(22).Bold())); // Set font

	wxImage pfpIcon(wxT("resources\\profile.png"), wxBITMAP_TYPE_PNG);
	pfpIcon.Rescale(80, 80, wxIMAGE_QUALITY_HIGH); // Rescale the image to 60x60
	wxBitmap pfpBitmap(pfpIcon);
	pfpButton = new wxBitmapButton(topPanel, wxID_ANY, pfpBitmap, wxPoint(15, 15), wxSize(80, 80), wxBU_AUTODRAW | wxBORDER_NONE);
	pfpButton->SetBackgroundColour(wxColour(52, 100, 117));

	pfpButton->Bind(wxEVT_ENTER_WINDOW, &MainFrame::onHover, this);
	pfpButton->Bind(wxEVT_LEAVE_WINDOW, &MainFrame::onLeaveHover, this);
	pfpButton->Bind(wxEVT_BUTTON, &MainFrame::onPfpButtonClick, this);

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

	rechargeButton->Bind(wxEVT_ENTER_WINDOW, &MainFrame::onHover, this);
	rechargeButton->Bind(wxEVT_LEAVE_WINDOW, &MainFrame::onLeaveHover, this);
	rechargeButton->Bind(wxEVT_BUTTON, &MainFrame::onRechargeBalanceButtonClick, this);

	sendMoneyButton->Bind(wxEVT_ENTER_WINDOW, &MainFrame::onHover, this);
	sendMoneyButton->Bind(wxEVT_LEAVE_WINDOW, &MainFrame::onLeaveHover, this);

	requestMoneyButton->Bind(wxEVT_ENTER_WINDOW, &MainFrame::onHover, this);
	requestMoneyButton->Bind(wxEVT_LEAVE_WINDOW, &MainFrame::onLeaveHover, this);
	requestMoneyButton->Bind(wxEVT_BUTTON, &MainFrame::onRequestMoneyButtonClick, this);

	transactionButton->Bind(wxEVT_ENTER_WINDOW, &MainFrame::onHover, this);
	transactionButton->Bind(wxEVT_LEAVE_WINDOW, &MainFrame::onLeaveHover, this);
	transactionButton->Bind(wxEVT_BUTTON, &MainFrame::onTransactionsClick, this);

	

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
	wxStaticText* displayBalance = new wxStaticText(balanceDisplayPanel, wxID_ANY, "Balance: " + to_string((*user).getBalance()).substr(0, to_string((*user).getBalance()).length() - 4), wxPoint(130, 7), wxSize(300, -1), wxALIGN_CENTRE_HORIZONTAL);
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

	sendMoneyPanel->Hide();
	requestMoneyPanel->Hide();
	transactionButtonPanel->Hide();
	rechargeBalancePanel->Hide();

}
void MainFrame::paintPendingRequests()
{
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
						if (user->getSuspended() == false)
						{
							if (Validation::sentAmountEnoughFundsValid(to_string(tans->getAmount()), user)) {
								user->acceptRequest(tans);
								repaintBalance();
								MSWClickButtonIfPossible(requestsPanelBackButton);
								paintPendingRequests();
							}
							else {
								string error = "Invalid Amount\n\n";
								error += "Account does not have enough funds\n";
								error += "\n";
								wxMessageBox(error, "Invalid", wxICON_ERROR | wxOK);
							}
							
						}
						else
						{
							wxMessageBox("User Suspended, Can't make any Transactions.", "Error", wxICON_INFORMATION | wxOK, this);
						}
						
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
						if (user->getSuspended() == false)
						{
							user->rejectRequest(tans);
							MSWClickButtonIfPossible(requestsPanelBackButton);
							paintPendingRequests();
						}
						else
						{
							wxMessageBox("User Suspended, Can't make any Transactions.", "Error", wxICON_INFORMATION | wxOK, this);

						}
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
	sendMoneyPanel->Hide();
	requestMoneyPanel->Hide();
	transactionButtonPanel->Hide();
	rechargeBalancePanel->Hide();

}
void MainFrame::paintRechargeBalancePanel()
{
	wxImage backIcon(wxString("resources\\back.png"), wxBITMAP_TYPE_PNG);
	backIcon.Rescale(25, 35, wxIMAGE_QUALITY_HIGH);

	wxBitmap backBitmap(backIcon);
	rechargeBalanceBackButton = new wxBitmapButton(balanceDisplayPanel, wxID_ANY, backBitmap, wxPoint(40, 8), wxSize(25, 35), wxBU_AUTODRAW | wxBORDER_NONE);
	rechargeBalanceBackButton->SetBackgroundColour(wxColour(52, 100, 117));

	rechargeBalanceBackButton->Bind(wxEVT_ENTER_WINDOW, &MainFrame::onHover, this);
	rechargeBalanceBackButton->Bind(wxEVT_LEAVE_WINDOW, &MainFrame::onLeaveHover, this);
	rechargeBalanceBackButton->Bind(wxEVT_BUTTON, &MainFrame::onRechargeMoneybackButtonClick, this);

	cardNumberInputPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(215, 200), wxSize(240, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	cardNumberInputPanel->SetBackgroundColour(*wxWHITE);

	cvvInputPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(215, 300), wxSize(240, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	cvvInputPanel->SetBackgroundColour(*wxWHITE);

	rechargeAmountInputPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(215, 400), wxSize(240, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	rechargeAmountInputPanel->SetBackgroundColour(*wxWHITE);

	cardNumberBox = new wxTextCtrl(cardNumberInputPanel, wxID_ANY, "Number", wxPoint(10, 13), wxSize(220, 30), wxTE_CENTRE | wxBORDER_NONE);
	cardNumberBox->SetBackgroundColour(wxColour(229, 229, 229));
	cardNumberBox->SetForegroundColour(wxColour(178, 178, 178));
	cardNumberBox->SetFont(wxFont(wxFontInfo(14).Bold()));
	cardNumberBox->Bind(wxEVT_SET_FOCUS, &MainFrame::onEnterCardNumber, this);
	cardNumberBox->Bind(wxEVT_KILL_FOCUS, &MainFrame::onLeaveCardNumber, this);

	cardNumberText = new wxStaticText(midPanel, wxID_ANY, "Card", wxPoint(70, 213), wxSize(-1, -1), wxALIGN_CENTRE_HORIZONTAL);
	cardNumberText->SetBackgroundColour(*wxWHITE);
	cardNumberText->SetForegroundColour(*wxBLACK);
	cardNumberText->SetFont(wxFont(wxFontInfo(14).Bold()));

	cvvBox = new wxTextCtrl(cvvInputPanel, wxID_ANY, "CVV", wxPoint(10, 13), wxSize(220, 30), wxTE_CENTRE | wxBORDER_NONE);
	cvvBox->SetBackgroundColour(wxColour(229, 229, 229));
	cvvBox->SetForegroundColour(wxColour(178, 178, 178));
	cvvBox->SetFont(wxFont(wxFontInfo(14).Bold()));
	cvvBox->Bind(wxEVT_SET_FOCUS, &MainFrame::onEnterCvv, this);
	cvvBox->Bind(wxEVT_KILL_FOCUS, &MainFrame::onLeaveCvv, this);

	cvvText = new wxStaticText(midPanel, wxID_ANY, "3 Digit", wxPoint(70, 313), wxSize(-1, -1), wxALIGN_CENTRE_HORIZONTAL);
	cvvText->SetBackgroundColour(*wxWHITE);
	cvvText->SetForegroundColour(*wxBLACK);
	cvvText->SetFont(wxFont(wxFontInfo(14).Bold()));

	rechargeAmountBox = new wxTextCtrl(rechargeAmountInputPanel, wxID_ANY, "EGP", wxPoint(10, 13), wxSize(220, 30), wxTE_CENTRE | wxBORDER_NONE);
	rechargeAmountBox->SetBackgroundColour(wxColour(229, 229, 229));
	rechargeAmountBox->SetForegroundColour(wxColour(178, 178, 178));
	rechargeAmountBox->SetFont(wxFont(wxFontInfo(14).Bold()));

	rechargeAmountBox->Bind(wxEVT_SET_FOCUS, &MainFrame::onEnterAmount, this);
	rechargeAmountBox->Bind(wxEVT_KILL_FOCUS, &MainFrame::onLeaveAmount, this);

	rechargeAmountText = new wxStaticText(midPanel, wxID_ANY, "Amount", wxPoint(70, 413), wxSize(-1, -1), wxALIGN_CENTRE_HORIZONTAL);
	rechargeAmountText->SetBackgroundColour(*wxWHITE);
	rechargeAmountText->SetForegroundColour(*wxBLACK);
	rechargeAmountText->SetFont(wxFont(wxFontInfo(14).Bold()));

	rechargeButtonPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(185, 580), wxSize(180, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(52, 100, 117));
	rechargeButtonPanel->SetBackgroundColour(*wxWHITE);

	rechargeButton = new wxButton(rechargeButtonPanel, wxID_ANY, "Recharge", wxPoint(10, 5), wxSize(160, 40), wxBORDER_NONE);
	rechargeButton->SetBackgroundColour(wxColour(52, 100, 117));
	rechargeButton->SetForegroundColour(*wxWHITE);
	rechargeButton->SetFont(wxFont(wxFontInfo(18).Bold()));

	rechargeButton->Bind(wxEVT_ENTER_WINDOW, &MainFrame::onHover, this);
	rechargeButton->Bind(wxEVT_LEAVE_WINDOW, &MainFrame::onLeaveHover, this);
	rechargeButton->Bind(wxEVT_BUTTON, &MainFrame::onRechargeButtonCLick, this);

	sendMoneyPanel->Hide();
	requestMoneyPanel->Hide();
	transactionButtonPanel->Hide();
	rechargeBalancePanel->Hide();
}
void MainFrame::paintProfile()
{
	wxImage backIcon(wxString("resources\\back.png"), wxBITMAP_TYPE_PNG);
	backIcon.Rescale(25, 35, wxIMAGE_QUALITY_HIGH);

	wxBitmap backBitmap(backIcon);
	pfpPanelBackButton = new wxBitmapButton(balanceDisplayPanel, wxID_ANY, backBitmap, wxPoint(40, 8), wxSize(25, 35), wxBU_AUTODRAW | wxBORDER_NONE);
	pfpPanelBackButton->SetBackgroundColour(wxColour(52, 100, 117));

	pfpPanelBackButton->Bind(wxEVT_BUTTON, &MainFrame::onPfpBackButtonClick, this);
	pfpPanelBackButton->Bind(wxEVT_ENTER_WINDOW, &MainFrame::onHover, this);
	pfpPanelBackButton->Bind(wxEVT_LEAVE_WINDOW, &MainFrame::onLeaveHover, this);

	pfpUsernameInputPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(235, 160), wxSize(240, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	pfpUsernameInputPanel->SetBackgroundColour(*wxWHITE);

	pfpPasswordInputPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(235, 240), wxSize(240, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	pfpPasswordInputPanel->SetBackgroundColour(*wxWHITE);

	pfpDisplayNameInputPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(235, 320), wxSize(240, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	pfpDisplayNameInputPanel->SetBackgroundColour(*wxWHITE);

	pfpPhoneNumberInputPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(235, 400), wxSize(240, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	pfpPhoneNumberInputPanel->SetBackgroundColour(*wxWHITE);

	pfpEmailInputPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(235, 480), wxSize(240, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(229, 229, 229));
	pfpEmailInputPanel->SetBackgroundColour(*wxWHITE);

	pfpUsernameBox = new wxTextCtrl(pfpUsernameInputPanel, wxID_ANY, user->getUsername(), wxPoint(10, 13), wxSize(220, 30), wxTE_CENTRE | wxBORDER_NONE);
	pfpUsernameBox->SetBackgroundColour(wxColour(229, 229, 229));
	pfpUsernameBox->SetForegroundColour(*wxBLACK);
	pfpUsernameBox->SetFont(wxFont(wxFontInfo(14).Bold()));

	pfpUsernameText = new wxStaticText(midPanel, wxID_ANY, "Username", wxPoint(70, 173), wxSize(-1, -1), wxALIGN_CENTRE_HORIZONTAL);
	pfpUsernameText->SetBackgroundColour(*wxWHITE);
	pfpUsernameText->SetForegroundColour(*wxBLACK);
	pfpUsernameText->SetFont(wxFont(wxFontInfo(14).Bold()));

	pfpUsernameBox->Bind(wxEVT_SET_FOCUS, &MainFrame::onEnterUsername, this);
	pfpUsernameBox->Bind(wxEVT_KILL_FOCUS, &MainFrame::onLeaveUsername, this);

	pfpPasswordBox = new wxTextCtrl(pfpPasswordInputPanel, wxID_ANY, "Password", wxPoint(10, 13), wxSize(220, 30), wxTE_CENTRE | wxBORDER_NONE);
	pfpPasswordBox->SetBackgroundColour(wxColour(229, 229, 229));
	pfpPasswordBox->SetForegroundColour(wxColour(178, 178, 178));
	pfpPasswordBox->SetFont(wxFont(wxFontInfo(14).Bold()));

	pfpPasswordText = new wxStaticText(midPanel, wxID_ANY, "Password", wxPoint(70, 253), wxSize(-1, -1), wxALIGN_CENTRE_HORIZONTAL);
	pfpPasswordText->SetBackgroundColour(*wxWHITE);
	pfpPasswordText->SetForegroundColour(*wxBLACK);
	pfpPasswordText->SetFont(wxFont(wxFontInfo(14).Bold()));

	pfpPasswordBox->Bind(wxEVT_SET_FOCUS, &MainFrame::onEnterPassword, this);
	pfpPasswordBox->Bind(wxEVT_KILL_FOCUS, &MainFrame::onLeavePassword, this);

	pfpDisplayNameBox = new wxTextCtrl(pfpDisplayNameInputPanel, wxID_ANY, user->getDisplayName() , wxPoint(10, 13), wxSize(220, 30), wxTE_CENTRE | wxBORDER_NONE);
	pfpDisplayNameBox->SetBackgroundColour(wxColour(229, 229, 229));
	pfpDisplayNameBox->SetForegroundColour(*wxBLACK);
	pfpDisplayNameBox->SetFont(wxFont(wxFontInfo(14).Bold()));

	pfpDisplayNameText = new wxStaticText(midPanel, wxID_ANY, "Display Name", wxPoint(70, 333), wxSize(-1, -1), wxALIGN_CENTRE_HORIZONTAL);
	pfpDisplayNameText->SetBackgroundColour(*wxWHITE);
	pfpDisplayNameText->SetForegroundColour(*wxBLACK);
	pfpDisplayNameText->SetFont(wxFont(wxFontInfo(14).Bold()));

	//displayNameBox->Bind(wxEVT_SET_FOCUS, &MainFrame::onEnterDisplayName, this);
	//displayNameBox->Bind(wxEVT_KILL_FOCUS, &MainFrame::onLeaveDisplayName, this);

	pfpPhoneNumberBox = new wxTextCtrl(pfpPhoneNumberInputPanel, wxID_ANY, user->getPhoneNumber(), wxPoint(10, 13), wxSize(220, 30), wxTE_CENTRE | wxBORDER_NONE);
	pfpPhoneNumberBox->SetBackgroundColour(wxColour(229, 229, 229));
	pfpPhoneNumberBox->SetForegroundColour(*wxBLACK);
	pfpPhoneNumberBox->SetFont(wxFont(wxFontInfo(14).Bold()));

	pfpPhoneNumberText = new wxStaticText(midPanel, wxID_ANY, "Phone Number", wxPoint(70, 413), wxSize(-1, -1), wxALIGN_CENTRE_HORIZONTAL);
	pfpPhoneNumberText->SetBackgroundColour(*wxWHITE);
	pfpPhoneNumberText->SetForegroundColour(*wxBLACK);
	pfpPhoneNumberText->SetFont(wxFont(wxFontInfo(14).Bold()));

	//phoneNumberBox->Bind(wxEVT_SET_FOCUS, &MainFrame::onEnterPhoneNumber, this);
	//phoneNumberBox->Bind(wxEVT_KILL_FOCUS, &MainFrame::onLeavePhoneNumber, this);

	pfpEmailBox = new wxTextCtrl(pfpEmailInputPanel, wxID_ANY, user->getEmail(), wxPoint(10, 13), wxSize(220, 30), wxTE_CENTRE | wxBORDER_NONE);
	pfpEmailBox->SetBackgroundColour(wxColour(229, 229, 229));
	pfpEmailBox->SetForegroundColour(*wxBLACK);
	pfpEmailBox->SetFont(wxFont(wxFontInfo(14).Bold()));

	pfpEmailText = new wxStaticText(midPanel, wxID_ANY, "Email", wxPoint(70, 493), wxSize(-1, -1), wxALIGN_CENTRE_HORIZONTAL);
	pfpEmailText->SetBackgroundColour(*wxWHITE);
	pfpEmailText->SetForegroundColour(*wxBLACK);
	pfpEmailText->SetFont(wxFont(wxFontInfo(14).Bold()));


	pfpDoneButtonPanel = new RoundedPanel(midPanel, wxID_ANY, wxPoint(185, 630), wxSize(180, 50), wxALIGN_CENTRE_HORIZONTAL, wxColour(52, 100, 117));
	pfpDoneButtonPanel->SetBackgroundColour(*wxWHITE);

	wxButton* doneButton = new wxButton(pfpDoneButtonPanel, wxID_ANY, "Done", wxPoint(10, 5), wxSize(160, 40), wxBORDER_NONE);
	doneButton->SetBackgroundColour(wxColour(52, 100, 117));
	doneButton->SetForegroundColour(*wxWHITE);
	doneButton->SetFont(wxFont(wxFontInfo(18).Bold()));

	doneButton->Bind(wxEVT_BUTTON, &MainFrame::onPfpDoneClick, this);
	doneButton->Bind(wxEVT_ENTER_WINDOW, &MainFrame::onHover, this);
	doneButton->Bind(wxEVT_LEAVE_WINDOW, &MainFrame::onLeaveHover, this);

	sendMoneyPanel->Hide();
	requestMoneyPanel->Hide();
	transactionButtonPanel->Hide();
	rechargeBalancePanel->Hide();
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

	wxImage bellAlertIcon(wxString("resources\\bellAlert.png"), wxBITMAP_TYPE_PNG);
	bellAlertIcon.Rescale(80, 80, wxIMAGE_QUALITY_HIGH);
	wxBitmap bellAlertBitmap(bellAlertIcon);
	wxImage bellIcon(wxString("resources\\bell.png"), wxBITMAP_TYPE_PNG);
	bellIcon.Rescale(80, 80, wxIMAGE_QUALITY_HIGH);
	wxBitmap bellBitmap(bellIcon);

	bellButton = new wxBitmapButton(topPanel, wxID_ANY, wxNullBitmap, wxPoint(525, 15), wxSize(80, 80), wxBU_AUTODRAW | wxBORDER_NONE);
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

	if (user->getSuspended() == false)
	{
		if
			(
				Validation::sentAmountValid(amount, user)
				&& Validation::userExists(reciever)
			)
		{

			user->sendMoney(Bank::getUsers()->getUser(reciever), stod(amount));
			repaintBalance();

			wxMessageBox("Transaction Successful", "Success", wxICON_INFORMATION | wxOK, this);

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
			string error = "Error\n\n";
			if (!Validation::userExists(reciever)) {
				error += "Recipient Invalid:\n";
				error += "User " + reciever + " does not exist.\n";
			}
			if (!Validation::sentAmountValid(amount, user)) {
				if (!Validation::sentAmountTypeValid(amount)) {
					error += "Amount must be a number.\n";
				}
				if (!Validation::sentAmountInRangeValid(amount) && Validation::sentAmountTypeValid(amount)) {
					error += "Number must be in range 0-999999.\n";
				}
				if (!Validation::sentAmountEnoughFundsValid(amount, user) && Validation::sentAmountTypeValid(amount)) {
					error += "Account does not have enough funds\n";
				}
				error += "\n";
			}
			wxMessageBox(error, "Invalid", wxICON_ERROR | wxOK);
		}
	}
	else if (user->getSuspended() == true)
	{
		wxMessageBox("User Suspended, Can't make any Transactions.");
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

void MainFrame::onPfpButtonClick(wxCommandEvent& event)
{
	paintProfile();
}

void MainFrame::onPfpDoneClick(wxCommandEvent& event)
{
	string error = "Invalid form parameters\n\n";

	string username = string(pfpUsernameBox->GetValue().mb_str());
	string password = string(pfpPasswordBox->GetValue().mb_str());
	string displayName = string(pfpDisplayNameBox->GetValue().mb_str());
	string phoneNumber = string(pfpPhoneNumberBox->GetValue().mb_str());
	string email = string(pfpEmailBox->GetValue().mb_str());

	if
		(	   Validation::usernameValid(username)
			&& Validation::displayNameValid(displayName)
			&& Validation::passwordValid(password)
			&& Validation::phoneNumberValidFormat(phoneNumber)
			&& Validation::emailValidFormat(email)
		)
	{
		Bank::asAdmin()->editUser
		(
			user,
			username,
			password,
			displayName,
			user->getBalance(),
			phoneNumber,
			email,
			false
		);

		textDisplayName->SetLabel(user->getDisplayName());
		textDisplayName->SetLabelText(user->getDisplayName());
		textDisplayName->Refresh();

		wxMessageBox("User updated successfully");


		sendMoneyPanel->Show();
		requestMoneyPanel->Show();
		transactionButtonPanel->Show();
		rechargeBalancePanel->Show();
		
		pfpUsernameInputPanel->Hide();
		pfpPasswordInputPanel->Hide();
		pfpDisplayNameInputPanel->Hide();
		pfpPhoneNumberInputPanel->Hide();
		pfpEmailInputPanel->Hide();
		pfpDoneButtonPanel->Hide();
		pfpPanelBackButton->Hide();
		
		pfpUsernameText->Hide();
		pfpPasswordText->Hide();
		pfpPhoneNumberText->Hide();
		pfpDisplayNameText->Hide();
		pfpEmailText->Hide();
	}
	else if 
		(
			!Validation::usernameValid(username)
			&& Validation::displayNameValid(displayName)
			&& Validation::passwordValid(password)
			&& Validation::phoneNumberValidFormat(phoneNumber)
			&& Validation::emailValidFormat(email)
			&& user->getUsername() == username
		)
	{
		Bank::asAdmin()->editUser
		(
			user,
			username,
			SHA256::toSHA256(password),
			displayName,
			user->getBalance(),
			phoneNumber,
			email,
			false
		);

		textDisplayName->SetLabel(user->getDisplayName());
		textDisplayName->SetLabelText(user->getDisplayName());
		textDisplayName->Refresh();

		wxMessageBox("User updated successfully");

		//topPanel->Destroy();
		//paintTopPanel();

		sendMoneyPanel->Show();
		requestMoneyPanel->Show();
		transactionButtonPanel->Show();
		rechargeBalancePanel->Show();

		pfpUsernameInputPanel->Hide();
		pfpPasswordInputPanel->Hide();
		pfpDisplayNameInputPanel->Hide();
		pfpPhoneNumberInputPanel->Hide();
		pfpEmailInputPanel->Hide();
		pfpDoneButtonPanel->Hide();
		pfpPanelBackButton->Hide();

		pfpUsernameText->Hide();
		pfpPasswordText->Hide();
		pfpPhoneNumberText->Hide();
		pfpDisplayNameText->Hide();
		pfpEmailText->Hide();
	}
	else
	{
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
		
		wxMessageBox(error, "Invalid");
	}
}

void MainFrame::onRequestClick(wxCommandEvent& event)
{
	wxString recieverString((recieverNameBox->GetValue()));
	wxString amountString((amountBox->GetValue()));

	string reciever = string(recieverString.mb_str());
	string amount = string(amountString.mb_str());
	
	if (user->getSuspended() == false)
	{
		if
			(
				Validation::requestedAmountValid(amount)
				&& Validation::userExists(reciever)
			)
		{

			user->requestMoney(Bank::getUsers()->getUser(reciever), stod(amount));

			wxMessageBox("Request sent Successfully", "Success", wxICON_INFORMATION | wxOK, this);

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
			string error = "Error\n\n";
			if (!Validation::userExists(reciever)) {
				error += "Request Recipient Invalid:\n";
				error += "User " + reciever + " does not exist.\n";
			}
			if (!Validation::requestedAmountValid(amount)) {
				if (!Validation::requestedAmountTypeValid(amount)) {
					error += "Amount must be a number.\n";
				}
				if (!Validation::requestedAmountInRangeValid(amount) && Validation::requestedAmountTypeValid(amount)) {
					error += "Number must be in range 0-100000.\n";
				}
				error += "\n";
			}
			wxMessageBox(error, "Invalid", wxICON_ERROR | wxOK);
		}
	}
	else if (user->getSuspended() == true)
	{
		wxMessageBox("User Suspended, Can't make any Transactions.");
	}
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

void MainFrame::onRechargeMoneybackButtonClick(wxCommandEvent& event)
{
	sendMoneyPanel->Show();
	requestMoneyPanel->Show();
	transactionButtonPanel->Show();
	rechargeBalancePanel->Show();

	cardNumberInputPanel->Hide();
	rechargeAmountInputPanel->Hide();
	cvvInputPanel->Hide();
	rechargeBalanceBackButton->Hide();
	rechargeButtonPanel->Hide();
	rechargeAmountText->Hide();
	cvvText->Hide();
	cardNumberText->Hide();
}

void MainFrame::onRechargeButtonCLick(wxCommandEvent& event)
{
	string rechargeAmount = string(rechargeAmountBox->GetValue().mb_str());
	string cardNumber = string(cardNumberBox->GetValue().mb_str());
	string cvv = string(cvvBox->GetValue().mb_str());


	
	if (user->getSuspended() == false)
	{
		if
			(
				Validation::rechargeAmountValid(rechargeAmount)
				&& Validation::cardNumberValid(cardNumber)
				&& Validation::cvvValid(cvv)
			)
		{
			Bank::makeSystemTransaction(Bank::getUsers()->getAdmin("admin"), user, stod(rechargeAmount));

			wxMessageBox("Balance recharged successfully", "Success", wxICON_INFORMATION | wxOK, this);
			repaintBalance();
			MSWClickButtonIfPossible(rechargeBalanceBackButton);

		}
		else
		{
			string error = "Error\n\n";
			if (!Validation::cardNumberValid(cardNumber)) {
				error += "Card number invalid:\n";
				error += "Card number needs to be a 16 digit number.\n";
				error += "\n";
			}
			if (!Validation::cvvValid(cvv)) {
				error += "CVV invalid:\n";
				error += "CVV needs to be a 3 digit number.\n";
				error += "\n";
			}
			if (!Validation::rechargeAmountValid(rechargeAmount)) {
				error += "Recharge amount invalid:\n";
				error += "Amount must be a number from 0-10000.\n";
				error += "\n";
			}
			wxMessageBox(error, "Invalid", wxICON_ERROR | wxOK);
		}
	}
	else if (user->getSuspended() == true)
	{
		wxMessageBox("User Suspended, Can't make any Transactions.");
	}
}

void MainFrame::onRechargeBalanceButtonClick(wxCommandEvent& event)
{
	paintRechargeBalancePanel();
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
	pendingRequestsPanel->Hide();
	requestsPanelBackButton->Hide();

	sendMoneyPanel->Show();
	requestMoneyPanel->Show();
	transactionButtonPanel->Show();
	rechargeBalancePanel->Show();
}

void MainFrame::onPfpBackButtonClick(wxCommandEvent& event)
{
	sendMoneyPanel->Show();
	requestMoneyPanel->Show();
	transactionButtonPanel->Show();
	rechargeBalancePanel->Show();

	pfpUsernameInputPanel->Hide();
	pfpPasswordInputPanel->Hide();
	pfpDisplayNameInputPanel->Hide();
	pfpPhoneNumberInputPanel->Hide();
	pfpEmailInputPanel->Hide();
	pfpPanelBackButton->Hide();
	pfpDoneButtonPanel->Hide();

	pfpUsernameText->Hide();
	pfpPasswordText->Hide();
	pfpPhoneNumberText->Hide();
	pfpDisplayNameText->Hide();
	pfpEmailText->Hide();
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

void MainFrame::onEnterPassword(wxFocusEvent& event)
{
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->GetValue() == "Password") {
		object->SetForegroundColour(*wxBLACK);
		object->Clear();
	}
	event.Skip(true);
}

void MainFrame::onLeavePassword(wxFocusEvent& event)
{
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->IsEmpty()) {
		object->SetForegroundColour(wxColour(178, 178, 178));
		object->AppendText("Password");
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

void MainFrame::onEnterCardNumber(wxFocusEvent& event)
{
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->GetValue() == "Number") {
		object->SetForegroundColour(*wxBLACK);
		object->Clear();
	}
	event.Skip(true);
}

void MainFrame::onLeaveCardNumber(wxFocusEvent& event)
{
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->IsEmpty()) {
		object->SetForegroundColour(wxColour(178, 178, 178));
		object->AppendText("Number");
	}

	event.Skip(true);
}

void MainFrame::onEnterCvv(wxFocusEvent& event)
{
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->GetValue() == "CVV") {
		object->SetForegroundColour(*wxBLACK);
		object->Clear();
	}
	event.Skip(true);
}

void MainFrame::onLeaveCvv(wxFocusEvent& event)
{
	wxTextCtrl* object = (wxTextCtrl*)event.GetEventObject();
	if (object->IsEmpty()) {
		object->SetForegroundColour(wxColour(178, 178, 178));
		object->AppendText("CVV");
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
}
