//
//  main.cpp
//  OpenCV_Blending
//
//  Created by Isaac Wiebe on 2021-05-01.
//

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

// docs.opencv.org/4.5.2/d5/dc4/tutorial_adding_images.html tutorial


using namespace cv;


String getTruePath(String path)
{
    std::string base_path = "samples/data/";
    return base_path + path;
}


int main(int argc, const char * argv[])
{
    try {
        
        // Image setup
       
        String path = getTruePath("lena.jpg");
        Mat img1 = imread(path);
        
        path = getTruePath("opencv-logo-white.png");
        Mat img2 = imread(path);
        
        

       
        return 0;
    }
    catch (Exception e)
    {
        std::cout << "Could not read the image in exception\n";
        return -1;
    }
   
}

