/* $Rev: 250 $ */
#pragma once

#ifndef SPHERE_H_INCLUDED
#define SPHERE_H_INCLUDED

#include "Object.h"

/** 
 * \file
 * \brief Sphere class header file.
 */


/**
 * \brief Class for Sphere objects.
 * 
 * This class provides an Object which is a sphere centred at the origin with radius 1.
 * 
 */
class Sphere : public Object {

public:

	/** \brief Sphere default constructor.
	 * 
	 * A newly constructed Sphere is centred at the origin, and has a raidus of 1.
	 * It may be moved, rotated, and scaled through its transform member.
	 */
	Sphere();

	/** \brief Sphere copy constructor.      
	 * \param sphere The Sphere to copy.
	 */
	Sphere(const Sphere& sphere);
	
	/** \brief Sphere destructor. */
	~Sphere();
	
	/** \brief Sphere assignment operator.
	 *
	 * \param sphere The Sphere to assign to \c this.
	 * \return A reference to \c this to allow for chaining of assignment.
	 */
	const Sphere& operator=(const Sphere& sphere);
	
	/** \brief Sphere-Ray intersection computation.
	 *
	 * The intersection of a Ray with a Sphere comes down to a quadratic formula
	 * of the form \f$at^2 + bt + c\f$, where \f$t\f$ is the distance along the Ray, and
	 * \f$a\f$, \f$b\f$, and \f$c\f$ are some constants. The solutions for \f$t\f$ are given by
	 * \f[
	 *   \frac{-b \pm \sqrt{b^2-4ac}}{2a}
	 * \f]
	 * The number of intersections depends on the value of \f$b^2-4ac\f$. If it is negative
	 * then the Ray misses the Sphere and there are no intersections. A positive value indicates
	 * two intersection (entering and then leaving the Sphere). Finally, if \f$b^2-4ac = 0\f$ then
	 * there is a single grazing hit with the Sphere.
	 *
	 * \param ray The Ray to intersect with this Sphere.
	 * \return A list (std::vector) of intersections, which may be empty.
	 */
	std::vector<RayIntersection> intersect(const Ray& ray) const;

};

#endif // SPHERE_H_INCLUDED
