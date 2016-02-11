# PNG-Edge-Detection
Decodes PNG files, runs edge detection algorithms over the decoded image, then outputs new PNG(s). Still in progress.

Example output:

Initial image:

![alt tag](https://github.com/sjsimps/PNG-Edge-Detection/blob/master/Image_Edge_Detection/test.png)

After gaussian blur has been applied:

![alt tag](https://github.com/sjsimps/PNG-Edge-Detection/blob/master/Image_Edge_Detection/test_gauss.png)

After edge detection:

![alt tag](https://github.com/sjsimps/PNG-Edge-Detection/blob/master/Image_Edge_Detection/test_diff.png)

After edge angle comparison:

![alt tag](https://github.com/sjsimps/PNG-Edge-Detection/blob/master/Image_Edge_Detection/test_angle.png)

After 85% edge magnitude thresholding:

![alt tag](https://github.com/sjsimps/PNG-Edge-Detection/blob/master/Image_Edge_Detection/test_threshold.png)

After edge identification and 10px size thresholding:

![alt tag](https://github.com/sjsimps/PNG-Edge-Detection/blob/master/Image_Edge_Detection/test_disconnected_2.png)

Uses LodePNG [lodepng.cpp, lodepng.h] by Lode Vandevenne to complete the PNG image conversion.

