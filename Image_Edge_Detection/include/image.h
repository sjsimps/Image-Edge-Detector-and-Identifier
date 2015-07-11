/*
 * image.h
 *
 *  Created on: Jun 21, 2015
 *      Author: Samuel Simpson
 */
#include <vector>
#ifndef INCLUDE_IMAGE_H_
#define INCLUDE_IMAGE_H_

typedef struct Pixel
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
} Pixel;

typedef struct Intensity_Gradient
{
	float intensity;
	float angle;
} Intensity_Gradient;

class Image
{

public:
	Image();
	~Image();

	void Decode_From_Disk(const char* filename);
	void Encode_From_Disk(const char* filename);

	void Get_Pixel(int x, int y, Pixel* pix);
	void Set_Pixel(int x, int y, Pixel* pix);

	void Apply_Gauss_Filter3();
	void Apply_Gauss_Filter5();
	void Convolve(int kernel_size, float **kernel);

	std::vector<unsigned char> m_image;
	Intensity_Gradient **m_gradient;
	unsigned m_width;
	unsigned m_height;

};

#endif /* INCLUDE_IMAGE_H_ */
