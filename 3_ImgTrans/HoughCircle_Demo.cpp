/**
 * @file HoughCircle_Demo.cpp
 * @brief Demo code for Hough Transform
 * @author OpenCV team
 */

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

namespace
{
    // windows and trackbars name
    const std::string windowName = "Hough Circle Detection Demo";
    const std::string cannyThresholdTrackbarName = "Canny threshold";
    const std::string accumulatorThresholdTrackbarName = "Accumulator Threshold";

    // initial and max values of the parameters of interests.
    const int cannyThresholdInitialValue = 100;
    const int accumulatorThresholdInitialValue = 50;
    const int maxAccumulatorThreshold = 200;
    const int maxCannyThreshold = 255;

    void HoughDetection(const Mat& src_gray, const Mat& src_display, int cannyThreshold, int accumulatorThreshold)
    {
        // will hold the results of the detection，浮点矢量（x, y, radius）
        std::vector<Vec3f> circles;
        // runs the actual detection
        // HOUGH_GRADIENT 表示检测方法，目前 OpenCV 中就霍夫梯度法一种可以使用，标识符为 HOUGH_GRADIENT。
        // 1参数表示累加面分辨率，1表示和原始分辨率一致。
        // src_gray.rows/8表示两个圆心之间的最小距离，小于该值认为同一个圆。
        // cannyThreshold表示Canny 边缘检测的高阈值，低阈值被自动置为高阈值的一半，默认为 100。
        // accumulatorThreshold表示累加平面某点是否是圆心的判定阈值。它越大，能通过检测的圆就更接近完美的圆形，默认为 100。
        // 最后两个参数表示圆半径的最小最大值。
        HoughCircles( src_gray, circles, HOUGH_GRADIENT, 1, src_gray.rows/8, cannyThreshold, accumulatorThreshold, 0, 0 );

        // clone the colour, input image for displaying purposes
        Mat display = src_display.clone();
        for( size_t i = 0; i < circles.size(); i++ )
        {   
            // cvRound:四舍五入
            // cvFloor:向下取整
            // cvCeil:向上取整
            Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            // circle center
            // Scalar：标量, 在opencv中广泛用于值传递，https://blog.csdn.net/jndingxin/article/details/112606544
            circle( display, center, 3, Scalar(0,255,0), -1, 8, 0 );
            // circle outline
            circle( display, center, radius, Scalar(0,0,255), 3, 8, 0 );
        }

        // shows the results
        imshow( windowName, display);
    }
}


int main(int argc, char** argv)
{
    Mat src, src_gray;

    // Read the image
    String imageName("stuff.jpg"); // by default
    if (argc > 1)
    {
       imageName = argv[1];
    }
    // src = imread( samples::findFile( imageName ), IMREAD_COLOR );
    src = imread("D:\\GitHub\\Opencv_Learning_Notes\\Sources\\data\\stuff.jpg", IMREAD_COLOR);
    if( src.empty() )
    {
        std::cerr << "Invalid input image\n";
        std::cout << "Usage : " << argv[0] << " <path_to_input_image>\n";;
        return -1;
    }

    // Convert it to gray
    cvtColor( src, src_gray, COLOR_BGR2GRAY );

    // Reduce the noise so we avoid false circle detection
    GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );

    //declare and initialize both parameters that are subjects to change
    int cannyThreshold = cannyThresholdInitialValue;
    int accumulatorThreshold = accumulatorThresholdInitialValue;

    // create the main window, and attach the trackbars
    namedWindow( windowName, WINDOW_AUTOSIZE );
    createTrackbar(cannyThresholdTrackbarName, windowName, &cannyThreshold,maxCannyThreshold);
    createTrackbar(accumulatorThresholdTrackbarName, windowName, &accumulatorThreshold, maxAccumulatorThreshold);

    // infinite loop to display
    // and refresh the content of the output image
    // until the user presses q or Q
    char key = 0;
    while(key != 'q' && key != 'Q')
    {
        // those parameters cannot be =0
        // so we must check here
        cannyThreshold = std::max(cannyThreshold, 1);
        accumulatorThreshold = std::max(accumulatorThreshold, 1);

        //runs the detection, and update the display
        // 霍夫圆检测的输入可以不是二值图，灰度图就可以。
        HoughDetection(src_gray, src, cannyThreshold, accumulatorThreshold);

        // get user key
        key = (char)waitKey(10);
    }

    return 0;
}
