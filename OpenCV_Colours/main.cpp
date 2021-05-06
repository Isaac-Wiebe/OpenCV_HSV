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

Mat getimg1()
{
    Mat img1(2000, 2000, CV_8UC3, Scalar(0)); // Initialize a matrix of zeros, should be black
    for (int y = 0; y < 2000; y++)
    {
        for (int x = 0; x < 2000; x++)
        {
            img1.at<Vec3b>(y, x)[2] = 255; // Saturated red channel
            img1.at<Vec3b>(y, x)[0] = 255; // Saturated blue       channel
        }
    }
    
    for (int y = 500; y < 1500; y++)
    {
        for (int x = 500; x < 1500; x++)
        {
            img1.at<Vec3b>(x, y)[1] = 255;
            img1.at<Vec3b>(y, x)[0] = 0;
        }
    }
    
    
    return img1;
    
}

Mat getimg2()
{
    Mat img2(2000, 2000, CV_8UC3, Scalar(0));
    
    for (int y = 0; y < img2.rows; y++)
    {
        for (int x = 0; x < img2.cols; x++)
        {
            if (y < 1000)
            {
                img2.at<Vec3b>(y, x)[1] = 255;
            }
            else
            {
                img2.at<Vec3b>(y, x)[0] = 255;
            }
        }
    }
    return img2;
}

Mat getimg3()
{
    Mat img3(2000, 2000, CV_8UC3, Scalar(0));
    for (int y = 0; y < img3.rows; y++)
    {
        for (int x = 0; x < img3.cols; x++)
        {
            if (x < 667)
            {
                img3.at<Vec3b>(y, x)[2] = 255;
                
            }
            else if (x < 1333)
            {
                img3.at<Vec3b>(y, x)[1] = 255;
            }
            else
            {
                img3.at<Vec3b>(y, x)[0] = 255;
            }
        }
    }
    
    return img3;
    
}


int main(int argc, const char * argv[])
{
    const double SCALE_FACTOR = 50.39; // Resolution 12.7 mm, 640 pixels, therefore 50.39 pixels per mm
    const double SAMPLING_FACTOR = 29.29; // 3 x 2000 x 2000 pixels divided by 640 square pixels
    try {
        
        // Image setup
        Mat img1 = getimg1();
        Mat img2 = getimg2();
        Mat img3 = getimg3();
        
    
        // Matrix Setup
        Mat fpersp = Mat::eye(4, 4, CV_32F);
        float focal_length = 4;
        fpersp.at<float>(3, 2) = 1.0/focal_length;
        
        Mat QRP1 = (Mat_<double>(4, 4) << 0.866, 0, -0.5, 0, 0, 1, 0, 0, 0.5, 0, 0.866, 0, 0, 0, 0, 1);
        
        
        Mat QRP2 = (Mat_<double>(4, 4) << .9659, 0, 0.2588, -1830,
                    0, 1, 0, 0,
                    -0.2588, 0, 0.9659, 1460,
                    0, 0, 0, 1);
        
        Mat QRP3 = (Mat_<double>(4, 4) << 0.5, 0, 0.866, 1366,
                    0, 1, 0, 0, -0.866, 0, 0.5, 1334, 0, 0, 0, 1);
        
        Mat picGrid(640, 640, CV_8UC3, Scalar(0));
        
        // Transformed points into the image
        for (int y = 0; y <2000; y++)
        {
            
            for (int x = 0; x < 2000; x++)
            {
                Point3f P(x - 1000, y - 1000, 0);
            }
        }
        

        Mat img1R(img1.rows, img1.cols, CV_8UC3, Scalar::all(0));
        Mat img1G(img1.rows, img1.cols, CV_8UC3, Scalar::all(0));
        Mat img1B(img1.rows, img1.cols, CV_8UC3, Scalar::all(0));
        
        
       // Mat img2(img1); Copies img1 into img2
        
        // Mat D(img1, Rect(200, 200, 100, 100)); Creates a sub image
        if (img1.empty())
        {
            std::cout << "Could not read the image\n";
            return 1;
        }
        
        
       /* int k = waitKey(0); // Wait for a keystroke
        
        if (k == 's')
        {
            imwrite("smarties.png", img1);
        }
        
        
       // int channels = img1.channels();
        
        int nRows = img1.rows;
        int nCols = img1.cols;
        
      //  if (img1.isContinuous())
      //  {
      //      nCols *= nRows;
      //      nRows = 1;
      //  }
        
        int i, j;
        uchar* p;
        uchar table[256];
        for (int k = 0; k < 256; ++k)
        {
            table[k] = (uchar)(k); //
        }
        for(i = 0; i <nRows; ++i)
        {
            p = img1.ptr<uchar>(i);
            for (j = 0; j < nCols; j++)
            {
                Vec3b bgr = img1.at<Vec3b>(i, j);
                // We want to change all red pixels to blue
                if (bgr[2] > 150 && bgr[1] < 100 && bgr[0] < 100)
                {
                    // Identified a red pixel
                    img1.at<Vec3b>(i, j)[0] = 255; // Saturate blue
                    img1.at<Vec3b>(i, j)[1] = 0;
                    img1.at<Vec3b>(i, j)[2] = 0; // Set red and green channels to 0
                }
            }
        }
        imshow("Modified candy", img1);
        k = waitKey(0); // Wait for a keystroke
        
        if (k == 's')
        {
            imwrite("smarties.png", img1);
        } */
        return 0;
    }
    catch (Exception e)
    {
        std::cout << "Could not read the image in exception\n";
    }
   
}
