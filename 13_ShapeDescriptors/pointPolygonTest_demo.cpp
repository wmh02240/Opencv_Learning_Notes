/**
 * @function pointPolygonTest_demo.cpp
 * @brief Demo code to use the pointPolygonTest function...fairly easy
 * @author OpenCV team
 */

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

/**
 * @function main
 */
int main(void)
{
	/// Create an image
	const int r = 100;
	Mat src = Mat::zeros(Size(4 * r, 4 * r), CV_8U);

	/// Create a sequence of points to make a contour
	vector<Point2f> vert(6);
	vert[0] = Point(3 * r / 2, static_cast<int>(1.34 * r));
	vert[1] = Point(1 * r, 2 * r);
	vert[2] = Point(3 * r / 2, static_cast<int>(2.866 * r));
	vert[3] = Point(5 * r / 2, static_cast<int>(2.866 * r));
	vert[4] = Point(3 * r, 2 * r);
	vert[5] = Point(5 * r / 2, static_cast<int>(1.34 * r));

	/// Draw it in src
	for (int i = 0; i < 6; i++)
	{
		line(src, vert[i], vert[(i + 1) % 6], Scalar(255), 3);
	}

	/// Get the contours
	vector<vector<Point> > contours;
	findContours(src, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

	/// Calculate the distances to the contour
	Mat raw_dist(src.size(), CV_32F);
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{	
			/*
			pointPolygonTest（点多边形测试函数）函数说明:在进行缺陷检测的程序设计时，想根据一个点是否在给定的轮廓中来判断物件是否被沾污。
				该函数用来测试一个点是否在多边形中。
				当measureDist设置为true时，返回实际距离值。若返回值为正，表示点在多边形内部，返回值为负，表示在多边形外部，返回值为0，表示在多边形上。
				当measureDist设置为false时，返回 -1、0、1三个固定值。若返回值为+1，表示点在多边形内部，返回值为-1，表示在多边形外部，返回值为0，表示在多边形上。
			*/
			raw_dist.at<float>(i, j) = (float)pointPolygonTest(contours[0], Point2f((float)j, (float)i), true);
		}
	}

	double minVal, maxVal;
	Point maxDistPt; // inscribed circle center 内接圆心
	/*
	minMaxLoc()函数寻找全局最大最小值
		raw_dist:输入数组，若为图像需为单通道图
		minVal，返回最小值的指针。若无需返回，此值设为 NULL。
		maxVal，返回最大值的指针。若无需返回，此值设为 NULL。
		minLoc，返回最小值位置的指针（二维情况下）。若无需返回，此值设为 NULL。
		maxLoc，返回最大值位置的指针（二维情况下）。若无需返回，此值设为 NULL。
		mask，可选的掩膜操作，非零掩码元素用于标记待统计元素，需要与输入图像集有相同尺寸。
	*/
	minMaxLoc(raw_dist, &minVal, &maxVal, NULL, &maxDistPt);
	minVal = abs(minVal);
	maxVal = abs(maxVal);

	/// Depicting the distances graphically
	Mat drawing = Mat::zeros(src.size(), CV_8UC3);
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			if (raw_dist.at<float>(i, j) < 0)  //表示该点在多边形外部
			{
				drawing.at<Vec3b>(i, j)[0] = (uchar)(255 - abs(raw_dist.at<float>(i, j)) * 255 / minVal);
			}
			else if (raw_dist.at<float>(i, j) > 0)  //表示该点在多边形内部
			{
				drawing.at<Vec3b>(i, j)[2] = (uchar)(255 - raw_dist.at<float>(i, j) * 255 / maxVal);
			}
			else  //==0表示该点在多边形外部
			{
				drawing.at<Vec3b>(i, j)[0] = 255;
				drawing.at<Vec3b>(i, j)[1] = 255;
				drawing.at<Vec3b>(i, j)[2] = 255;
			}
		}
	}
	/*
	在图上画圆：
		参数依次为：原图、圆心、半径、颜色、线宽等
	*/
	circle(drawing, maxDistPt, (int)maxVal, Scalar(255, 255, 255));

	/// Show your results
	imshow("Source", src);
	imshow("Distance and inscribed circle", drawing);

	waitKey();
	return 0;
}
