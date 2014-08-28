#include "Image.h"

using namespace std;

Image *Image::createFromFile(string filename)
{

	string line;
	ifstream file(filename);

	if(file.is_open())
	{

		if(file.good())
		{

			getline(file, line);

			if(line.compare("P2") == 0)
			{

				stringstream ss;
				ss << file.rdbuf();

				uint64_t width = 0, height = 0, unknown = 0;
				ss >> width >> height >> unknown;

				if(width > 0 && height > 0)
				{

					Image *image = new Image(width, height);

					//getline(file, line);

					for(int i = 0; i < height; i++)
						for(int j = 0; j < width; j++)
							ss >> image->data[i][j];

					return image;

				}

			}

		}

	}

	return NULL;

}

Image::Image(uint64_t width, uint64_t height)
{

	this->width = width;
	this->height = height;

	data = new uint32_t *[height];

	for(int i = 0; i < height; i++)
		data[i] = new uint32_t[width];

}

Image::~Image()
{

	delete[] data;
	data = NULL;

}