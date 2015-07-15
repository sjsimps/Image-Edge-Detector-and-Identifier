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

enum Color {
	red,
	green,
	blue,
	monochrome
};

class Image
{

public:
	Image();
	~Image();

	bool Decode_From_Disk(const char* filename);
	bool Encode_From_Disk(const char* filename);

	void Get_Pixel(int x, int y, Pixel* pix);
	void Set_Pixel(int x, int y, Pixel* pix);

	void Apply_Gauss_Filter3();
	void Apply_Gauss_Filter5();

	void Calculate_Differential_Intensity(Color channel);
	void Calculate_Angular_Intensity(Color channel);

	std::vector<unsigned char> m_image;
	Intensity_Gradient **m_gradient;
	unsigned m_width;
	unsigned m_height;

private:
	void Apply_Gauss_Blur(const int kernel_size);
	float Get_Angular_Kernel_Val(int x, int y, float angle);
	void Map_Intensity_To_Pixels(Color channel);
	float Get_Angular_Similarity(float angle1, float angle2);

};


//////////////////////////// IMAGE KERNELS //////////////

////////////// GAUSS BLUR KERNELS

const float gauss_3_kernel[3][3] =
{
	{0.0625,	0.125,	0.0625},
	{0.125,		0.25,	0.125},
	{0.0625,	0.125,	0.0625}
};

const float gauss_5_kernel[5][5] =
{
	{2,	4,	5,	4,	2},
	{4,	9,	12,	9,	4},
	{5,	12,	15,	12,	5},
	{4,	9,	12,	9,	4},
	{2,	4,	5,	4,	2}
};


////////////// DIFFERENTIAL KERNELS

const float vert_kernel[3][3] =
{
	{-1,-2,-1},
	{0,0,0},
	{1,2,1}
};

const float horz_kernel[3][3] =
{
	{-1,0,1},
	{-2,0,2},
	{-1,0,1}
};

////////////// ANGULAR KERNELS

//The kernel postfixes indicate the angular center corresponding to each
//kernel. When used for angular comparison, the kernel used will be picked
// based on the angle.
const float kernel_0d8pi[3][3] =
{
		{0,0,0},
		{2,0,2},
		{0,0,0}
};
const float kernel_1d8pi[3][3] =
{
		{0,0,1},
		{1,0,1},
		{1,0,0}
};
const float kernel_2d8pi[3][3] =
{
		{0,0,2},
		{0,0,0},
		{2,0,0}
};
const float kernel_3d8pi[3][3] =
{
		{0,1,1},
		{0,0,0},
		{1,1,0}
};
const float kernel_4d8pi[3][3] =
{
		{0,2,0},
		{0,0,0},
		{0,2,0}
};
const float kernel_5d8pi[3][3] =
{
		{1,1,0},
		{0,0,0},
		{0,1,1}
};
const float kernel_6d8pi[3][3] =
{
		{2,0,0},
		{0,0,0},
		{0,0,2}
};
const float kernel_7d8pi[3][3] =
{
		{1,0,0},
		{1,0,1},
		{0,0,1}
};

#endif /* INCLUDE_IMAGE_H_ */
