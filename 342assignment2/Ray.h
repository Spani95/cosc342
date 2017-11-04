/* $Rev: 250 $ */
#pragma once

#ifndef RAY_H_INCLUDED
#define RAY_H_INCLUDED

#include "Point.h"
#include "Direction.h"

/**
 * \file
 * \brief Ray class header file.
 */

/**
 * \brief Rays as a starting Point and Direction.
 *
 * Unsurprisingly, a Ray is a fundamental concept in ray-tracing.
 * A Ray is defined by the Point at which it starts, and the Direction in which it goes.
 */
class Ray {
public:
	Point point; //!< The starting Point for the Ray.
	Direction direction; //!< The Direction for the Ray.
};

#endif
