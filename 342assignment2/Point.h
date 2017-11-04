/* $Rev: 250 $ */
#pragma once

#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include "Vector.h"

/** \file
 * \brief Point class header file.
 */

/** \brief Class for Point Vectors.
 *
 * A Point can be seen as either a 3-Vector or a homogeneous 4-Vector.
 * In this implementation a Point is a 3-Vector, and the Transform 
 * class deals with the homogeneous form. Point is essentially a thin
 * wrapper around Vector, which ensures that the Vector has 3 elements.
 *
 * Having separate types for Point, Direction, and Normal, means that 
 * it is possible to distinguish them when passing them to  Transform.apply() etc.
 */
class Point : public Vector {

public:
	/** \brief Point default constructor. */
	Point();

	/** \brief Point X-Y-Z constructor.
	 * 
	 * This creates a Point Vector with the specified X-, Y-, and Z-components.
	 *
	 * \param x The X-component of the Point Vector.
	 * \param y The Y-component of the Point Vector.
	 * \param z The Z-component of the Point Vector.
	 */
	Point(double x, double y, double z);
	
	/** \brief Point copy constructor.
	 *
	 * \param point The Point to copy to \c this.
	 */
	Point(const Point& point);
	
	/** \brief Point from Vector constructor.
	 *
	 * Arithmetic operations on Point objects use the Vector implementations.
	 * This means that the result is a Vector, and this allows them to be converted to 
	 * Point objects.
	 *
	 * \param vector The Vector to copy to \c this.
	 */
	Point(const Vector& vector);
	
	/** \brief Point from Matrix constructor.
	 *
	 * Some operations on Point objects use the Matrix implementations.
	 * This means that the result is a Matrix, and this allows them to be converted to 
	 * Point objects.
	 *
	 * \param matrix The Matrix to copy to \c this.
	 */
	Point(const Matrix& matrix);

};

#endif
