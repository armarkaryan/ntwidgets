/*! \file       nlgraphicobject.h
 *  \brief      NTGraphicObject module (header file).
 *  \details    Contains the NTGraphicObject class definitions in the NT system.
 *  \author     Arthur Markaryan
 *  \date       13.05.2025
 *  \copyright  Arthur Markaryan
 */

#ifndef _NTGRAPHICOBJECT_H_
#define _NTGRAPHICOBJECT_H_

/*! \brief  Mutex library */
#include <mutex>

/*!	\brief	Base NT types */
#include "nttypes.h"
/*! \brief  Base NT object */
#include "ntobject.h"

#define NTA_NONE				0			/*!< No attr */
#define NTA_TEXT_ATTR			(1 << 0)	/*!< Text attribute override flag */
#define NTA_SPACE_ATTR			(1 << 1)	/*!< Space attribute override flag */
#define NTA_SPACE_TRANSPARENT	(1 << 2)	/*!< Space transparent flag */

/*! \class      NTGraphicObject
 *  \brief      Graphic object class for NT system.
 *  \details    Represents an base graphic object with position, color attributes and transparency support.
 *  \extends    NTObject
 */
class NTGraphicObject : public NTObject {
public:
	/*!	\brief		Default constructor
	 *	\param		parent	Pointer to the parent object (default: nullptr)
	 *	\param		name	Label name (default: empty string)
	 */
	NTGraphicObject(NTObject* parent = nullptr, const std::string& name = "");

	/*!	\brief		Parameterized constructor
	 *	\param		parent		Pointer to the parent object
	 *	\param		name		Graphic Object name
	 *	\param		x			Initial X position
	 *	\param		y			Initial Y position
	 *	\param		colorPair	Color pair to draw from the palette
	 *	\param		attr		Attr of Graphic Object
	 *	\param		ntattr		nt attr of Graphic Object
	 */
	NTGraphicObject(NTObject* parent, const std::string& name,
					int x, int y,
					unsigned char colorPair,
					chtype attr,
					unsigned char ntattr);

	/*!	\brief		Copy constructor
	 *	\param		other	Reference to source NTLabel object
	 */
	NTGraphicObject(const NTGraphicObject& other);

	/*!	\brief		Destructor
	 */
	virtual ~NTGraphicObject();

	/*!	\brief		Assignment operator
	 *	\param		other	Reference to source NTLabel object
	 *	\return		Reference to the assigned NTLabel object
	 */
	NTGraphicObject& operator=(const NTGraphicObject& other);

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

	/*! \brief      Sets the X, Y coordinate
	 *  \param[in]	x   New X coordinate value
	 *	\param[in]	y   New Y coordinate value
	 */
	void setPosition(int x, int y);

	/*! \brief      Sets the color pair
	 *  \param      color   New color pair value
	 */
	void setColorPair(unsigned char colorPair);

	/*! \brief      Gets the color pair
	 *  \return     Current color pair value
	 */
	unsigned char colorPair() const;

	/*! \brief      Sets the ncurses attr
	 *  \param      attr New ncurses attr value
	 */
	void setAttr(chtype attr);

	/*! \brief      Gets the ncurses attr
	 *  \return     ncurses attr value
	 */
	chtype attr() const;

	/*! \brief      Sets the nt attr
	 *  \param      attr New nt attr value
	 */
	void setNtattr(unsigned char attr);

	/*! \brief      Gets the nt attr
	 *  \return     nt attr value
	 */
	unsigned char ntattr() const;

	/*! \brief      Gets the Graphic changed flag
	 *  \return     true if changed false otherwise
	 */
	bool isChanged() const;

	// Virtual methot to draw (must be override)
	virtual int draw() = 0;

protected:
	mutable std::mutex _mutex;	/*!< Thread-safe mutex */
	int _x;						/*!< X coordinate */
	int _y;						/*!< Y coordinate */
	unsigned char _colorPair;	/*!< Color pair to draw from the palette */
	chtype _attr;				/*!< ncurses attr*/
	unsigned char _ntattr;		/*!< nt attr*/
	bool _changed;				/*!< Changed flag */
};
#endif // _NTGRAPHICOBJECT_H_
