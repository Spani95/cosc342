/* $Rev: 250 $ */
#pragma once

#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "Colour.h"

/** 
 * \file
 * \brief Material class header file.
 */

/**
 * \brief Class defining Material colours and properties.
 *
 * The interaction between light and various sorts of material can be very complex.
 * In this ray tracer, we use a simplified model, which still has several components.
 * A Material for an object has a number of different Colour properties. The observed 
 * Colour of an object comes from the interaction of different types of light and different
 * Material properties:
 * - The ambientLight from the Scene and the Material's ambientColour combine to give a base Colour.
 * - Each light which can be seen from the surface provides a number of components:
 *   - A diffuse component, which follows a Lambertian illumination model and uses the Material's diffuseColour.
 *   - A specular component, which follows a Phong illumination model and uses the Material's specularColour and specularExponent.
 * - Some surfaces create mirror-reflections, which are influenced by the mirrorColour. For example, reflections in a gold surface should appear yellow.
 * Also, not all LightSource objects give white light, and the Colour of an object depends on the interaction between the light and surface colours.
 */
class Material {

public:
	/**
	 * \file
	 * \brief Material default constructor.
	 *
	 * By default
	 */
	Material() : ambientColour(1,1,1), diffuseColour(1,1,1), specularColour(0,0,0), specularExponent(1), mirrorColour(0,0,0) {};

	Colour ambientColour;     //!< Colour of Material under white ambient light. Usually, but not always, the same as diffuseColour.

	Colour diffuseColour;     //!< Colour of Material under direct white light. Usually, but not always, the same as ambientColour.

	Colour specularColour;    //!< Colour of Material's specular highlights. If this is zero then there are no highlights.
	double specularExponent;  //!< 'Hardness' of Material's specular hightlights - high values give small, sharp highlights.

	Colour mirrorColour;      //!< Colour of reflected rays under direct white light. If this is zero then there are no reflections.
};

#endif
