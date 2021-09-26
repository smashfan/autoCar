//定义相机标定的相关常量设置与变量

vector<string> files;
glob("D:/images/camera2d", files);
 
// 定义变量
vector<vector<Point2f>> imagePoints;
vector<vector<Point3f>> objectPoints;
TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::MAX_ITER, 30, 0.001);
int numCornersHor = 7;
int numCornersVer = 7;
int numSquares = 50;
vector<Point3f> obj;
for (int i = 0; i < numCornersHor; i++)
    for (int j = 0; j < numCornersVer; j++)
        obj.push_back(Point3f((float)j * numSquares, (float)i * numSquares, 0));


// 发现棋盘格与绘制
Size s;
for (int i = 0; i < files.size(); i++) {
    printf("image file : %s \n", files[i].c_str());
    Mat image = imread(files[i]);
    s = image.size();
    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);
    vector<Point2f> corners;
    bool ret = findChessboardCorners(gray, Size(7, 7), corners, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_FILTER_QUADS);
    if (ret) {
        cornerSubPix(gray, corners, Size(11, 11), Size(-1, -1), criteria);
        drawChessboardCorners(image, Size(7, 7), corners, ret);
        imagePoints.push_back(corners);
        objectPoints.push_back(obj);
        imshow("calibration-demo", image);
        waitKey(500);
    }
}

// 相机校正
Mat intrinsic = Mat(3, 3, CV_32FC1);
Mat distCoeffs;
vector<Mat> rvecs;
vector<Mat> tvecs;
intrinsic.ptr<float>(0)[0] = 1;
intrinsic.ptr<float>(1)[1] = 1;
calibrateCamera(objectPoints, imagePoints, s, intrinsic, distCoeffs, rvecs, tvecs);

// 畸变校正
for (int i = 0; i < files.size(); i++) {
    Mat dst;
    Mat image = imread(files[i]);
    undistort(image, dst, intrinsic, distCoeffs);
    imshow("image", image);
    imshow("undistort image", dst);
    waitKey(1000);
}