#include "App.h"
#include "LoginFrame.h"
#include "VirtualUser.h"
#include "User.h"
#include "MainFrame.h"
#include "FileSystemManagement.h"
#include "Transaction.h"


bool App::OnInit() {
	AllocConsole();
	AttachConsole(ATTACH_PARENT_PROCESS);
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);

	User user = User(1, "TheOne1", "The One", 5000.0, "one1", "01211466100", "one@gmail.com", "active");
	printf(user.getDisplayName().c_str());
	FileSystemManagement::writeRow(FileSystemManagement::userFile, user.toStringArray());
	wxIcon icon(wxT("resources\\walterWallet.ico"), wxBITMAP_TYPE_ICO);

	Transaction transaction = Transaction(&user, &user, 200.0, std::chrono::system_clock::now(), TransactionState::accepted);
	printf(transaction.getDisplayTime().data());
	printf(to_string(transaction.getEpochTime()).data());

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
wxIMPLEMENT_APP(App);
