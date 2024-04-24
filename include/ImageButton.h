#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string>
#include <wx/wx.h>
#include<memory>

using namespace std;

class ImageButton {

	private:

	public:

		shared_ptr<wxBitmapButton> bitmap;

		ImageButton(string imgSrc, wxPanel panel, wxPoint position, wxSize size);

		//wxBitmapButton* getBitmap();
};