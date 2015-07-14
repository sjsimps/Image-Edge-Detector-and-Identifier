# PNG-Edge-Detection
Decodes PNG files, runs edge detection algorithms over the decoded image, then outputs new PNG(s). Still in progress.

Example output:
Initial image:
![alt tag](https://github.com/sjsimps/PNG-Edge-Detection/blob/master/Image_Edge_Detection/test.png)

After gaussian blur has been applied:
![alt tag](https://github.com/sjsimps/PNG-Edge-Detection/blob/master/Image_Edge_Detection/testxGauss5.png)

After red channel edge detection:
![alt tag](https://github.com/sjsimps/PNG-Edge-Detection/blob/master/Image_Edge_Detection/testxR.png)

Todo: add edge angle intensity calculation to improve edge detection

Uses LodePNG [lodepng.cpp, lodepng.h] by Lode Vandevenne to complete the PNG image conversion.


