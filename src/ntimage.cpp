/*!	\file		ntimage.cpp
 *	\brief		Implementation of thread-safe NTImage class
 *	\details	Contains method implementations for text label handling in the NT system
 *	\author		Arthur Markaryan
 *	\date		11.05.2025
 *	\copyright	Arthur Markaryan
 */

#include "ntimage.h"

// Default constructor
NTImage::NTImage(NTObject* parent, const std::string& name)
	: NTGraphicObject(parent, name,	// parent, name
	0, 0,							// x, y coordinate of the left-top corner of the image
	0,								// Color pair to draw from the palette
	A_NORMAL,						// attr
	NTA_NONE),						// nattr
	_image({{""}, 0, 0}),			// image
	_width(0), _height(0)			// width, height
{
	std::lock_guard<std::mutex> lock(_mutex);
	//notifyObservers();
}

// Parameterized constructor
NTImage::NTImage(NTObject *parent, const std::string& name,
			   const struct nt::Image& image,
			   int x, int y, unsigned char colorPair, chtype attr, unsigned char ntattr)
	: NTGraphicObject(parent, name,	// parent, name
	x, y,							// x, y coordinate of the left-top corner of the image
	colorPair,						// Color pair to draw from the palette
	attr,							// attr
	ntattr),						// ntattr
	_image(image)					// image
{
	std::lock_guard<std::mutex> lock(_mutex);
	//notifyObservers();
}

// Copy constructor
NTImage::NTImage(const NTImage& other)
	: NTGraphicObject(other.parent(), other.name(),	// parent, name
	other._x, other._y,								// x, y coordinate of the left-top corner of the image
	other._colorPair,								// Color pair to draw from the palette
	other._attr,									// attr
	other._ntattr),									// ntattr
	_image(other._image)							// image
{
	std::lock_guard<std::mutex> lock(_mutex);
	//notifyObservers();
}

// Destructor
NTImage::~NTImage() = default;

// Assignment operator
NTImage& NTImage::operator=(const NTImage& other)
{
	if (this != &other) {
		std::unique_lock<std::mutex> lock1(_mutex, std::defer_lock);
		std::unique_lock<std::mutex> lock2(other._mutex, std::defer_lock);
		std::lock(lock1, lock2);

		NTObject::operator=(other);
		_image = other._image;
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

// Sets the image data
void NTImage::setImage(const struct nt::Image& image)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_image = image;
	_changed = true;
	//notifyObservers();
}

// Gets the image data
const struct nt::Image& NTImage::image() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _image;
}

// Sets the image width
void NTImage::setWidth(unsigned int width)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_width = width;
	_changed = true;
	//notifyObservers();
}

// Gets the image width
unsigned int NTImage::width() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _width;
}

// Sets the image height
void NTImage::setHeight(unsigned int height)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_height = height;
	_changed = true;
	//notifyObservers();
}

// Gets the image height
unsigned int NTImage::height() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _height;
}

// Draw the image
int NTImage::draw()
{
	std::lock_guard<std::mutex> lock(_mutex);
	int result = NT_OK;

	// Get terminal dimensions
	int max_y, max_x;
	getmaxyx(stdscr, max_y, max_x);

	// Check if Y-position is out of bounds or no need to draw
	if ( _y+_height < 0 || _y > max_y ) {
		result |= NT_ERR_RANGE_Y;	// Position Y completely out of bounds
	}

	// Check if X-position is out of bounds or no need to draw
	if ( _x+_width < 0 || _x > max_x) {
		result |= NT_ERR_RANGE_X;	// Position X completely out of bounds
	}

	// Position (Y, X) completely out of bounds
	if(NT_OK != result) return result;

	// Get the start of character and length
	int visible_vstart = 0;
	int visible_vlength = 0;
	int visible_hstart = 0;
	int visible_hlength = 0;

	// Check if visible y-position
	if(_y < 0) {
		visible_vstart = 0 - _y;
	}

	visible_vlength = std::min({
		static_cast<int>(_height),
		static_cast<int>(_image.height),
		static_cast<int>(_image.img.size())
	});

	if(visible_vlength + _y > max_y) {
		visible_vlength = max_y - _y;
	}

	// If text is invisible
	if(NT_OK != result) return result;

	// Draw visible portion
	for(int y = visible_vstart; y < visible_vlength; y++){
		//
		const std::string& line = _image.img[y];

		// If no visible characters left
		if (visible_vlength <= 0) {
			result |=  NT_ERR_INVISIBLE_Y;
		}

		// Check if visible x-position
		if(_x < 0) {
			visible_hstart = 0 - _x;
		}

		visible_hlength = line.length();

		if(visible_hlength + _x > max_x) {
			visible_hlength = max_x - _x;
		}

		// If no visible characters left
		if (visible_hlength <= 0) {
			result |=  NT_ERR_INVISIBLE_X;
			continue;
		}

		//
		for(int x = visible_hstart; x < visible_hlength; x++){
			// Move cursor to the x, y - position to get the attrs
			result = move(_y + y, _x + x);

			// Get the attrs in the current cursor position
			chtype ch = inch();					// Get character and attrs
			int color_pair = PAIR_NUMBER(ch);	// Get color pair
			int attributes = ch & A_ATTRIBUTES;	// Get attr

			// If attrs for the text then...
			if( _ntattr & NTA_TEXT_ATTR ){
				if(line.at(x) != ' '){
					color_pair = _colorPair;
					attributes = _attr;
				}
			}

			// If attr for the space then...
			if( _ntattr & NTA_SPACE_ATTR ){
				if(line.at(x) == ' '){
					color_pair = _colorPair;
					attributes = _attr;
				}
			}

			// Prepare character to print in terminal
			if( _ntattr & NTA_SPACE_TRANSPARENT ){
				if(line.at(x) == ' '){
					ch = inch();
				}else{
					ch = line.at(x);
				}
			}else{
				ch = line.at(x);
			}

			// Set the attrs, color, background color
			result = attron(COLOR_PAIR(color_pair) | attributes);

			// Print character
			result = addch(ch);

			// Unset attrs
			result = attroff(COLOR_PAIR(color_pair) | attributes);
		}
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
