#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	CvPoint center;
    double scale = -3; 

	IplImage* image = cvLoadImage("test1.png");
	argc == 2? cvLoadImage(argv[1]) : 0;
	
	cvShowImage("Image", image);
	
	
	if (!image) return -1; 	center = cvPoint(image->width / 2, image->height / 2);
	for (int i = 0;i<image->height;i++)
		for (int j = 0;j<image->width;j++) {
			double dx = (double)(j - center.x) / center.x;
			double dy = (double)(i - center.y) / center.y;
			double weight = exp((dx*dx + dy*dy)*scale);
			uchar* ptr = &CV_IMAGE_ELEM(image, uchar, i, j * 3);
			ptr[0] = cvRound(ptr[0] * weight);
			ptr[1] = cvRound(ptr[1] * weight);
			ptr[2] = cvRound(ptr[2] * weight);
		}

	Mat src;Mat dst;
	src = cvarrToMat(image);
	cv::imwrite("test.png", src);

    cvNamedWindow("test",1);  	imshow("test", src);
	 cvWaitKey();
	 return 0;
}



