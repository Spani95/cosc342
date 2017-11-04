/* $Rev: 250 $ */
#pragma once

#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "Ray.h"
#include "Transform.h"

/**
 * \file 
 * \brief Camera class header file.
 */

/**
 * \brief Abstract base class for Cameras.
 *
 * Cameras are the primary source of rays in a scene. A camera 
 * is defined by its castRay() function, which generates a ray
 * given a image plane co-ordinate.
 *
 * As an abstract base class, you cannot create a Camera directly.
 * Instead one of its concrete subclasses must be created.
 */
class Camera {

public:

	/** \brief Generate a ray for a given image plane co-ordinate
	 *
	 * Given a point on a virtual image plane, this method generates a ray
	 * for a given camera model. Note that image plane co-ordinates are not 
	 * the same as pixel co-ordinates. There are two main differences:
	 * - The origin of the image plane co-ordinates are in the centre of 
	 * the image plane, while pixels usually count from the top left corner.
	 * - Image plane co-ordinates are continuous (real) values, wheras
	 * pixel values are discrete.
	 *
	 * By convention, x-values are in the range [-1,1], and the range of
	 * y-values depends on the aspect ratio of the image. For wide (landscape)
	 * images y-values will lie in a narrower range, while for tall (portrait)
	 * images, y-values will exceed this range. This is, however, merely a 
	 * convention so is neither required nor enforced.
	 *
	 * \param x the horizontal location
	 * \param y the vertical location
	 * \return The Ray that passes from the Camera through (x,y) in the image plane.
	 */
	virtual Ray castRay(double x, double y) const = 0;

	Transform transform; //!< Transformation to apply to the Camera.

protected:

	/** \brief Camera default constructor. */
	Camera(); 

	/** \brief Camera copy constructor. 
	 *
	 * \param camera The Camera to copy.
	 */
	Camera(const Camera& camera);

	/** \brief Camera destructor. */
	virtual ~Camera();

	/** \brief Camera assignment operator. 
	 *
	 * \param camera The Camera to assign to \c this.
	 * \return A reference to \c this to allow for chaining of assignment.
	 */
	const Camera& operator=(const Camera& camera);

};

#endif
