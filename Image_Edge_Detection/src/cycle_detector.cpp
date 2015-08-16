/*
 * cycle_detector.h
 *
 *  Created on: Aug 16th, 2015
 *      Author: Samuel Simpson
 */

#include "image.h"
#include "cycle_detector.h"
#include <iostream>

Cycle_Detector::Cycle_Detector()
{

}

Cycle_Detector::~Cycle_Detector()
{
	for(int x = 0; x<m_width; x++)
	{
		delete[] m_edges[x];
	}
	delete[] m_edges;
}

void Cycle_Detector::Extract_Image_Data(Image* thresholded_image)
{
	m_width = thresholded_image->m_width;
	m_height = thresholded_image->m_height;

	m_edges = new bool*[m_width];
	for(int x = 0; x<m_width; x++)
	{
		m_edges[x] = new bool[m_height];
	}
}
