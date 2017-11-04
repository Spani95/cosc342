#pragma once

#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include "Colour.h"
#include "NonCopyable.h"

#include <memory>
#include <string>

/** \file
 *
 * \brief Display class header file.
 */

/**
 * \brief Class to display and save images.
 *
 * The Display class [should provide] a simple method to make images, show them in
 * a window, and save them to a file. This version only writes binary PPM
 * files, and does not do any actual display functions. However, it doesn't
 * require OpenCV, so may be useful to people working outside of the lab environment.
 *
 * Note that Display is NonCopyable, so does not have a copy constructor or
 * assingment operator available. You can, however, create multiple displays..
 */
class Display : private NonCopyable {
public:

    /**
	 * \brief Display constructor.
	 *
	 * A Display is an image associated with a window where it can be shown.
	 * Multple displays can be created, and should normally have different window 
	 * names, but this is not enforced. Two Display objects with the same window
	 * name will function correctly, and will store distinct images. It just won't 
	 * be possible to view them both at the same time.
	 *
	 * \param windowName The (unique) name of the window for this Display.
	 * \param width The width, in pixels, of the image associated with this Display.
	 * \param height The height, in pixels, of the image associated with this Display.
	 * \param colour The initial colour of the image.
	 */
	Display(const std::string& windowName, unsigned int width, unsigned int height, Colour colour);
	/**
	 * \brief Display destructor.
	 *
	 * Display's destructor closes the associated window, and deallocates the image.
	 */
	~Display();

	/**
	 * \brief Set a pixel value.
	 *
	 * Set a pixel value to the specified Colour. Pixels are indexed from (0,0) 
	 * in the top-left corner, with the x-axis running left to right and the 
	 * y-axis running top to bottom.
	 *
	 * Note that this updates the <em>internal</em> image, but not the display
	 * shown in the window. To update the window call refresh().
	 *
	 * \param x The x co-ordinate of the pixel to set.
	 * \param y The y co-ordinate of the pixel to set.
	 * \param colour The Colour to set at (x,y).
	 */
	void set(int x, int y, Colour colour);

	/**
	 * \brief Update the window displaying the image.
	 * 
	 * In the minimal implementation, this does nothing.
	 */
	void refresh() const;
	
	/**
	 * \brief Save an image to file.
	 *
	 * Save the image to an ASCII PNM file. This is a very simple file format.
	 * Note that the file extension is ignored. If you write to \c image.jpg then
	 * it will make a file called \c image.jpg, but that file will contain PNM
	 * data, and not a JPEG image.
	 *
	 * \param filename The file to save to, with an appropriate extension.
	 */
	void save(const std::string& filename) const;
	
	/**
	 * \brief Wait for a specified duration.
	 *
	 * In the minimal implementation, this does nothing.
	 *
	 * \param seconds The number of seconds to wait (fractions allowed).
	 */
	void pause(double seconds) const;

private:

	unsigned int width_;    //!< Width of image in pixels
	unsigned int height_;   //!< Height if image in pixels

	unsigned char *red_;     //!< Internal storage for red values
	unsigned char *green_;   // !< Internal storage for green values
	unsigned char *blue_;    // !< Internal storage for blue values
	std::string windowName_; //!< Title of the window to display the render in.

};

#endif
