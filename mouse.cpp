#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
using namespace cv;


int kase = 0;
Mat img = imread("/home/yjwudi/tpic/tooth/first.jpg");
char tmp_name[50] =  {"/home/yjwudi/tpic/tooth/ground/ground_truth0.jpg"};
char red_name[50] =  {"/home/yjwudi/tpic/tooth/ground/ground_red0.jpg"};
char white_name[50] =  {"/home/yjwudi/tpic/tooth/ground/ground_white0.jpg"};
static void onMouse( int event, int x, int y, int, void* );
int main()
{

    namedWindow("src_img", WINDOW_NORMAL);
    imshow("src_img",img);

    setMouseCallback("src_img", onMouse, 0);

    waitKey();
    return 0;
}
static void onMouse( int event, int x, int y, int, void* )
{
    //x就是横向的width，y就是纵向的height
    //cout << x << " " << y << endl;
    switch(event)
    {
        case CV_EVENT_LBUTTONUP:
            cout << "lbuttonup\n";
            Mat roi_img, src_img;
            //src_img = imread("/home/yjwudi/tpic/tooth/first.jpg");
            Rect rect(x-100,y-100,200,200);
            img(rect).copyTo(roi_img);
            vector<int> compression_params;
            compression_params.push_back(IMWRITE_JPEG_QUALITY);
            compression_params.push_back(9);

            int len = strlen(white_name);
            white_name[len-5] = kase++ + '0';
            //imwrite(tmp_name, roi_img, compression_params);
            imwrite(white_name, roi_img, compression_params);
            //imwrite("/home/yjwudi/tpic/tooth/ground/confuse.jpg", roi_img, compression_params);
            /*
            namedWindow("roi_img", WINDOW_NORMAL);
            imshow("roi_img",roi_img);
            waitKey(0);
            */
    }
}












