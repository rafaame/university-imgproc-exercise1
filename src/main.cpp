#include "common.h"
#include "Operation.h"

using namespace std;

int main(int argc, char *argv[])
{

	if(argc < 2)
	{

		cout << "Usage: main /path/to/pgm/image -s/path/to/pgm/image/to/sum -u/path/to/pgm/image/to/subtract -c";

		return 0;

	}

	queue<Operation *> ops;

	for(int i = 1; i < argc; i++)
	{

		char *arg = argv[i];

		Operation *op = NULL;

		if(arg[0] == '-')
		{

			if(strlen(arg) > 1)
			{

				string filename = string(arg + 2);

				switch(arg[1])
				{

					case 's':

						op = new Operation(OPERATION_SUM, filename);

						break;

					case 'u':

						op = new Operation(OPERATION_SUBTRACT, filename);

						break;

					case 'c':

						op = new Operation(OPERATION_CONTRAST_STRECH);

						break;

					default:

						cout << "Invalid argument '" << arg << "'" << endl;

				}

			}

		}
		else
			op = new Operation(OPERATION_NONE, arg);

		if(op)
			ops.push(op);

	}

	Operation *op = NULL;
	while(op = ops.front())
	{

		cout << "Operation = " << op->getType() << "; filename = " << op->getFilename() << endl;

		ops.pop();

	}

}