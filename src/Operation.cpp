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

        case OPERATION_LOW_PASS_FILTER:
        {

            result = leftOperand;

            Image *tmpImage = new Image(result->width + 2, result->height + 2);

            //Copy the image to the center of our tmpImage for processing
            for(uint64_t i = 0; i < result->height; i++)
                for(uint64_t j = 0; j < result->width; j++)
                {

                    if(i == 0)
                        tmpImage->data[0][j+1] = result->data[0][j];
                    else if(i == (result->height - 1))
                        tmpImage->data[result->height][j+1] = result->data[i][j];

                    if(j == 0)
                        tmpImage->data[i][0] = result->data[i][0];
                    else if(j == (result->width - 1))
                        tmpImage->data[i+1][result->width] = result->data[i][j];

                    tmpImage->data[i+1][j+1] = result->data[i][j];

                }

            //Fix corners
            tmpImage->data[0][0] = result->data[0][0];
            tmpImage->data[0][tmpImage->width-1] = result->data[0][result->width-1];
            tmpImage->data[tmpImage->height-1][0] = result->data[result->height-1][0];
            tmpImage->data[tmpImage->height-1][tmpImage->width-1] = result->data[result->height-1][result->width-1];

            double **meanMask = new double *[3];
            for(uint8_t i = 0; i < 3; i++)
            {

                meanMask[i] = new double[3];

                for(uint8_t j = 0; j < 3; j++)
                    meanMask[i][j] = 1.0 / 9.0;

            }

            for(uint64_t x = 0; x < result->height; x++)
                for(uint64_t y = 0; y < result->width; y++)
                {

                    uint32_t value = 0;

                    for(uint64_t i = 0; i < 3; i++)
                        for(uint64_t j = 0; j < 3; j++)
                            value += meanMask[i][j] * tmpImage->data[x+i][y+j];

                    tmpImage->data[x+1][y+1] = value;

                }

            for(uint64_t i = 0; i < result->height; i++)
                for(uint64_t j = 0; j < result->width; j++)
                    result->data[i][j] = tmpImage->data[i+1][j+1];

            delete tmpImage;

            /*for(uint64_t i = 0; i < result->height; i++)
            {

                for(uint64_t j = 0; j < result->width; j++)
                    std::cout << result->data[i][j] << " ";

                std::cout << std::endl;

            }*/

            /*std::cout << std::endl;
            for(uint64_t i = 0; i < tmpImage->height; i++)
            {

                for(uint64_t j = 0; j < tmpImage->width; j++)
                    std::cout << tmpImage->data[i][j] << " ";

                std::cout << std::endl;

            }
            std::cout << std::endl;*/

            break;

        }

		default:
		{

			result = rightOperand;

		}

	}

	return result;

}