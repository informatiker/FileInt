/***************************************************************
 * Name:      FileIntApp.cpp
 * Purpose:   Code for Application Class
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

#include "FileIntApp.h"
#include "FileIntMain.h"

#include <string>

IMPLEMENT_APP(FileIntApp);

FileIntApp::FileIntApp() {
	this->currentFile = NULL;
	this->Frame = NULL; //not neede yet
}

bool FileIntApp::OnInit()
{
		this->ArgParser = new wxCmdLineParser(CmdArgs, argc, argv);
    this->ArgParser->Parse();

		this->Frame = new FileIntMain(0L, wxT("Integrity Check"), this);
    this->Frame->SetIcon(wxICON(aaaa)); // To Set App Icon

		this->Frame->SetSize(wxSize(400,-1));
		this->Frame->Show();

    //check for param
    if(this->ArgParser->GetParamCount() > 0) {
			this->setFile(std::string(this->ArgParser->GetParam().mb_str()));
		} else {
			this->Frame->setFilePath(std::string("Filepath"));
			this->Frame->setFileSize(0);
			this->Frame->setCheckSum(std::string("Checksum"));
		}

    return true;
}

void FileIntApp::setFile(std::string newPath) {
	delete this->currentFile;
	this->currentFile = new PosixFile(newPath);

	this->Frame->setFilePath(this->currentFile->getFilePath());
	this->Frame->setFileSize(this->currentFile->getFileSize());
	this->Frame->setCheckSum(std::string("calculating..."));
	this->Frame->Update();

	int step = 1;
	while(this->currentFile->stepCRC32(1000)) {
		this->Frame->setProgress(step*1000, this->currentFile->getFileSize());
		step++;
	}

	this->Frame->setCheckSum(this->currentFile->buildCRC32string());
	this->Frame->setProgress(0, 100);
}

FileIntApp::~FileIntApp() {
	delete this->ArgParser;
	delete this->currentFile;
}
