#pragma once
#include <wx/wx.h>

class RoundedPanel : public wxPanel {
private:
    wxColour color;
public:

    RoundedPanel(wxWindow* parent, wxWindowID id = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxTAB_TRAVERSAL, wxColour color = wxColour(*wxWHITE));

    void OnPaint(wxPaintEvent& event);

    wxDECLARE_EVENT_TABLE();
};

