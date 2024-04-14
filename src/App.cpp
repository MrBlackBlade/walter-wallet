#include "App.h"
#include "LoginFrame.h"
#include "VirtualUser.h"
#include "User.h"

bool App::OnInit() {
	AllocConsole();
	AttachConsole(ATTACH_PARENT_PROCESS);
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);
	
	LoginFrame* loginFrame = new LoginFrame("Walter Wallet");
	loginFrame->SetClientSize(450, 700);
	loginFrame->Center();
	loginFrame->Show();
	return true;
}
wxIMPLEMENT_APP(App);
