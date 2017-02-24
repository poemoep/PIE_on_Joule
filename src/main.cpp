#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <time.h>

#include "zigsowFunc.h"

#define WIDTH 640
#define HEIGHT 480
#define VERT WIDTH / 10
#define HOLZ HEIGHT / 10

#define LEFT 65361 //left
#define UP 65362 //up
#define RIGHT 65363 // right
#define DOWN 65364 // down
#define BREAK 27 // esc
#define CAPTURE 112 // p

int main(int argc,char** argv){
    
    if(argc < 3){
        std::cout << "Usage: " << argv[0] << " [cameraNum or Video] [alpha image]" << std::endl;
        return 1;
    }
    
    
    bool play = true,capture = false;
    int offset[2],key;
    offset[0] = 0;
    offset[1] = 0;

    std::string now,syn_name,pie_name;
    cv::Mat src,frame,output,pie,pie_result;
    cv::Rect rect; 
    cv::Mat src_roi,frame_roi,pie_roi;

    cv::VideoCapture cap(argv[1]);
    src = cv::imread(argv[2],-1);

    rect = checkRoi(src);

    if(!cap.isOpened()){
        cap.open(atoi(argv[1]));

        if(!cap.isOpened()){
            std::cout << "Open Video File or device Failed." << std::endl;
            return 2;
        }
        
        cap.set(CV_CAP_PROP_FRAME_WIDTH,WIDTH);
        cap.set(CV_CAP_PROP_FRAME_HEIGHT,HEIGHT);
    }


    while(play){
        cap >> frame;
        if(frame.empty()) play = false;

        output = synthesis(src,frame,offset);
        cv::imshow("output",output);
        
        key = cv::waitKey(30);
        switch(key){
            case BREAK:
                play = false;
                break;
            case LEFT:
                offset[1] = (offset[1] - VERT) > 0? offset[1] - VERT: 0;
                break;
            case RIGHT:
                offset[1] = (offset[1] + VERT) < (WIDTH - src.cols)? offset[1] + VERT: WIDTH - src.cols;
                break;
            case UP:
                offset[0] = (offset[0] - HOLZ) > 0? offset[0] - HOLZ: 0;
                break;
            case DOWN:
                offset[0] = (offset[0] + HOLZ) < (HEIGHT - src.rows)? offset[0] + HOLZ: HEIGHT - src.rows;
                break;
            case CAPTURE:
                play = false;
                capture = true;
                break;
            default:
                break;
                
        }
    }

    if(capture){
        
        frame.copyTo(pie);
        frame_roi = frame(cv::Rect(rect.x + offset[1],rect.y  + offset[0],rect.width ,rect.height ));
        pie_roi = pie(cv::Rect(rect.x + offset[1],rect.y  + offset[0],rect.width ,rect.height ));
        src_roi = src(rect);
        
//        cv::imshow("frame_roi",frame_roi);
//        cv::imshow("pie_roi",pie_roi);
//        cv::imshow("src_roi",src_roi);
//        cv::waitKey(0);

        pie_result = poissonCalc(src_roi,frame_roi);
        pie_result.copyTo(pie_roi);
        frame = synthesis(src,frame,offset);
        
        now = getTime();
        syn_name = "./output/" + now + "_synthesis.png";
        pie_name = "./output/" + now + "_pie.png";

        cv::imshow("frame",frame);
        cv::imshow("pie",pie);
        
        cv::imwrite(syn_name,frame);
        cv::imwrite(pie_name,pie);
        cv::waitKey(0);
    }


    return 0;

}

