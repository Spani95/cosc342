/* $Rev: 250 $ */
#pragma once

#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include "Material.h"
#include "Ray.h"
#include "RayIntersection.h"
#include "Transform.h"

#include <memory>
#include <vector>

/** \file
 * \brief Object class header file.
 */

/**
 * \brief Abstract base class for Objects.
 *
 * An Object is a geometric entity that can be seen in a camera, such as a Sphere or Cube.
 * The term 'Object' is commonly used, but creates a bit of tension with the 'object' in 
 * 'object-oriented programming'. For this documentation a 'big-O' Object is a thing that
 * can be seen by a camera, and a 'little-o' object is a data structure with members and
 * methods etc. Hopefully this will be clear from context anyway.
 *
 * Different types of Object are distinguished primarily by their intersect() functions,
 * which determine how a given Ray intersects the surface of the Object. An Object is 
 * usually created at the origin with some standard dimensions. They can then me moved,
 * rotated, and resized through their transform member.
 *
 * As an abstract base class, you cannot create a Camera directly.
 * Instead one of its concrete subclasses must be created.
 */
class Object {
public:
	
	/** \brief Object-Ray intersection computation.
	 *
	 * Given a Ray in space, this finds the point(s) of intersection with the surface of the 
	 * Object. Note that there may be 0, 1, or more intersection points, and so a std::vector
	 * of RayIntersections is returned.
	 *
	 * The details of this depend on the geometry of the particular Object, so this is a 
	 * pure virtual method.
	 *
	 * \param ray The Ray to intersect with this Object.
	 * \return A list (std::vector) of intersections, which may be empty.
	 */
	virtual std::vector<RayIntersection> intersect(const Ray& ray) const = 0;

	Transform transform; //!< A 3D transformation to apply to this Object.
	
	Material material; //!< The colour and reflectance properties of the Object.

protected:

	/** \brief Object default constructor. */
	Object();

	/** \brief Object copy constructor.
	 *
	 * \param object The Object to copy to \c this.
	 */
	Object(const Object& object);

	/** \brief Object destructor. */
	virtual ~Object();

	/** \brief Object assignment operator. 
	 *
	 * \param object The Object to assign to \c this.
	 * \return A reference to \c this to allow for chaining of assignment.
	 */
	const Object& operator=(const Object& object);

};

#endif
