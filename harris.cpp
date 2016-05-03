#include <opencv2/opencv.hpp>  
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp"  

using namespace cv;  
using namespace std;  

#define WINDOW_NAME1 "【程序窗口1】"        //为窗口标题定义的宏    
#define WINDOW_NAME2 "【程序窗口2】"        //为窗口标题定义的宏    

//-----------------------------------【全局变量声明部分】--------------------------------------  
//      描述：全局变量声明  
//-----------------------------------------------------------------------------------------------  
Mat g_srcImage, g_srcImage1,g_grayImage;  
int thresh = 0; //当前阈值  
int max_thresh = 175; //最大阈值  


int main( int argc, char** argv )  
{  
	Mat normImage;//归一化后的图  
	Mat scaledImage;//线性变换后的八位无符号整型的图

	Mat srcImage = imread("C:\\Users\\my07\\Desktop\\tooth\\first.jpg", 0);    
	namedWindow("原始图", WINDOW_NORMAL);
	imshow("原始图", srcImage);    

	//进行Harris角点检测找出角点  
	Mat cornerStrength;    
	cornerHarris(srcImage, cornerStrength, 2, 3, 0.01);  

	normalize( cornerStrength, normImage, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );  
	convertScaleAbs( normImage, scaledImage );//将归一化后的图线性变换成8位无符号整型

	for( int j = 0; j < normImage.rows ; j++ )  
	{
		for( int i = 0; i < normImage.cols; i++ )  
		{  
			if( (int) normImage.at<float>(j,i) > thresh+80 )  
			{  
				circle( srcImage, Point( i, j ), 5,  Scalar(10,10,255), 2, 8, 0 );  
				circle( scaledImage, Point( i, j ), 5,  Scalar(0,10,255), 2, 8, 0 );  
			}  
		}  
	}

	namedWindow("src", WINDOW_NORMAL);
	imshow("src", srcImage);    

	vector<int> compression_params;
	compression_params.push_back(IMWRITE_JPEG_QUALITY);
	compression_params.push_back(9);
	imwrite("harris.jpg", srcImage, compression_params);
	namedWindow("scale", WINDOW_NORMAL);
	imshow("scale", scaledImage);    


	waitKey(0);  
	return(0);  
}  
