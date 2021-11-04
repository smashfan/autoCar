//参数为原图像、逆透视图、四个原图上的对应点
bool IpmTransform::executeipm(Mat& img,Mat& dst,Point2d P1,Point2d P2,Point2d P3,Point2d P4)
{
    if (img.data)
    {
        Point2f corners[4];//原图四个点
        Point2f corners_trans[4];//逆透视图四个点
 
        //**车载场景图象的其他参数**//
        float roi_x0=0;
        float roi_y0=228;
        float ROI_HEIGHT=30000;
        float ROI_WIDTH=3750;
        //************************//
 
        corners[0] = P2;
        corners[1] = P3;
        corners[2] = P1;
        corners[3] = P4;
 
        //设定逆透视图的宽度
        float IPM_WIDTH=500;
        float N=5;
        //保证逆透视图的宽度大概为N个车头宽
        float sacale=(IPM_WIDTH/N)/ROI_WIDTH;
        float IPM_HEIGHT=ROI_HEIGHT*sacale;
 
        //逆透视图初始化
        dst=Mat::zeros(IPM_HEIGHT+50,IPM_WIDTH,img.type());
 
        corners_trans[0] = Point2f(IPM_WIDTH/2-IPM_WIDTH/(2*N),0);  //P2
        corners_trans[1] = Point2f(IPM_WIDTH/2+IPM_WIDTH/(2*N),0);  //P3
        corners_trans[2] = Point2f(IPM_WIDTH/2-IPM_WIDTH/(2*N),IPM_HEIGHT);   //P1
        corners_trans[3] = Point2f(IPM_WIDTH/2+IPM_WIDTH/(2*N),IPM_HEIGHT);   //P4
 
        //计算原图到逆透视图和逆透视图到原图的变换矩阵
        warpMatrix_src2ipm = getPerspectiveTransform(corners, corners_trans);
        warpPerspective(img, dst, warpMatrix_src2ipm, dst.size());
        //标出两组点
        for(int i=0;i<4;i++)
            circle(img,corners[i],5,Scalar(0,255,255),4);
        for(int i=0;i<4;i++)
            circle(dst,corners_trans[i],5,Scalar(0,255,255),4);
 
        imshow("img",img);
        imshow("dst",dst);
    }
    else
    {
        cout << "NO IMAGE!!!" << endl;
        return false;
    }
 
    return true;
}