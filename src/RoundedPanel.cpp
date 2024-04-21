#include "RoundedPanel.h"

RoundedPanel::RoundedPanel(wxWindow* parent, wxWindowID id,const wxPoint& pos, const wxSize& size,long style, wxColour color)
    : wxPanel(parent, id, pos, size, style)
{
    this->color = color;
}

void RoundedPanel::OnPaint(wxPaintEvent& event) {

    wxPaintDC dc(this);
    dc.SetBrush(color); // Set the background color
    dc.SetPen(color);
    
    // Draw a rounded rectangle
    int radius = 20;
    int width, height;
    GetSize(&width, &height);
    dc.DrawRoundedRectangle(0, 0, width, height, radius);
}

wxBEGIN_EVENT_TABLE(RoundedPanel, wxPanel)
EVT_PAINT(RoundedPanel::OnPaint)
wxEND_EVENT_TABLE()
