#include "Operation.h"

#include "Image.h"

using namespace std;

Image *Operation::execute(Image *leftOperand/* = NULL*/)
{

	Image *rightOperand = NULL;
	Image *result = NULL;

    if(filename.length() > 0)
        rightOperand = Image::createFromFile(filename);

	switch(type)
	{

		case OPERATION_INVERT:
		{

			//@FIXME: clone object instead
			result = leftOperand;

            for(int i = 0; i < leftOperand->height; i++)
                for(int j = 0; j < leftOperand->width; j++)
                    result->data[i][j] = abs((uint8_t) result->data[i][j] - 255);

            break;

		}

		default:
		{

			result = rightOperand;

		}

	}

	return result;

}