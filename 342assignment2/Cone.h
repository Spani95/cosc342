/* $Rev: 250 $ */
#pragma once

#ifndef CONE_H_INCLUDED
#define CONE_H_INCLUDED

#include "Object.h"

/** 
 * \file
 * \brief Cone class header file.
 */


/**
 * \brief Class for Cone objects.
 * 
 * This class provides an Object which is a cone that has its tip at
 * the origin, and its curved surface extends between this tip, to the
 * edge of a circle with unit radius, that is perpendicular to the
 * Z-axis, at Z=1.
 * 
 */
class Cone : public Object {

public:

	/** \brief Cone default constructor.
	 * 
	 * A newly constructed Cone that has its tip at the origin,
	 * and its curved surface extends between this tip, to the
	 * edge of a circle with unit radius, that is perpendicular to
	 * the Z-axis, at Z=1.
	 * It may be moved, rotated, and scaled through its transform member.
	 *
	 * \image html cone.png
	 * \image latex cone.eps
	 */
	Cone();

	/** \brief Cone copy constructor.      
	 * \param cone The Cone to copy.
	 */
	Cone(const Cone& cone);
	
	/** \brief Cone destructor. */
	~Cone();
	
	/** \brief Cone assignment operator.
	 *
	 * \param cone The Cone to assign to \c this.
	 * \return A reference to \c this to allow for chaining of assignment.
	 */
	const Cone& operator=(const Cone& cone);
	
	/** \brief Cone-Ray intersection computation.
	 *
	 * \todo Currently this method does no object intersections. This needs to be updated.
	 *
	 * The intersection of a Ray with the curved face of a Cone comes down to a quadratic formula
	 * of the form \f$at^2 + bt + c = 0\f$, where \f$t\f$ is the distance along the Ray, and
	 * \f$a\f$, \f$b\f$, and \f$c\f$ are some constants. The solutions for \f$t\f$ are given by
	 * \f[
	 *   \frac{-b \pm \sqrt{b^2-4ac}}{2a}
	 * \f]
	 * The number of intersections depends on the value of \f$b^2-4ac\f$. If it is negative
	 * then the Ray misses the Cone and there are no intersections. A positive value indicates
	 * two intersections (entering and then leaving the Cone). Finally, if \f$b^2-4ac = 0\f$ then
	 * there is a single grazing hit with the Cone.
	 *
	 * Intersections with the circle at the base of the cone are
	 * handled separately. One approach is to determine where the
	 * ray in primitive space intersects with the plane at
	 * \f$Z=1\f$. If there is an intersection, then the \f$X\f$
	 * and \f$Y\f$ coordinates at that intersection can be
	 * examined to determine it is within radius 1 of the
	 * \f$Z\f$-axis. When within that radius, we have an
	 * additional intersection with the circle at the base of the
	 * cone.
	 *
	 * \param ray The Ray to intersect with this Cone.
	 * \return A list (std::vector) of intersections, which may be empty.
	 */
	std::vector<RayIntersection> intersect(const Ray& ray) const;

};

#endif // CONE_H_INCLUDED
