/* $Rev: 250 $ */
#pragma once

#ifndef RAY_INTERSECTION_H_INLUCDED
#define RAY_INTERSECTION_H_INCLUDED

#include "Point.h"
#include "Material.h"
#include "Normal.h"

#include <memory>

/**
 * \file
 * \brief RayIntersection class header file.
 */

/**
 * \brief Class to store the intersection of a Ray and an Object.
 * 
 * The fundamental operation in ray-tracing is intersecting a Ray with an Object.
 * A RayIntersection stores the information about this intersection. As well as 
 * the Point at which the intersection occurs, the Normal to the object at that location,
 * the Material of the object, and the distance along the ray are all required.
 *
 * RayInteresections can also be sorted on distance along the ray.
 */
class RayIntersection {

public:

	Point point; //!< The Point at which a Ray intersects with an Object.
	Normal normal; //!< The Normal at the Point of intersection.
	Material material; //!< The Material of the Object that is hit.
	double distance; //!< The distance along the Ray to the intersection Point.

	/** \brief Less-than comparison for RayIntersection.
	 * 
	 * In order to sort RayIntersection objects using the standard algorithms
	 * a less-than operator is required. This is defined in terms of the distance
	 * property, which provides a natural ordering for multipe Object intersections 
	 * for a single Ray.
	 *
	 * \param ri The RayIntersection to compare to \c this
	 * \return true if \c this.distance is less than \c ri.distance, false otherwise.
	 */
	bool operator<(const RayIntersection& ri) {
		return distance < ri.distance;
	}

};

#endif // RAY_INTERSECTION_H_INCLUDED
