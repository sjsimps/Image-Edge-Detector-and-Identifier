/*
 * object_detector.cpp
 *
 *  Created on: Aug 16th, 2015
 *      Author: Samuel Simpson
 */

#include <object_detector.h>
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

	delete index_pix;
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

void Object_Detector::Determine_Disconected_Graph(int x_in, int y_in)
{
	std::queue<Graph_Point,std::list<Graph_Point> > bfs_queue;
	Graph_Point new_point, current_point;
	Graph new_graph;
	int index_x, index_y;
	Pixel blue_pix;

	blue_pix = {.r = 0x00,	.g = 0x00,	.b = 0xFF,	.a = 0xFF};
	new_graph.size = 0;
	new_point = {.x = x_in, .y = y_in};
	bfs_queue.push(new_point);

	while ( ! bfs_queue.empty() )
	{
		current_point = bfs_queue.front();
		bfs_queue.pop();

		m_image->Set_Pixel(current_point.x, current_point.y, &blue_pix);

		new_graph.points.push_back(current_point);
		new_graph.size++;

		m_edges[current_point.x][current_point.y] = false;

		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				index_x = current_point.x + i;
				index_y = current_point.y + j;
				if ( (index_x >= 0) && (index_x < m_image->m_width) && (index_y >= 0) && (index_y < m_image->m_height))
				{
					if (m_edges[x_in][y_in])
					{
						new_point = {.x = index_x, .y = index_y};
						bfs_queue.push(new_point);
					}
				}
			}
		}
	}

	m_graphs.push_back(new_graph);
}

void Object_Detector::Determine_All_Disconected_Graphs()
{
	/* TODO :
	 * 	- Find each disc. graph using BFS
	 * 	- Add each graph to m_graphs
	 * 	- store all applicable graph points & graph size values within graph structure
	 */

	for (int x = 0; x < (m_image->m_width); x++)
	{
		for (int y = 0; y < (m_image->m_height); y++)
		{
			if (m_edges[x][y])
			{
				Determine_Disconected_Graph(x,y);
			}
		}
	}

}

void Object_Detector::Highlight_Largest_Graphs(int num_graphs)
{
	/* TODO :
	 * 	- Sort graphs by size and highlight the num_graphs # of largest graphs
	 * 	- Each disconnected graph should be of different colour (ideally)
	 * 	- The rest of the image will be black
	 */
}

void Object_Detector::Highlight_Largest_Graphs_By_Threshold(int threshold)
{
	/* TODO :
	 * 	- Sort graphs by size and highlight the largest upper threshold % of graphs
	 * 	- Each disconnected graph should be of different colour (ideally)
	 * 	- The rest of the image will be black
	 */
}

