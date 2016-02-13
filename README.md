##PNG Edge Detection Tool
Determines and identifies all prominent edges within a PNG image.

###Example output:




![alt tag](https://github.com/sjsimps/PNG-Edge-Detection/blob/master/output_flow.png)

###Processing Steps:

  1] Initial image
  
  2] Applying Gaussian blur
  
  3] Edge maginitude and direction calculation
  
  4] Edge angle comparison
  
  5] 82% edge magnitude thresholding
  
  6] Edge identification and 25px edge length thresholding

###Sources Used:

Uses LodePNG [lodepng.cpp, lodepng.h] by Lode Vandevenne to complete the PNG image conversion.

