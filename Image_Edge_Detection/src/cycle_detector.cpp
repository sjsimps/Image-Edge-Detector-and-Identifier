/*
 * cycle_detector.h
 *
 *  Created on: Aug 16th, 2015
 *      Author: Samuel Simpson
 */

#include "image.h"
#include "cycle_detector.h"
#include <iostream>

Cycle_Detector::Cycle_Detector(Image* thresholded_image)
{
	m_image = thresholded_image;
	m_edges = new bool*[m_image->m_width];
	for(int x = 0; x < (m_image->m_width); x++)
	{
		m_edges[x] = new bool[m_image->m_height];
	}
}

Cycle_Detector::~Cycle_Detector()
{
	for(int x = 0; x < (m_image->m_width); x++)
	{
		delete[] m_edges[x];
	}
	delete[] m_edges;
}
