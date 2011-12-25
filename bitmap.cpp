/* The MIT License

Copyright (c) 2011 Sahab Yazdani

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <cstdlib>
#include <cmath>

#include "bitmap.h"

Bitmap::Bitmap( std::string &filename ) {
	file = PNG::load( filename );

	intensityMap = new unsigned char[file->w * file->h];
	unsigned char *imPtr = intensityMap, *cPtr = file->data;

	for (unsigned int y = 0; y < file->h; y++) {
		for (unsigned int x = 0; x < file->w; x++, imPtr++, cPtr+=4) {
			*imPtr = 255 - (unsigned char)std::ceil(((double)(*(cPtr)) * 0.2126 + (double)(*(cPtr+1)) * 0.7152 + (double)(*(cPtr+2)) * 0.0722));
		}
	}
}

Bitmap::~Bitmap() {
	PNG::freePng( file );
	delete[] intensityMap;
}

double Bitmap::getIntensity( unsigned int x, unsigned int y ) {
	return (double)getDiscreteIntensity(x,y)/255.0;
}

unsigned char Bitmap::getDiscreteIntensity( unsigned int x, unsigned int y ) {
	return intensityMap[y * file->w + x];
}

void Bitmap::getColour( unsigned int x, unsigned int y, unsigned char &r, unsigned char &g, unsigned char &b ) {
	unsigned char *dataPtr = file->data + ( (y * file->w + x) * 4 );
	r = *(dataPtr);
	g = *(dataPtr+1);
	b = *(dataPtr+2);
}

unsigned int Bitmap::getWidth() {
	return file->w;
}

unsigned int Bitmap::getHeight() {
	return file->h;
}

