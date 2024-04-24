#include "ImageButton.h"
#include <string>
#include <wx/wx.h>
#include <memory>

using namespace std;
ImageButton::ImageButton(string imgSrc, wxPanel panel, wxPoint position, wxSize size)
{
    wxImage icon(imgSrc, wxBITMAP_TYPE_PNG);
    if (icon.IsOk()) {
        printf("zobr");
        bitmap = make_shared<wxBitmapButton>(&panel, wxID_ANY, wxBitmap(icon.Rescale(size.x, size.y, wxIMAGE_QUALITY_HIGH)),position, size, wxBU_AUTODRAW | wxBORDER_NONE);
        bitmap->SetBackgroundColour(panel.GetBackgroundColour());
    }
}


//wxBitmapButton* ImageButton::getBitmap()
//{
//	return bitmap;
//}

//wxImage pfpIcon(wxT("resources\\profile.png"), wxBITMAP_TYPE_PNG);
//pfpIcon.Rescale(80, 80, wxIMAGE_QUALITY_HIGH); // Rescale the image to 60x60
//wxBitmap pfpBitmap(pfpIcon);
//wxBitmapButton* pfpButton = new wxBitmapButton(topPanel, wxID_ANY, pfpBitmap, wxPoint(15, 15), wxSize(80, 80), wxBU_AUTODRAW | wxBORDER_NONE);
//pfpButton->SetBackgroundColour(wxColour(52, 100, 117));
//pfpButton->Bind(wxEVT_BUTTON, &MainFrame::onBellButtonClick, this);