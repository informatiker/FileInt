#ifndef CRC32GENERATOR_H
#define CRC32GENERATOR_H

#include "ccrc32.h"


class crc32generator : protected CCRC32
{
	public:
		/** Default constructor */
		crc32generator();
		void addVal(byte data);
		void reset();
		unsigned long getCRC();
	protected:
	private:
		unsigned long currentCRC;
};

#endif // CRC32GENERATOR_H
