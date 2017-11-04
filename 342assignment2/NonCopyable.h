/* $Rev: 250 $ */
#pragma once

#ifndef NON_COPYABLE_H_INCLUDED
#define NON_COPYABLE_H_INCLUDED

/** 
 * \file
 * \brief NonCopyable class header file.
 */

/**
 * \brief NonCopyable class.
 *
 * Sometimes it doesn't make sense for an object to be duplicated. This may be for
 * technical reasons (such as the class representing a limited physical resoruce), 
 * and sometimes for practical reasons (such as the class storing lots of information).
 * In C++ this can be enforced by making the copy constructor and assignment operator
 * private. The NonCopyable class makes this easy and less error prone to do. To make a
 * class NonCopyable, just inherit (privately) from NonCopyable:
 * \code
 *  class MyClassCannotBeCopied: private NonCopyable {
 *    ...
 *  };
 * \endcode
 */
class NonCopyable {
protected:

	/** \brief NonCopyable default constructor. */
	NonCopyable() {}

	/** \brief NonCopyable destructor. */
	~NonCopyable() {}


private:

	/** \brief NonCopyable copy constructor. 
	 * 
	 * Note that there is no implementation for the copy constructor.
	 * You cannot copy construct NonCopyable objects.
	 */
	NonCopyable(const NonCopyable& /**< NOT USED*/);

	/** \brief NonCopyable assignment operator. 
	 * 
	 * Note that there is no implementation for the assignment operator.
	 * You cannot assign NonCopyable objects.
	 *
	 * \return Nothing - you cannot assign NonCopyable objects.
	 */
	NonCopyable& operator=(const NonCopyable& /**< NOT USED*/);

};

#endif
