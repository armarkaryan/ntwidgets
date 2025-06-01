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
	_image({""}),					// image
	_width(0), _height(0)			// width, height
{
	std::lock_guard<std::mutex> lock(_mutex);
	//notifyObservers();
}

// Parameterized constructor
NTImage::NTImage(NTObject *parent, const std::string& name,
			   const std::vector<std::string>& image,	//  Может быть сделать структуру?
			   int x, int y, unsigned char colorPair, chtype attr, unsigned char ntattr)
	: NTGraphicObject(parent, name,	// parent, name
	x, y,							// x, y coordinate of the left-top corner of the image
	colorPair,						// Color pair to draw from the palette
	attr,							// attr
	ntattr),						// ntattr
	_image(image)					// image
{
	// To do... width, height
	std::lock_guard<std::mutex> lock(_mutex);
	//_height = image.size();
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
    // To do... width, height, chanals
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
		_changed = true;	// !!!
	}
	//notifyObservers();
	return *this;
}

// Sets the image data
void NTImage::setImage(const std::vector<std::string>& image)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_image = image;
	_changed = true;
	//notifyObservers();
}

// Gets the image data
const std::vector<std::string>& NTImage::image() const
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
	if ( _y+_height < 0 || _y >= max_y ) {
		result |= NT_ERR_RANGE_Y;	// Position Y completely out of bounds
	}

	// Check if X-position is out of bounds or no need to draw
	if ( _x+_width < 0 || _x >= max_x) {
		result |= NT_ERR_RANGE_X;	// Position X completely out of bounds
	}

	// Position (Y, X) completely out of bounds
	if(NT_OK != result) return result;
/*
	// Check if position is out of bounds
	if (_y < 0 || _y >= max_y || _x < 0 || _x >= max_x) {
		return NT_ERR_RANGE_X;  // Position completely out of bounds
	}

	// Calculate visible portion of image
	size_t visible_width = _width;
	if (_x + visible_width > static_cast<size_t>(max_x)) {
		visible_width = max_x - _x;
	}

	size_t visible_height = _height;
	if (_y + visible_height > static_cast<size_t>(max_y)) {
		visible_height = max_y - _y;
	}

	// If no visible characters left
	if (visible_width <= 0 || visible_height <= 0) {
		return NT_ERR_RANGE_X;
	}
*/
	// Draw visible portion
	//for (size_t y = 0; y < _image.size() && (_y + static_cast<int>(y)) < static_cast<int>(visible_height); y++) {
	for (size_t y = 0; y < _image.size(); y++) {
		//if (_y + static_cast<int>(y) < 0) continue;
		const std::string& line = _image[y];
		//for (size_t x = 0; x < line.size() && (_x + static_cast<int>(x)) < static_cast<int>(visible_width); x++) {
		for (size_t x = 0; x < line.size(); x++) {
			//if (_x + static_cast<int>(x) < 0) continue;
			// Перемещаем курсор в позицию y, x и считываем атрибуты
			result = move(_y + static_cast<int>(y), _x + static_cast<int>(x));
			//
			chtype ch = inch();					//
			int color_pair = PAIR_NUMBER(ch);	//
			int attributes = ch & A_ATTRIBUTES;	//

			// Если атрибуты для текста
			if( _ntattr & NTA_TEXT_ATTR ){
				if(line.at(x) != ' '){
					color_pair = _colorPair;
					attributes = _attr;
				}
			}

			// Если атрибуты для пробела
			if( _ntattr & NTA_SPACE_ATTR ){
				if(line.at(x) == ' '){
					color_pair = _colorPair;
					attributes = _attr;
				}
			}

			// // Готовим символ для вывода
			if( _ntattr & NTA_SPACE_TRANSPARENT ){
				if(line.at(x) == ' '){
					ch = inch();
				}else{
					ch = line.at(x);
				}
			}else{
				ch = line.at(x);
			}

			// Устанавливаем атрибуты, цвет и фон знакоместа
			result = attron(COLOR_PAIR(color_pair) | attributes);

			// Выводим символ
			result = addch(ch);

			// Выключаем атрибуты
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
