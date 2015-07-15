#include "image.h"
#include <iostream>
#include <math.h>

int main(int argc, char* argv[])
{
	Color channel = blue;
	char* file = "test.png";

	std::cout<< "Edge detection started.\n";

	Image* my_png = new Image();

	bool decoded = my_png->Decode_From_Disk(file);

	if (decoded)
	{
		my_png->Apply_Gauss_Filter5();

		my_png->Encode_From_Disk("testxGauss5.png");

		std::cout<< "Gauss Filter Applied.\n";

		my_png->Calculate_Differential_Intensity(channel);

		my_png->Encode_From_Disk("testxG5.png");

		my_png->Calculate_Angular_Intensity(channel);

		my_png->Encode_From_Disk("testxAG5.png");


		std::cout<< "RGB edge detection completed.\n";
	}
	else
	{
		std::cout<< "PNG decode failed. Check to make sure the file you wish to decode exists.";
	}
	return 0;
}
