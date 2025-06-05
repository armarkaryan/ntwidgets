/*! \file       nlgraphicobject.h
 *  \brief      NTGraphicObject module (source file).
 *  \details    Contains method implementations for NTGraphicObject handling in the NT system.
 *  \author     Arthur Markaryan
 *  \date       13.05.2025
 *  \copyright  Arthur Markaryan
 */

#include "ntgraphicobject.h"

// Default constructor
NTGraphicObject::NTGraphicObject(NTObject* parent, const std::string& name)
	: NTObject(parent, name), _x(0), _y(0),
	_colorPair(0), _attr(0), _ntattr(NTA_NONE),
	_changed(true) {}

//Parameterized constructor
NTGraphicObject::NTGraphicObject(NTObject* parent, const std::string& name,
			   int x, int y, unsigned char colorPair, chtype attr, unsigned char ntattr)
	: NTObject(parent, name), _x(x), _y(y),
	_colorPair(colorPair), _attr(attr), _ntattr(ntattr),
	_changed(true) {}

// Copy constructor
NTGraphicObject::NTGraphicObject(const NTGraphicObject& other)
{
	std::lock_guard<std::mutex> lock(other._mutex);
	NTObject::operator=(other);
	_x = other._x;
	_y = other._y;
	_colorPair = other._colorPair;
	_attr = other._attr;
	_ntattr = other._ntattr;
	_changed = other._changed;
	//notifyObservers();
}

// Destructor
NTGraphicObject::~NTGraphicObject() = default;

// Assignment operator
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

// Set X coordinate position
void NTGraphicObject::setx(int x)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_x = x;
	_changed = true;
	//notifyObservers();
}

// Get X coordinate position
int NTGraphicObject::x() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _x;
}

// Set Y coordinate position
void NTGraphicObject::sety(int y)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_y = y;
	_changed = true;
	//notifyObservers();
}

// Get Y coordinate position
int NTGraphicObject::y() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _y;
}

// Sets the X, Y coordinate
void NTGraphicObject::setPosition(int x, int y)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_x = x;
	_y = y;
	//notifyObservers();
}

// Set text color
void NTGraphicObject::setColorPair(unsigned char colorPair)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_colorPair = colorPair;
	_changed = true;
	//notifyObservers();
}

// Get text color
unsigned char NTGraphicObject::colorPair() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _colorPair;
}

// Sets the ncurses attr
void NTGraphicObject::setAttr(chtype attr)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_attr = attr;
	_changed = true;
	//notifyObservers();
}

// Gets the ncurses attr
chtype NTGraphicObject::attr() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _attr;
}

// Set nt attr
void NTGraphicObject::setNtattr(unsigned char ntattr)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_ntattr = ntattr;
	_changed = true;
	//notifyObservers();
}

//Get nt attr
unsigned char NTGraphicObject::ntattr() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _ntattr;
}

// Gets the Text Label changed flag
bool NTGraphicObject::isChanged() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _changed;
}
