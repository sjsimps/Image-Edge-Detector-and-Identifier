# PNG-Edge-Detection
Decodes PNG files, runs edge detection algorithms over the decoded image, then outputs new PNG(s). Still in progress.

Example output:

1] Initial image
2] Applying Gaussian blur
3] Edge maginitude and direction calculation
4] Edge angle comparison
5] 85% edge magnitude thresholding
6] Edge identification and 10px size thresholding

![alt tag](https://github.com/sjsimps/PNG-Edge-Detection/blob/master/output_flow.png)

Uses LodePNG [lodepng.cpp, lodepng.h] by Lode Vandevenne to complete the PNG image conversion.

