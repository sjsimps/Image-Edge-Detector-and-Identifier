#include "lodepng.h"
#include "image.h"
#include <iostream>


Image::Image()
{
	m_width = 0;
	m_height = 0;
}

Image::~Image(){}

void Image::Encode_From_Disk(const char* filename)
{
	//Encode and save image to disk

	std::vector<unsigned char> png;

	unsigned error = lodepng::encode(png, m_image, m_width, m_height);
	if(!error) lodepng::save_file(png, filename);

	if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

void Image::Decode_From_Disk(const char* filename)
{
	//Load image from disk and decode
	std::vector<unsigned char> png;

	lodepng::load_file(png, filename);
	unsigned error = lodepng::decode(m_image, m_width, m_height, png);

	if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

	//the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA...
}

void Image::Get_Pixel(int x, int y, Pixel* pix)
{
	int index = 0;
	index += x*4;
	index += y*m_width*4;

	pix->r = m_image[index];
	pix->g = m_image[index+1];
	pix->b = m_image[index+2];
	pix->a = m_image[index+3];
}

void Image::Set_Pixel(int x, int y, Pixel* pix)
{
	int index = 0;
	index += x*4;
	index += y*m_width*4;

	m_image[index] 	= 	pix->r;
	m_image[index+1]= 	pix->g;
	m_image[index+2]= 	pix->b;
	m_image[index+3]= 	pix->a;
}

void Image::Apply_Gauss_Filter3()
{
	const int kernel_size = 3;
	float tmp_kernel[kernel_size][kernel_size] =
	{
		{0.0625,	0.125,	0.0625},
		{0.125,		0.25,	0.125},
		{0.0625,	0.125,	0.0625}
	};

	float **kernel = new float*[kernel_size];
	for(int i = 0; i<kernel_size; i++)
	{
		kernel[i] = new float[kernel_size];
		for(int j = 0; j<kernel_size; j++)
		{
			kernel[i][j]=tmp_kernel[i][j];
		}
	}

	Convolve(kernel_size, kernel);

	for(int i = 0; i<kernel_size; i++)
	{
		delete kernel[i];
	}
	delete kernel;
}

void Image::Apply_Gauss_Filter5()
{
	const int kernel_size = 5;
	float tmp_kernel[kernel_size][kernel_size] =
	{
		{2,	4,	5,	4,	2},
		{4,	9,	12,	9,	4},
		{5,	12,	15,	12,	5},
		{4,	9,	12,	9,	4},
		{2,	4,	5,	4,	2}
	};

	float **kernel = new float*[kernel_size];
	for(int i = 0; i<kernel_size; i++)
	{
		kernel[i] = new float[kernel_size];
		for(int j = 0; j<kernel_size; j++)
		{
			kernel[i][j]= (tmp_kernel[i][j]/159);
		}
	}

	Convolve(kernel_size, kernel);

	for(int i = 0; i<kernel_size; i++)
	{
		delete kernel[i];
	}
	delete kernel;
}

void Image::Convolve(const int kernel_size, float **kernel)
{
	//Kernel size must be an odd number
	int kernel_width = kernel_size >> 1;
	float r,g,b;

	Pixel* index_pix = new Pixel;
	Pixel* new_img[m_width][m_height];

	for (int x = 0; x < m_width; x++)
	{
		for (int y = 0; y < m_height; y++)
		{
			r=0;
			g=0;
			b=0;

			for (int i = -kernel_width; i <= kernel_width; i++)
			{
				for (int j = -kernel_width; j <= kernel_width; j++)
				{
					if (x+i > 0 && y+i > 0 && x+i < m_width && y+j < m_height)
					{
						Get_Pixel(x+i, y+j, index_pix);
						r += (index_pix->r * kernel[i+kernel_width][j+kernel_width]);
						g += (index_pix->g * kernel[i+kernel_width][j+kernel_width]);
						b += (index_pix->b * kernel[i+kernel_width][j+kernel_width]);
					}
				}
			}
			new_img[x][y] = new Pixel;
			new_img[x][y]->r = (r > 0xFF) ? 0xFF : (unsigned char)r;
			new_img[x][y]->g = (g > 0xFF) ? 0xFF : (unsigned char)g;
			new_img[x][y]->b = (b > 0xFF) ? 0xFF : (unsigned char)b;
			new_img[x][y]->a = 0xFF;
		}
	}

	for (int x = 0; x < m_width; x++)
	{
		for (int y = 0; y < m_height; y++)
		{
			Set_Pixel(x,y,new_img[x][y]);
			delete new_img[x][y];
		}
	}
	delete index_pix;
}

void Image::Calculate_Intensity(const int kernel_size, float **kernel)
{
	//Kernel size must be an odd number
	int kernel_width = kernel_size >> 1;
	float r,g,b;

	Pixel* index_pix = new Pixel;
	Pixel* new_img[m_width][m_height];

	for (int x = 0; x < m_width; x++)
	{
		for (int y = 0; y < m_height; y++)
		{
			r=0;
			g=0;
			b=0;

			for (int i = -kernel_width; i <= kernel_width; i++)
			{
				for (int j = -kernel_width; j <= kernel_width; j++)
				{
					if (x+i > 0 && y+i > 0 && x+i < m_width && y+j < m_height)
					{
						Get_Pixel(x+i, y+j, index_pix);
						r += (index_pix->r * kernel[i+kernel_width][j+kernel_width]);
						g += (index_pix->g * kernel[i+kernel_width][j+kernel_width]);
						b += (index_pix->b * kernel[i+kernel_width][j+kernel_width]);
					}
				}
			}
			new_img[x][y] = new Pixel;
			new_img[x][y]->r = (r > 0xFF) ? 0xFF : (unsigned char)r;
			new_img[x][y]->g = (g > 0xFF) ? 0xFF : (unsigned char)g;
			new_img[x][y]->b = (b > 0xFF) ? 0xFF : (unsigned char)b;
			new_img[x][y]->a = 0xFF;
		}
	}

	for (int x = 0; x < m_width; x++)
	{
		for (int y = 0; y < m_height; y++)
		{
			Set_Pixel(x,y,new_img[x][y]);
			delete new_img[x][y];
		}
	}
	delete index_pix;
}



