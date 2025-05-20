/*!	\file		ntimage.cpp
 *	\brief		Implementation of thread-safe NTImage class
 *	\details	Contains method implementations for text label handling in the NT system
 *	\author		Arthur Markaryan
 *	\date		11.05.2025
 *	\copyright	Arthur Markaryan
 */

#include "ntimage.h"

/*! \brief      Default constructor
 *  \param      parent  Pointer to the parent object (default: nullptr)
 *  \param      name    Image name (default: empty string)
 */
NTImage::NTImage(NTObject* parent, const std::string& name)
	: NTGraphicObject(parent, name,	// parent, name
	0, 0,							// x, y
	0,								// Color pair to draw from the palette
	A_NORMAL,						// attr
	false),							// transparent
	_image({""}),					// image
	_width(0), _height(0)			// width, height
{
    // To do... image, width, height, chanals
	std::lock_guard<std::mutex> lock(_mutex);
	//notifyObservers();
}

// Полный конструктор
NTImage::NTImage(NTObject *parent, const std::string& name,
			   const std::vector<std::string>& image,	//  Может быть сделать структуру?
			   int x, int y, unsigned char colorPair, chtype attr, bool transparent)
	: NTGraphicObject(parent, name,	// parent, name
	x, y,							// x, y
	colorPair,						// Color pair to draw from the palette
	attr,							// attr
	transparent),					// transparent
	_image(image)					// image
{
    // To do... image, width, height, chanals
	std::lock_guard<std::mutex> lock(_mutex);
	//_height = image.size();
	//notifyObservers();
}

// Конструктор копирования
NTImage::NTImage(const NTImage& other)
	: NTGraphicObject(other.parent(), other.name(),	// parent, name
	other._x, other._y,								// x, y
	other._colorPair,								// Color pair to draw from the palette
	other._attr,									// attr
	other._transparent),							// transparent
	_image(other._image)							// image
{
    // To do... width, height, chanals
	std::lock_guard<std::mutex> lock(_mutex);
	//notifyObservers();
}

/*! \brief  Destructor */
NTImage::~NTImage() = default;

/*!	\brief		Assignment operator
 *	\param		other	Reference to source NTImage object
 *	\return		Reference to the assigned NTImage object
 */
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
		_transparent = other._transparent;
		_changed = true;	// !!!
	}
	//notifyObservers();
	return *this;
}

//
void NTImage::setImage(const std::vector<std::string>& image)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_image = image;
	_changed = true;
	//notifyObservers();
}

//
const std::vector<std::string>& NTImage::image() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _image;
}

//
unsigned int NTImage::width() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _width;
}

//
unsigned int NTImage::height() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _height;
}

//
int NTImage::draw()
{
	//
	std::lock_guard<std::mutex> lock(_mutex);

	// Get terminal dimensions
	int max_y, max_x;
	getmaxyx(stdscr, max_y, max_x);

	// Check if position is out of bounds
	if (_y < 0 || _y >= max_y || _x < 0 || _x >= max_x) {
		return NT_ERR_RANGE;  // Position completely out of bounds
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
		return NT_ERR_RANGE;
	}

	// Draw visible portion
	int result = ERR;

	attron(COLOR_PAIR(_colorPair) | _attr);

	for (size_t y = 0; y < _image.size() && (_y + static_cast<int>(y)) < 20; y++) {
		if (_y + static_cast<int>(y) < 0) continue;
			const std::string& line = _image[y];
			for (size_t x = 0; x < line.size() && (_x + static_cast<int>(x)) < 80; x++) {
				if (_x + static_cast<int>(x) < 0) continue;
				//mvaddch(this->y() + static_cast<int>(y), this->x() + static_cast<int>(x), line[x]);
				if(line[x] == 'X') mvaddch(_y + static_cast<int>(y), _x + static_cast<int>(x), ' ' | A_REVERSE);
				//if(line[x] == ' ') mvaddch(_y + static_cast<int>(y), _x + static_cast<int>(x), ' ');
			}
	}

	attroff(COLOR_PAIR(_colorPair) | _attr);

	if (result == ERR) {
		return ERR;
	}

	refresh();
	_changed = false;

	return result;
}
