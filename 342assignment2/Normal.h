/* $Rev: 250 $ */
#pragma once

#ifndef NORMAL_H_INCLUDED
#define NORMAL_H_INCLUDED

#include "Vector.h"

/** \file
 * \brief Direction class header file.
 */


/**
 * \brief Class for Normal Vectors.
 *
 * A Normal can be seen as either a 3-Vector or a homogeneous 4-Vector.
 * It can also be seen as a special sort of Direction. In this implementation
 * a Normal is stored as a 3-Vector and the Transform class deals with the
 * homogeneous form. Normal is a thin wrapper around Vector, which ensures
 * that the Vector has 3 elements.
 *
 * Having separate types for Point, Direction, and Normal means that it is 
 * possible to distinguish them when passing them to Transform.apply() etc.
 */
class Normal : public Vector {

public:
       /** \brief Normal default constructor. */
	Normal();

	/** \brief Normal X-Y-Z constructor.
	 * 
	 * This creates a Normal Vector with the specified X-, Y-, and Z-components.
	 *
	 * \param x The X-component of the Normal Vector.
	 * \param y The Y-component of the Normal Vector.
	 * \param z The Z-component of the Normal Vector.
	 */	
	Normal(double x, double y, double z);

	/** \brief Normal copy constructor.
	 *
	 * \param normal The Normal to copy to \c this.
	 */
	Normal(const Normal& normal);

	/** \brief Normal from Vector constructor.
	 *
	 * Arithmetic operations on Normal objects use the Vector implementations.
	 * This means that the result is a Vector, and this allows them to be converted to 
	 * Normal objects.
	 *
	 * \param vector The Vector to copy to \c this.
	 */	
	Normal(const Vector& vector);
	
	/** \brief Normal from Matrix constructor.
	 *
	 * Some operations on Normal objects use the Matrix implementations.
	 * This means that the result is a Matrix, and this allows them to be converted to 
	 * Normal objects.
	 *
	 * \param matrix The Matrix to copy to \c this.
	 */	
	Normal(const Matrix& matrix);

};

#endif
