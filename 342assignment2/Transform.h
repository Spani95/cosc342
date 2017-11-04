/* $Rev: 250 $ */
#pragma once

#ifndef RT_TRANSFORM_H_INCLUDED
#define RT_TRANSFORM_H_INCLUDED

#include "Direction.h"
#include "Matrix.h"
#include "Normal.h"
#include "Point.h"
#include "Ray.h"

/** \file 
 * \brief Transform class header file
 */

/**
 * \brief Class for Transform objects.
 *
 * A Transform is essentially a 4x4 matrix which is applied to a Vector represented 
 * in homogeneous form. How the Transform is applied, however, depends on what the
 * Vector represents. This is accounted for by having separate subclasses of Vector
 * for Point, Normal, and Direction representations. The Transform can then be applied
 * to any of these in the correct way. 
 *
 * A Transform is computed through a series of basic transformations, such as scaling
 * or translation. As these are applied, an inverse transformation matrix is also 
 * computed, by applying geometrical reasoning to generate matrix inverses.
 */
class Transform {

public:

	/** \brief Default Transform constructor.
	 * 
	 * Creates a Transform with an identity transformation matrix.
	 */
	Transform();

	/** \brief Transform copy constructor.
	 * 
	 * Creates a Transform with an identity transformation matrix.
	 *
	 * \param transform The Transform to copy to \c this.
	 */
	Transform(const Transform& transform);

	/** \brief Transform destructor. */
	~Transform();

	/** \brief Transform assignment operator. 
	 *
	 * \param transform The Transform to assign to \c this.
	 * \return A reference to \c this to allow for chaining of assignment.
	 */
	Transform& operator=(const Transform& transform);

	/** \brief Apply a transformation to a Point.
	 *
	 * A Point is transformed by applying the transformation matrix to
	 * a homogeneous vector with a 1 in the last co-ordinate.
	 * 
	 * \param point The Point to Transform.
	 * \return The transformed Point.
	 */
	Point apply(const Point& point) const;

	/** \brief Apply a transformation to a Direction.
	 *
	 * A Direction is transformed by applying the transformation matrix to
	 * a homogeneous vector with a 0 in the last co-ordinate. This
	 * prevents translations from being applied to Direction vectors.
	 * 
	 * \param direction The Direction to Transform.
	 * \return The transformed Direction.
	 */
	Direction apply(const Direction& direction) const;
	
	/** \brief Apply a transformation to a Normal.
	 *
	 * A Normal is transformed by applying the <em>transposed inverse</em>
	 * transformation matrix. As with ordinary Direction vectors, the 
	 * homgeneous form is created with a 0 in the last co-ordinate to 
	 * prevent translations from being applied. For discussion on why the
	 * normal transforms with the transposed inverse, see the lecture notes
	 * or <a href="http://tog.acm.org/resources/RTNews/html/rtnews1a.html#art4">Abnormal Normals</a>
	 * by Eric Haines.
	 * 
	 * \param normal The Normal to Transform.
	 * \return The transformed Normal.
	 */
	Normal apply(const Normal& normal) const;

	/** \brief Apply a transformation to a Ray.
	 *
	 * A Ray is a Point and a Direction, and both need to be transformed appropriately.
	 * 
	 * \param ray The Ray to Transform.
	 * \return The transformed Ray.
	 */
	Ray apply(const Ray& ray) const;

	/** \brief Apply an inverse transformation to a Point.
	 *
	 * \param point The Point to Transform.
	 * \return The transformed Point.
	 * \sa Transform::apply(const Point&) const
	 */	
	Point applyInverse(const Point& point) const;
	
	/** \brief Apply an inverse transformation to a Direction.
	 *
	 * \param direction The Direction to Transform.
	 * \return The transformed Direction.
	 * \sa Transform::apply(const Direction&) const
	 */	
	Direction applyInverse(const Direction& direction) const;
	
	/** \brief Apply an inverse transformation to a Normal.
	 *
	 * \param normal The Normal to Transform.
	 * \return The transformed Normal.
	 * \sa Transform::apply(const Normal&) const
	 */	
	Normal applyInverse(const Normal& normal) const;
	
	/** \brief Apply an inverse transformation to a Ray.
	 *
	 * \param ray The Ray to Transform.
	 * \return The transformed Ray.
	 * \sa Transform::apply(const Ray&) const
	 */	
	Ray applyInverse(const Ray& ray) const;

	/** \brief Apply a rotation about the X-axis.
	 *
	 * Rotate by some angle (in degrees) about the X-axis.
	 * Following the right-handed co-ordinate convention, this is a 
	 * rotation from the positive Y-axis towards the positive Z-axis.
	 *
	 * \param rx The rotation in degrees.
	 */
	void rotateX(double rx);

	/** \brief Apply a rotation about the Y-axis.
	 *
	 * Rotate by some angle (in degrees) about the Y-axis.
	 * Following the right-handed co-ordinate convention, this is a 
	 * rotation from the positive Z-axis towards the positive X-axis.
	 *
	 * \param ry The rotation in degrees.
	 */
	void rotateY(double ry);

	/** \brief Apply a rotation about the Z-axis.
	 *
	 * Rotate by some angle (in degrees) about the Z-axis.
	 * Following the right-handed co-ordinate convention, this is a 
	 * rotation from the positive X-axis towards the positive Y-axis.
	 *
	 * \param rz The rotation in degrees.
	 */
	void rotateZ(double rz);

	/** \brief Apply a uniform scaling in all directions.
	 *
	 * Scale by some constant factor in all directions.
	 * If the scaling factor is greater than 1 it represents a magnification.
	 * Scaling factors less than 1 represent a reduction.
	 * Negative scaling factors are valid but cause a reflection as well as a scaling.
	 *
	 * \param s The scaling factor to apply.
	 */
	void scale(double s);

	/** \brief Apply a non-uniform scaling along the axes.
	 *
	 * Scale by different factors in the X-, Y-, and Z-directions.
	 * If a scaling factor is greater than 1 it represents a magnification.
	 * Scaling factors less than 1 represent a reduction.
	 * Negative scaling factors are valid but cause a reflection as well as a scaling.
	 *
	 * \param sx The scaling factor to apply in the X-direction.
	 * \param sy The scaling factor to apply in the Y-direction.
	 * \param sz The scaling factor to apply in the Z-direction.
	 */
	void scale(double sx, double sy, double sz);

	/** \brief Shift along the X-, Y-, and Z-axes.
	 *
	 * Shift by some distance along each of the X-, Y-, and Z- axes.
	 *
	 * \param tx The distance to move in the X-direction.
	 * \param ty The distance to move in the Y-direction.
	 * \param tz The distance to move in the Z-direction.
	 */
	void translate(double tx, double ty, double tz);

	/** \brief Shift along a Direction Vector.
	 *
	 * \param direction The Direction to move along.
	 */
	void translate(const Direction& direction);

private:

	Matrix T_;    //!< The 4x4 homogeneous transformation matrix.
	Matrix Tinv_; //!< The 4x4 inverse transformation matrix.

};

#endif
