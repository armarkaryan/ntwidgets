/*! \file       nlabel.h
 *  \brief      NT Label module (header file).
 *  \details    Contains the NTLabel class definitions for image handling in the NT system.
 *  \author     Arthur Markaryan
 *  \date       09.05.2025
 *  \copyright  Arthur Markaryan
 */

#ifndef NTLABEL_H
#define NTLABEL_H

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

#include <ncurses.h>

/*! \brief  Base NT object */
#include "ntobject.h"

/*! \class      NTLabel
 *  \brief      Text label class for NT system.
 *  \details    Represents an text label object with position, color attributes and transparency support.
 *  \extends    NTObject
 */
class NTLabel : public NTObject
{
public:
	/*! \brief      Default constructor
	 *  \param      parent  Pointer to the parent object (default: nullptr)
	 *  \param      name    Image name (default: empty string)
	 */
	NTLabel(NTObject *parent = nullptr, const std::string &name = "");

	/*! \brief      Parameterized constructor
	 *  \param      parent      Pointer to the parent object
	 *  \param      name        Image name
	 *  \param      text		Text data of the text label
	 *  \param      x           X coordinate of the text label
	 *  \param      y           Y coordinate of the text abel
	 *  \param      color		Text color for the text label
	 *  \param      bgColor		Background color for the text label
	 *	\param      transparent	Transparent flag for the text label
	 */
	NTLabel(NTObject *parent, const std::string& name,
			const std::string& text,
			int x, int y, nt::color color, nt::color bgColor, bool transparent);

	/*! \brief  Destructor */
	~NTLabel();

	/*! \brief      Copy constructor
	 *  \param      other   Reference to source NTLabel object
	 */
	NTLabel(const NTLabel& other);

	/*! \brief      Assignment operator
	 *  \param      other   Reference to source NTLabel object
	 *  \return     Reference to the assigned NTLabel object
	 */
	NTLabel& operator=(const NTLabel& other);

	/*! \brief      Sets the text data
	 *  \param      text   Representing the new text data
	 */
	void setText(const std::string& image);

	/*! \brief      Gets the text data
	 *  \return     Constant reference to the text data
	 */
	std::string& text() const;

	/*! \brief      Sets the X coordinate
	 *  \param      x   New X coordinate value
	 */
	void setx(int x);

	/*! \brief      Gets the X coordinate
	 *  \return     Current X coordinate value
	 */
	int x() const;

	/*! \brief      Sets the Y coordinate
	 *  \param      y   New Y coordinate value
	 */
	void sety(int y);

	/*! \brief      Gets the Y coordinate
	 *  \return     Current Y coordinate value
	 */
	int y() const;

	/*! \brief      Sets the text color
	 *  \param      color   New text color value
	 */
	void setColor(nt::color color);

	/*! \brief      Gets the text color
	 *  \return     Current text color value
	 */
	nt::color color() const;

	/*! \brief      Sets the background color
	 *  \param      color   New background color value
	 */
	void setBgColor(nt::color bgColor);

	/*! \brief      Gets the background color
	 *  \return     Current background color value
	 */
	nt::color bgColor() const;

	/*! \brief      Sets the transparency flag
	 *  \param      transparent New transparency value
	 */
	void setTransparent(bool transparent);

	/*! \brief      Gets the image transparency flag
	 *  \return     true if transparent false otherwise
	 */
	bool isTransparent() const;

	bool isChanged() const {return _changed; };

	/*! \brief     Draw the text label
	 *  \return    ?? true if transparent false otherwise
	 */
	void draw();

private:
	std::string _text;		/*!< Image data storage */
	unsigned short _x;		/*!< X coordinate */
	unsigned short _y;		/*!< Y coordinate */
	nt::color _color;		/*!< Text Color */
	nt::color _bgColor;		/*!< Background Color */
	bool _transparent;		/*!< Transparency flag */
	bool _changed;			/*!< Label changed flag */
};

#endif // NTLABEL_H
