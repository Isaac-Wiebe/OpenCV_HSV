//
//  main.cpp
//  OpenCV_AffineTransforms
//
//  Created by Isaac Wiebe on 2021-05-01.
//

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>


// Note to check environment variables type in printenv in the terminal // //
// docs.opencv.org/3.4/d5/d98/tutorial_mat_operations.html -> Tutorial on image Mat components

// docs.opencv.org/master/d6/d6d/tutorial_mat_the_basic_image_container.html

// docs.opencv.org/3.4/d6/dba/group__core__utils__samples.html -> Reference


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
       
        String path = getTruePath("board.jpg");
        Mat img = imread(path);
       
       
        
        
        
        
        

       // Mat img2(img1); Copies img1 into img2
        
        // Mat D(img1, Rect(200, 200, 100, 100)); Creates a sub image at x, y by nxn
       
        return 0;
    }
    catch (Exception e)
    {
        std::cout << "Could not read the image in exception\n";
        return -1;
    }
   
}

