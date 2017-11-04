/* $Rev: 250 $ */
#include "Cone.h"

#include "utility.h"

Cone::Cone() : Object() {

}

Cone::Cone(const Cone& cone) : Object(cone) {

}

Cone::~Cone() {

}

const Cone& Cone::operator=(const Cone& cone) {
	if (this != &cone) {
		Object::operator=(cone);
	}
	return *this;
}

std::vector<RayIntersection> Cone::intersect(const Ray& ray) const {

	std::vector<RayIntersection> result;

	Ray inverseRay = transform.applyInverse(ray);

	RayIntersection hit;
	hit.material = material;
	double d;

	// Intersection is of the form ad^2 + bd + c, where d = distance along the ray

	return result;
}
