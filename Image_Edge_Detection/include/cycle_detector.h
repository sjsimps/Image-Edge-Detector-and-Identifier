/*
 * cycle_detector.h
 *
 *  Created on: Aug 16th, 2015
 *      Author: Samuel Simpson
 */
#include <vector>
#ifndef INCLUDE_CYCLE_DETECTOR_H_
#define INCLUDE_CYCLE_DETECTOR_H_

typedef struct Cycle_Point
{
	unsigned int x,y;
	Cycle_Point* next;
} Cycle_Point;

typedef struct Cycle
{
	Cycle_Point* start;
	unsigned int length;
} Cycle;

class Cycle_Detector
{
public:
	Cycle_Detector(Image* thresholded_image);
	~Cycle_Detector();

	std::vector<Cycle> m_cycles;
	bool **m_edges;
	Image *m_image;
};

#endif /* INCLUDE_CYCLE_DETECTOR_H_ */
