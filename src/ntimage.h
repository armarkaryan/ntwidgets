/*! \file       ntimage.h
 *  \brief      NT Image module (header file).
 *  \details    Contains the NTImage class definitions for image handling in the NT system.
 *  \author     Arthur Markaryan
 *  \date       11.05.2025
 *  \copyright  Arthur Markaryan
 */

#ifndef _NTIMAGE_H_
#define _NTIMAGE_H_

/*! \brief  Standard vector library */
#include <vector>
/*! \brief  Standard string library */
#include <string>
/*! \brief  File stream operations */
#include <fstream>
/*! \brief  Standard exception handling */
#include <stdexcept>
/*! \brief  Standard algorithms */
#include <algorithm>
/*! \brief  Mutex library */
#include <mutex>

/*!	\brief	ncurses library */
#include <ncurses.h>

/*! \brief  Base NT object */
#include "ntobject.h"

/*! \brief  Base NT graphic object */
#include "ntgraphicobject.h"

/*! \class      NTImage
 *  \brief      Image class for NT system.
 *  \details    Represents an image object with position, color attributes and transparency support.
 *  \extends    NTGraphicObject
 */
class NTImage : public NTGraphicObject
{
public:
	/*! \brief      Default constructor
	 *  \param      parent  Pointer to the parent object (default: nullptr)
	 *  \param      name    Image name (default: empty string)
	 */
	NTImage(NTObject *parent = nullptr, const std::string &name = "");

	/*! \brief      Parameterized constructor
	 *  \param      parent      Pointer to the parent object
	 *  \param      name        Image name
	 *  \param      image       Vector of strings representing image data
	 *  \param      x           X coordinate of the image
	 *  \param      y           Y coordinate of the image
	 *	\param		colorPair	Color pair to draw from the palette
	 *	\param		attr		Attr for the image
	 *	\param      transparent	Transparent flag for the image
	 */
	NTImage(NTObject *parent, const std::string& name,
			const std::vector<std::string>& image,
			int x, int y, unsigned char colorPair, chtype attr, bool transparent);

	/*! \brief  Destructor */
	~NTImage();

	/*! \brief      Copy constructor
	 *  \param      other   Reference to source NTImage object
	 */
	NTImage(const NTImage& other);

	/*! \brief      Assignment operator
	 *  \param      other   Reference to source NTImage object
	 *  \return     Reference to the assigned NTImage object
	 */
	NTImage& operator=(const NTImage& other);

	/*! \brief      Sets the image data
	 *  \param      image   Vector of strings representing the new image data
	 */
	void setImage(const std::vector<std::string>& image);

	/*! \brief      Gets the image data
	 *  \return     Constant reference to the image data vector
	 */
	const std::vector<std::string>& image() const;

	/*! \brief      Sets the image width
	 *  \param      width   New width value
	 */
	void setWidth(unsigned int width);

	/*! \brief      Gets the image width
	 *  \return     Current width value
	 */
	unsigned int width() const;

	/*! \brief      Sets the image height
	 *  \param      height  New height value
	 */
	void setHeight(unsigned int height);

	/*! \brief      Gets the image height
	 *  \return     Current height value
	 */
	unsigned int height() const;

	/*! \brief     Draw the text label
	 *  \return    OK if success,
	 *            ERR_RANGE if out of terminal bounds,
	 *            ERR if other error occurred
	 */
	int draw() override;

private:
	std::vector<std::string> _image;	/*!< Image data storage */
	unsigned short _width;				/*!< Image width */
	unsigned short _height;				/*!< Image height */
};

#endif // _NTIMAGE_H_
