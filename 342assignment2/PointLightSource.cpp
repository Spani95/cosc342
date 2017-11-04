/* $Rev: 250 $ */
#include "PointLightSource.h"

#include "utility.h"

PointLightSource::PointLightSource() : 
LightSource() {

}

PointLightSource::PointLightSource(const PointLightSource& lightSource) :
LightSource(lightSource) {

}

PointLightSource::~PointLightSource() {

}

const PointLightSource& PointLightSource::operator=(const PointLightSource& lightSource) {
	if (this != &lightSource) {
		LightSource::operator=(lightSource);
	}
	return *this;
}

double PointLightSource::getIntensityAt(const Point& point) const {
	double distance = (location - point).norm();
	if (distance < epsilon) distance = epsilon;
	return 1 / (distance*distance);
}
