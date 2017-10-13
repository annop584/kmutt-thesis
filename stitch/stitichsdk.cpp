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
using namespace cv;
using namespace std;

Mat rotate(Mat src, double angle)
{
    Mat dst;
    Point2f pt(src.cols/2., src.rows/2.);
    Mat r = getRotationMatrix2D(pt, angle, 1.0);
    warpAffine(src, dst, r, Size(src.cols, src.rows));
    return dst;
}


int main(int argc, const char * argv[]) {
//     insert code here...
    vector<Mat> imgs;
//    vector<Mat> imgss;
    Mat imgss = imread("/Users/annopkobhiran/Movies/Thesis/Dataset/1light2/frames/1.png");
    Mat scan = Mat::zeros(cv::Size(imgss.cols, imgss.rows),CV_8UC3);
    Mat pano;
    for (int i=1; i<=790; i=i+20) {
        
//        std::string img= "/Users/annopkobhiran/Pictures/teehorder2/"+std::to_string(i)+".jpg";
        std::string imgstr= "/Users/annopkobhiran/Movies/Thesis/Dataset/1light2/frames/"+std::to_string(i)+".png";
        
        std::string imgsave= "/Users/annopkobhiran/Movies/Thesis/Dataset/1light2/scans/"+std::to_string(i)+".png";
//        std::string imgsave2= "/Users/annopkobhiran/Movies/Thesis/Dataset/1test2/pano/"+std::to_string(i)+".png";
//            imshow( "Display window", img );
        Mat img = imread(imgstr);
        Mat zero = Mat::zeros(cv::Size(scan.cols, scan.rows),CV_8UC3);
        Mat zero_roi = zero(Rect(0, 0, img.cols, img.rows));
//        img.copyTo(zero_roi);
        
//        imgs.push_back(zero);
        imgs.push_back(img);
        

        
        Ptr<Stitcher> stitcher = Stitcher::create(Stitcher::SCANS, true);
        Stitcher::Status status = stitcher->stitch(imgs, scan);
        imwrite(imgsave,scan);
//        imshow( "ZERO", zero );
//        imshow( "IMG", img );
//        imshow( "SXAN", scan );
//        waitKey(0);
//    
//        if(i>=41){
//            std::string scanimg= "/Users/annopkobhiran/Movies/Thesis/Dataset/1test/scan/"+std::to_string(i)+".png";
//            //            imshow( "Display
////                    imshow("Livescan", scan);
////                    imshow("Live", imgs[1]);
//            
//        imgs.clear();
//        imgs.push_back(imread(scanimg));
//        }
//        Ptr<Stitcher> stitcher2 = Stitcher::create(Stitcher::PANORAMA, true);
//        Stitcher::Status status2 = stitcher2->stitch(imgs, pano);
//        imwrite(imgsave2,pano);
    }
    

//    VideoCapture cap;
//    cap.set(CV_CAP_PROP_FOURCC, CV_FOURCC('A', 'V', 'C', '1'));
//    cap.open("/Users/annopkobhiran/Movies/Thesis/Dataset/1light2/teeth.m4v");
//    Mat frame;
//    int count = 0;
//    for (;;)
//    {
//        // wait for a new frame from camera and store it into 'frame'
//        cap.read(frame);
//        // check if we succeeded
//        if (frame.empty()) {
//            cerr << "ERROR! blank frame grabbed\n";
//            break;
//        }
//        count++;
//        // show live and wait for a key with timeout long enough to show images
//        resize(frame, frame,cv::Size(frame.cols/3, frame.rows/3) , INTER_CUBIC);
//        
//        imshow("Live", frame);
//            std::string saveimg1= "/Users/annopkobhiran/Movies/Thesis/Dataset/1light2/frames/"+std::to_string(count)+".png";
//        
//        imwrite(saveimg1,frame);
//
//        if (waitKey(5) >= 0)
//            break;
//    }
    
    
    
    
    
    
//    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
//    imshow( "Display window", pano );                   // Show our image inside it.
    
    waitKey(0);
    return 0;
}
