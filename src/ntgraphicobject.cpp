/*! \file       nlgraphicobject.h
 *  \brief      NTGraphicObject module (source file).
 *  \details    Contains method implementations for NTGraphicObject handling in the NT system.
 *  \author     Arthur Markaryan
 *  \date       13.05.2025
 *  \copyright  Arthur Markaryan
 */

#include "ntgraphicobject.h"

/*!	\brief		Default constructor
 *	\param		parent	Pointer to the parent object (default: nullptr)
 *	\param		name	Label name (default: empty string)
 */
NTGraphicObject::NTGraphicObject(NTObject* parent, const std::string& name)
	: NTObject(parent, name), _x(0), _y(0),
	_colorPair(0), _attr(0), _ntattr(NTA_NONE),
	_changed(true) {}

/*!	\brief		Parameterized constructor
 *	\param		parent		Pointer to the parent object
 *	\param		name		Graphic Object name
 *	\param		x			Initial X position
 *	\param		y			Initial Y position
 *	\param		colorPair	Color pair to draw from the palette
 *	\param		attr		ncurses Attr of Graphic Object
 *	\param		ntattr		nt Attr of Graphic Object
 */
NTGraphicObject::NTGraphicObject(NTObject* parent, const std::string& name,
			   int x, int y, unsigned char colorPair, chtype attr, unsigned char ntattr)
	: NTObject(parent, name), _x(x), _y(y),
	_colorPair(colorPair), _attr(attr), _ntattr(ntattr),
	_changed(true) {}

/*!	\brief		Copy constructor
 *	\param		other	Reference to source NTLabel object
 */
NTGraphicObject::NTGraphicObject(const NTGraphicObject& other)
{
	std::lock_guard<std::mutex> lock(other._mutex);
	NTObject::operator=(other);
	//_text = other._text;
	_x = other._x;
	_y = other._y;
	_colorPair = other._colorPair;
	_attr = other._attr;
	_ntattr = other._ntattr;
	_changed = other._changed;
	//notifyObservers();
}

/*!	\brief		Destructor
 */
//NTGraphicObject::~NTGraphicObject() = default;

/*!	\brief		Assignment operator
 *	\param		other	Reference to source NTLabel object
 *	\return		Reference to the assigned NTLabel object
 */
NTGraphicObject& NTGraphicObject::operator=(const NTGraphicObject& other)
{
	if (this != &other) {
		std::unique_lock<std::mutex> lock1(_mutex, std::defer_lock);
		std::unique_lock<std::mutex> lock2(other._mutex, std::defer_lock);
		std::lock(lock1, lock2);

		NTObject::operator=(other);
		_x = other._x;
		_y = other._y;
		_colorPair = other._colorPair;
		_attr = other._attr;
		_ntattr = other._ntattr;
		_changed = other._changed;
	}
	//notifyObservers();
	return *this;
}

/*!	\brief		Set X coordinate position
 *	\param		x	New X coordinate value
 */
void NTGraphicObject::setx(int x)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_x = x;
	_changed = true;
	//notifyObservers();
}

/*!	\brief		Get X coordinate position
 *	\return		Current X coordinate value
 */
int NTGraphicObject::x() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _x;
}

/*!	\brief		Set Y coordinate position
 *	\param		y	New Y coordinate value
 */
void NTGraphicObject::sety(int y)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_y = y;
	_changed = true;
	//notifyObservers();
}

/*!	\brief		Get Y coordinate position
 *	\return		Current Y coordinate value
 */
int NTGraphicObject::y() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _y;
}

/*! \brief      Sets the X, Y coordinate
 *  \param[in]	x   New X coordinate value
 *	\param[in]	y   New Y coordinate value
 */
void NTGraphicObject::setPosition(int x, int y)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_x = x;
	_y = y;
	//notifyObservers();
}

/*!	\brief		Set text color
 *	\param		color	New text color value
 */
void NTGraphicObject::setColorPair(unsigned char colorPair)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_colorPair = colorPair;
	_changed = true;
	//notifyObservers();
}

/*!	\brief		Get text color
 *	\return		Current text color value
 */
unsigned char NTGraphicObject::colorPair() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _colorPair;
}

/*! \brief      Sets the ncurses attr
 *  \param      attr New ncurses attr value
 */
void NTGraphicObject::setAttr(unsigned char attr)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_attr = attr;
	_changed = true;
	//notifyObservers();
}

/*! \brief      Gets the ncurses attr
 *  \return     ncurses attr value
 */
unsigned char NTGraphicObject::attr() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _attr;
}

/*!	\brief		Set nt attr
 *	\param		ntattr	nt attr value
 */
void NTGraphicObject::setNtattr(unsigned char ntattr)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_ntattr = ntattr;
	_changed = true;
	//notifyObservers();
}

/*!	\brief		Get nt attr
 *	\return		ntattr	nt attr value
 */
unsigned char NTGraphicObject::ntattr() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _ntattr;
}

/*! \brief      Gets the Text Label changed flag
 *  \return     true if changed false otherwise
 */
bool NTGraphicObject::isChanged() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _changed;
}
