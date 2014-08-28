#include "Operation.h"

#include "Image.h"

using namespace std;

Image *Operation::execute(Image *leftOperand/* = NULL*/)
{

	Image *rightOperand = Image::createFromFile(filename);
	Image *result = NULL;

	switch(type)
	{

		case OPERATION_SUM:

			//@FIXME: clone object instead
			result = leftOperand;

			if(leftOperand->height == rightOperand->height && leftOperand->width == rightOperand->width)
				for(int i = 0; i < leftOperand->height; i++)
					for(int j = 0; j < leftOperand->width; j++)
						result->data[i][j] = leftOperand->data[i][j] + rightOperand->data[i][j];

			break;

		case OPERATION_SUBTRACT:

			//@FIXME: clone object instead
			result = leftOperand;

			if(leftOperand->height == rightOperand->height && leftOperand->width == rightOperand->width)
				for(int i = 0; i < leftOperand->height; i++)
					for(int j = 0; j < leftOperand->width; j++)
						result->data[i][j] = leftOperand->data[i][j] - rightOperand->data[i][j];

			break;

		case OPERATION_CONTRAST_STRETCH:


			break;

		default:

			result = rightOperand;

	}

	for(int i = 0; i < result->height; i++)
	{

		for(int j = 0; j < result->width; j++)
			cout << result->data[i][j] << " ";

		cout << endl;

	}

	cout << endl;

	return result;

}