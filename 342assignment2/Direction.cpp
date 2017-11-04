/* $Rev: 250 $ */
#include "Direction.h"
#include <cassert>

Direction::Direction() : Vector(3) {

}

Direction::Direction(double x, double y, double z) : Vector(3){
	data_[0] = x;
	data_[1] = y;
	data_[2] = z;
}

Direction::Direction(const Direction& direction) : Vector(direction) {
	
}

Direction::Direction(const Vector& vector) : Vector(vector) {
	assert(this->rows_ == 3);
}

Direction::Direction(const Matrix& matrix) : Vector (matrix) {
	assert(this->rows_ == 3);
}
