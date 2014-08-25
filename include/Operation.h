#ifndef __OPERATION_H__
#define __OPERATION_H__

using namespace std;

enum Operation_t
{

	OPERATION_NONE,
	OPERATION_SUM,
	OPERATION_SUBTRACT,
	OPERATION_CONTRAST_STRECH,
	OPERATION_LAST

};

class Operation
{

private:

	Operation_t type;
	string filename;

public:

	Operation(Operation_t type, string filename)
	{

		this->type = type;
		this->filename = filename;

	}

	Operation(Operation_t type, char *filename)
	{

		this->type = type;
		this->filename = string(filename);

	}

	Operation(Operation_t type)
	{

		this->type = type;

	}

	const Operation_t getType()
	{

		return type;

	}

	const string getFilename()
	{

		return filename;

	}

};

#endif