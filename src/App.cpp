#include "App.h"
#include "LoginFrame.h"

bool App::OnInit() {
	LoginFrame* loginFrame = new LoginFrame("Walter Wallet");
	loginFrame->SetClientSize(450, 700);
	loginFrame->Center();
	loginFrame->Show();
	return true;
}
wxIMPLEMENT_APP(App);
