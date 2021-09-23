#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <iostream>
using namespace cv;
using namespace cv::xfeatures2d;
using namespace std;

int main()
{
    Mat srcImage = imread("1.png");

    int numFeatures = 20;
    Ptr<SIFT> dectector = SIFT::create(numFeatures);

    vector<KeyPoint> keypoints;
    dectector->detect(srcImage, keypoints, Mat());
    printf("Total keypoints: %d\n", keypoints.size());

    Mat keypoint_img;
    drawKeypoints(srcImage, keypoints, keypoint_img, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
    imshow("keypoint_img", keypoint_img);

    waitKey(0);
    return 0;
}