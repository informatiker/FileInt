/***************************************************************
 * Name:      FileIntMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Christian Müller (cmueller@email.is)
 * Created:   2007-04-28
 * Copyright: (no)
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "FileINtMain.h"
#include "AbsFileIntController.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

BEGIN_EVENT_TABLE(FileIntMain, wxFrame)
END_EVENT_TABLE()

FileIntMain::FileIntMain(wxFrame *frame, const wxString& title, AbsFileIntController *app)
    : wxFrame(frame, MAINFRAME_ID, title, wxDefaultPosition, wxDefaultSize)
{
	//assign Controller to call back
	this->Controller = app;

	//create progressbar
	this->ProgressBar = new wxGauge(this,
																	-1,
																	100,
																	wxDefaultPosition,
																	wxSize(-1,10),
																	wxGA_HORIZONTAL,
																	wxDefaultValidator,
																	wxT("ProgressBar"));

	//prepare file chooser
	this->FileChooser = new wxFileDialog(this);

	this->SetBackgroundStyle(wxBG_STYLE_SYSTEM);
	this->SetBackgroundColour(wxNullColour);
	//this->Update();

	this->MainSizer = new wxBoxSizer(wxVERTICAL);

	//prepare left side of the first 2 lines
	this->FileOutputLabel = new wxStaticText(this,
																						-1,
																						_T("File"),
																						wxDefaultPosition,
																						wxDefaultSize,
																						wxALIGN_LEFT);

	this->FilePathOutput = new wxTextCtrl(this,
																				FILEPATH_OUTPUT_ID,
																				_T("Default Text"),
																				wxDefaultPosition,
																				wxSize(200,-1),
																				wxTE_READONLY);

	//**connect FilePathOutput to ONCLICK event:
	this->FilePathOutput->Connect(FILEPATH_OUTPUT_ID,
								wxEVT_LEFT_DOWN,
								(wxObjectEventFunction) &FileIntMain::onSetFile,
								NULL,
								this);

	this->FilePathOutput->SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	this->FilePathOutput->SetBackgroundColour(wxColor(212, 208, 200));

	//add file label & filepath output to mainframe
	this->MainSizer->Add(this->FileOutputLabel,
												0,
												wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER|wxTOP|wxLEFT|wxRIGHT,
												2,//5
												NULL);
	this->MainSizer->Add(this->FilePathOutput,
												0,
												wxEXPAND|wxALIGN_TOP|wxALIGN_CENTER|wxTOP|wxLEFT|wxRIGHT,
												0,//5
												NULL);


	this->MainSizer->AddStretchSpacer(1);

	//last lines: size label & size + algorithm name & checksum

	this->BottomLineSizer = new wxBoxSizer(wxHORIZONTAL);

	//prepare left side of last two lines
	this->BottomLeftSizer = new wxBoxSizer(wxVERTICAL);
	this->FileSizeLabel = new wxStaticText(this,
																						-1,
																						_T("Size"),
																						wxDefaultPosition,
																						wxDefaultSize,
																						wxALIGN_LEFT);
	this->FileSizeOutput = new wxTextCtrl(this,
												-1,
												_T("0"),
												wxDefaultPosition,
												wxSize(100,-1),
												wxTE_READONLY);

	this->FileSizeOutput->SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	this->FileSizeOutput->SetBackgroundColour(wxColor(212, 208, 200));

	this->BottomLeftSizer->Add(FileSizeLabel,
														0,
														wxALIGN_CENTER_VERTICAL,
														0,
														NULL);
	this->BottomLeftSizer->Add(FileSizeOutput, 0, wxEXPAND, 0, NULL);


	//prepare right side of the first 2 lines
	this->BottomRightSizer = new wxBoxSizer(wxVERTICAL);

	this->ChecksumLabel = new wxStaticText(this,
																					-1,
																					_T("CRC-32:"),
																					wxDefaultPosition,
																					wxDefaultSize,
																					wxALIGN_LEFT);
	this->FileChecksumOutput = new wxTextCtrl(this,
																				-1,
																				_T("Checksum"),
																				wxDefaultPosition,
																				wxDefaultSize,
																				wxTE_READONLY);

	this->FileChecksumOutput->SetBackgroundStyle(wxBG_STYLE_CUSTOM);
	this->FileChecksumOutput->SetBackgroundColour(wxColor(212, 208, 200));

	this->BottomRightSizer->Add(ChecksumLabel, 0, wxALIGN_LEFT|wxALIGN_LEFT, 0, NULL);
	this->BottomRightSizer->Add(FileChecksumOutput,
															1,
															wxEXPAND|wxALIGN_LEFT,
															0,
															NULL);

	this->BottomLineSizer->Add(this->BottomLeftSizer,
															1,
															wxEXPAND,
															0,
															NULL);
	this->BottomLineSizer->Add(this->BottomRightSizer,
															1,
															wxEXPAND,
															0,
															NULL);
	this->MainSizer->Add(this->BottomLineSizer,
												0,
												wxEXPAND,
												0,//5
												NULL);

	this->MainSizer->Add(this->ProgressBar,
												0,
												wxEXPAND|wxALIGN_BOTTOM|wxALIGN_CENTER|wxLEFT|wxRIGHT|wxBOTTOM,
												2,
												NULL);

	this->SetSizer(this->MainSizer);
	this->MainSizer->SetSizeHints(this);

}

//***Setters for Viewstate
void FileIntMain::setCheckSum(std::string sum) {
	this->FileChecksumOutput->ChangeValue(wxString(sum.c_str(), wxConvUTF8));
}

void FileIntMain::setFilePath(std::string path) {
	this->FilePathOutput->ChangeValue(wxString(path.c_str(), wxConvUTF8));
}

void FileIntMain::setFileSize(unsigned long size) {
	this->FileSizeOutput->ChangeValue(wxString(wxString::Format(wxT("%d"),size)));
}

//readjust the progessbar
void FileIntMain::setProgress(int curr, int max) {
	this->ProgressBar->SetRange(max);
	this->ProgressBar->SetValue(curr);
}

//select new file
void FileIntMain::onSetFile(wxMouseEvent& event) {
	if(this->FileChooser->ShowModal() == wxID_OK) {
		//this->setFilePath(std::string((this->FileChooser->GetPath().mb_str())));
		this->Controller->setFile(std::string((this->FileChooser->GetPath().mb_str())));
	}
}

FileIntMain::~FileIntMain()
{
}
