#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
using namespace cv;


FILE *fp;
int kase = 0;
Mat img = imread("/home/yjwudi/tpic/tooth/first_gray.jpg");
void get_hist(Mat roi_img);
static void onMouse( int event, int x, int y, int, void* );
int main()
{

    namedWindow("src_img", WINDOW_NORMAL);
    imshow("src_img",img);
    fp = fopen("minus_test.txt", "ab+");

    setMouseCallback("src_img", onMouse, 0);

    waitKey();
    return 0;
}
void get_hist(Mat roi_img)
{
    int channels = 0;
	//然后是配置输出的结果存储的空间 ，用MatND类型来存储结果
	MatND dstHist;
	//接下来是直方图的每一个维度的 柱条的数目（就是将数值分组，共有多少组）
	int histSize[] = { 32 };
	float midRanges[] = { 0, 256 };
	const float *ranges[] = { midRanges };

	calcHist(&roi_img, 1, &channels, Mat(), dstHist, 1, histSize, ranges, true, false);

	//calcHist  函数调用结束后，dstHist变量中将储存了 直方图的信息  用dstHist的模版函数 at<Type>(i)得到第i个柱条的值
	//at<Type>(i, j)得到第i个并且第j个柱条的值

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
		fprintf(fp, "%d%c", value, i==31?'\n':' ');
	}
}
static void onMouse( int event, int x, int y, int, void* )
{
    //cout << x << " " << y << endl;
    switch(event)
    {
        case CV_EVENT_LBUTTONUP:
            //cout << "lbuttonup\n";
            Mat roi_img;
            Rect rect(x-50,y-50,100,100);
            img(rect).copyTo(roi_img);
            get_hist(roi_img);
    }
}












