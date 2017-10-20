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
    
    Mat img_1 = imread( "/Users/annopkobhiran/Movies/Thesis/Dataset/1/frames-4/1.png", IMREAD_GRAYSCALE );
//    Mat img_1 = imread( "/Users/annopkobhiran/Documents/Xcode/kmutt/testopencv/codes/idealteethstitch/imgs/1.png", IMREAD_GRAYSCALE );
    //Mat img_1 = imread( "/Users/annopkobhiran/Movies/Thesis/Dataset/1low/frames/200.png", IMREAD_GRAYSCALE );
    Mat img_2 = imread( "/Users/annopkobhiran/Movies/Thesis/Dataset/1/frames-4/2.png", IMREAD_GRAYSCALE );
    Mat I = cv::Mat::eye(3,3,CV_64F);
    Mat result(Size(6*img_1.cols,6*img_1.rows),CV_8UC3);
    for (int i=1; i<=790; i=i+20) {
//        std::string imgstr= "/Users/annopkobhiran/Documents/Xcode/kmutt/testopencv/codes/idealteethstitch/imgs/"+std::to_string(i)+".png";
          std::string imgstr= "/Users/annopkobhiran/Movies/Thesis/Dataset/1/frames-4/"+std::to_string(i)+".png";

        Mat img = imread(imgstr,IMREAD_GRAYSCALE);
        imgs.push_back(img);
        if(i==21){
            warpPerspective(imgs[0], result, I, result.size(),cv::INTER_CUBIC + cv::WARP_INVERSE_MAP , cv::BORDER_TRANSPARENT);
//            warpAffine(imgs[0], result, I, result.size());
        }
        else if(i>=2){
            Mat img_1 = imgs[0].clone();
            Mat img_2 = imgs[1].clone();

            Ptr<ORB> detector = ORB::create();
            std::vector<KeyPoint> keypoints_1, keypoints_2;
            Mat descriptors_1, descriptors_2;
            detector->detectAndCompute( img_1, Mat(), keypoints_1, descriptors_1 );
            detector->detectAndCompute( img_2, Mat(), keypoints_2, descriptors_2 );
            //-- Step 2: Matching descriptor vectors using FLANN matcher
            BFMatcher matcher(NORM_HAMMING);
            std::vector< DMatch > matches,matches21;
            matcher.match( descriptors_1, descriptors_2, matches );
            matcher.match( descriptors_2, descriptors_1, matches21 );
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
//                                    for( int i = 0; i < descriptors_1.rows; i++ )
//                                    {
//                                        if( matches[i].distance <= 3*min_dist )
//                                        { good_matches.push_back( matches[i]); }
//                                    }
                        for( int i = 0; i < descriptors_1.rows; i++ )
                        {
                            DMatch forward = matches[i];
                            DMatch backward = matches21[forward.trainIdx];
                            if( backward.trainIdx == forward.queryIdx )
                                good_matches.push_back( forward );
                        }
            
//            for( int i = 0; i < descriptors_1.rows; i++ )
//            {
//                good_matches.push_back( matches[i] );
//            }
            //-- Draw only "good" matches
            Mat img_matches;
            drawMatches( img_1, keypoints_1, img_2, keypoints_2,
                        good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
                        vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
            //-- Show detected matches
            imshow( "Good Matches", img_matches );
            
//            waitKey();
            
            if(good_matches.size()<=4){
                cout<<"sizeeee "<<good_matches.size()<<endl;
                Mat imgtemp = img_1.clone();
                imgs.clear();
                imgs.push_back(imgtemp);
            }
            else{
                std::vector<Point2f> obj;
                std::vector<Point2f> scene;
                
                for( int i = 0; i < good_matches.size(); i++ )
                {
                    //-- Get the keypoints from the good matches
                    obj.push_back( keypoints_1[ good_matches[i].queryIdx ].pt );
                    scene.push_back( keypoints_2[ good_matches[i].trainIdx ].pt );
                }
                
                vector<char> inliers;
//                Mat H = findHomography( obj, scene ,inliers,RANSAC,2);
                Mat R = estimateRigidTransform(obj, scene, 0);
                Mat H = cv::Mat(3,3,R.type());
                H.at<double>(0,0) = R.at<double>(0,0);
                H.at<double>(0,1) = R.at<double>(0,1);
                H.at<double>(0,2) = R.at<double>(0,2);

                H.at<double>(1,0) = R.at<double>(1,0);
                H.at<double>(1,1) = R.at<double>(1,1);
                H.at<double>(1,2) = R.at<double>(1,2);

                H.at<double>(2,0) = 0.0;
                H.at<double>(2,1) = 0.0;
                H.at<double>(2,2) = 1.0;
                cout << "INDEX = "<< endl << i << endl << endl;
                cout << "H = "<< endl << " "  << H << endl << endl;
                I=H*I;
                cout << "I = "<< endl << " "  << I << endl << endl;
                warpPerspective(imgs[1], result, I, result.size(),cv::INTER_CUBIC + cv::WARP_INVERSE_MAP , cv::BORDER_TRANSPARENT);
                
                
                imshow( "Warp", result );
                waitKey(0);
                imgs.clear();
                imgs.push_back(img_2);
            }
            
        }
        
        
    }
    waitKey();
    return 0;
}
/*
 * @function readme
 */



