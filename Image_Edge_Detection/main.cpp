
#include <iostream>
#include <math.h>
#include <getopt.h>
#include <string.h>

#include "image.h"
#include "object_detector.h"

static Color channel = monochrome;
static int threshold = 89;
static int edge_length = 89;
static char* file = "test.png";
static char output[256];

static void set_config(int argc, char* argv[])
{
    int option_index;
    static struct option options[] =
    {
        {"help",       no_argument,       0, 'h'},
        {"green",      no_argument,       0, 'g'},
        {"red",        no_argument,       0, 'r'},
        {"blue",       no_argument,       0, 'b'},
        {"file",       required_argument, 0, 'f'},
        {"threshold",  required_argument, 0, 't'},
        {"edge-length",required_argument, 0, 'e'},
        {0, 0, 0, 0}
    };

    while ((option_index = getopt_long(argc, argv, "hrgbf:t:e:", options, NULL)) != -1)
    {
        switch (option_index){
            case 'g':
                channel = green;
                break;
            case 'r':
                channel = red;
                break;
            case 'b':
                channel = blue;
                break;
            case 'f':
                file = optarg;
                break;
            case 't':
                threshold = strtol(optarg, NULL, 10);
                break;
            case 'e':
                edge_length = strtol(optarg, NULL, 10);
                break;
            case 'h':
                std::cout <<"\nUsage: png_edge_detection [options]"
                     <<"\n\t[-f | --file       ] <filename>"
                     <<"\n\t[-t | --threshold  ] <percent>"
                     <<"\n\t[-e | --edge-length] <length>"
                     <<"\n\t[-r | --red  ]"
                     <<"\n\t[-b | --blue ]"
                     <<"\n\t[-g | --green]"
                     <<"\n\t[-h | --help ]";
                exit(EXIT_SUCCESS);
                break;
            default:
                std::cout<< "\nInvalid option. Program exiting.\n";
                exit(EXIT_FAILURE);
                break;
        }
    }
}

static void filename_append(char* file, char* append, char* retval)
{
    int length = strlen(file) + strlen(append) + 1;
    char end[length];
    int state, index;

    strcpy(retval, file);
    for (index = 0; index<length; index++)
    {
        if (retval[index] == '.')
        {
            retval[index] = 0;
            strcpy(end, &retval[index+1]);
            strcat(retval, append);
            strcat(retval, ".");
            strcat(retval, end);
            break;
        }
        else if (!retval[index])
        {
            break;
        }
    }
}

int main(int argc, char* argv[])
{
	Image* my_png = new Image();
	Object_Detector* my_object_detector = new Object_Detector(my_png);

    set_config(argc, argv);

	std::cout<< "Edge detection started.\n";

	bool decoded = my_png->Decode_From_Disk(file);

	if (decoded)
	{
		my_png->Apply_Gauss_Filter5();
        filename_append(file, "_gauss", output);
		my_png->Encode_To_Disk(output);
		std::cout<< "Gauss Filter Applied.\n";

		my_png->Calculate_Differential_Intensity(channel);
        filename_append(file, "_diff", output);
		my_png->Encode_To_Disk(output);
        std::cout<< "Differential Intensity Calculated.\n";

		my_png->Calculate_Angular_Intensity(channel);
        filename_append(file, "_angle", output);
		my_png->Encode_To_Disk(output);
        std::cout<< "Angular Intensity Calculated.\n";

        my_png->Apply_Threshold(threshold);
        filename_append(file, "_threshold", output);
		my_png->Encode_To_Disk(output);
		std::cout<< "Threshold Applied.\n";

		my_object_detector->Initialize();
		my_object_detector->Determine_Edges();
		my_object_detector->Determine_All_Disconected_Graphs();
        filename_append(file, "_disconnected", output);
		my_png->Encode_To_Disk(output);
		std::cout<< "Disconnected Graphs Detected.\n";

        my_object_detector->Highlight_Largest_Graphs(edge_length);
        filename_append(file, "_disconnected_2", output);
		my_png->Encode_To_Disk(output);
		std::cout<< "Disconnected Graphs Thresholded.\n";

		my_png->Discard_Image();

		std::cout<< "RGB edge detection completed.\n";
	}
	else
	{
		std::cout<< "PNG decode failed. Check to make sure the file you wish to decode exists.";
	}

	return 0;
}
