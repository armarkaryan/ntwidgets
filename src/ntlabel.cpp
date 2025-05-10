/*!	\file		NTLabel.cpp
 *	\brief		Implementation of thread-safe NTLabel class
 *	\details	Contains method implementations for text label handling in the NT system
 *	\author		Arthur Markaryan
 *	\date		09.05.2025
 *	\copyright	Arthur Markaryan
 */

#include "ntlabel.h"

/*!	\brief		Default constructor
 *	\param		parent	Pointer to the parent object (default: nullptr)
 *	\param		name	Label name (default: empty string)
 */
NTLabel::NTLabel(NTObject* parent, const std::string& name)
	: NTObject(parent, name),
	_text(""),
	_x(0), _y(0),
	_color(nt::color({255, 255, 255})),
	_bgColor(nt::color({0, 0, 0})),
	_transparent(false),
	_changed(true)
{
	std::lock_guard<std::mutex> lock(_mutex);
	notifyObservers();
}

/*!	\brief		Parameterized constructor
 *	\param		parent		Pointer to the parent object
 *	\param		name		Label name
 *	\param		text		Initial text content
 *	\param		x			Initial X position
 *	\param		y			Initial Y position
 *	\param		color		Initial text color
 *	\param		bgColor		Initial background color
 *	\param		transparent	Initial transparency flag
 */
NTLabel::NTLabel(NTObject* parent, const std::string& name,
			   const std::string& text,
			   int x, int y, nt::color color, nt::color bgColor, bool transparent)
	: NTObject(parent, name),
	_text(text),
	_x(x), _y(y),
	_color(color),
	_bgColor(bgColor),
	_transparent(transparent),
	_changed(true)
{
	std::lock_guard<std::mutex> lock(_mutex);
	notifyObservers();
}

/*!	\brief		Copy constructor
 *	\param		other	Reference to source NTLabel object
 */
NTLabel::NTLabel(const NTLabel& other)
{
	std::lock_guard<std::mutex> lock(other._mutex);
	NTObject::operator=(other);
	_text = other._text;
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
NTLabel::~NTLabel() = default;

/*!	\brief		Assignment operator
 *	\param		other	Reference to source NTLabel object
 *	\return		Reference to the assigned NTLabel object
 */
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
		_color = other._color;
		_bgColor = other._bgColor;
		_transparent = other._transparent;
		_changed = other._changed;
	}
	notifyObservers();
	return *this;
}

/*! \brief      Sets the text data
 *  \param      text   Representing the new text data
 */
void NTLabel::setText(const std::string& text)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_text = text;
	_changed = true;
	notifyObservers();
}

/*! \brief      Gets the text data
 *  \return     Constant reference to the text data
 */
std::string NTLabel::text() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _text;
}

/*!	\brief		Set X coordinate position
 *	\param		x	New X coordinate value
 */
void NTLabel::setx(int x)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_x = x;
	_changed = true;
	notifyObservers();
}

/*!	\brief		Get X coordinate position
 *	\return		Current X coordinate value
 */
int NTLabel::x() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _x;
}

/*!	\brief		Set Y coordinate position
 *	\param		y	New Y coordinate value
 */
void NTLabel::sety(int y)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_y = y;
	_changed = true;
	notifyObservers();
}

/*!	\brief		Get Y coordinate position
 *	\return		Current Y coordinate value
 */
int NTLabel::y() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _y;
}

/*!	\brief		Set text color
 *	\param		color	New text color value
 */
void NTLabel::setColor(nt::color color)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_color = color;
	_changed = true;
	notifyObservers();
}

/*!	\brief		Get text color
 *	\return		Current text color value
 */
nt::color NTLabel::color() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _color;
}

/*!	\brief		Set background color
 *	\param		bgColor	New background color value
 */
void NTLabel::setBgColor(nt::color bgColor)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_bgColor = bgColor;
	_changed = true;
	notifyObservers();
}

/*!	\brief		Get background color
 *	\return		Current background color value
 */
nt::color NTLabel::bgColor() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _bgColor;
}

/*!	\brief		Set transparency flag
 *	\param		transparent	New transparency value
 */
void NTLabel::setTransparent(bool transparent)
{
	std::lock_guard<std::mutex> lock(_mutex);
	_transparent = transparent;
	_changed = true;
	notifyObservers();
}

/*!	\brief		Get transparency flag
 *	\return		true if transparent, false otherwise
 */
bool NTLabel::transparent() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _transparent;
}

/*!	\brief		Draw the text label
 *	\details	Thread-safe rendering of the label using ncurses library.
 *			Only visible characters within terminal bounds are drawn.
 *	\return		OK if draw success,
 *			ERR_RANGE if text is out of terminal bounds,
 *			ERR if other error occurred
 */

int NTLabel::draw() {
	std::lock_guard<std::mutex> lock(_mutex);

	// Get terminal dimensions
	int max_y, max_x;
	getmaxyx(stdscr, max_y, max_x);

	// Check if position is out of bounds
	if (_y < 0 || _y >= max_y || _x < 0 || _x >= max_x) {
		return ERR_RANGE;  // Position completely out of bounds
	}

	// Calculate visible portion of text
	size_t visible_length = _text.length();
	if (_x + visible_length > static_cast<size_t>(max_x)) {
		visible_length = max_x - _x;
	}

	// If no visible characters left
	if (visible_length <= 0) {
		return ERR_RANGE;
	}

	// Prepare colors
	short color_id = 100;
	short colorBg_id = 101;

	short r_text = _color.red;
	short g_text = _color.green;
	short b_text = _color.blue;
	short r_bg = _bgColor.red;
	short g_bg = _bgColor.green;
	short b_bg = _bgColor.blue;

	// Initialize colors
	if (init_color(color_id, r_text * 1000 / 255, g_text * 1000 / 255, b_text * 1000 / 255) == ERR ||
		init_color(colorBg_id, r_bg * 1000 / 255, g_bg * 1000 / 255, b_bg * 1000 / 255) == ERR) {
		return ERR;
	}

	if (init_pair(9, color_id, colorBg_id) == ERR) {
		return ERR;
	}

	// Draw visible portion
	attron(COLOR_PAIR(9));
	int result = mvprintw(_y, _x, "%.*s", static_cast<int>(visible_length), _text.c_str());
	attroff(COLOR_PAIR(9));

	if (result == ERR) {
		return ERR;
	}

	refresh();
	_changed = false;
	return OK;
}

