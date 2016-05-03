#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>


using namespace cv;
using namespace std;

int main()
{
	//Mat srcImage = imread("C:\\Users\\my07\\Desktop\\tooth\\third.jpg");
	Mat srcImage = imread("/home/yjwudi/tpic/tooth/ground/ground_white.jpg");
	namedWindow("原始图", WINDOW_NORMAL);
	imshow("原始图", srcImage);

	//为计算直方图配置变量
	//首先是需要计算的图像的通道，就是需要计算图像的哪个通道（bgr空间需要确定计算 b或g或r空间）
	int channels = 0;
	//然后是配置输出的结果存储的空间 ，用MatND类型来存储结果
	MatND dstHist;
	//接下来是直方图的每一个维度的 柱条的数目（就是将数值分组，共有多少组）
	int histSize[] = { 32 };        //如果这里写成int histSize = 32;   那么下面调用计算直方图的函数的时候，该变量需要写 &histSize
	//最后是确定每个维度的取值范围，就是横坐标的总数
	//首先得定义一个变量用来存储 单个维度的 数值的取值范围
	float midRanges[] = { 0, 256 };
	const float *ranges[] = { midRanges };

	calcHist(&srcImage, 1, &channels, Mat(), dstHist, 1, histSize, ranges, true, false);

	//calcHist  函数调用结束后，dstHist变量中将储存了 直方图的信息  用dstHist的模版函数 at<Type>(i)得到第i个柱条的值
	//at<Type>(i, j)得到第i个并且第j个柱条的值

	//开始直观的显示直方图——绘制直方图
	//首先先创建一个黑底的图像，为了可以显示彩色，所以该绘制图像是一个8位的3通道图像
	Mat drawImage = Mat::zeros(Size(256, 256), CV_8UC3);
	//因为任何一个图像的某个像素的总个数，都有可能会有很多，会超出所定义的图像的尺寸，针对这种情况，先对个数进行范围的限制
	//先用 minMaxLoc函数来得到计算直方图后的像素的最大个数
	double g_dHistMaxValue;
	minMaxLoc(dstHist, 0, &g_dHistMaxValue, 0, 0);
	//将像素的个数整合到 图像的最大范围内
	//遍历直方图得到的数据
	RNG &rng = theRNG();
	for (int i = 0; i < 32; i++)
	{
		int value = cvRound(dstHist.at<float>(i) * 256 * 0.9 / g_dHistMaxValue);
		cout << value << endl;

		//对角线上的两个点
		rectangle(drawImage, Point(i * 8, drawImage.rows - 1), Point(i * 8 + 256 / 32, drawImage.rows - 1 - value)
			, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), -1);
	}

	imshow("【直方图】", drawImage);
	vector<int> compression_params;
	compression_params.push_back(IMWRITE_JPEG_QUALITY);
	compression_params.push_back(9);
	//imwrite("C:\\Users\\my07\\Desktop\\tooth\\white_hist.jpg", drawImage, compression_params);
	//imwrite("/home/yjwudi/tpic/tooth/ground/ground_truth2_hist.jpg", drawImage, compression_params);

	waitKey(0);

	return 0;
}
