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
        Mat dest, dest_dirFilt, dest_gaussFilt;
       
        
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
        
        Mat gauss_kernel = (Mat_<double>(7, 7) << 1., 4., 7., 10., 7., 4., 1.,
                            4., 12., 26., 33., 26., 12., 4.,
                            7., 26., 55., 71., 55., 26., 7.,
                            10., 33., 71., 91., 71., 33., 10.,
                            7., 26., 55., 71., 55., 26., 7.,
                            4., 12., 26., 33., 26., 12., 4.,
                            1., 4., 7., 10., 7., 4., 1.
                            );
        
        gauss_kernel = gauss_kernel/1115;
        
        
        filter2D(img, dest_gaussFilt, img.depth(), gauss_kernel );
        
        
        
        
        imshow("Averaging filter", dest); // Averaging filter
        waitKey();
        
        imshow("Directional Averaging filter", dest_dirFilt);
        waitKey();
        
        imshow("Gaussian filter", dest_gaussFilt);
        waitKey();
        
       
        return 0;
    }
    catch (Exception e)
    {
        std::cout << "Could not read the image in exception\n";
        return -1;
    }
   
}

