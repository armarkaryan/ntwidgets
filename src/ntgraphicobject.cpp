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
	_color({255, 255, 255}), _bgColor({0, 0, 0}), _transparent(false),
	_changed(true) {}

/*!	\brief		Parameterized constructor
 *	\param		parent		Pointer to the parent object
 *	\param		name		Graphic Object name
 *	\param		x			Initial X position
 *	\param		y			Initial Y position
 *	\param		color		Initial text color
 *	\param		bgColor		Initial background color
 *	\param		transparent	Initial transparency flag
 */
NTGraphicObject::NTGraphicObject(NTObject* parent, const std::string& name,
			   int x, int y, nt::color color, nt::color bgColor, bool transparent)
	: NTObject(parent, name), _x(x), _y(y),
	_color(color), _bgColor(bgColor), _transparent(transparent),
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
	_color = other._color;
	_bgColor = other._bgColor;
	_transparent = other._transparent;
	_changed = other._changed;
	notifyObservers();
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
		//_text = other._text;
		_x = other._x;
		_y = other._y;
		_color = other._color;
		_bgColor = other._bgColor;
		_transparent = other._transparent;
		_changed = other._changed;
	}
	notifyObservers();
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
	notifyObservers();
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
	notifyObservers();
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
	notifyObservers();
}

/*!	\brief		Set text color
 *	\param		color	New text color value
 */
void NTGraphicObject::setColor(nt::color color)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_color = color;
	_changed = true;
	notifyObservers();
}

/*!	\brief		Get text color
 *	\return		Current text color value
 */
nt::color NTGraphicObject::color() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _color;
}

/*!	\brief		Set background color
 *	\param		bgColor	New background color value
 */
void NTGraphicObject::setBgColor(nt::color bgColor)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_bgColor = bgColor;
	_changed = true;
	notifyObservers();
}

/*!	\brief		Get background color
 *	\return		Current background color value
 */
nt::color NTGraphicObject::bgColor() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _bgColor;
}

/*!	\brief		Set transparency flag
 *	\param		transparent	New transparency value
 */
void NTGraphicObject::setTransparent(bool transparent)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_transparent = transparent;
	_changed = true;
	notifyObservers();
}

/*!	\brief		Get transparency flag
 *	\return		true if transparent, false otherwise
 */
bool NTGraphicObject::transparent() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _transparent;
}

/*! \brief      Gets the Text Label changed flag
 *  \return     true if changed false otherwise
 */
bool NTGraphicObject::isChanged() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _changed;
}
