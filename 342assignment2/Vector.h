/* $Rev: 250 $ */
#pragma once

#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

/** \file
 * \brief Vector class header file.
 */

#include "Matrix.h"

/**
 * \brief Basic class for vectors.
 *
 * A Vector is a Matrix with exactly one column, and in many cases can be dealt with as such.
 * However, having a separate Vector class means that we can implement Vector-specific behaviour like dot and cross products.
 * Since all Vectors are Matrices, Vector is a subclass of Matrix.
 *
 * Many Matrix operations (such as + and *) are overloaded in cases when a Vector is gauranteed to be the result.
 * Thus Matrix*Vector is overloaded (it is always a Vector), but Vector*Matrix is not - we can just use Matrix*Matrix for that.
 * Most of these just call the Matrix equivalents, so this provides some convenience at the cost of a layer of redirecton.
 * 
 * Note that a Vector as a mathematical object, is quite distinct from a std:vector, which is essentially an array. 
 */
class Vector : public Matrix {

public:

	/**
	 * \brief Vector constructor
	 *
	 * This constructor creates a Vector of the specified size.
	 * If no size is provided, it creates a 1-Vector, and so also provides a default constructor.
	 *
	 * \param size The size of the resulting Vector.
	 */
	Vector(size_t size = 1);

	
	/**
	 * \brief Vector copy constructor.
	 *
	 * This constructor creates a new Vector which is a copy of an existing one.
	 * The new Vector has independent storage etc.
	 *
	 * \param vec The Vector to copy.
	 */
	Vector(const Vector& vec);
	
	/**
	 * \brief Vector from Matrix constructor.
	 *
	 * This constructor creates a new Vector which is a copy of an existing Matrix.
	 * The Matrix must have exactly one column.
	 * This form allows us to turn a Matrix into a Vector when needed.
	 *
	 * \param mat The Matrix to copy.
	 */
	Vector(const Matrix& mat);


	/**
	 * \brief Vector destructor
	 *
	 * As with Matrices, there's not a lot to do here.
	 * The destructor is \c virtual in case we want to make subclasses of Vector (like Point or Normal)
	 */
	virtual ~Vector();

	/**
	 * \brief Vector assignment operator
	 *
	 * This allows expressions like u = v; where u and v are Vectors.
	 * It also allows chained assignment, like u = v = w;
	 * 
	 * \param vec The Vector on the right hand side of the assignment.
	 * \return a reference to \c this, to allow chaining of assignment.
	 */
	Vector& operator=(const Vector& vec);

	/**
	 * \brief Vector element access.
	 *
	 * This method provides access to the elements of a Vector using the syntax \c v(i).
	 * This notation is equivalent to \c v.operator()(i).
	 * Since a reference is returned, this can be used for assignment, eg: \c v(1)=3.1415;
	 * The value of \c ix must less than the size of the Vector.
	 *
	 * \param ix The element of the Vector to access.
	 * \return A reference to the requested element of the Vector.
	 */
	double& operator()(size_t ix);

	/**
	 * \brief Vector element access (\c const version).
	 *
	 * This method provides access to the elements of a Vector using the syntax \c v(i).
	 * Since a const reference is returned, this \b cannot be used for assignment, but it can be applied to \c const Vector.
	 * The value of \c ix must less than the size of the Vector.
	 *
	 * \param ix The element of the Vector to access.
	 * \return A \c const reference to the requested element of the Vector.
	 */
	const double& operator()(size_t ix) const;

	/**
	 * \brief Unary minus.
	 *
	 * This provides the ability to negate a Vector.
	 * \c -v is equivalent to \c v.operator-()
	 *
	 * \return A negated version of the Vector.
	 */
	Vector operator-() const;

	/**
	 * \brief Vector addition operator.
	 * 
	 * This performs addition of two Vectors.
	 * The two Vectors must have the same size
	 *
	 * Note that addition is declared as a friend. 
	 * It could be declared as a normal method <tt>Vector operator+(const Vector& rhs);</tt>.
	 * The friend form provides a more symmetric view of the two Matrices being added.
	 *
	 * \param lhs The Vector on the left hand side of the +.
	 * \param rhs The Vector on the right hand side of the +.
	 * \return The Matrix formed by lhs + rhs.
	 */
	friend Vector operator+(const Vector& lhs, const Vector& rhs);
	
	/**
	 * \brief Vector addition-assignment operator.
	 * 
	 * This adds a Vector to an existing one in place.
	 * The two Vectors must have the same size.
	 *
	 * \param vec The Vector to add to \c this.
	 * \return A reference to the updated \c this, to allow chaining of assignment.
	 */
	Vector& operator+=(const Vector& vec);

	/**
	 * \brief Vector subtraction operator.
	 * 
	 * This performs subtraction of two Vectors.
	 * The two Vectors must have the same size
	 *
	 * Note that subtraction is declared as a friend. 
	 * It could be declared as a normal method <tt>Vector operator-(const Vector& rhs);</tt>.
	 * The friend form provides a more symmetric view of the two Vectors being subtracted.
	 *
	 * \param lhs The Vector on the left hand side of the -.
	 * \param rhs The Vector on the right hand side of the -.
	 * \return The Matrix formed by lhs - rhs.
	 */
	friend Vector operator-(const Vector& lhs, const Vector& rhs);
	
	/**
	 * \brief Vector subtraction-assignment operator.
	 * 
	 * This subtracts a Vector from an existing one in place.
	 * The two Vectors must have the same size.
	 *
	 * \param vec The Vector to subtract from \c this.
	 * \return A reference to the updated \c this, to allow chaining of assignment.
	 */
	Vector& operator-=(const Vector& vec);

	/**
	 * \brief scalar-Vector multiplication operator.
	 * 
	 * This creates the product of a scalar and a Vector.
	 *
	 * Note that multiplication is declared as a friend. 
	 * In this case a normal method <tt>Vector operator*(const scalar s);</tt> only works for multiplication by a scalar on the right.
	 * 
	 * \param s The scalar value to multiply the Matrix by.
	 * \param vec The Vector to be scaled.
	 * \return The Vector formed by s*vec.
	 */
	friend Vector operator*(double s, const Vector& vec);
	
	/**
	 * \brief scalar-Vector multiplication operator.
	 * 
	 * This creates the product of a Vector and a scalar.
	 *
	 * Note that multiplication is declared as a friend. 
	 * In this case a normal method <tt>Vector operator*(const scalar s);</tt> only works for multiplication by a scalar on the right.
	 * 
	 * \param vec The Vector to be scaled.
	 * \param s The scalar value to multiply the Matrix by.
	 * \return The Vector formed by vec*s.
	 */
	friend Vector operator*(const Vector& vec, double s);
	
	/**
	 * \brief Vector-scalar multiplication-assignment operator.
	 * 
	 * This scales a Vector in place.
	 *
	 * \param s The scalar multiplier to apply to \c this.
	 * \return A reference to the updated \c this, to allow chaining of assignment.
	 */
	Vector& operator*=(double s);

	/**
	 * \brief Vector-scalar division operator.
	 * 
	 * This creates the result of a Vector divided by a scalar.
	 * Division by a scalar, s, is essentially the same as multiplcation (or scaling) by 1/s.
	 * Division by numbers close to 0 will result in \c NaN and \c Inf values and wildly unstable results as normal.
	 *
	 * Note that division is declared as a friend. 
	 * In this case a normal method <tt>Vector operator/(const scalar s);</tt> would be probably OK, but inconsistent with other operators.
	 * 
	 * \param vec The Vector to be scaled.
	 * \param s The scalar value to divide the Matrix by.
	 * \return The Vector formed by vec/s.
	 */
	friend Vector operator/(const Vector& vec, double s);

	/**
	 * \brief Vector-scalar multiplication-assignment operator.
	 * 
	 * This divides a Vector in place.
	 *
	 * \param s The scalar multiplier to divide \c this by.
	 * \return A reference to the updated \c this, to allow chaining of assignment.
	 */
	Vector& operator/=(double s);

	/**
	 * \brief Vector dot product.
	 *
	 * This computes the dot product of two vectors, \c u.dot(v).
	 * The two Vectors must have the same size.
	 *
	 * \param vec The Vector to take the dot product with.
	 * \return The dot product of vec and \c this
	 */
	double dot(const Vector& vec) const;


	/**
	 * \brief Vector cross product.
	 *
	 * This computes the cross product of two vectors, \c u.cross(v).
	 * The Vectors must both be 3-vectors.
	 *
	 * \param vec The Vector to take the cross product with.
	 * \return The cross product of \c this and vec.
	 */
	Vector cross(const Vector& vec) const;

	/**
	 * \brief Vector norm.
	 *
	 * This computes the norm or length of a Vector.
	 * Technically, this is the L2- or Euclidean norm.
	 * Other norms exist, but this is the one that is concerns us most of the time.
	 *
	 * \return The norm (length) of of \c this.
	 */
	double norm() const;

	/**
	 * \brief SquaredVector norm.
	 *
	 * This computes the squared norm or length of a Vector.
	 * Technically, this is the squared L2- or Euclidean norm.
	 * Other norms exist, but this is the one that is concerns us most of the time.
	 *
	 * Computing the squared norm (rather than the norm itself) is often sufficient for a task (eg: to see which of two Vectors is shorter), and avoids a \c sqrt operation.
	 * 
	 * \return The norm (length) of of \c this.
	 */
	double squaredNorm() const;
	
};

#endif // VECTOR_H_INCLUDED
