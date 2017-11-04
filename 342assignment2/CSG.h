/* $Rev: 250 $ */
#pragma once

#ifndef CSG_H_INCLUDED
#define CSG_H_INCLUDED

#include "Object.h"
#include "Sphere.h"

/** 
 * \file
 * \brief CSG class header file.
 */

enum csg_state {OUTSIDE, BORDER, INSIDE};

/**
 * \brief Class for CSG objects.
 * 
 * This class provides an Object which is a CSG tree with two children
 * and a type of CSG operation to perform (union, intersection, etc.).
 * 
 */
class CSG : public Object {

	std::string csgType;
  
 public:

	std::shared_ptr<Object> left;
	std::shared_ptr<Object> right;

	/** \brief CSG default constructor.
	 * 
	 * A newly constructed CSG with two child objects
	 */
	CSG();

	/** \brief CSG copy constructor.      
	 * \param csg The CSG to copy.
	 */
	CSG(const CSG& csg);
	
	/** \brief CSG destructor. */
	~CSG();
	
	/** \brief CSG assignment operator.
	 *
	 * \param csg The CSG to assign to \c this.
	 * \return A reference to \c this to allow for chaining of assignment.
	 */
	const CSG& operator=(const CSG& csg);
	
	/** \brief CSG-Ray csg computation.
	 *
	 * \todo This method does not have an valid implementation for
	 * the CSG operations. It needs to be completed. There are
	 * four TODO marks in CSG.cpp where you will need to add code.
	 *
	 * CSG combines two objects into one, using some boolean
	 * operation, such as union, intersection, or
	 * difference. (Note that either or both of these child
	 * objects may itself be a CSG node.)
	 *
	 * This CSG implementation traces the given ray through each
	 * of its child objects in turn. Every intersection will
	 * indicate where the ray passes through the border of the
	 * object and flips between being inside or outside of that
	 * object. By sorting and then merging the lists of
	 * intersections from each of the two child objects, it can be
	 * determined which intersections represent an actual hitpoint
	 * on the overall CSG object.
	 *
	 * \param ray The Ray to intersect with this (CSG) CSG.
	 * \return A list (std::vector) of intersections, which may be empty.
	 *
	 */
	std::vector<RayIntersection> intersect(const Ray& ray) const;

	/** \brief Configure CSG table
	 *
	 * \param csgType A string name of the CSG node type ("UNION", etc.)
	 */	
	void setupCSG(std::string csgType);
};

#endif // CSG_H_INCLUDED
