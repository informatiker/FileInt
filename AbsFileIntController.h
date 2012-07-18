#ifndef ABSFILEINTCONTROLLER_H
#define ABSFILEINTCONTROLLER_H

#include <string>

class AbsFileIntController
{
	public:
		virtual void setFile(std::string newPath)=0;
	protected:
	private:
};

#endif // ABSFILEINTCONTROLLER_H
