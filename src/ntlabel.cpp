/*!	\file		ntlabel.cpp
 *	\brief		Implementation of thread-safe NTLabel class
 *	\details	Contains method implementations for text label handling in the NT system
 *	\author		Arthur Markaryan
 *	\date		09.05.2025
 *	\copyright	Arthur Markaryan
 */

#include "ntlabel.h"

// Default constructor
NTLabel::NTLabel(NTObject* parent, const std::string& name)
	: NTGraphicObject(parent, name,	// parent, name
	0, 0,							// x, y
	0,								// Color pair to draw from the palette
	A_NORMAL,						// attr
	NTA_NONE),						// nattr
	_text("")						// Empty text
{
	std::lock_guard<std::mutex> lock(_mutex);
	//notifyObservers();
}

// Parameterized constructor
NTLabel::NTLabel(NTObject* parent, const std::string& name,
				const std::string& text, int x, int y,
				unsigned char colorPair, chtype attr, unsigned char ntattr)
	: NTGraphicObject(parent, name, x, y, colorPair, attr, ntattr),
	_text(text)
{
	std::lock_guard<std::mutex> lock(_mutex);
	//notifyObservers();
}

// Copy constructor
NTLabel::NTLabel(const NTLabel& other)
	: NTGraphicObject(other.parent(), other.name(),	// parent, name
	other._x, other._y,								// x, y
	other._colorPair,								// Color pair to draw from the palette
	other._attr,									// attr
	other._ntattr),									// ntattr
	_text(other._text)								// image
{
	std::lock_guard<std::mutex> lock(_mutex);
	//notifyObservers();
}

// Destructor
NTLabel::~NTLabel() = default;

// Assignment operator
NTLabel& NTLabel::operator=(const NTLabel& other)
{
	if (this != &other) {
		std::unique_lock<std::mutex> lock1(_mutex, std::defer_lock);
		std::unique_lock<std::mutex> lock2(other._mutex, std::defer_lock);
		std::lock(lock1, lock2);

		NTObject::operator=(other);
		_text = other._text;
		_x = other._x;
		_y = other._y;
		_colorPair = other._colorPair;
		_attr = other._attr;
		_ntattr = other._ntattr;
		_changed = true;
	}
	//notifyObservers();
	return *this;
}

// Sets the text data
void NTLabel::setText(const std::string& text)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_text = text;
	_changed = true;
	//notifyObservers();
}

// Gets the text data
std::string NTLabel::text() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _text;
}

// Draw the text label
int NTLabel::draw() {
	std::lock_guard<std::mutex> lock(_mutex);
	int result = NT_OK;

	// Get terminal dimensions
	int max_y, max_x;
	getmaxyx(stdscr, max_y, max_x);

	// Check if Y-position is out of bounds or no need to draw
	if ( _y < 0 || _y >= max_y ) {
		result |= NT_ERR_RANGE_Y;	// Position Y completely out of bounds
	}

	// Check if X-position is out of bounds or no need to draw
	if ( _x+_text.length() < 0 || _x >= max_x) {
		result |= NT_ERR_RANGE_X;	// Position X completely out of bounds
	}

	// Position (Y, X) completely out of bounds
	if(NT_OK != result) return result;

	// Get the start character and length
	int visible_hstart = 0;
	int visible_hlength = 0;

	if(_x < 0) {
		visible_hstart = 0 - _x;
	}

	visible_hlength = _text.length();

	if(visible_hlength + _x > max_x) {
		visible_hlength = max_x - _x;
	}

	// If no visible characters left
	if (visible_hlength <= 0) {
		result |=  NT_ERR_INVISIBLE_X;
	}

	// If text is invisible
	if(NT_OK != result) return result;

	// Draw visible portion
	for(int x = visible_hstart; x < visible_hlength; x++){
		// Move cursor to the x, y - position to get the attrs
		result = move(_y, _x + x);

		// Get the attrs in the current cursor position
		chtype ch = inch();					// Get character and attrs
		int color_pair = PAIR_NUMBER(ch);	// Get color pair
		int attributes = ch & A_ATTRIBUTES;	// Get attr

		// If attrs for the text then...
		if( _ntattr & NTA_TEXT_ATTR ){
			if(_text.at(x) != ' '){
				color_pair = _colorPair;
				attributes = _attr;
			}
		}

		// If attr for the space then...
		if( _ntattr & NTA_SPACE_ATTR ){
			if(_text.at(x) == ' '){
				color_pair = _colorPair;
				attributes = _attr;
			}
		}

		// Prepare character to print in terminal
		if( _ntattr & NTA_SPACE_TRANSPARENT ){
			if(_text.at(x) == ' '){
				ch = inch();
			}else{
				ch = _text.at(x);
			}
		}else{
			ch = _text.at(x);
		}

		// Set the attrs, color, background color
		result = attron(COLOR_PAIR(color_pair) | attributes);

		// Print character
		result = addch(ch);

		// Unset attrs
		result = attroff(COLOR_PAIR(color_pair) | attributes);
	}

	// If any fatal error occured then return ERR
	if (result == ERR) {
		return ERR;
	}

	// No fatal error occured
	refresh();
	_changed = false;
	return result;
}

