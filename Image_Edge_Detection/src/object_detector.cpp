/*
 * object_detector.cpp
 *
 *  Created on: Aug 16th, 2015
 *      Author: Samuel Simpson
 */

#include <object_detector.h>
#include "image.h"
#include <iostream>

Object_Detector::Object_Detector(Image* thresholded_image)
{
	m_image = thresholded_image;
}

Object_Detector::~Object_Detector()
{
	for(int x = 0; x < (m_image->m_width); x++)
	{
		delete[] m_edges[x];
	}
	delete[] m_edges;
}

void Object_Detector::Initialize()
{
	m_edges = new bool*[m_image->m_width];
	for(int x = 0; x < (m_image->m_width); x++)
	{
		m_edges[x] = new bool[m_image->m_height];
	}
}

void Object_Detector::Determine_Edges()
{
	Pixel red_pix;
	red_pix = {.r = 0xFF,	.g = 0x00,	.b = 0x00,	.a = 0xFF};

	Pixel* index_pix = new Pixel;

	for (int x = 0; x < (m_image->m_width); x++)
	{
		for (int y = 0; y < (m_image->m_height); y++)
		{
			m_edges[x][y] = Is_Edge(x, y, index_pix);

			if (m_edges[x][y])
			{
				m_image->Set_Pixel(x,y, &red_pix);
			}
		}
	}
}

bool Object_Detector::Is_Edge(int x, int y, Pixel* index_pix)
{
	bool retval = false;
	int start_x, start_y, end_x, end_y, index_x, index_y;

	m_image->Get_Pixel(x, y, index_pix);

	//if the pixel is not within the threshold, it is ignored
	//this means only a relatively small percentage of pixels
	//must be checked
	if (index_pix->r == 0xFF)
	{
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				index_x = x+i;
				index_y = y+j;

				if ( (index_x >= 0) && (index_x < m_image->m_width) && (index_y >= 0) && (index_y < m_image->m_height))
				{
					m_image->Get_Pixel(index_x, index_y, index_pix);
					if (index_pix->r == 0x00)
					{
						retval = true;
						break;
					}
				}

			}
		}
	}

	return retval;
}
