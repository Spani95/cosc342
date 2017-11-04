/* $Rev: 250 $ */
#pragma once

#ifndef PINHOLE_CAMERA_H_INCLUDED
#define PINHOLE_CAMERA_H_INCLUDED

#include "Camera.h"

/** \file
 * \brief PinholeCamera class header file
 */
 
/**
 * \brief PinholeCamera class.
 *
 * PinholeCamera implements a common Camera model that gives ideal perspective
 * projections. The camera is defined by a point (the camera centre) and an image 
 * plane at some distance along the Z-axis (the focal distance). The projection of
 * a 3D point into the image is the intersection of the line from the camera centre 
 * to the 3D point with the image plane.
 */
class PinholeCamera : public Camera {

public:

	/**
	 * \brief PinholeCamera constructor.
	 *
	 * This creates a new PinholeCamera with the camera centre at the origin,
	 * looking along the positive Z-axis. The focal length is provided as 
	 * a parameter (default: 1 unit). The position and orientation of a Camera
	 * can be altered via its transform member.
	 *
	 * \param f The focalLength of the new camera.
	 */
	PinholeCamera(double f = 1);

	/** \brief PinholeCamera copy constructor.
	 *
	 * \param camera The PinholeCamera to copy to \c this.
	 */
	PinholeCamera(const PinholeCamera& camera);

	/** \brief PinholeCamera destructor. */
	~PinholeCamera();

	/** \brief PinholeCamera assignment operator.
	 *
	 * \param camera The PinholeCamera to assign to \c this.
	 * \return A reference to \c this to allow for chaining of assignments.
	 */
	PinholeCamera& operator=(const PinholeCamera& camera);

	/** \brief Generate a ray for a given image plane co-ordinate
	 *
	 * For a untransformed PinholeCamera the ray starts at the origin
	 * and passes through (x, y, focalLength).
	 *
	 * \param x the horizontal location
	 * \param y the vertical location
	 * \return The Ray that passes from the Camera through (x,y) in the image plane.
	 */
	Ray castRay(double x, double y) const;

	double focalLength; //!< The distance from the camera centre to the image plane.

private:


};

#endif
