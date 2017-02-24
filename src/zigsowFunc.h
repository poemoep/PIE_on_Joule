#ifndef __ZIGSOWFUNC_H_INCLUDED__
#define __ZIGSOWFUNC_H_INCLUDED__

cv::Rect checkRoi(cv::Mat);
cv::Mat convertMatD2I(cv::Mat);
cv::Mat poissonCalc(cv::Mat,cv::Mat);
cv::Mat synthesis(cv::Mat,cv::Mat,int*);
std::string getTime();
#endif

