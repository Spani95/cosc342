/* $Rev: 250 $ */
#include "Transform.h"
#include "utility.h"

Transform::Transform() :
T_(Matrix::identity(4,4)), Tinv_(Matrix::identity(4,4)) {

}

Transform::Transform(const Transform& transform) :
T_(transform.T_), Tinv_(transform.Tinv_) {

}

Transform::~Transform() {

}

Transform& Transform::operator=(const Transform& transform) {
	if (this != &transform) {
		T_ = transform.T_;
		Tinv_ = transform.Tinv_;
	}
	return *this;
}


Point Transform::apply(const Point& point) const {
	Vector v(4);
	v(0) = point(0);
	v(1) = point(1);
	v(2) = point(2);
	v(3) = 1;
	v = T_*v;
	Point result;
	result(0) = v(0)/v(3);
	result(1) = v(1)/v(3);
	result(2) = v(2)/v(3);
	return result;
}

Direction Transform::apply(const Direction& direction) const {
	Vector v(4);
	v(0) = direction(0);
	v(1) = direction(1);
	v(2) = direction(2);
	v(3) = 0;
	v = T_*v;
	Direction result;
	result(0) = v(0);
	result(1) = v(1);
	result(2) = v(2);
	return result;
}

Normal Transform::apply(const Normal& normal) const {
	Vector v(4);
	v(0) = normal(0);
	v(1) = normal(1);
	v(2) = normal(2);
	v(3) = 0;
	v = Tinv_.transpose()*v;
	Normal result;
	result(0) = v(0);
	result(1) = v(1);
	result(2) = v(2);
	return result;
}

Ray Transform::apply(const Ray& ray) const {
	Ray result;
	result.point = apply(ray.point);
	result.direction = apply(ray.direction);
	return result;
}

Point Transform::applyInverse(const Point& point) const {
	Vector v(4);
	v(0) = point(0);
	v(1) = point(1);
	v(2) = point(2);
	v(3) = 1;
	v = Tinv_*v;
	Point result;
	result(0) = v(0)/v(3);
	result(1) = v(1)/v(3);
	result(2) = v(2)/v(3);
	return result;
}

Direction Transform::applyInverse(const Direction& direction) const {
	Vector v(4);
	v(0) = direction(0);
	v(1) = direction(1);
	v(2) = direction(2);
	v(3) = 0;
	v = Tinv_*v;
	Direction result;
	result(0) = v(0);
	result(1) = v(1);
	result(2) = v(2);
	return result;
}

Normal Transform::applyInverse(const Normal& normal) const {
	Vector v(4);
	v(0) = normal(0);
	v(1) = normal(1);
	v(2) = normal(2);
	v(3) = 0;
	v = T_.transpose()*v;
	Normal result;
	result(0) = v(0);
	result(1) = v(1);
	result(2) = v(2);
	return result;
}

Ray Transform::applyInverse(const Ray& ray) const {
	Ray result;
	result.point = applyInverse(ray.point);
	result.direction = applyInverse(ray.direction);
	return result;
}

void Transform::rotateX(double rx) {
	Matrix R(Matrix::identity(4,4));

	rx = deg2rad(rx);
	R(1,1) = R(2,2) = cos(rx);
	R(1,2) = -sin(rx);
	R(2,1) = sin(rx);

	T_ = R*T_;
	Tinv_ = Tinv_*R.transpose();
}

void Transform::rotateY(double ry) {
	Matrix R(Matrix::identity(4,4));

	ry = deg2rad(ry);
	R(0,0) = R(2,2) = cos(ry);
	R(0,2) = sin(ry);
	R(2,0) = -sin(ry);

	T_ = R*T_;
	Tinv_ = Tinv_*R.transpose();
}

void Transform::rotateZ(double rz) {
	Matrix R(Matrix::identity(4,4));

	rz = deg2rad(rz);
	R(0,0) = R(1,1) = cos(rz);
	R(0,1) = -sin(rz);
	R(1,0) = sin(rz);

	T_ = R*T_;
	Tinv_ = Tinv_*R.transpose();
}

void Transform::scale(double s) {
	Matrix S(Matrix::identity(4,4));
	
	S(0,0) = S(1,1) = S(2,2) = s;

	T_ = S*T_;

	S(0,0) = S(1,1) = S(2,2) = 1/s;

	Tinv_ = Tinv_*S;
}

void Transform::scale(double sx, double sy, double sz) {
	Matrix S(Matrix::identity(4,4));
	
	S(0,0) = sx;
	S(1,1) = sy;
	S(2,2) = sz;

	T_ = S*T_;

	S(0,0) = 1/sx;
	S(1,1) = 1/sy;
	S(2,2) = 1/sz;

	Tinv_ = Tinv_*S;
}

void Transform::translate(double tx, double ty, double tz) {
	Matrix T(Matrix::identity(4,4));
	
	T(0,3) = tx;
	T(1,3) = ty;
	T(2,3) = tz;

	T_ = T*T_;

	T(0,3) = -tx;
	T(1,3) = -ty;
	T(2,3) = -tz;

	Tinv_ = Tinv_*T;
}

void Transform::translate(const Direction& direction) {
	translate(direction(0), direction(1), direction(2));
}
