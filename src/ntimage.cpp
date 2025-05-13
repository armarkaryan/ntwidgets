// NTImage.cpp

#include "ntimage.h"

// Простой конструктор
NTImage::NTImage(NTObject* parent, const std::string& name)
	: NTObject(parent, name),
	_image({""}),
	_x(0), _y(0),
	_color(nt::color({255, 255, 255})),
	_bgColor(nt::color({0, 0, 0})),
	_transparent(true),
	_changed(true),
	_width(0), _height(0)
{
    // To do... image, width, height, chanals
	std::lock_guard<std::mutex> lock(_mutex);
	notifyObservers();
}

// Полный конструктор
NTImage::NTImage(NTObject *parent, const std::string& name,
			   const std::vector<std::string>& image,	//  Может быть сделать структуру?
			   int x, int y, nt::color color, nt::color bgColor, bool transparent)
	: NTObject(parent, name),
	_image(image),
	_x(x), _y(y),
	_color(color),
	_bgColor(bgColor),
	_transparent(transparent),
	_changed(true)
{
    // To do... image, width, height, chanals
	std::lock_guard<std::mutex> lock(_mutex);
	//_height = image.size();
	notifyObservers();
}

// Конструктор копирования
NTImage::NTImage(const NTImage& other)
	: NTObject(other.parent(), other.name()),
	_image(other._image),
	_x(other._x),
	_y(other._y),
	_color(other._color),
	_bgColor(other._bgColor),
	_transparent(other._transparent),
	_changed(true)
{
    // To do... width, height, chanals
	std::lock_guard<std::mutex> lock(_mutex);
	notifyObservers();
}

// Деструктор
NTImage::~NTImage() = default;

// Оператор присваивания
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
		_color = other._color;
		_bgColor = other._bgColor;
		_transparent = other._transparent;
		_changed = true;	// !!!
	}
	notifyObservers();
	return *this;
}

//
void NTImage::setImage(const std::vector<std::string>& image)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_image = image;
	_changed = true;
	notifyObservers();
}

//
const std::vector<std::string>& NTImage::image() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _image;
}

//
void NTImage::setx(int x)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_x = x;
	_changed = true;
	notifyObservers();
}

//
int NTImage::x() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _x;
}

//
void NTImage::sety(int y)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_y = y;
	_changed = true;
	notifyObservers();
}

//
int NTImage::y() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _y;
}

//
void NTImage::setPosition(int x, int y)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_x = x;
	_y = y;
	_changed = true;
	notifyObservers();
}

/*!	\brief		Set text color
 *	\param		color	New text color value
 */
void NTImage::setColor(nt::color color)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_color = color;
	_changed = true;
	notifyObservers();
}

/*!	\brief		Get text color
 *	\return		Current text color value
 */
nt::color NTImage::color() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _color;
}

/*!	\brief		Set background color
 *	\param		bgColor	New background color value
 */
void NTImage::setBgColor(nt::color bgColor)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_bgColor = bgColor;
	_changed = true;
	notifyObservers();
}

/*!	\brief		Get background color
 *	\return		Current background color value
 */
nt::color NTImage::bgColor() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _bgColor;
}

//
void NTImage::setTransparent(bool transparent)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_transparent = transparent;
	_changed = true;
	notifyObservers();
}

//
bool NTImage::transparent() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _transparent;
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
	//std::lock_guard<std::mutex> lock(_mutex);
/*
	// Get terminal dimensions
	int max_y, max_x;
	getmaxyx(stdscr, max_y, max_x);

	// Check if position is out of bounds
	if (_y < 0 || _y >= max_y || _x < 0 || _x >= max_x) {
		return ERR_RANGE;  // Position completely out of bounds
	}

	// Calculate visible portion of text
	size_t visible_length = _width;
	if (_x + visible_length > static_cast<size_t>(max_x)) {
		visible_length = max_x - _x;
	}

	// If no visible characters left
	if (visible_length <= 0) {
		return ERR_RANGE;
	}
*/
	//for (size_t y = 0; y < image().size() && (this->y() + static_cast<int>(y)) < term_height; y++) {
	for (size_t y = 0; y < image().size() && (this->y() + static_cast<int>(y)) < 20; y++) {
			if (this->y() + static_cast<int>(y) < 0) continue;

			const std::string& line = this->image()[y];
			//for (size_t x = 0; x < line.size() && (this->x() + static_cast<int>(x)) < term_width; x++) {
			for (size_t x = 0; x < line.size() && (this->x() + static_cast<int>(x)) < 80; x++) {
				if (this->x() + static_cast<int>(x) < 0) continue;
				//mvaddch(img->y() + static_cast<int>(y), img->x() + static_cast<int>(x), line[x]);
				if(line[x] == 'X') mvaddch(this->y() + static_cast<int>(y), this->x() + static_cast<int>(x), ' ' | A_REVERSE);
				if(line[x] == ' ') mvaddch(this->y() + static_cast<int>(y), this->x() + static_cast<int>(x), ' ');
			}
		}
	refresh();
	_changed = false;
	return OK;
}
