/*
 * object_detector.h
 *
 *  Created on: Aug 16th, 2015
 *      Author: Samuel Simpson
 */
#include <vector>
#ifndef INCLUDE_OBJECT_DETECTOR_H_
#define INCLUDE_OBJECT_DETECTOR_H_

typedef struct Walk_Point
{
	int x,y;
	Walk_Point* next;
} Walk_Point;

typedef struct Walk
{
	Walk_Point* start;
	unsigned int length;
} Walk;

class Object_Detector
{
public:
	Object_Detector(Image* thresholded_image);
	~Object_Detector();
	void Initialize();

	void Determine_Edges();

	std::vector<Walk> m_walks;
	bool **m_edges;
	Image *m_image;

private:
	bool Is_Edge(int x, int y, Pixel* index_pix);
};

#endif /* INCLUDE_OBJECT_DETECTOR_H_ */
