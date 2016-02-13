/*
 * object_detector.cpp
 *
 *  Created on: Aug 16th, 2015
 *      Author: Samuel Simpson
 */

#include "object_detector.h"
#include <iostream>
#include <stdlib.h>


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
	Pixel red_pix, black_pix;
	red_pix = {.r = 0xFF,	.g = 0x00,	.b = 0x00,	.a = 0xFF};
	black_pix = {.r = 0x00,	.g = 0x00,	.b = 0x00,	.a = 0xFF};
	Pixel* index_pix = new Pixel;

	for (int x = 1; x < (m_image->m_width-1); x++)
	{
		for (int y = 1; y < (m_image->m_height-1); y++)
		{
			m_edges[x][y] = Is_Edge(x, y, index_pix);

			if (m_edges[x][y])
			{
				m_image->Set_Pixel(x,y, &red_pix);
			}
		}
	}
    
    for (int x = 1; x < (m_image->m_width-1); x++)
	{
		for (int y = 1; y < (m_image->m_height-1); y++)
		{
			if (!m_edges[x][y])
            {
                m_image->Set_Pixel(x,y, &black_pix);
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

                //Bounds must be set to reduce edges at the border of the image
				if ( (index_x >= 1) && (index_x < (m_image->m_width-1)) && (index_y >= 1) && (index_y < (m_image->m_height)-1))
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

void Object_Detector::Determine_Disconected_Graph(int x_in, int y_in, int blu, int gre)
{
	std::queue<Graph_Point,std::list<Graph_Point> > bfs_queue;
	Graph_Point new_point, current_point;
	Graph new_graph;
	int index_x, index_y;
	Pixel *blue_pix = new Pixel;

	*blue_pix = {.r = 0x00,	.g = gre,	.b = blu,	.a = 0xFF};
	new_graph.size = 0;
	new_point = {.x = x_in, .y = y_in};
	bfs_queue.push(new_point);
	m_edges[x_in][y_in] = false;

	while ( ! bfs_queue.empty() )
	{
		current_point = bfs_queue.front();
		bfs_queue.pop();

		m_image->Set_Pixel(current_point.x, current_point.y, blue_pix);
		new_graph.points.push_back(current_point);
		new_graph.size++;

        for (int i = 0; i < 4; i++)
        {
            switch(i)
            {
                case 0:
                    index_x = -1;
                    index_y = 0;
                    break;
                case 1:
                    index_x = 0;
                    index_y = 1;
                    break;
                case 2:
                    index_x = 0;
                    index_y = -1;
                    break;
                case 3:
                    index_x = 1;
                    index_y = 0;
                    break;
                default:
                    exit(EXIT_FAILURE);
                    break;
            }
            index_x += current_point.x;
            index_y += current_point.y;

            if ( (index_x >= 1) && (index_x < (m_image->m_width-1)) && (index_y >= 1) && (index_y < (m_image->m_height-1)))
            {
                if (m_edges[index_x][index_y])
                {
                    new_point.x = index_x;
                    new_point.y = index_y;
                    bfs_queue.push(new_point);
                    m_edges[index_x][index_y] = false;
                }
            }
        }
	}

	delete blue_pix;

	m_graphs.push_back(new_graph);
}

void Object_Detector::Determine_All_Disconected_Graphs()
{
	/* TODO :
	 * 	- Find each disc. graph using BFS
	 * 	- Add each graph to m_graphs
	 * 	- store all applicable graph points & graph size values within graph structure
	 */

	int blu = 0x255, gre = 0;

	for (int x = 1; x < (m_image->m_width-1); x++)
	{
		for (int y = 1; y < (m_image->m_height-1); y++)
		{
			if (m_edges[x][y])
			{
				blu = (blu - 0x2) % 0xFF;
				gre = (gre + 0x7) % 0xFF;

				Determine_Disconected_Graph(x,y,blu,gre);
			}
            else
            {
            }
		}
	}

}

void Object_Detector::Highlight_Largest_Graphs(int threshold)
{
	/* TODO :
	 * 	- Sort graphs by size and highlight the num_graphs # of largest graphs
	 * 	- Each disconnected graph should be of different colour (ideally)
	 * 	- The rest of the image will be black
	 */

    Pixel *empty_pix = new Pixel;
	*empty_pix = {.r = 0, .g = 0, .b = 0, .a = 0xFF};

    for(std::list<Graph>::iterator iter = m_graphs.begin();
        iter != m_graphs.end();
        iter ++)
    {
        if (iter->size < threshold)
        {
            for(std::list<Graph_Point>::iterator point = iter->points.begin();
                point != iter->points.end();
                point ++)
            {
                m_image->Set_Pixel(point->x, point->y, empty_pix);
            }
        }
    }

    delete empty_pix;
}

void Object_Detector::Highlight_Largest_Graphs_By_Threshold(int threshold)
{
	/* TODO :
	 * 	- Sort graphs by size and highlight the largest upper threshold % of graphs
	 * 	- Each disconnected graph should be of different colour (ideally)
	 * 	- The rest of the image will be black
	 */
}

