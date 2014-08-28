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
		{

			//@FIXME: clone object instead
			result = leftOperand;

			if(leftOperand->height == rightOperand->height && leftOperand->width == rightOperand->width)
				for(int i = 0; i < leftOperand->height; i++)
					for(int j = 0; j < leftOperand->width; j++)
						result->data[i][j] = leftOperand->data[i][j] + rightOperand->data[i][j];

			break;

		}

		case OPERATION_SUBTRACT:
		{

			//@FIXME: clone object instead
			result = leftOperand;

			if(leftOperand->height == rightOperand->height && leftOperand->width == rightOperand->width)
				for(int i = 0; i < leftOperand->height; i++)
					for(int j = 0; j < leftOperand->width; j++)
						result->data[i][j] = leftOperand->data[i][j] - rightOperand->data[i][j];

			break;

		}

		case OPERATION_CONTRAST_STRETCH:
		{

			//@FIXME: clone object instead
			result = leftOperand;

			uint32_t min = 0, max = 0, a = 255, b = 0;

			for(int i = 0; i < leftOperand->height; i++)
				for(int j = 0; j < leftOperand->width; j++)
				{

					if(result->data[i][j] < min)
						min = result->data[i][j];

					if(result->data[i][j] > max)
						max = result->data[i][j];

				}

			for(int i = 0; i < leftOperand->height; i++)
				for(int j = 0; j < leftOperand->width; j++)
					result->data[i][j] = (result->data[i][j] - min) * ( (b - a) / (max - min) );

			break;

		}

		default:
		{

			result = rightOperand;

		}

	}

	return result;

}