#include "App.h"
#include "LoginFrame.h"
#include "VirtualUser.h"
#include "User.h"

bool App::OnInit() {
	AllocConsole();
	AttachConsole(ATTACH_PARENT_PROCESS);
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);

	wxIcon icon(wxT("resources\\walterWallet.ico"), wxBITMAP_TYPE_ICO);

	LoginFrame* loginFrame = new LoginFrame("Walter Wallet");
	loginFrame->SetClientSize(450, 700);
	loginFrame->Center();
	loginFrame->Show();
	loginFrame->SetIcon(icon);
	return true;
}
wxIMPLEMENT_APP(App);
