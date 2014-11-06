#include "Image.h"

using namespace std;

Image *Image::createFromFile(string filename)
{

	string line;
	ifstream file(filename, ios::in | ios::binary);

	if(file.is_open())
	{

		if(file.good())
		{

			getline(file, line);

			if(/*line.compare("P2") == 0*/ true)
			{

				stringstream ss;
				ss << file.rdbuf();

				uint64_t width = 0, height = 0, unknown = 0;
				ss >> width >> height >> unknown;

				if(width > 0 && height > 0)
				{

					Image *image = new Image(width, height);

                    uint8_t *buffer = new uint8_t[width * height];

                    ss.read(reinterpret_cast<char *>(buffer), width * height * sizeof(uint8_t));

					for(int i = 0; i < height; i++)
						for(int j = 0; j < width; j++)
                            image->data[i][j] = (uint8_t) buffer[i * width + j];

					return image;

				}

			}

		}

	}

	return NULL;

}

bool Image::writeToFile(string filename)
{

    string line;
    ofstream file(filename, ios::out | ios::binary);

    if(!file.is_open())
        return false;

    if(!file.good())
        return false;

    file << "P5" << endl;
    file << width << " " << height << endl;
    file << 255 << endl;

    for(uint64_t i = 0; i < height; i++)
    {

        char *buffer = new char[width];

        for(uint64_t j = 0; j < width; j++)
            buffer[j] = (uint8_t) data[i][j];

        file.write((const char *) buffer, width);

    }

    file.close();

    return true;

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