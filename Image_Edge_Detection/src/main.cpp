#include "image.h"
#include "cycle_detector.h"
#include <iostream>
#include <math.h>

int main(int argc, char* argv[])
{
	Color channel = green;
	char* file = "test.png";
	Image* my_png = new Image();
	Cycle_Detector* my_cycle_detector = new Cycle_Detector(my_png);

	std::cout<< "Edge detection started.\n";

	bool decoded = my_png->Decode_From_Disk(file);

	if (decoded)
	{
		my_png->Apply_Gauss_Filter5();

		my_png->Encode_To_Disk("testxGauss5.png");

		std::cout<< "Gauss Filter Applied.\n";

		my_png->Calculate_Differential_Intensity(channel);

		my_png->Encode_To_Disk("testxB5.png");

		my_png->Calculate_Angular_Intensity(channel);

		my_png->Apply_Threshold(89);

		my_png->Encode_To_Disk("threshold.png");

		my_cycle_detector->Initialize();
		my_cycle_detector->Determine_Edges();

		my_png->Encode_To_Disk("edges.png");

		my_png->Discard_Image();

		std::cout<< "RGB edge detection completed.\n";
	}
	else
	{
		std::cout<< "PNG decode failed. Check to make sure the file you wish to decode exists.";
	}

	return 0;
}
