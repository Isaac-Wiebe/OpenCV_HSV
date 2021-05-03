//
//  main.cpp
//  OpenCV_HelloWorld
//
//  Created by Isaac Wiebe on 2021-05-01.
//

#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <stdio.h>

#include <opencv2/core.hpp>
//#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

// Note to check environment variables type in printenv in the terminal // //
// docs.opencv.org/master/db/deb/tutorial_display_image.html -> Tutorial

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
        Mat img = imread(image_path, IMREAD_COLOR);
        
        
        
        if (img.empty())
        {
            cout << "Could not read the image\n";
            return 1;
        }
        cout << "Success\n";
        imshow("Display window", img);
        int k = waitKey(0); // Wait for a keystroke
        
        if (k == 's')
        {
            
            imwrite("starry_night.png", img);
            
        }
        
        return 0;
        
            
        
    } catch (Exception e) {
        cout << "Could not read the image in exception\n";
    }
   
}
