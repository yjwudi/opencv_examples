#include <map>
#include <cstring>
#include <cstdio>
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
    int i, j;
    char name[50]={"/home/yjwudi/tpic/tooth/ground/ground_truth1.png"};
    char namew[50]={"/home/yjwudi/tpic/tooth/patches/white0.png"};
    Mat half_arr[15], white_arr[15];
    //Mat halfImg=imread("/home/yjwudi/tpic/tooth/patches/half.png");
    Mat halfImg = imread("/home/yjwudi/tpic/tooth/ground/ground_truth1.png");
    Mat conImg[3];
    conImg[1]=imread("/home/yjwudi/tpic/tooth/patches/confuse1.png");
    conImg[2]=imread("/home/yjwudi/tpic/tooth/patches/confuse2.png");

    for(i = 1; i <= 10; i++)
    {
        int len = strlen(name);
        name[len-5] = i + '0';
        printf("%s\n", name);
        half_arr[i] = imread(name);
    }


    //为计算直方图配置变量
	//首先是需要计算的图像的通道，就是需要计算图像的哪个通道（bgr空间需要确定计算 b或g或r空间）
	int channels = 0;
	//然后是配置输出的结果存储的空间 ，用MatND类型来存储结果
	MatND halfHist, half_arr_hist[5], con_hist[3], white_hist[15];

	//接下来是直方图的每一个维度的 柱条的数目（就是将数值分组，共有多少组）
	int histSize[] = { 32 };        //如果这里写成int histSize = 32;   那么下面调用计算直方图的函数的时候，该变量需要写 &histSize
	//最后是确定每个维度的取值范围，就是横坐标的总数
	//首先得定义一个变量用来存储 单个维度的 数值的取值范围
	float midRanges[] = { 0, 256 };
	const float *ranges[] = { midRanges };

	calcHist(&halfImg, 1, &channels, Mat(), halfHist, 1, histSize, ranges, true, false);
	for(i = 1; i <= 10; i++)
	{
        calcHist(&half_arr[i], 1, &channels, Mat(), half_arr_hist[i], 1, histSize, ranges, true, false);
        if(i < 3)
        calcHist(&conImg[i], 1, &channels, Mat(), con_hist[i], 1, histSize, ranges, true, false);
	}
	for(i = 0; i < 10; i++)
	{
        calcHist(&white_arr[i], 1, &channels, Mat(), white_hist[i], 1, histSize, ranges, true, false);
	}


    double dist_arr[5], con_dist_arr[3], white_dist_arr[15];
    cout << "half:\n";
    for(i = 1; i <=10 ; i++)
    {
        dist_arr[i] = compareHist(halfHist,half_arr_hist[i],CV_COMP_CORREL);
        cout << dist_arr[i] << endl;
    }
    /*
    cout << "confuse:\n";
    for(i = 1; i < 3; i++)
    {
        con_dist_arr[i] = compareHist(halfHist,con_hist[i],CV_COMP_CORREL);
        cout << con_dist_arr[i] << endl;
    }
    cout << "white:\n";
    for(i = 0; i < 10; i++)
    {
        white_dist_arr[i] = compareHist(halfHist,white_hist[i],CV_COMP_CORREL);
        cout << white_dist_arr[i] << endl;
    }
    */


    return 0;
}
