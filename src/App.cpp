#include "App.h"
#include "LoginFrame.h"
#include "VirtualUser.h"
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
	User user = User(1, "TheOne1", "one1", "The One", 5000.0, "01211466100", "one@gmail.com", "active");

	Transaction transaction1 = Transaction(&user, &user, 700.0, std::chrono::system_clock::now(), TransactionState::accepted);
	Sleep(1000);
	Transaction transaction2 = Transaction(&user, &user, 800.0, std::chrono::system_clock::now(), TransactionState::accepted);
	Sleep(1000);
	Transaction transaction3 = Transaction(&user, &user, 900.0, std::chrono::system_clock::now(), TransactionState::accepted);
	Bank::getTransactions()->insert(&transaction1);
	(*Bank::getTransactions()).insert(&transaction2);
	(*Bank::getTransactions()).insert(&transaction3);
	for (Transaction* tans : Bank::getTransactions()->get(0.0, 1000.0)) {
		for (string e : (*tans).toStringArray()) {
			cout << e << " ";
		}
		cout << endl;
	}
	//LoginFrame* loginFrame = new LoginFrame("HeisenBank");
	//loginFrame->SetClientSize(450, 700);
	//loginFrame->Center();
	//loginFrame->Show();
	//loginFrame->SetIcon(icon);

	MainFrame* mainFrame = new MainFrame(user, "Heisenbank");
	mainFrame->SetClientSize(620, 1000);
	mainFrame->Center();
	mainFrame->Show();
	mainFrame->SetIcon(icon);
	return true;
}

int App::OnExit() {

	FileSystemManagement::updateData();
	Sleep(5000);
	system("pause");

	return 0;
}

wxIMPLEMENT_APP(App);
