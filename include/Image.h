#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "common.h"

using namespace std;

class Image
{

public:

	uint64_t width;
	uint64_t height;
	//uint8_t **data;
	uint32_t **data;

public:

	Image(uint64_t width, uint64_t height);
	~Image();

	static Image *createFromFile(string filename);

};

#endif