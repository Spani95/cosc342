/* $Rev: 250 $ */
#include "Vector.h"

#include <cmath>
#include <assert.h>

// Vector constructor
Vector::Vector(size_t size) : Matrix(size, 1) {

}

// Vector copy constructor
Vector::Vector(const Vector& vec) : Matrix(vec) {

}

// Vector from Matrix constructor
Vector::Vector(const Matrix& mat) : Matrix(mat) {
	assert(cols_ == 1);
}

// Vector destructor
Vector::~Vector() {

}

// Vector assignement operator
Vector& Vector::operator=(const Vector& vec) {
	if (this != &vec) {
		Matrix::operator=(vec);
	}
	return *this;
}

// Vector element access
double& Vector::operator()(size_t ix) {
	return data_[ix];
}

// Vector element access (const version)
const double& Vector::operator()(size_t ix) const {
	return data_[ix];
}

// Unary minus
Vector Vector::operator-() const {
	return Vector(Matrix::operator-());
}

// Vector addition
Vector operator+(const Vector& lhs, const Vector& rhs) {
	Vector result(lhs);
	result += rhs;
	return result;
}

// Vector adidition-assignement
Vector& Vector::operator+=(const Vector& vec) {
	this->Matrix::operator+=(vec);
	return *this;
}

// Vector difference
Vector operator-(const Vector& lhs, const Vector& rhs) {
	Vector result(lhs);
	result -= rhs;
	return result;
}

// Vector subtraction-assignment
Vector& Vector::operator-=(const Vector& vec) {
	this->Matrix::operator-=(vec);
	return *this;
}

// Vector scalar multiplication from the left
Vector operator*(double s, const Vector& vec) {
	Vector result(vec);
	result *= s;
	return result;
}

// Vector scalar multiplication from the right
Vector operator*(const Vector& vec, double s) {
	Vector result(vec);
	result *= s;
	return result;
}

// Vector scalar multiplication-assignment
Vector& Vector::operator*=(double s) {
	this->Matrix::operator*=(s);
	return *this;
}

// Vector scalar division
Vector operator/(const Vector& vec, double s) {
	Vector result(vec);
	result /= s;
	return result;
}

// Vector scalar division-assignment
Vector& Vector::operator/=(double s) {
	this->Matrix::operator/=(s);
	return *this;
}

// Vector dot product
double Vector::dot(const Vector& vec) const {
	assert(data_.size() == vec.data_.size());
	double sum = 0;
	for (size_t i = 0; i < data_.size(); ++i) {
		sum += data_[i] * vec.data_[i];
	}
	return sum;
}

// Vector cross product
Vector Vector::cross(const Vector& vec) const {
	assert(rows_ == 3 && vec.rows_ == 3);
	Vector result(3);
	result(0) = data_[1]*vec.data_[2] - data_[2]*vec.data_[1];
	result(1) = data_[2]*vec.data_[0] - data_[0]*vec.data_[2];
	result(2) = data_[0]*vec.data_[1] - data_[1]*vec.data_[0];
	return result;
}

// Vector norm
double Vector::norm() const {
	return std::sqrt(dot(*this));
}

// Squared Vector norm
double  Vector::squaredNorm() const {
	return dot(*this);
}
