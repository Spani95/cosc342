/* $Rev: 250 $ */
#pragma once

#ifndef DIRECTION_H_INCLUDED
#define DIRECTION_H_INCLUDED

#include "Vector.h"

/** \file
 * \brief Direction class header file.
 */

/** \brief Class for Direction Vectors.
 *
 * A Direction can be seen as either a 3-Vector or a homogeneous 4-Vector.
 * In this implementation a Direction is a 3-Vector, and the Transform 
 * class deals with the homogeneous form. Direction is essentially a thin
 * wrapper around Vector, which ensures that the Vector has 3 elements.
 *
 * Having separate types for Point, Direction, and Normal, means that 
 * it is possible to distinguish them when passing them to  Transform.apply() etc.
 */
class Direction : public Vector {

public:

    /** \brief Direction default constructor. */
	Direction();
	
	/** \brief Direction X-Y-Z constructor.
	 * 
	 * This creates a Direction Vector with the specified X-, Y-, and Z-components.
	 *
	 * \param x The X-component of the Direction Vector.
	 * \param y The Y-component of the Direction Vector.
	 * \param z The Z-component of the Direction Vector.
	 */
	Direction(double x, double y, double z);

	/** \brief Direction copy constructor.
	 *
	 * \param direction The Direction to copy to \c this.
	 */
	Direction(const Direction& direction);

	/** \brief Direction from Vector constructor.
	 *
	 * Arithmetic operations on Direction objects use the Vector implementations.
	 * This means that the result is a Vector, and this allows them to be converted to 
	 * Direction objects.
	 *
	 * \param vector The Vector to copy to \c this.
	 */
	Direction(const Vector& vector);

	/** \brief Direction from Matrix constructor.
	 *
	 * Some operations on Direction objects use the Matrix implementations.
	 * This means that the result is a Matrix, and this allows them to be converted to 
	 * Direction objects.
	 *
	 * \param matrix The Matrix to copy to \c this.
	 */
	Direction(const Matrix& matrix);

};

#endif
