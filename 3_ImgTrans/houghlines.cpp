/**
 * @file houghlines.cpp
 * @brief This program demonstrates line finding with the Hough transform
 */

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;


int main1(int argc, char** argv)
{
	Mat dst, cdst, cstP;

	const char* default_file = "";
	const char* filename = argc >= 2 ? argv[1] : default_file;

	Mat src = imread(samples::findFile(filename), IMREAD_COLOR);

	if (src.empty()) {
		cout << "loading image error..." << endl;
		return -1;
	}

	Canny(src, dst, 50, 200, 3);

	return 0;

}


// argc时argumenr count 的缩写, 表示传入参数的数量
// argv时argument vector的缩写, 表示传入main函数的参数序列或者指针, 并且第一个参数argv[0]一定是程序的名称,并且包含了
// 程序所在的完整路径, argv是指向指针的指针, 所以char* argv[]也可以替换成char** argv。
int main(int argc, char** argv)
{
	// Declare the output variables
	Mat dst, cdst, cdstP;

	//![load]
	const char* default_file = "D:\\GitHub\\Opencv_Learning_Notes\\Sources\\data\\sudoku.png";
	const char* filename = argc >= 2 ? argv[1] : default_file;  //三目运算？

	// Loads an image
	Mat src = imread(samples::findFile(filename), IMREAD_GRAYSCALE);
	// Mat src = imread("D:\\GitHub\\Opencv_Learning_Notes\\Sources\\data\\sudoku.png", IMREAD_GRAYSCALE);

	// Check if image is loaded fine
	if (src.empty()) {
		printf(" Error opening image\n");
		printf(" Program Arguments: [image_name -- default %s] \n", default_file);
		return -1;
	}
	//![load]

	//![edge_detection]
	// Edge detection
	// 霍夫线检测的输入应该是一个二值图。
	Canny(src, dst, 50, 200, 3);
	//![edge_detection]

	// Copy edges to the images that will display the results in BGR
	cvtColor(dst, cdst, COLOR_GRAY2BGR);
	cdstP = cdst.clone();

	//![hough_lines]
	// Standard Hough Line Transform
	vector<Vec2f> lines; // will hold the results of the detection
	HoughLines(dst, lines, 1, CV_PI / 180, 150, 0, 0); // runs the actual detection
	//![hough_lines]
	//![draw_lines]
	// Draw the lines
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(cdst, pt1, pt2, Scalar(0, 0, 255), 3, LINE_AA);
	}
	//![draw_lines]

	//![hough_lines_p]
	// Probabilistic Line Transform
	vector<Vec4i> linesP; // will hold the results of the detection
	HoughLinesP(dst, linesP, 1, CV_PI / 180, 50, 50, 10); // runs the actual detection
	//![hough_lines_p]
	//![draw_lines_p]

	// Draw the lines
	for (size_t i = 0; i < linesP.size(); i++)
	{
		Vec4i l = linesP[i];
		line(cdstP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
	}
	//![draw_lines_p]

	//![imshow]
	// Show results
	imshow("Source", src);
	imshow("Detected Lines (in red) - Standard Hough Line Transform", cdst);
	imshow("Detected Lines (in red) - Probabilistic Line Transform", cdstP);
	//![imshow]

	//![exit]
	// Wait and Exit
	waitKey();
	return 0;
	//![exit]
}
