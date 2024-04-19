#include "App.h"
#include "LoginFrame.h"
#include "VirtualUser.h"
#include "User.h"
#include "MainFrame.h"

bool App::OnInit() {
	AllocConsole();
	AttachConsole(ATTACH_PARENT_PROCESS);
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);

	User user =  User(1, "TheOne1", "The One", 5000.0, "one1", "01211466100", "one@gmail.com", "active");

	wxIcon icon(wxT("resources\\walterWallet.ico"), wxBITMAP_TYPE_ICO);

	//LoginFrame* loginFrame = new LoginFrame("HeisenBank");
	//loginFrame->SetClientSize(450, 700);
	//loginFrame->Center();
	//loginFrame->Show();
	//loginFrame->SetIcon(icon);

	MainFrame* mainFrame = new MainFrame(user, "HeisenBank");
	mainFrame->SetClientSize(720, 1000);
	mainFrame->Center();
	mainFrame->Show();
	mainFrame->SetIcon(icon);
	return true;
}
wxIMPLEMENT_APP(App);
