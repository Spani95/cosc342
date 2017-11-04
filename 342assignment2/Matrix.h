/* $Rev: 250 $ */
#pragma once

#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

/** \file
 * \brief Matrix class header file.
 */

#include <vector>
#include <iostream>

/**
 * \brief Basic class for matrices.
 *
 * This class provides basic matrix operatations (addition, subtraction, multiplication, etc.) as overloaded operators.
 * This is sufficient for COSC432 and the Ray Tracer assignment, but does not include more advanced operations like inverse, or matrix decompositions.
 *
 * The class is designed to be simple and easy to understand rather than hyper-efficient.
 * For production code a more professional library is recommended.
 */
class Matrix {

public:

	/**
	 * \brief Square Matrix constructor
	 *
	 * This constructor creates a square (size x size) matrix.
	 * If no size is provided, it creates a 1 x 1 matrix, and so also provides a default constructor.
	 *
	 * \param size The size of the resulting Matrix.
	 */
	Matrix(size_t size=1);

	/** 
	 * \brief General Matrix constructor
	 *
	 * This constructor creates a matrix of the specified size.
	 * The number of rows and columns is specified and must be postivie integers.
	 *
	 * \param rows The number of rows in the resulting Matrix.
	 * \param cols The number of columns in the resulting Matrix.
	 */
	Matrix(size_t rows, size_t cols);

	/**
	 * \brief Matrix copy constructor.
	 *
	 * This constructor creates a new Matrix which is a copy of an existing one.
	 * The new Matrix has independent storage etc.
	 *
	 * \param mat The Matrix to copy.
	 */
	Matrix(const Matrix& mat);

	/**
	 * \brief Matrix destructor
	 *
	 * The Matrices are based on std::vector, so there's not much to do here, but it is provided for completeness.
	 * Note that this is virtual, since other classes (like Vector) may inherit from Matrix.
	 */
	virtual ~Matrix();

	/**
	 * \brief Matrix assignment operator
	 *
	 * This allows expressions like A = B; where A and B are Matrices.
	 * It also allows chained assignment, like A = B = C;
	 * 
	 * \param mat The Matrix on the right hand side of the assignment.
	 * \return a reference to \c this, to allow chaining of assignment.
	 */
	Matrix& operator=(const Matrix& mat);

	// Handy factory methods

	/**
	 * \brief Factory method for Identity Matrices.
	 *
	 * This returns an Identity Matrix of a given size.
	 * Identity Matrices have ones on the main diagonal, and zeros off the diagonal.
	 * For non-square Matrices, any 'extra' rows or columns are all zero.
	 *
	 * \param rows The number of rows in the resulting Matrix.
	 * \param cols The number of columns in the resulting Matrix.
	 * \return A rows x cols Identity matrix
	 */
	static Matrix identity(size_t rows, size_t cols);

	/**
	 * \brief Factory method for Zero Matrices.
	 *
	 * This returns a Zero Matrix of a given size.
	 * Zero matrices have all entries set to Zero (unsurprisingly).
	 *
	 * \param rows The number of rows in the resulting Matrix.
	 * \param cols The number of columns in the resulting Matrix.
	 * \return A rows x cols Zero Matrix
	 */
	static Matrix zero(size_t rows, size_t cols);

	/**
	 * \brief Matrix element access.
	 *
	 * This method provides access to the elements of a Matrix using the syntax \c A(i,j).
	 * This notation is equivalent to \c A.operator()(i,j).
	 * Since a reference is returned, this can be used for assignment, eg: \c A(1,2)=3.1415;
	 * The values of row and column must be less than the size of the Matrix.
	 *
	 * \param row The row of the Matrix to access.
	 * \param col The column of the Matrix to access.
	 * \return A reference to the requested element of the Matrix.
	 */
	double& operator()(size_t row, size_t col);

	/**
	 * \brief Matrix element access (\c const version).
	 *
	 * This method provides access to the elements of a \c const Matrix using the syntax A(i,j).
	 * Since a const reference is returned, this \b cannot be used for assignment, but it can be applied to \c const Matrices.
	 * The values of row and column must be less than the size of the Matrix.
	 *
	 * \param row The row of the Matrix to access.
	 * \param col The column of the Matrix to access.
	 * \return A \c const reference to the requested element of the Matrix.
	 */
	const double& operator()(size_t row, size_t col) const;

	/**
	 * \brief Number of rows in a Matrix.
	 *
	 * \return The number of rows in the given Matrix.
	 */
	size_t numRows() const;

	/**
	 * \brief Number of columns in a Matrix.
	 *
	 * \return The number of columns in the given Matrix.
	 */
	size_t numCols() const;

	/**
	 * \brief Number of elements in a Matrix.
	 *
	 * \return The number of elements in the given Matrix.
	 */
	size_t numElements() const;

	/**
	 * \brief Unary minus.
	 *
	 * This provides the ability to negate a Matrix.
	 * \c -A is equivalent to \c A.operator-()
	 *
	 * \return A negated version of the Matrix.
	 */
	Matrix operator-() const;

	/**
	 * \brief Matrix addition operator.
	 * 
	 * This performs addition of two Matrices.
	 * The two Matrices must have the same size
	 *
	 * Note that addition is declared as a friend. 
	 * It could be declared as a normal method <tt>Matrix operator+(const Matrix& rhs);</tt>.
	 * The friend form provides a more symmetric view of the two Matrices being added.
	 *
	 * \param lhs The Matrix on the left hand side of the +.
	 * \param rhs The Matrix on the right hand side of the +.
	 * \return The Matrix formed by lhs + rhs.
	 */
	friend Matrix operator+(const Matrix& lhs, const Matrix& rhs);
		
	/**
	 * \brief Matrix addition-assignment operator.
	 * 
	 * This adds a Matrix to an existing one in place.
	 * The two Matrices must have the same size.
	 *
	 * \param mat The Matrix to add to \c this.
	 * \return A reference to the updated \c this, to allow chaining of assignment.
	 */
	Matrix& operator+=(const Matrix& mat);

	/**
	 * \brief Matrix subtraction operator.
	 * 
	 * This performs subtraction of two Matrices.
	 * The two Matrices must have the same size
	 *
	 * Note that subtraction is declared as a friend. 
	 * It could be declared as a normal method <tt>Matrix operator-(const Matrix& rhs);</tt>.
	 * The friend form provides a more symmetric view of the two Matrices being subtracted.
	 *
	 * \param lhs The Matrix on the left hand side of the -.
	 * \param rhs The Matrix on the right hand side of the -.
	 * \return The Matrix formed by lhs - rhs.
	 */
	friend Matrix operator-(const Matrix& lhs, const Matrix& rhs);

	/**
	 * \brief Matrix subtraction-assignment operator.
	 * 
	 * This subtracts a Matrix from an existing one in place.
	 * The two Matrices must have the same size.
	 *
	 * \param mat The Matrix to subtract from \c this.
	 * \return A reference to the updated \c this, to allow chaining of assignment.
	 */
	Matrix& operator-=(const Matrix& mat);

	/**
	 * \brief Matrix-Matrix multiplication operator.
	 * 
	 * This creates the product of two Matrices.
	 * The first Matrix must have the same number of columns as the second Matrix has rows.
	 *
	 * Note that multiplication is declared as a friend. 
	 * It could be declared as a normal method <tt>Matrix operator*(const Matrix& rhs);</tt>.
	 * The friend form provides a more symmetric view of the two Matrices being multiplied.
	 *
	 * \param lhs The Matrix on the left hand side of the *.
	 * \param rhs The Matrix on the right hand side of the *.
	 * \return The Matrix formed by lhs * rhs.
	 */
	friend Matrix operator*(const Matrix& lhs, const Matrix& rhs);

	/**
	 * \brief scalar-Matrix multiplication operator.
	 * 
	 * This creates the product of a scalar and a Matrix.
	 *
	 * Note that multiplication is declared as a friend. 
	 * In this case a normal method <tt>Matrix operator*(const scalar s);</tt> only works for multiplication by a scalar on the right.
	 * 
	 * \param s The scalar value to multiply the Matrix by.
	 * \param mat The Matrix to be scaled.
	 * \return The Matrix formed by s*mat.
	 */
	friend Matrix operator*(double s, const Matrix& mat);
	
	/**
	 * \brief Matrix-scalar multiplication operator.
	 * 
	 * This creates the product of a Matrix and a scalar.
	 *
	 * Note that multiplication is declared as a friend. 
	 * In this case a normal method <tt>Matrix operator*(const scalar s);</tt> only works for multiplication by a scalar on the right.
	 * 
	 * \param mat The Matrix to be scaled.
	 * \param s The scalar value to multiply the Matrix by.
	 * \return The Matrix formed by mat*s.
	 */
	friend Matrix operator*(const Matrix& mat, double s);


	/**
	 * \brief Matrix-scalar multiplication-assignment operator.
	 * 
	 * This scales a Matrix in place.
	 * Note that there is no *= operator defined between two Matrices.
	 * This is because Matrix multiplication is not commutative, so <tt>A*B != B*A</tt> in general.
	 * That makes \c A*=B a little confusing. 
	 * Following C++ convention, this should mean \c A=A*B, but we'll often be multiplying vectors by matrices, and \c a*=B would intuitively mean \c a=B*a.
	 * This is easily avoided by not having \c *= for two Matrices.
	 *
	 * \param s The scalar multiplier to apply to \c this.
	 * \return A reference to the updated \c this, to allow chaining of assignment.
	 */
	Matrix& operator*=(double s);

	/**
	 * \brief Matrix-scalar division operator.
	 * 
	 * This creates the result of a Matrix divided by a scalar.
	 * Division by a scalar, s, is essentially the same as multiplcation (or scaling) by 1/s.
	 * Division by numbers close to 0 will result in \c NaN and \c Inf values and wildly unstable results as normal.
	 *
	 * Note that division is declared as a friend. 
	 * In this case a normal method <tt>Matrix operator/(const scalar s);</tt> would be probably OK, but inconsistent with other operators.
	 * 
	 * \param mat The Matrix to be scaled.
	 * \param s The scalar value to divide the Matrix by.
	 * \return The Matrix formed by mat/s.
	 */
	friend Matrix operator/(const Matrix& mat, double s);

	/**
	 * \brief Matrix-scalar multiplication-assignment operator.
	 * 
	 * This divides a Matrix in place.
	 *
	 * \param s The scalar multiplier to divide \c this by.
	 * \return A reference to the updated \c this, to allow chaining of assignment.
	 */
	Matrix& operator/=(double s);

	/**
	 * \brief Matrix transpose.
	 *
	 * This creates the transpose of a Matrix, which is a new Matrix with the original rows and columns interchanged.
	 *
	 * \return A transposed copy of \c this.
	 */
	Matrix transpose() const;

protected:

	size_t rows_; //!< Number of rows in the Matrix.
	size_t cols_; //!< Number of columns in the Matrix.
	std::vector<double> data_; //!< Storage for Matrix data elements.

};

/**
 * \brief Stream insertion operator.
 *
 * Provides the ability to output Matrices to C++ streams, including \c std::cout and \c filestreams.
 *
 * Note that the stream operators do not require special access to the Matrix internals, so are not members or friends.
 *
 * \param outputStream the stream to send the Matrix to.
 * \param mat the matrix to send to the stream.
 * \return The updated output stream.
 */
std::ostream& operator<<(std::ostream& outputStream, const Matrix& mat);


/**
 * \brief Stream extraction operator.
 *
 * Provides the ability to read Matrices from C++ streams, including \c std::cin and \c filestreams.
 * The size of the Matrix determines how much data is read from the stream.
 *
 * Note that the stream operators do not require special access to the Matrix internals, so are not members or friends.
 *
 * \param inputStream the stream to read the Matrix from.
 * \param mat the matrix to read from the stream.
 * \return The updated input stream.
 */
std::istream& operator>>(std::istream& inputStream, Matrix& mat);

#endif // MATRIX_H_INCLUDED
