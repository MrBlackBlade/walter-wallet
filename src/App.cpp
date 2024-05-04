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
	//User user = User(1, "TheOne1", "one1", "The One", 5000.0, "01211466100", "one@gmail.com", "active");

	//Bank::getTransactions()->insert(new Transaction(&(Bank::getUsers()->find("TheOne1")->second), &(Bank::getUsers()->find("TheOne1")->second), 700.0, std::chrono::system_clock::now(), TransactionState::accepted));
	/*Bank::getTransactions()->insert(Transaction(&user, &user, 800.0, std::chrono::system_clock::now(), TransactionState::accepted));
	Sleep(1000);
	Sleep(1000);
	Bank::getTransactions()->insert(Transaction(&user, &user, 900.0, std::chrono::system_clock::now(), TransactionState::accepted));*/
	//Bank::getUsers()->at("3m7md").sendMoney(&Bank::getUsers()->at("TheOne1"), 300);
	Bank::getUsers()->at("MazinMohamedPeter").requestMoney(&Bank::getUsers()->at("TheOne1"), 500);
	Transaction* trans = Bank::getTransactions()->get(&Bank::getUsers()->at("MazinMohamedPeter")).back();
	Bank::getUsers()->at("TheOne1").rejectRequest(Bank::getTransactions()->get(&Bank::getUsers()->at("MazinMohamedPeter")).back());
	Sleep(1000);
	Bank::getUsers()->at("MazinMohamedPeter").requestMoney(&Bank::getUsers()->at("TheOne1"), 200);
	trans = Bank::getTransactions()->get(&Bank::getUsers()->at("MazinMohamedPeter")).back();
	Bank::getUsers()->at("TheOne1").acceptRequest(Bank::getTransactions()->get(&Bank::getUsers()->at("MazinMohamedPeter")).back());

	for (Transaction* tans : Bank::getTransactions()->get(&Bank::getUsers()->at("3m7md"))) {
		for (string e : tans->toStringArray()) {
			cout << e << " ";
		}
		cout << endl;
	}
	//LoginFrame* loginFrame = new LoginFrame("HeisenBank");
	//loginFrame->SetClientSize(450, 700);
	//loginFrame->Center();
	//loginFrame->Show();
	//loginFrame->SetIcon(icon);

	MainFrame* mainFrame = new MainFrame(Bank::getUsers()->find("TheOne1")->second, "Heisenbank");
	mainFrame->SetClientSize(620, 1000);
	mainFrame->Center();
	mainFrame->Show();
	mainFrame->SetIcon(icon);
	return true;
}

int App::OnExit() {
	
	
	cout << "System Exit" << endl;
	system("pause");

	return 0;
}

wxIMPLEMENT_APP(App);
