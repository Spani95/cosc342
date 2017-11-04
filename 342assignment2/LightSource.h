/* $Rev: 250 $ */
#pragma once

#ifndef LIGHT_SOURCE_H_INCLUDED
#define LIGTH_SOURCE_H_INCLUDED

#include "Colour.h"
#include "Point.h"

/**
 * \file 
 * \brief LightSource class header file.
 */

/**
 * \brief Abstract base class for LightSources.
 *
 * LightSources provide illumination to the scene. They are defined by their
 * getIntensityAt() function, which determines how much light reaches a particular Point,
 * their Colour, and the Point at which they are located.
 *
 * As an abstract base class, you cannot create a LightSource directly.
 * Instead one of its concrete subclasses must be created.
 */
class LightSource {

public:

	Colour colour; //!< The amount and Colour of light emitted by this LightSource.

	/** \brief Determine how much light reaches a Point.
	 *
	 * The amount of light emitted by a LightSource is determined by its colour property,
	 * but this generally varies across the Scene. This method returns a scaling factor to
	 * apply to the colour of the light at a given Point in the Scene.
	 *
	 * \param point The Point at which light is measured.
	 * \return The proportion of the base illumination that reaches the Point.
	 */
	virtual double getIntensityAt(const Point& point) const = 0;
	
	Point location; //!< The location of this LightSource.

protected:

	/** \brief LightSource default constructor.
	 *
	 * By default light sources are at the origin, and emit white light with a basic intensity of 1.
	 */
	LightSource();
	
	/** \brief LightSource copy constructor. 
	 *
	 * \param lightSource The LightSource to copy.
	 */
	LightSource(const LightSource& lightSource);
	
	/** \brief LightSource destructor. */
	virtual ~LightSource();
	
	/** \brief LightSource assignment operator. 
	 *
	 * \param lightSource The LightSource to assign to \c this.
	 * \return A reference to \c this to allow for chaining of assignment.
	 */
	const LightSource& operator=(const LightSource& lightSource);


};

#endif
