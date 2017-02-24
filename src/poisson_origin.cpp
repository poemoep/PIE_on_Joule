#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#define ERR 5.0
#define Nnum 4
#define LOOP_MAX 1024

int Ns[Nnum][2] = {{-1,0},{0,1},{1,0},{-1,1}};

cv::Mat convertMatD2I(cv::Mat src){
    cv::Mat returnMat = cv::Mat(src.rows,src.cols,CV_8UC1);

    for(int i = 0;i < src.rows; i++){
        for(int j = 0; j < src.cols; j++){
            int pixel = (int) src.at<double>(i,j);
            if(pixel < 0) pixel = 0;
            else if( pixel > 255) pixel = 255;
            returnMat.at<unsigned char>(i,j) = pixel;
        }
    }
    return returnMat;
}


cv::Mat poissonCalc(cv::Mat src,cv::Mat dst){
    
    std::vector<cv::Mat> imgs,src_v,dst_v;
    cv::split(dst,dst_v);
    cv::split(src,src_v);
    cv::Mat returnMat;
    
        int i,j,c,n,loop;
        bool flag;

    for(int chan = 0; chan < 3; chan++){
        flag = false;
        cv::Mat doubleMat = cv::Mat_<double>(dst.rows,dst.cols);

        for(i = 0; i < dst.rows; i ++)
            for(j = 0; j < dst.cols; j++)
                doubleMat.at<double>(i,j) = (double)dst_v[chan].at<unsigned char>(i,j);

        for(loop = 0 ; loop < LOOP_MAX; loop++){
        flag = true;

        for(i = 0; i <  src_v[chan].rows; i++){
            for(j = 0; j < src_v[chan].cols; j++){
                if(src_v[3].at<unsigned char>(i,j) != 0){
                    double sum_f = 0.0;
                    double sum_v = 0.0;
                    int count = 0;
                    
                    for(n = 0; n < Nnum; n++){
                        if( Ns[n][0] + i >= 0 &&
                            Ns[n][1] + j >= 0 &&
                            Ns[n][0] + i < doubleMat.rows &&
                            Ns[n][1] + j < doubleMat.cols){
                                
                            sum_f += doubleMat.at<double>(i + Ns[n][0],j + Ns[n][1]);
                            sum_v += (double)(src_v[chan].at<unsigned char>(i,j) - src_v[chan].at<unsigned char>(i + Ns[n][0],j + Ns[n][1]));
                            count++;
                        }
                        
                        double new_f = (sum_f + sum_v) /(float)count;

                            //std::cout << new_f << "," << sum_f << "," << sum_v << "," << count << std::endl;

                        double err = fabs(new_f - doubleMat.at<double>(i,j));
                        if(flag && err > ERR) flag = false;
                        doubleMat.at<double>(i,j) = new_f;
                        
                    }
                }
            }
        }
        if(flag) break;
        }

        imgs.push_back(convertMatD2I(doubleMat));

    }

    cv::merge(imgs,returnMat);
    return returnMat;
}

/*
int main(int argc,char** argv){
    if(argc < 5){
        std::cout << "Usage: " << argv[0] << " src[has alpha] dst offset_row offset_col" << std::endl;
        return -1;
    }

    cv::Mat src,dst,mask,output;
    src = cv::imread(argv[1],-1);
    dst = cv::imread(argv[2]);
    
    std::cout << "src channels: "<< src.channels() << std::endl;

    int offset[2];
    offset[0] = atoi(argv[3]);
    offset[1] = atoi(argv[4]);

    cv::imshow("src",src);
    cv::imshow("dst",dst);
    cv::waitKey(0);

    output = poissonCalc(src,dst,offset);
    
    cv::imshow("output",output);
    cv::waitKey(0);

    return 0;
}
*/
