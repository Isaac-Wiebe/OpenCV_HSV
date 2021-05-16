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

// These images must be the exact same dimensions for this to work


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
       
        String path = getTruePath("aloeL.jpg");
        Mat img1 = imread(path);
        
        path = getTruePath("aloeR.jpg");
        Mat img2 = imread(path);
        
        float alpha = 0.5;
        float beta = 1-alpha;
        
        Mat combined;
        
        addWeighted(img1, alpha, img2, beta, 0.0, combined);
        
        imshow("Combined imgs", combined);
        
        waitKey();
        
        

       
        return 0;
    }
    catch (Exception e)
    {
        std::cout << "Could not read the image in exception\n";
        return -1;
    }
   
}

