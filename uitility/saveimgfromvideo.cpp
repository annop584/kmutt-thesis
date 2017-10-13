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


int main(int argc, const char * argv[]) {

        VideoCapture cap;
        cap.set(CV_CAP_PROP_FOURCC, CV_FOURCC('A', 'V', 'C', '1'));
        cap.open(z/Users/annopkobhiran/Movies/Thesis/Dataset/ideateeth.mov");
        Mat frame;
        int count = 0;
        for (;;)
        {
            // wait for a new frame from camera and store it into 'frame'
            cap.read(frame);
            // check if we succeeded
            if (frame.empty()) {
                cerr << "ERROR! blank frame grabbed\n";
                break;
            }
            count++;
            // show live and wait for a key with timeout long enough to show images
            resize(frame, frame,cv::Size(frame.cols/3, frame.rows/3) , INTER_CUBIC);
    
            imshow("Live", frame);
                std::string saveimg1= "/Users/annopkobhiran/Documents/Xcode/kmutt/testopencv/codes/idealteethstitch/imgs/"+std::to_string(count)+".png";
            if(count%50==0){
                imwrite(saveimg1,frame);
            }
            
    
            if (waitKey(5) >= 0)
                break;
        }

    return 0;
}
