#include "App.h"
#include "LoginFrame.h"
#include "VirtualUser.h"
#include "RegisterFrame.h"
#include "AdminFrame.h"
#include "User.h"
#include "MainFrame.h"
#include "FileSystemManagement.h"
#include "Transaction.h"
#include "TransactionStructure.h"
#include "Bank.h"
#include <chrono>
#include <windows.h>
using namespace std;

bool App::OnInit() {

	wxIcon icon(wxT("resources\\walterWallet.ico"), wxBITMAP_TYPE_ICO);

	Bank::init();

	LoginFrame* loginFrame = new LoginFrame();
	loginFrame->SetClientSize(620, 1000);
	loginFrame->Center();
	loginFrame->Show();
	loginFrame->SetIcon(icon);

	return true;
}

int App::OnExit() {
	
	cout << "System Exit" << endl;

	return 0;
}

wxIMPLEMENT_APP(App);
