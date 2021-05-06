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

const double SCALE_FACTOR = 50.39; // Resolution 12.7 mm, 640 pixels, therefore 50.39 pixels per mm
const double SAMPLING_FACTOR = 29.29; // 3 x 2000 x 2000 pixels divided by 640 square pixels


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
    int nRows = img1.rows;
    int nCols = img1.cols;
    for (int y = 0; y < nRows; y++)
    {
        for (int x = 0; x < nCols; x++)
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
    
    int nRows = img2.rows;
    int nCols = img2.cols;
    for (int y = 0; y < nRows; y++)
    {
        for (int x = 0; x < nCols; x++)
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
    int nRows = img3.rows;
    int nCols = img3.cols;
    for (int y = 0; y < nRows; y++)
    {
        for (int x = 0; x < nCols; x++)
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

void addImage(Mat *picGrid, Mat img, Mat fpersp, Mat QRP1)
{
    for (int y = 0; y <2000; y++)
    {
        for (int x = 0; x < 2000; x++)
        {
        
        
            Mat P = (Mat_<double>(4, 1) <<x - 1000, y - 1000, 0, 1);
            
            Mat temp = fpersp * QRP1;
            temp = temp * P;
            
            double w = temp.at<double>(3);
    
            temp.at<double>(0) = temp.at<double>(0) / w;
            temp.at<double>(1) = temp.at<double>(1) / w;
            temp.at<double>(2) = 0;
            
            
            double xCord = temp.at<double>(0);
            double yCord = temp.at<double>(1);
            if (round(xCord * SCALE_FACTOR) + 640/2 > 0 && round(yCord * SCALE_FACTOR) + 640/2 > 0 && round(xCord * SCALE_FACTOR) + 640/2 < 640 && round(yCord * SCALE_FACTOR) + 640/2 < 640)
            {
            
                Vec3b RGB = img.at<Vec3b>(y, x);
                picGrid->at<Vec3b>(round(yCord * SCALE_FACTOR) + 640/2, round(xCord * SCALE_FACTOR) +640/2)[0] = RGB[0];
                
                picGrid->at<Vec3b>(round(yCord * SCALE_FACTOR) + 640/2, round(xCord * SCALE_FACTOR) +640/2)[1] = RGB[1];
                picGrid->at<Vec3b>(round(yCord * SCALE_FACTOR) + 640/2, round(xCord * SCALE_FACTOR) +640/2)[2] = RGB[2];
            }
            
            
        }
        
    }
    
}

int main(int argc, const char * argv[])
{
    try {
        
        // Image setup
        Mat img1 = getimg1();
        Mat img2 = getimg2();
        Mat img3 = getimg3();
        
        // Matrix Setup
        float focal_length = 4;

        Mat fpersp = (Mat_<double>(4, 4) << 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1/focal_length, 1);
        Mat QRP1 = (Mat_<double>(4, 4) << 0.866, 0, -0.5, 0, 0, 1, 0, 0, 0.5, 0, 0.866, 1700, 0, 0, 0, 1);
        
        
        Mat QRP2 = (Mat_<double>(4, 4) << .9659, 0, 0.2588, -1830,
                    0, 1, 0, 0,
                    -0.2588, 0, 0.9659, 1460,
                    0, 0, 0, 1);
        
        Mat QRP3 = (Mat_<double>(4, 4) << 0.5, 0, 0.866, 1366,
                    0, 1, 0, 0, -0.866, 0, 0.5, 1334, 0, 0, 0, 1);
        
        Mat picGrid(640, 640, CV_8UC3, Scalar(0));
        
        addImage(&picGrid, img1, fpersp, QRP1);
        addImage(&picGrid, img2, fpersp, QRP2);
        addImage(&picGrid, img3, fpersp, QRP3);
        // Transformed points into the image
    
        
        
        imshow("Display image", picGrid);
        int k = waitKey(0);
        

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

