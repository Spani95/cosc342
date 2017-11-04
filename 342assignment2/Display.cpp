/* $Rev: 250 $ */
#include "Display.h"

#include <opencv/highgui.h>

Display::Display(const std::string& windowName, unsigned int width, unsigned int height, Colour colour) :
img_(cv::Size(width, height), CV_8UC3), windowName_(windowName) {
	cv::namedWindow(windowName_);
	img_.setTo(cv::Scalar(255*colour.blue, 255*colour.green, 255*colour.red));
}

Display::~Display() {
	cv::destroyWindow(windowName_);
}

void Display::set(int x, int y, Colour colour) {
	cv::Vec3b& col = img_.at<cv::Vec3b>(y,x);
	col[2] = int(255*colour.red);
	col[1] = int(255*colour.green);
	col[0] = int(255*colour.blue);
}

void Display::refresh() const {
	cv::imshow(windowName_, img_);
	cv::waitKey(5);
}

void Display::save(const std::string& filename) const {
	cv::imwrite(filename, img_);
}

void Display::pause(double seconds) const {
	cv::waitKey(int(seconds*1000));
}
