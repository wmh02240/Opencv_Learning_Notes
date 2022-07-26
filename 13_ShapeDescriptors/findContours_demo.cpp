/**
 * @function findContours_Demo.cpp
 * @brief Demo code to find contours in an image
 * @author OpenCV team
 */

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat src_gray;
int thresh = 100;

// RNG是opencv中产生随机数的类 https://blog.csdn.net/qq_33485434/article/details/78980587
RNG rng(12345);

/// Function header
void thresh_callback(int, void* );

/**
 * @function main
 */
int main( int argc, char** argv )
{
    /// Load source image
    CommandLineParser parser(argc, argv, "{@input | HappyFish.jpg | input image}");

    //Mat src = imread(samples::findFile(parser.get<String>("@input")), IMREAD_COLOR);
    Mat src = imread("D:\\GitHub\\Opencv_Learning_Notes\\Sources\\data\\HappyFish.jpg", IMREAD_COLOR);
    
    if( src.empty() )
    {
      cout << "Could not open or find the image!\n" << endl;
      cout << "Usage: " << argv[0] << " <Input image>" << endl;
      return -1;
    }

    /// Convert image to gray and blur it
    cvtColor( src, src_gray, COLOR_BGR2GRAY );
    // 消除噪点，不然提取到的轮廓中会包含比较多的小区域轮廓
    blur( src_gray, src_gray, Size(3,3) );

    /// Create Window
    const char* source_window = "Source";
    namedWindow( source_window );
    imshow( source_window, src );

    const int max_thresh = 255;
    // 做边缘检测，输出二值图或者使用阈值处理也可以
    createTrackbar( "Canny thresh:", source_window, &thresh, max_thresh, thresh_callback );
    thresh_callback( 0, 0 );

    waitKey();
    return 0;
}

/**
 * @function thresh_callback
 */
void thresh_callback(int, void* )
{
    /// Detect edges using Canny
    Mat canny_output;
    Canny( src_gray, canny_output, thresh, thresh * 2 );

    /// Find contours
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    /*
    findContours函数说明：
      输入图：canny_output
      输出结果:contours 检测到的轮廓点坐标
      图像保存的层级拓扑（一般不使用）： hierarchy
      轮廓的检索模式：
                RETR_EXTERNAL，只检索最外面的轮廓；
                RETR_LIST，检索所有的轮廓，并将其保存到一条链表中；
                RETR_CCOMP，检索所有的轮廓，并将他们组织为两层，顶层是各部分的外部边界，第二次是空洞的边界；
                RETR_TREE，检索所有的轮廓，并重构嵌套轮廓的整个层次，推荐用这种，应用范围广，够用了。
      轮廓逼近方法：
               CHAIN_APPROX_NONE，以Freeman链码的方式输出轮廓，所有其他方法输出多边形（顶点序列）。
               CHAIN_APPROX_SIMPLE，压缩水平、垂直的和斜的部分，也就是只保留他们的终点部分。
    */
    findContours( canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE );

    /// Draw contours
    Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
    for( size_t i = 0; i< contours.size(); i++ )
    {
        Scalar color = Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
        /*
        drawContours函数说明:
            drawing:表示目标图像
            contours：轮廓点
            i:表示第几个轮廓，-1表示绘制所有的轮廓
            color；颜色
            2：线宽
            LINE_8:线的类型
        */
        drawContours( drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0 );
    }

    /// Show in a window
    imshow( "Contours", drawing );
}
