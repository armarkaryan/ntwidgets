/*! \file       nlabel.h
 *  \brief      NT Label module (header file).
 *  \details    Contains the NTLabel class definitions for image handling in the NT system.
 *  \author     Arthur Markaryan
 *  \date       09.05.2025
 *  \copyright  Arthur Markaryan
 */

#ifndef _NTLABEL_H_
#define _NTLABEL_H_

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

/*! \class      NTLabel
 *  \brief      Text label class for NT system.
 *  \details    Represents an text label object with position, color attributes and transparency support.
 *  \extends    NTGraphicObject
 */
class NTLabel : public NTGraphicObject
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
	 *	\param		colorPair	Color pair to draw from the palette
	 *	\param		attr		Attr of the text label
	 *	\param      transparent	Transparent flag for the text label
	 */
	NTLabel(NTObject *parent, const std::string& name,
			const std::string& text,
			int x, int y, unsigned char colorPair, chtype attr, bool transparent);

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
	void setText(const std::string& text);

	/*! \brief      Gets the text data
	 *  \return     Constant reference to the text data
	 */
	std::string text() const;

	/*! \brief     Draw the text label
	 *  \return    OK if success,
	 *            ERR_RANGE if out of terminal bounds,
	 *            ERR if other error occurred
	 */
	int draw() override;

private:
	std::string _text;			/*!< Text data */
};

#endif // _NTLABEL_H_
