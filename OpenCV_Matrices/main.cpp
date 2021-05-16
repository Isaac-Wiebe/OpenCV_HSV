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

// docs.opencv.org/4.5.2/d7/d37/tutorial_mat_mask_operations.html tutorial


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
       
        String path = getTruePath("licenseplate_motion.jpg");
        Mat img = imread(path);
        Mat dest, dest_dirFilt;
       
        
        imshow("motion.jpg", img);
        
        
        
        int k = waitKey(0);
        
        
        Mat kernel = (Mat_<double>(3, 3) << 0.111, 0.111,  0.111,
                      0.111,  0.111, 0.111,
                     0.111, 0.111,  0.111);
        
        filter2D(img, dest, img.depth(), kernel);
        
        Mat kernel_dir = (Mat_<double>(3, 3) << 1./16, 1./8, 1./16,
                      1./8, 1./4, 1./8,
                      1./16, 1./8, 1./16);
        
        filter2D(img, dest_dirFilt, img.depth(), kernel_dir);
        
        
        
        
        imshow("Averaging filter", dest); // Averaging filter
        waitKey();
        
        imshow("Directional Averaging filter", dest_dirFilt);
        waitKey();
        
        
       
        return 0;
    }
    catch (Exception e)
    {
        std::cout << "Could not read the image in exception\n";
        return -1;
    }
   
}

