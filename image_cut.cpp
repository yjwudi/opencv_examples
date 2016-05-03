#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <vector>
using namespace std;
using namespace cv;


//剪切图片为m * n 块
void Cut_img(Mat src_img,int m,int n,vector<Mat> ceil_img){

    int t = m * n;
    int height = src_img.rows;
    int width  = src_img.cols;
    cout << "rows: " << src_img.rows << endl;
    cout << "cols: " << src_img.cols << endl;

    int ceil_height = height/m;
    int ceil_width  = width/n;

    Mat roi_img,tmp_img;

    Point p1,p2;
    for(int i = 0;i<m;i++)
        for(int j = 0;j<n;j++){
            //rect(x, y, width, height)
            //x是横向的左边，y是纵向的坐标
            Rect rect(j*ceil_width,i*ceil_height,ceil_width,ceil_height);

            src_img(rect).copyTo(roi_img);

            ceil_img.push_back(roi_img);
            namedWindow("roi_img", WINDOW_NORMAL);
            imshow("roi_img",roi_img);
            //getchar();
            waitKey(0);
        //rectangle(i+j*ceil_width,j+i*ceil_height,);
        }
}
int main()
{
    Mat img = imread("/home/yjwudi/tpic/tooth/first.jpg");
    Mat img2 = imread("/home/yjwudi/tpic/tooth/patches/half.png");
    cout << img2.rows << " " << img2.cols << endl;
    namedWindow("src img", WINDOW_NORMAL);
    imshow("src img",img);
    int m = 3;
    int n = 3;
    vector<Mat> ceil_img;

    Cut_img(img,m,n,ceil_img);

    waitKey();
    return 0;
}
