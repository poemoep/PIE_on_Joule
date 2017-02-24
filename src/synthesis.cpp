#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

cv::Mat synthesis(cv::Mat input_alpha, cv::Mat main,int offset[]){
	
    int i,j,k;
	cv::Mat pic = cv::Mat(main.size(),CV_8UC3);
    main.copyTo(pic);
	
    for(i = 0;i < input_alpha.rows;i++){
		for(j = 0;j < input_alpha.cols;j++){
            if(offset[0] + i >= 0 &&
               offset[0] + i < main.rows &&
               offset[1] + j >= 0 &&
               offset[1] + j < main.cols){
			
                cv::Vec4b px = input_alpha.at<cv::Vec4b>(i,j);
			    if(px[3] == 0){
				    pic.at<cv::Vec3b>(i+offset[0],j+offset[1]) = main.at<cv::Vec3b>(i+offset[0],j+offset[1]);
			    }else{
				    cv::Vec3b m = main.at<cv::Vec3b>(i+offset[0],j+offset[1]);
				    cv::Vec3b p = pic.at<cv::Vec3b>(i+offset[0],j+offset[1]);
				    float alpha = (float)px[3]/255.0;
				    for(k = 0;k < 3;k++) p[k] = (1.0 - alpha) * m[k] + alpha * px[k];
				    pic.at<cv::Vec3b>(i+offset[0],j+offset[1]) = p;
			    }
            }
		}
	}
	


  // 表示
	return pic;
}
/*
int main(int argc,char** argv){

    if(argc < 4) return -1;

    cv::Mat alpha = cv::imread(argv[1], -1);
    cv::Mat frame,output;
    int offset[2];
    offset[0] = atoi(argv[2]);
    offset[1] = atoi(argv[3]);

    cv::VideoCapture cap(0);

//    cap.set(CV_CAP_PROP_FRAME_WIDTH,1920);
//    cap.set(CV_CAP_PROP_FRAME_HEIGHT,1080);
    while(true){
        cap >> frame;
        if(frame.empty()) break;

        output = synthesis(alpha,frame,offset);
        cv::imshow("output",output);
        if(cv::waitKey(30) != -1) break;
    }
    return 0;
}
*/
