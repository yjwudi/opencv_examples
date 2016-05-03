#include <map>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    Mat redImg=imread("/home/yjwudi/tpic/tooth/patches/red.png");
    Mat whiteImg=imread("/home/yjwudi/tpic/tooth/patches/white.png");
    Mat mred=imread("/home/yjwudi/tpic/tooth/patches/mred.png");
    Mat mwhite=imread("/home/yjwudi/tpic/tooth/patches/mwhite.png");
    Mat half=imread("/home/yjwudi/tpic/tooth/patches/half.png");

    //为计算直方图配置变量
	//首先是需要计算的图像的通道，就是需要计算图像的哪个通道（bgr空间需要确定计算 b或g或r空间）
	int channels = 0;
	//然后是配置输出的结果存储的空间 ，用MatND类型来存储结果
	MatND redHist, whiteHist, halfHist, mwhiteHist, mredHist;
	//接下来是直方图的每一个维度的 柱条的数目（就是将数值分组，共有多少组）
	int histSize[] = { 32 };        //如果这里写成int histSize = 32;   那么下面调用计算直方图的函数的时候，该变量需要写 &histSize
	//最后是确定每个维度的取值范围，就是横坐标的总数
	//首先得定义一个变量用来存储 单个维度的 数值的取值范围
	float midRanges[] = { 0, 256 };
	const float *ranges[] = { midRanges };

	calcHist(&redImg, 1, &channels, Mat(), redHist, 1, histSize, ranges, true, false);
	calcHist(&whiteImg, 1, &channels, Mat(), whiteHist, 1, histSize, ranges, true, false);
	calcHist(&half, 1, &channels, Mat(), halfHist, 1, histSize, ranges, true, false);
	calcHist(&mwhite, 1, &channels, Mat(), mwhiteHist, 1, histSize, ranges, true, false);
	calcHist(&mred, 1, &channels, Mat(), mredHist, 1, histSize, ranges, true, false);


    double dist1,dist2,dist3, dist4, dist5, dist6, dist7;
    dist1=compareHist(redHist,whiteHist,CV_COMP_CORREL);
    dist2=compareHist(redHist,halfHist,CV_COMP_CORREL);
    dist3=compareHist(whiteHist,halfHist,CV_COMP_CORREL);
    dist4=compareHist(mwhiteHist,halfHist,CV_COMP_CORREL);
    dist5=compareHist(mredHist,halfHist,CV_COMP_CORREL);
    dist6=compareHist(mwhiteHist,whiteHist,CV_COMP_CORREL);
    dist7=compareHist(mredHist,whiteHist,CV_COMP_CORREL);

    cout << "红与白的距离: " << dist1 << endl;
    cout << "红与半的距离: " << dist2 << endl;
    cout << "白与半的距离: " << dist3 << endl;
    cout << "半与大部分白的距离: " << dist4 << endl;
    cout << "半与大部分红的距离: " << dist5 << endl;
    cout << "白与大部分白的距离: " << dist6 << endl;
    cout << "白与大部分红的距离: " << dist7 << endl;

    return 0;
}
