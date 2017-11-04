/* $Rev: 250 $ */
#include "Colour.h"

Colour::Colour() : 
red(0), green(0), blue(0) {

}

Colour::Colour(double r, double g, double b) :
red(r), green(g), blue(b) {

}

Colour::Colour(const Colour& colour) :
red(colour.red), green(colour.green), blue(colour.blue) {

}

Colour::~Colour() {

}

Colour& Colour::operator=(const Colour& colour) {
	if (this != &colour) {
		red = colour.red;
		green = colour.green;
		blue = colour.blue;
	}
	return *this;
}
	
Colour Colour::operator-() const {
	return Colour(-red, -green, -blue);
}

Colour operator+(const Colour& lhs, const Colour& rhs) {
	return Colour(lhs) += rhs;
}

Colour& Colour::operator+=(const Colour& colour) {
	red += colour.red;
	green += colour.green;
	blue += colour.blue;
	return *this;
}


Colour operator-(const Colour& lhs, const Colour& rhs) {
	return Colour(lhs) -= rhs;
}

Colour& Colour::operator-=(const Colour& colour) {
	red -= colour.red;
	green -= colour.green;
	blue -= colour.blue;
	return *this;
}


Colour operator*(const Colour& lhs, const Colour& rhs) {
	return Colour(lhs) *= rhs;
}

Colour& Colour::operator*=(const Colour& colour) {
	red *= colour.red;
	green *= colour.green;
	blue *= colour.blue;
	return *this;
}

Colour operator*(double s, const Colour& colour) {
	return Colour(colour) *= s;
}

Colour operator*(const Colour& colour, double s) {
	return Colour(colour) *= s;
}

Colour& Colour::operator*=(double s) {
	red *= s;
	green *= s;
	blue *= s;
	return *this;
}

Colour operator/(const Colour& colour, double s) {
	return Colour(colour) /= s;
}

Colour& Colour::operator/=(double s) {
	red /= s;
	green /= s;
	blue /= s;
	return *this;
}

void Colour::clip() {
	if (red < 0) red = 0;
	if (red > 1) red = 1;
	if (green < 0) green = 0;
	if (green > 1) green = 1;
	if (blue < 0) blue = 0;
	if (blue > 1) blue = 1;
}
