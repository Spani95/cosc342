/* $Rev: 250 $ */
#include "PinholeCamera.h"

PinholeCamera::PinholeCamera(double f) : Camera(), focalLength(f) {

}

PinholeCamera::PinholeCamera(const PinholeCamera& camera) : Camera(camera), focalLength(camera.focalLength) {

}

PinholeCamera::~PinholeCamera() {

}

PinholeCamera& PinholeCamera::operator=(const PinholeCamera& camera) {
	if (this != &camera) {
		Camera::operator=(camera);
		focalLength = camera.focalLength;
	}
	return *this;
}

Ray PinholeCamera::castRay(double x, double y) const {
	Ray ray;
	ray.point = Point::zero(3,1);
	ray.direction(0) = x;
	ray.direction(1) = y;
	ray.direction(2) = focalLength;
	return transform.apply(ray);
}
