/* $Rev: 250 $ */
#pragma once

#ifndef POINT_LIGHT_SOURCE_H_INCLUDED
#define POINT_LIGHT_SOURCE_H_INCLUDED

#include "LightSource.h"

/**
 * \file 
 * \brief PointLightSource class header file.
 */

/**
 * \brief Light emitted from a Point.
 *
 * A PointLightSource represents light emitted from a point in the Scene.
 * The amount of light that reaches any given part of the scene follows
 * a \f$1/r^2\f$ law, so more distant Objects receive less illumination.
 */
class PointLightSource : public LightSource {

public:

	/** \brief PointLightSource default constructor. 
	 *
	 * This creates a white light source at the origin that has intensity 1 at distance 1.
	 **/
	PointLightSource();


	/** \brief PointLightSource copy constructor. 
	 *
	 * \param lightSource The PointLightSource to copy to \c this.
	 **/
	PointLightSource(const PointLightSource& lightSource);
	
	/** \brief PointLightSource destructor */
	~PointLightSource();
	
	/** \brief PointLightSource assignment operator.
	 *
	 * \param lightSource The PointLightSource to copy to \c this.
	 * \return A reference to \c this to allow for chaining of assignment.
	 **/
	const PointLightSource& operator=(const PointLightSource& lightSource);

	/** \brief Determine how much light reaches a Point.
	 *
	 * The colour property determines the basic amount of light emitted by a 
	 * PointLightSource. This is the illumination received at distance 1 from 
	 * the origin, but it will appear brighter or darker if the illuminated
	 * Point is closer or further away. The amount of light received by a Point
	 * is scaled by \f$1/d^2\f$, where \f$d\f$ is the distance between the Point
	 * and the PointLightSource.
	 *
	 * \param point The Point at which light is measured.
	 * \return The proportion of the base illumination that reaches the Point.
	 */
	double getIntensityAt(const Point& point) const;

};

#endif
