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
	AllocConsole();
	AttachConsole(ATTACH_PARENT_PROCESS);
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);

	wxIcon icon(wxT("resources\\walterWallet.ico"), wxBITMAP_TYPE_ICO);

	Bank::init();

	LoginFrame* loginFrame = new LoginFrame();
	loginFrame->SetClientSize(620, 1000);
	loginFrame->Center();
	loginFrame->Show();
	loginFrame->SetIcon(icon);

	//MainFrame* mainFrame = new MainFrame(&Bank::getUsers()->at("TheOne1"), "Heisenbank");
	//mainFrame->SetClientSize(620, 1000);
	//mainFrame->Center();
	//mainFrame->Show();
	//mainFrame->SetIcon(icon);

	//RegisterFrame* registerFrame = new RegisterFrame("HeisenBank");
	//registerFrame->SetClientSize(620, 1000);
	//registerFrame->Center();
	//registerFrame->Show();
	//registerFrame->SetIcon(icon);

	//cout<<Validation::usernameAvailable("mohab");
	//AdminFrame* adminFrame = new AdminFrame(Bank::getUsers()->getAdmin("admin"));
	//adminFrame->SetClientSize(620, 1000);
	//adminFrame->Center();
	//adminFrame->Show();
	//adminFrame->SetIcon(icon);
	return true;
}

int App::OnExit() {
	
	
	cout << "System Exit" << endl;
	system("pause");

	return 0;
}

wxIMPLEMENT_APP(App);
