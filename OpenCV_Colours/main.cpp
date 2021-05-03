//
//  main.cpp
//  OpenCV_HelloWorld
//
//  Created by Isaac Wiebe on 2021-05-01.
//

#include <iostream>


#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

// Note to check environment variables type in printenv in the terminal // //
// docs.opencv.org/3.4/d5/d98/tutorial_mat_operations.html -> Tutorial

// docs.opencv.org/3.4/d6/dba/group__core__utils__samples.html -> Reference


using namespace cv;
using namespace std;



String getTruePath(string path)
{
    string base_path = "samples/data/";
    return base_path + path;
    
}

int main(int argc, const char * argv[]) {
    
    try {
        
        //string image_path = samples::findFile("aloeL.jpg", false, false); Does not work
       
        string image_path = getTruePath("smarties.png");
        
        Mat img1, img2;
        img1 = imread(image_path, IMREAD_COLOR);
       // Mat img2(img1); Copies img1 into img2
        
        // Mat D(img1, Rect(200, 200, 100, 100)); Creates a sub image
        if (img1.empty())
        {
            cout << "Could not read the image\n";
            return 1;
        }
        imshow("Display window", img1);
        int k = waitKey(0); // Wait for a keystroke
        
        if (k == 's')
        {
            imwrite("smarties.png", img1);
        }
        
        
        for(int j = 0;j < img1.rows;j++)
        {
            for(int i = 0;i < img1.cols;i++)
            {
                Vec3f intensity = img1.at<Vec3f>(j, i);
                float blue = intensity.val[0];
                float green = intensity.val[1];
                float red = intensity.val[2];
                
                if (red > 200) {
                    red = 0;
                    blue = 255;
                }
                
                
               
            }
        }
        
      
        

        return 0;
        
            
        
    }
        catch (Exception e) {
        cout << "Could not read the image in exception\n";
    }
   
    }
