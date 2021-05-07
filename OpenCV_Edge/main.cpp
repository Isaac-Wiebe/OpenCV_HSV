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
// docs.opencv.org/master/d2/d2c/tutorial_sobel_derivatives.html -> Tutorial on Sobel Edge Detection


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
        Mat sobel_img, laplace_img, laplace_gray, abs_laplace_img;
       
       
        
        imshow("circuit board.jpg", img);
        
        int k = waitKey(0);
        
        cvtColor(img, sobel_img, COLOR_BGR2GRAY); // Generates grayscale image
        cvtColor(img, laplace_gray, COLOR_BGR2GRAY);
        
       
        
        Mat grad_x, grad_y;
        Mat abs_grad_x, abs_grad_y;
        
        Sobel(sobel_img, grad_x, CV_16S, 1, 0, 1, 1, 0.01, BORDER_DEFAULT);
        
        Sobel(sobel_img, grad_y, CV_16S, 1, 0, 1, 1, 0.01, BORDER_DEFAULT);
        
        Laplacian(laplace_gray, laplace_img, CV_16S, 3, 1, 0, BORDER_DEFAULT);
        convertScaleAbs(laplace_img, abs_laplace_img);

        // converting back to CV_8U
        convertScaleAbs(grad_x, abs_grad_x);
        convertScaleAbs(grad_y, abs_grad_y);
        addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, sobel_img);
        
        imshow("Sobel edge detection", sobel_img);
        k = waitKey(0);
        
        imshow("Laplacian Edge Detection", abs_laplace_img);
        k = waitKey(0);
        
        

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

