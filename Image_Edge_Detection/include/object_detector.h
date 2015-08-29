/*
 * object_detector.h
 *
 *  Created on: Aug 16th, 2015
 *      Author: Samuel Simpson
 */
#include <vector>
#ifndef INCLUDE_OBJECT_DETECTOR_H_
#define INCLUDE_OBJECT_DETECTOR_H_

typedef struct Graph_Point
{
	int x,y;
	Graph_Point* next;
} Graph_Point;

typedef struct Graph
{
	Graph_Point* start;
	unsigned int length;
} Graph;

class Object_Detector
{
public:
	Object_Detector(Image* thresholded_image);
	~Object_Detector();
	void Initialize();

	void Determine_Edges();

	void Determine_All_Disconected_Graphs();

	void Object_Detector::Highlight_Largest_Graphs(int num_graphs);
	void Object_Detector::Highlight_Largest_Graphs_By_Threshold(int threshold);

	std::vector<Graph> m_graphs;
	bool **m_edges;
	Image *m_image;

private:
	bool Is_Edge(int x, int y, Pixel* index_pix);
};

#endif /* INCLUDE_OBJECT_DETECTOR_H_ */
