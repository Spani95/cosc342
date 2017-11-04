#include "Display.h"

#include <iostream>
#include <fstream>

Display::Display(const std::string& windowName, unsigned int width, unsigned int height, Colour colour) :
width_(width), height_(height), windowName_(windowName) {
	red_ = new unsigned char[width_*height_];
	green_ = new unsigned char[width_*height_];
	blue_ = new unsigned char[width_*height_];
}

Display::~Display() {
	delete [] red_;
	delete [] green_;
	delete [] blue_;
}

void Display::set(int x, int y, Colour colour) {
	size_t ix = y*width_ + x;
	red_[ix] = int(255*colour.red);
	green_[ix] = int(255*colour.green);
	blue_[ix] = int(255*colour.blue);
}

void Display::refresh() const {
	
}

void Display::save(const std::string& filename) const {
	std::ofstream out(filename);
	out << "P6" << std::endl;
	out << width_ << " " << height_ << std::endl;
	out << 255 << std::endl;
	for (int ix = 0; ix < width_*height_; ++ix) {
		out << red_[ix] << green_[ix] << blue_[ix];
	}
	out.close();
}

void Display::pause(double seconds) const {
	
}
