/* $Rev: 250 $ */
/** \file
 * \brief Matrix class implementation file.
 */

#include "Matrix.h"

#include <assert.h>

// Construction, destruction, assignment

// Square/default constructor
Matrix::Matrix(size_t size) : 
	rows_(size), 
	cols_(size), 
	data_(size*size) {
		assert(size > 0);
	}

// General constructor
Matrix::Matrix(size_t rows, size_t cols) : 
	rows_(rows), 
	cols_(cols), 
	data_(rows*cols) {
		assert(rows > 0 && cols > 0);
	}

// Copy constructor
Matrix::Matrix(const Matrix& mat) : 
	rows_(mat.rows_),
	cols_(mat.cols_),
	data_(mat.data_) {
		
	}

// Destructor
Matrix::~Matrix() {
	// Nothing to do here - std::vectors take care of themselves
}

// Assignment operator
Matrix& Matrix::operator=(const Matrix& mat) {
	
	// Check for self assignment - A = A shouldn't do anything
	if (this != &mat) {
		rows_ = mat.rows_;
		cols_ = mat.cols_;
		data_ = mat.data_;
	}

	// Return a reference to this, to allow A = B = C; to work as expected
	return *this;
}


// Handy factory methods

// Create an identity matrix
Matrix Matrix::identity(size_t rows, size_t cols) {
	assert(rows > 0 && cols > 0);
	Matrix I(rows, cols);
	std::fill(I.data_.begin(), I.data_.end(), 0);
	for (size_t i = 0; i < std::min(rows, cols); ++i) {
		I(i,i) = 1;
	}
	return I;
}

// Create a matrix of all zeros
Matrix Matrix::zero(size_t rows, size_t cols) {
	assert(rows > 0 && cols > 0);
	Matrix Z(rows, cols);
	// Technically not needed, since std::vector default initialises to 0. 
	// However, best to be safe in case implementation details change
	std::fill(Z.data_.begin(), Z.data_.end(), 0);
	return Z;
}

// Data access

// Matrix element access
double& Matrix::operator()(size_t row, size_t col) {
	assert(row < rows_ && col < cols_);
	return data_[col*rows_ + row];
}

// Matrix element access (const version)
const double& Matrix::operator()(size_t row, size_t col ) const {
	assert(row < rows_ && col < cols_);
	return data_[col*rows_ + row];
}

// Number of rows in a Matrix
size_t Matrix::numRows() const {
	return rows_;
}

// Number of columns in a Matrix
size_t Matrix::numCols() const {
	return cols_;
}

// Number of elements in a Matrix
size_t Matrix::numElements() const {
	return rows_*cols_;
}

// Arithmetic operators

// Unary minus
Matrix Matrix::operator-() const {
	Matrix result(this->rows_, this->cols_);
	for (size_t i = 0; i < data_.size(); ++i) {
		result.data_[i] = -this->data_[i];
	}
	return result;
}

// Matrix addition operator
Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
	// Note that defining + in terms of += ensures that they are consistent
	return Matrix(lhs) += rhs;
}

// Matrix addtion-assignment operator
Matrix& Matrix::operator+=(const Matrix& mat) {
	assert(rows_ == mat.rows_ && cols_ == mat.cols_);

	for (size_t i = 0; i < data_.size(); ++i) {
		data_[i] += mat.data_[i];
	}

	return *this;
}

// Subtraction: A = B-C, and assignment verison: A -= B
Matrix operator-(const Matrix& lhs, const Matrix& rhs) {
	return Matrix(lhs) -= rhs;
}

Matrix& Matrix::operator-=(const Matrix& mat) {
	assert(rows_ == mat.rows_ && cols_ == mat.cols_);

	for (size_t i = 0; i < data_.size(); ++i) {
		data_[i] -= mat.data_[i];
	}
	
	return *this;
}

// Matrix multiplication: A = B*C and assignment version: A *= B
Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
	assert(lhs.cols_ == rhs.rows_);
		
	Matrix result(lhs.rows_, rhs.cols_);

	for (size_t r = 0; r < result.rows_; ++r) {
		for (size_t c = 0; c < result.cols_; ++c) {
			result(r,c) = 0;
			for (size_t i = 0; i < lhs.cols_; ++i) {
				result(r,c) += lhs(r,i)*rhs(i,c);
			}
		}
	}

	return result;
}

// Scalar multiplication: A = s*B, A = B*s, and assignment version: A *= s
Matrix operator*(double s, const Matrix& mat) {
	return Matrix(mat) *= s;
}

Matrix operator*(const Matrix& mat, double s) {
	return Matrix(mat) *= s;
}

Matrix& Matrix::operator*=(double s) {
	for (size_t i = 0; i < data_.size(); ++i) {
		data_[i] *= s;
	}

	return *this;
}

// Scalar division: A = B/s, and assignment version: A /= s
Matrix operator/(const Matrix& mat, double s) {
	return Matrix(mat)/=s;
}

Matrix& Matrix::operator/=(double s) {
	for (size_t i = 0; i < data_.size(); ++i) {
		data_[i] /= s;
	}
	return *this;
}

// Matrix transpose
Matrix Matrix::transpose() const {
	Matrix result(cols_, rows_);
	for (size_t r = 0; r < rows_; ++r) {
		for (size_t c = 0; c < cols_; ++c) {
			result(c,r) = operator()(r,c);
		}
	}

	return result;
}

std::ostream& operator<<(std::ostream& outputStream, const Matrix& mat) {
	for (size_t r = 0; r < mat.numRows(); ++r) {
		for (size_t c = 0; c < mat.numCols(); ++c) {
			if (c > 0) {
				outputStream << "\t";
			}
			outputStream << mat(r,c);
		}
		outputStream << std::endl;
	}
	return outputStream;
}

std::istream& operator>>(std::istream& inputStream, Matrix& mat) {
	for (size_t r = 0; r < mat.numRows(); ++r) {
		for (size_t c = 0; c < mat.numCols(); ++c) {
			inputStream >> mat(r,c);
		}
	}
	return inputStream;
}
