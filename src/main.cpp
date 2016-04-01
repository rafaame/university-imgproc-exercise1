#include "common.h"
#include "Operation.h"
#include "Image.h"

using namespace std;

int main(int argc, char *argv[])
{

	if(argc < 2)
	{

		cout << "Usage: main /path/to/pgm/image";

		return 0;

	}

	char *arg = argv[1];
	string filename = string(arg);

	Image *image = NULL;

	Operation *openImage = new Operation(OPERATION_NONE, filename);
	image = openImage->execute();

	Operation *invert = new Operation(OPERATION_INVERT);
	image = invert->execute(image);

    image->writeToFile("output.pgm");

}