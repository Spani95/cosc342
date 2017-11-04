/* $Rev: 250 $ */
#include "Point.h"
#include <cassert>

Point::Point() : Vector(3) {

}

Point::Point(double x, double y, double z) : Vector(3){
	data_[0] = x;
	data_[1] = y;
	data_[2] = z;
}

Point::Point(const Point& point) : Vector(point) {
	
}

Point::Point(const Vector& vector) : Vector(vector) {
	assert(this->rows_ == 3);
}

Point::Point(const Matrix& matrix) : Vector (matrix) {
	assert(this->rows_ == 3);
}
