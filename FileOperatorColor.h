#ifndef FILEOPERATORCOLOR_H
#define FILEOPERATORCOLOR_H
#include "Grain.h"


class FileOperatorColor
{
public:
	FileOperatorColor();
	void saveToFile(Grain***, int, int, int);	

	virtual ~FileOperatorColor();

protected:

private:
};

#endif // FILEOPERATORCOLOR_H