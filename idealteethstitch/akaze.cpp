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

    Mat img_1 = imread( "/Users/annopkobhiran/Documents/Xcode/kmutt/testopencv/codes/idealteethstitch/imgs/19.png", IMREAD_GRAYSCALE );
    Mat img_2 = imread( "/Users/annopkobhiran/Documents/Xcode/kmutt/testopencv/codes/idealteethstitch/imgs/21.png", IMREAD_GRAYSCALE );
    if( !img_1.data || !img_2.data )
    { std::cout<< " --(!) Error reading images " << std::endl; return -1; }
    //-- Step 1: Detect the keypoints using SURF Detector, compute the descriptors
    Ptr<AKAZE> detector = AKAZE::create();
    std::vector<KeyPoint> keypoints_1, keypoints_2;
    Mat descriptors_1, descriptors_2;
    detector->detectAndCompute( img_1, Mat(), keypoints_1, descriptors_1 );
    detector->detectAndCompute( img_2, Mat(), keypoints_2, descriptors_2 );
    //-- Step 2: Matching descriptor vectors using FLANN matcher
    BFMatcher matcher(NORM_HAMMING);
    std::vector< DMatch > matches;
    matcher.match( descriptors_1, descriptors_2, matches );
    double max_dist = 0; double min_dist = 100;
    //-- Quick calculation of max and min distances between keypoints
    for( int i = 0; i < descriptors_1.rows; i++ )
    { double dist = matches[i].distance;
        if( dist < min_dist ) min_dist = dist;
        if( dist > max_dist ) max_dist = dist;
    }
    printf("-- Max dist : %f \n", max_dist );
    printf("-- Min dist : %f \n", min_dist );
    //-- Draw only "good" matches (i.e. whose distance is less than 2*min_dist,
    //-- or a small arbitary value ( 0.02 ) in the event that min_dist is very
    //-- small)
    //-- PS.- radiusMatch can also be used here.
    std::vector< DMatch > good_matches;
    for( int i = 0; i < descriptors_1.rows; i++ )
    { if( matches[i].distance <= max(2*min_dist, 0.02) )
    { good_matches.push_back( matches[i]); }
    }
    //-- Draw only "good" matches
    Mat img_matches;
    drawMatches( img_1, keypoints_1, img_2, keypoints_2,
                good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
                vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
    //-- Show detected matches
    imshow( "Good Matches", img_matches );
    
    std::vector<Point2f> obj;
    std::vector<Point2f> scene;
    
    for( int i = 0; i < good_matches.size(); i++ )
    {
        //-- Get the keypoints from the good matches
        obj.push_back( keypoints_1[ good_matches[i].queryIdx ].pt );
        scene.push_back( keypoints_2[ good_matches[i].trainIdx ].pt );
    }
    
//    vector<char> inliers;
//    Mat H = findHomography( obj, scene ,inliers,RANSAC,1.);
//    Mat result(Size(3*img_1.cols,3*img_1.rows),CV_8UC3);
//    warpPerspective(img_1, result, H, Size(img_1.cols,img_1.rows));
//    imshow( "Warp ", result );
//    Mat half(result,Rect(0,0,img_2.cols,img_2.rows));
//    img_2.copyTo(half);
//    
//    imshow( "half ", result
//           );
//    // set up a virtual camera
//    float f = 1, w = 176, h = 188;
//    
//    cv::Mat1f K = (cv::Mat1f(3, 3) <<
//                   f, 0, w/2,
//                   0, f, h/2,
//                   0, 0,   1);
//    
//    std::vector<cv::Mat> Rs, Ts;
//    decomposeHomographyMat(H,
//                               K,
//                               Rs, Ts,
//                               cv::noArray());
//    
//    std::cout << "-------------------------------------------\n";
//    std::cout << "Estimated decomposition:\n\n";
//    std::cout << "rvec = " << std::endl;
//    for (auto R_ : Rs) {
//        cv::Mat1d rvec;
//        cv::Rodrigues(R_, rvec);
//        std::cout << rvec*180/CV_PI << std::endl << std::endl;
//    }
//    
//    std::cout << std::endl;
//    
//    std::cout << "t = " << std::endl;
//    for (auto t_ : Ts) {
//        std::cout << t_ << std::endl << std::endl;
//    }
    
    for( int i = 0; i < (int)good_matches.size(); i++ )
    { printf( "-- Good Match [%d] Keypoint 1: %d  -- Keypoint 2: %d  \n", i, good_matches[i].queryIdx, good_matches[i].trainIdx ); }
    waitKey(0);
    return 0;
}
/*
 * @function readme
 */
