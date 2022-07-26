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

// RNG��opencv�в������������ https://blog.csdn.net/qq_33485434/article/details/78980587
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
    // ������㣬��Ȼ��ȡ���������л�����Ƚ϶��С��������
    blur( src_gray, src_gray, Size(3,3) );

    /// Create Window
    const char* source_window = "Source";
    namedWindow( source_window );
    imshow( source_window, src );

    const int max_thresh = 255;
    // ����Ե��⣬�����ֵͼ����ʹ����ֵ����Ҳ����
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
    findContours����˵����
      ����ͼ��canny_output
      ������:contours ��⵽������������
      ͼ�񱣴�Ĳ㼶���ˣ�һ�㲻ʹ�ã��� hierarchy
      �����ļ���ģʽ��
                RETR_EXTERNAL��ֻ�����������������
                RETR_LIST���������е������������䱣�浽һ�������У�
                RETR_CCOMP���������е�����������������֯Ϊ���㣬�����Ǹ����ֵ��ⲿ�߽磬�ڶ����ǿն��ı߽磻
                RETR_TREE���������е����������ع�Ƕ��������������Σ��Ƽ������֣�Ӧ�÷�Χ�㣬�����ˡ�
      �����ƽ�������
               CHAIN_APPROX_NONE����Freeman����ķ�ʽ����������������������������Σ��������У���
               CHAIN_APPROX_SIMPLE��ѹ��ˮƽ����ֱ�ĺ�б�Ĳ��֣�Ҳ����ֻ�������ǵ��յ㲿�֡�
    */
    findContours( canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE );

    /// Draw contours
    Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
    for( size_t i = 0; i< contours.size(); i++ )
    {
        Scalar color = Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
        /*
        drawContours����˵��:
            drawing:��ʾĿ��ͼ��
            contours��������
            i:��ʾ�ڼ���������-1��ʾ�������е�����
            color����ɫ
            2���߿�
            LINE_8:�ߵ�����
        */
        drawContours( drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0 );
    }

    /// Show in a window
    imshow( "Contours", drawing );
}
