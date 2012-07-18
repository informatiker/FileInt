/***************************************************************
 * Name:      FileIntMain.h
 * Purpose:   Defines Application Frame
 * Author:    Christian Müller (cmueller@email.is)
 * Created:   2007-04-28
 * Copyright: (no)
 * License:
 **************************************************************/

#ifndef FILEINTMAIN_H
#define FILEINTMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <string>
#include "AbsFileIntController.h"

class FileIntMain: public wxFrame
{
    public:
        FileIntMain(wxFrame *frame, const wxString& title, AbsFileIntController *app);

        //setters for viewstate
        void setCheckSum(std::string sum);
        void setFilePath(std::string path);
        void setFileSize(unsigned long size);

        void setProgress(int curr, int max);

        ~FileIntMain();
    private:
				//controllerpointer
				AbsFileIntController *Controller;
				wxBoxSizer *MainSizer;

				wxStaticText *FileOutputLabel;
				wxTextCtrl *FilePathOutput;


				wxBoxSizer *BottomLineSizer;
				//Holds filesize
				wxBoxSizer *BottomLeftSizer;
				wxStaticText *FileSizeLabel;
				wxTextCtrl *FileSizeOutput;
				//holds checksum
				wxBoxSizer *BottomRightSizer;
				wxStaticText *ChecksumLabel;
				wxTextCtrl *FileChecksumOutput;

				wxFileDialog *FileChooser;

				wxGauge *ProgressBar;
        //switch file
        void onSetFile(wxMouseEvent& event);

        DECLARE_EVENT_TABLE()
};

enum {
	MAINFRAME_ID = wxID_HIGHEST +1,
	FILEPATH_OUTPUT_ID
	};


#endif // FILEINTMAIN_H
