//
//  main.cpp
//  testopencv
//
//  Created by Annop Kobhiran on 8/26/2560 BE.
//  Copyright © 2560 Annop Kobhiran. All rights reserved.
//

#include <iostream>
#import <opencv2/opencv.hpp>
#import <opencv2/stitching.hpp>
#import <opencv2/highgui.hpp>
#import <opencv2/imgcodecs.hpp>
#include <dirent.h>
using namespace cv;
using namespace std;


int main(int argc, const char * argv[]) {
    // set up a virtual camera
    float f = 100, w = 640, h = 480;
    
    cv::Mat1f K = (cv::Mat1f(3, 3) <<
                   f, 0, w/2,
                   0, f, h/2,
                   0, 0,   1);
    
    // set transformation from 1st to 2nd camera (assume K is unchanged)
    cv::Mat1f rvecDeg = (cv::Mat1f(3, 1) << 45, 12, 66);
    cv::Mat1f t = (cv::Mat1f(3, 1) << 100, 200, 300);
    
    std::cout << "-------------------------------------------\n";
    std::cout << "Ground truth:\n";
    
    std::cout << "K = \n" << K << std::endl << std::endl;
    std::cout << "rvec = \n" << rvecDeg << std::endl << std::endl;
    std::cout << "t = \n" << t << std::endl << std::endl;
    
    return 0;
}
