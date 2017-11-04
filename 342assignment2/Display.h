/* $Rev: 250 $ */
#pragma once

#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include "Colour.h"
#include "NonCopyable.h"

#include <opencv/cv.h>

#include <string>

/** \file
 *
 * \brief Display class header file.
 */

/**
 * \brief Class to display and save images.
 *
 * The Display class provides a simple method to make images, show them in
 * a window, and save them to a file. It is a wrapper around some OpenCV 
 * functions that provides an abstraction that gives just enough functionality
 * for the Ray Tracer.
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
	 * The window displaying the image is not automatically updated when the 
	 * image changes for efficiency reasons. Calling refresh() causes the 
	 * current image to be displayed.
	 */
	void refresh() const;
	
	/**
	 * \brief Save an image to file.
	 *
	 * Images can be saved to files, and the image format is determined by
	 * the file extension. For example, saving to \c render.png would write a 
	 * PNG image, while saving to \c RENDER.JPG would write a JPEG.
	 *
	 * \param filename The file to save to, with an appropriate extension.
	 */
	void save(const std::string& filename) const;
	
	/**
	 * \brief Wait for a specified duration.
	 *
	 * This function pauses the program for a specified duration. The
	 * paused state can be interrupted by pressing any key while the 
	 * window associated with this Display has focus. 
	 *
	 * \param seconds The number of seconds to wait (fractions allowed).
	 */
	void pause(double seconds) const;

private:

	cv::Mat img_; //!< Internal storage of the image to render to.
	std::string windowName_; //!< Title of the window to display the render in.

};

#endif
