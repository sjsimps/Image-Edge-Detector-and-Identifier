#include "image.h"
#include <iostream>
#include <math.h>

int main(int argc, char* argv[])
{
	Image* my_png = new Image();
	my_png->Decode_From_Disk("test.png");

	my_png->Apply_Gauss_Filter3();

	my_png->Encode_From_Disk("testxG3.png");

	std::cout<< "Completed.";

	return 0;
}
