/* $Rev: 250 $ */
#include "Normal.h"
#include <cassert>

Normal::Normal() : Vector(3) {

}

Normal::Normal(double x, double y, double z) : Vector(3){
	data_[0] = x;
	data_[1] = y;
	data_[2] = z;
}

Normal::Normal(const Normal& normal) : Vector(normal) {
	
}

Normal::Normal(const Vector& vector) : Vector(vector) {
	assert(this->rows_ == 3);
}

Normal::Normal(const Matrix& matrix) : Vector (matrix) {
	assert(this->rows_ == 3);
}
