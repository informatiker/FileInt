/***************************************************************
 * Name:      FileIntApp.h
 * Purpose:   Defines Application Class
 * Author:    Christian Müller (cmueller@email.is)
 * Created:   2007-04-28
 * Copyright: (no)
 * License:
 **************************************************************/

#ifndef FILEINTAPP_H
#define FILEINTAPP_H

#include <wx/app.h>
#include <wx/cmdline.h>

#include "PosixFile.h"
#include "AbsFileIntController.h"
#include "FileIntMain.h"

static const wxCmdLineEntryDesc CmdArgs[] =
	{
		{
		wxCMD_LINE_PARAM,
		NULL,
		NULL,
		wxT("Filepath"),
		wxCMD_LINE_VAL_STRING,
		wxCMD_LINE_PARAM_OPTIONAL
		},
		{ wxCMD_LINE_NONE	}
	};

class FileIntApp : public AbsFileIntController, public wxApp
{
    public:
			FileIntApp();
			~FileIntApp();
      virtual bool OnInit();
			void setFile(std::string newPath);
		private:
			wxCmdLineParser *ArgParser;
			PosixFile *currentFile;
			FileIntMain *Frame;
};

#endif // FILEINTAPP_H
