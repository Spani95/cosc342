/* $Rev: 250 $ */
#pragma once

#ifndef COLOUR_H_INCLUDED
#define COLOUR_H_INCLUDED
/**
 * \file 
 * \brief Colour class header file.
 */

/**
 * \brief Class to store colour information.
 *
 * Colours are an important aspect of Material objects, and the 
 * basic quanitity that a ray tracer comptues for a ray. Colours
 * are represented as RGB triples, with values in the range [0,1].
 * Note that during computation, Colour values may go outside of the
 * range [0,1]. Because of this, these bounds are not enforced. However
 * Colours can be brought back into this range with the clip() method.
 *
 * Colour objects also have basic arithmetic operators defined on them.
 * These are applied independently to each component. This is an important
 * distinction from Vector and Matrix objects, which have particular rules
 * for arithmetic (particularly multiplication).
 */
class Colour {

public:

    /** \brief Colour default constructor.
	 * 
	 * Creates a new colour with all values set to 0 (black).
	 */
	Colour();


	/** \brief Colour constructor.
	 * 
	 * Creates a new colour with the given red, green, and blue values.
	 *
	 * \param r The red value of the new Colour.
	 * \param g The green value of the new Colour.
	 * \param b The blue value of the new Colour.
	 */
	Colour(double r, double g, double b);


	/** \brief Colour copy constructor.
	 *
	 * \param colour The Colour to copy.
	 */
	Colour(const Colour& colour);

	/** \brief Colour destructor. */
	~Colour();

	/** \brief Colour assignment operator.
	 *
	 * \param colour The Colour to assign to \c this.
	 * \return A reference to \c this to allow for chaining of assignment.
	 */
	Colour& operator=(const Colour& colour);

	/** \brief Colour unary negation.
	 * 
	 * Given a Colour (R, G, B), the negated Colour is (-R, -G, -B).
	 *
	 * \return The negated Colour.
	 */
	Colour operator-() const;

	/** \brief Colour addition.
	 * 
	 * Given two Colours, (R1, G1, B1) and (R2, G2, B2), their sum is (R1+R2, G1+G2, B1+B2).
	 *
	 * \param lhs The Colour on the left hand side of the + operator.
	 * \param rhs The Colour on the right hand side of the + operator.
	 * \return The sum of lhs and rhs.
	 */
	friend Colour operator+(const Colour& lhs, const Colour& rhs);

	/** \brief Colour addition-assignment operator
	 * 
	 * Add one Colour to another in place.
	 *
	 * \param colour The Colour to add to \c this.
	 * \return A reference to the updated \c this, to allow chaining of assignment.
	 */
	Colour& operator+=(const Colour& colour);

	/** \brief Colour subtraction.
	 * 
	 * Given two Colours, (R1, G1, B1) and (R2, G2, B2), their difference is (R1-R2, G1-G2, B1-B2).
	 *
	 * \param lhs The Colour on the left hand side of the - operator.
	 * \param rhs The Colour on the right hand side of the - operator.
	 * \return The difference between lhs and rhs.
	 */
	friend Colour operator-(const Colour& lhs, const Colour& rhs);

	/** \brief Colour subtraction-assignment operator
	 * 
	 * Subtract one Colour from another in place.
	 *
	 * \param colour The Colour to subtract from \c this.
	 * \return A reference to the updated \c this, to allow chaining of assignment.
	 */
	Colour& operator-=(const Colour& colour);


	/** \brief Colour multiplication.
	 * 
	 * Given two Colours, (R1, G1, B1) and (R2, G2, B2), their product is (R1*R2, G1*G2, B1*B2).
	 * Note that this is different from the usual Vector dot and cross products.
	 *
	 * \param lhs The Colour on the left hand side of the * operator.
	 * \param rhs The Colour on the right hand side of the * operator.
	 * \return The product of lhs and rhs.
	 */
	friend Colour operator*(const Colour& lhs, const Colour& rhs);

	/** \brief Colour multiplication-assignment operator
	 * 
	 * Multiply one Colour by another in place.
	 *
	 * \param colour The Colour to multiply \c this by.
	 * \return A reference to the updated \c this, to allow chaining of assignment.
	 */
	Colour& operator*=(const Colour& colour);
	
	/** \brief Scalar-Colour multiplication.
	 * 
	 * The product of a Colour, (R, G, B) and a scalar, s, is (s*R, s*G, s*B).
	 *
	 * \param s The scalar on the left hand side of the * operator.
	 * \param colour The Colour on the right hand side of the * operator.
	 * \return The product of lhs and rhs.
	 */
	friend Colour operator*(double s, const Colour& colour);

	/** \brief Colour-scalar multiplication.
	 * 
	 * The product of a Colour, (R, G, B) and a scalar, s, is (s*R, s*G, s*B).
	 *
	 * \param colour The Colour on the left hand side of the * operator.
	 * \param s The scalar on the right hand side of the * operator.
	 * \return The product of lhs and rhs.
	 */
	friend Colour operator*(const Colour& colour, double s);

	/** \brief Colour-scalar multiplication-assignment operator
	 * 
	 * Multiply a Colour by a scalar in place.
	 *
	 * \param s The scalar to multiply \c this by.
	 * \return A reference to the updated \c this, to allow chaining of assignment.
	 */
	Colour& operator*=(double s);

	/** \brief Colour-scalar division.
	 * 
	 * The division of a Colour, (R, G, B) by a scalar, s, is (R/s, G/s, B/s).
	 *
	 * \param colour The Colour on the left hand side of the / operator.
	 * \param s The scalar on the right hand side of the / operator.
	 * \return The division of lhs by rhs.
	 */
	friend Colour operator/(const Colour& colour, double s);
	
	/** \brief Colour-scalar division-assignment operator
	 * 
	 * Divide a Colour by a scalar in place.
	 *
	 * \param s The scalar to divide \c this by.
	 * \return A reference to the updated \c this, to allow chaining of assignment.
	 */
	Colour& operator/=(double s);

	/** \brief Enforce bounds on Colour components.
	 *
	 * Colour component values should lie in the range [0,1], but during computation
	 * it is sometimes valid for values to lie outside this range. This method clips
	 * values to this range by simple truncation.
	 */
	void clip();

	double red;   //!< The red component of the Colour.
	double green; //!< The green component of the Colour.
	double blue;  //!< The blue component of the Colour.
	
};

#endif
