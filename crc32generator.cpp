#include "crc32generator.h"
#include "ccrc32.h"

/*crc32generator abstracts the generation of polynomes so each step can be
	triggered individually and progress can be reported on the way*/
crc32generator::crc32generator() {
	this->reset();
}

void crc32generator::addVal(byte data) {
	this->currentCRC =
		((this->currentCRC) >> 8) ^ this->ulTable[((this->currentCRC) & 0xFF) ^ data];
}

void crc32generator::reset() {
	this->currentCRC = 0xffffffff;
}

unsigned long crc32generator::getCRC() {
	return this->currentCRC ^= 0xffffffff;
}
