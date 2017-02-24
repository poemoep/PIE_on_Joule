#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

cv::Rect checkRoi(cv::Mat src){
    
    cv::Rect returnRect;

    int i,j,k;
    int istart = src.rows;
    int iend = 0;
    int jstart = src.cols;
    int jend = 0;

    bool white = false;
    bool firsti = false;
    int fini = 0;
    
    for(i = 0; i < src.rows;i++) for(j = 0;j < src.cols;j++){
        if(src.data[i*src.step + j*src.elemSize() + 3] != 0){
            if(!white){
                if(j < jstart) jstart = j;
                if(!firsti){
                    istart = i;
                    firsti = true;
                }
                white = true;
            }
        }else{
            if(white){
                if(j > jend) jend = j;
                iend = i;
                white = false;
            }
        }
    }

    returnRect.x = jstart;
    returnRect.y = istart;
    returnRect.width = jend - jstart + 1;
    returnRect.height = iend - istart + 1;
    
    return returnRect;
}

/*
int main(int argc,char** argv){
    if(argc < 5) return -1;

    cv::Mat src,dst,src_roi,dst_roi;
    src = cv::imread(argv[1],-1);
    dst = cv::imread(argv[2]);

    int offset[2];
    offset[0] = atoi(argv[3]);
    offset[1] = atoi(argv[4]);

    cv::Rect rect;
    rect = checkRoi(src);

    std::cout << rect.x << "," << rect.y << "\n"
                << rect.width << "," << rect.height << std::endl;

    src_roi = src(rect);
    dst_roi = dst(cv::Rect(rect.x + offset[1],rect.y + offset[0],rect.width ,rect.height));

    cv::imshow("src_roi",src_roi);
    cv::imshow("dst_roi",dst_roi);

    cv::waitKey(0);

    return 0;
}

*/
