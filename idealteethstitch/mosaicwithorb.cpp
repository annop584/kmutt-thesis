/*
 * @file SURF_FlannMatcher
 * @brief SURF detector + descriptor + FLANN Matcher
 * @author A. Huaman
 */
#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <iostream>
#import <opencv2/opencv.hpp>
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;


/*
 * @function main
 * @brief Main function
 */
int main( int argc, char** argv )
{
    vector<Mat> imgs;
    Mat img_1 = imread( "/Users/annopkobhiran/Documents/Xcode/kmutt/testopencv/codes/idealteethstitch/imgs/1.png", IMREAD_GRAYSCALE );
    //Mat img_1 = imread( "/Users/annopkobhiran/Movies/Thesis/Dataset/1low/frames/200.png", IMREAD_GRAYSCALE );
    Mat img_2 = imread( "/Users/annopkobhiran/Movies/Thesis/Dataset/1low/frames/210.png", IMREAD_GRAYSCALE );
    Mat I = cv::Mat::eye(3,3,CV_64F);
    Mat result(Size(6*img_1.cols,6*img_1.rows),CV_8UC3);
    for (int i=1; i<=790; i=i+1) {
        std::string imgstr= "/Users/annopkobhiran/Documents/X  code/kmutt/testopencv/codes/idealteethstitch/imgs/"+std::to_string(i)+".png";
        
        Mat img = imread(imgstr,IMREAD_GRAYSCALE);
        imgs.push_back(img);
        if(i==1){
            warpPerspective(imgs[0], result, I, result.size(),cv::INTER_CUBIC + cv::WARP_INVERSE_MAP , cv::BORDER_TRANSPARENT);
        }
        else if(i>=2){
            Mat img_1 = imgs[0].clone();
            Mat img_2 = imgs[1].clone();
    
        }
        
        
    }
    waitKey();
    return 0;
}
/*
 * @function readme
 */


