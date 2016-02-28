/*
 * object_detector.h
 *
 *  Created on: Aug 16th, 2015
 *      Author: Samuel Simpson
 */
#include <vector>
#include <list>
#include <queue>
#include <iterator>

#include "image.h"
#ifndef INCLUDE_OBJECT_DETECTOR_H_
#define INCLUDE_OBJECT_DETECTOR_H_

typedef struct Graph_Point
{
	int x,y;
} Graph_Point;

typedef struct Graph
{
	std::list<Graph_Point> points;
	int size;
} Graph;

class Object_Detector
{
public:
	Object_Detector(Image* thresholded_image);
	~Object_Detector();
	void Initialize();
    void Deinitialize();

	void Determine_Edges();

	void Determine_Disconected_Graph(int x_in, int y_in, Pixel* color);
	void Determine_All_Disconected_Graphs();

	void Highlight_Largest_Graphs(int num_graphs);
	void Highlight_Largest_Graphs_By_Threshold(int threshold);

	std::list<Graph> m_graphs;
	bool **m_edges;
	Image *m_image;

private:
	bool Is_Edge(int x, int y, Pixel* index_pix);
    int initialized_height;
    int initialized_width;
};

#endif /* INCLUDE_OBJECT_DETECTOR_H_ */
