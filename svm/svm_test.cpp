#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/ml.hpp>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
using namespace cv;
using namespace cv::ml;



FILE *fp1, *fp2, *fp3, *fp4, *fp5, *fp6;
float trainingData[1600][32];
int labels[1600];
float testData[32];
int main(int, char**)
{
    // Set up training data
    int row_number = 0, i = 0, j = 0;
    fp1 = fopen("/home/yjwudi/cv_code/plus_sam.txt", "r");
    fp2 = fopen("/home/yjwudi/cv_code/minus_sam.txt", "r");
    fp3 = fopen("/home/yjwudi/cv_code/plus_sam.txt", "r");
    fp4 = fopen("/home/yjwudi/cv_code/minus_test.txt", "r");
    fp5 = fopen("/home/yjwudi/cv_code/plus_res.txt", "w");
    fp6 = fopen("/home/yjwudi/cv_code/minus_res.txt", "w");

    while(fscanf(fp1, "%f", &trainingData[row_number][0]) != EOF)
    {
        for(i = 1; i < 32; i++)
            fscanf(fp1, "%f", &trainingData[row_number][i]);
        labels[row_number] = 1;
        row_number++;
    }
    while(fscanf(fp2, "%f", &trainingData[row_number][0]) != EOF)
    {
        for(i = 1; i < 32; i++)
            fscanf(fp2, "%f", &trainingData[row_number][i]);
        labels[row_number] = -1;
        row_number++;
    }
    //cout << row_number << endl;
    Mat trainingDataMat(row_number, 32, CV_32FC1, trainingData);
    Mat labelsMat(row_number, 1, CV_32S, labels);
    // Train the SVM
    Ptr<SVM> svm = SVM::create();
    svm->setType(SVM::C_SVC);
    svm->setKernel(SVM::LINEAR);
    svm->setTermCriteria(TermCriteria(TermCriteria::MAX_ITER, 100, 1e-6));
    svm->train(trainingDataMat, ROW_SAMPLE, labelsMat);

    double sub_sum = 0, sum = 0;
    while(fscanf(fp3, "%f", &testData[0])!=EOF)
    {
        for(i = 1; i < 32; i++)
            fscanf(fp1, "%f", &testData[i]);
        Mat testDataMat(1, 32, CV_32FC1, testData);
        float response = svm->predict(testDataMat);
        fprintf(fp5, "%f\n", response);
        if(response == 1)
            sub_sum++;
        sum++;
    }
    cout << sub_sum/sum << endl;
    sub_sum = 0, sum = 0;
    while(fscanf(fp4, "%f", &testData[0])!=EOF)
    {
        for(i = 1; i < 32; i++)
            fscanf(fp1, "%f", &testData[i]);
        Mat testDataMat(1, 32, CV_32FC1, testData);
        float response = svm->predict(testDataMat);
        fprintf(fp6, "%f\n", response);
        if(response == -1)
            sub_sum++;
        sum++;
    }
    cout << sub_sum/sum << endl;
    // Show the decision regions given by the SVM
    /*
    for (int i = 0; i < image.rows; ++i)
        for (int j = 0; j < image.cols; ++j)
        {
            Mat sampleMat = (Mat_<float>(1,2) << j,i);
            float response = svm->predict(sampleMat);
            if (response == 1)
                image.at<Vec3b>(i,j)  = green;
            else if (response == -1)
                image.at<Vec3b>(i,j)  = blue;
        }
    */
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);
    fclose(fp6);
}
