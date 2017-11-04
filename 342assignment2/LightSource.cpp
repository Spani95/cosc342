/* $Rev: 250 $ */
#include "LightSource.h"

LightSource::LightSource() :
colour(1,1,1), location(0, 0, 0) {

}

LightSource::LightSource(const LightSource& lightSource) :
colour(lightSource.colour), location(lightSource.location) {

}

LightSource::~LightSource() {

}

const LightSource& LightSource::operator=(const LightSource& lightSource) {
	if (this != &lightSource) {
		colour = lightSource.colour;
		location = lightSource.location;
	}
	return *this;

}
