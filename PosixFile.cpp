#include "PosixFile.h"
#include "crc32generator.h"

#include <string>
#include <fstream>
#include <cstdio>

//PosixFile represents a file with the ability to "tell" its crc32-checksum
PosixFile::PosixFile(std::string FilePath) {
	this->FilePath = FilePath;
	this->Generator = new crc32generator;
	this->Handle = fopen(this->FilePath.c_str(), "rb");
}

//fread "step" bytes and add to crc polynome
bool PosixFile::stepCRC32(int step) {

	byte buffer;
	for(int i = 0; (i < step && !feof(this->Handle)); i++) {
		//read byte
		fread(&buffer, 1, 1, this->Handle);
		this->Generator->addVal(buffer);
	}

	if(feof(this->Handle)) return false;
	else return true;
}

//return crc32 polynome as hex string
std::string PosixFile::getCRC32string() {
	unsigned long retrnval = this->Generator->getCRC();
	char hexcrc[9];
	memset(hexcrc, 0, 9);

	//sprintf(hexcrc, "%d:%0.2X;%0.2X;%0.2X;%0.2X",counter, *ptr, *(ptr+1), *(ptr+2), *(ptr+3));
	sprintf(hexcrc, "%X", (unsigned int)retrnval);
	return std::string(hexcrc);
}

//automates building the crc32-polynome and returning it's hex-string
std::string PosixFile::buildCRC32string() {
	while(this->stepCRC32(-1));
	return this->getCRC32string();
}

unsigned long PosixFile::getFileSize() {
	//save old position in open stream
	unsigned long oldposition = ftell(this->Handle);
	//jump to end
	fseek(this->Handle, 0, SEEK_END);
	//save new position
	unsigned long newpos = ftell(this->Handle);;
	//reset position
	fseek(this->Handle, oldposition, SEEK_SET);

	return newpos;
}

PosixFile::~PosixFile() {
	fclose(this->Handle);
	delete this->Generator;
}
