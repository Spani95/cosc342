/* $Rev: 250 $ */
#include "Camera.h"

Camera::Camera() : transform() {

}

Camera::Camera(const Camera& camera) : transform(camera.transform) {

}

Camera::~Camera() {

}

const Camera& Camera::operator=(const Camera& camera) {
	if (this != &camera) {
		transform = camera.transform;
	}

	return *this;
}
