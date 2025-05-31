/*!	\file		ntlabel.cpp
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

/*!	\brief		Parameterized constructor
 *	\param		parent		Pointer to the parent object
 *	\param		name		Label name
 *	\param		text		Initial text content
 *	\param		x			Initial X position
 *	\param		y			Initial Y position
 *	\param		colorPair	Color pair to draw from the palette
 *	\param		attr		Attr of the text label
 *	\param      ntattr		nt attr for the text label
 */
NTLabel::NTLabel(NTObject* parent, const std::string& name,
				const std::string& text, int x, int y,
				unsigned char colorPair, chtype attr, unsigned char ntattr)
	: NTGraphicObject(parent, name, x, y, colorPair, attr, ntattr),  // передаём всё родителю
	_text(text)  // инициализируем только своё поле
{
	std::lock_guard<std::mutex> lock(_mutex);
	//notifyObservers();
}

/*!	\brief		Copy constructor
 *	\param		other	Reference to source NTLabel object
 */
NTLabel::NTLabel(const NTLabel& other)
	: NTGraphicObject(other.parent(), other.name(),	// parent, name
	other._x, other._y,								// x, y
	other._colorPair,								// Color pair to draw from the palette
	other._attr,									// attr
	other._ntattr),									// ntattr
	_text(other._text)								// image
{
	// To do... width, height, chanals
	std::lock_guard<std::mutex> lock(_mutex);
	//notifyObservers();
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
		_colorPair = other._colorPair;
		_attr = other._attr;
		_ntattr = other._ntattr;
		//_changed = other._changed;
		_changed = true;
	}
	//notifyObservers();
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
	//notifyObservers();
}

/*! \brief      Gets the text data
 *  \return     Constant reference to the text data
 */
std::string NTLabel::text() const
{
	std::lock_guard<std::mutex> lock(_mutex);
	return _text;
}

/*!	\brief		Draw the text label
 *	\details	Thread-safe rendering of the label using ncurses library.
 *			Only visible characters within terminal bounds are drawn.
 *	\return		OK if draw success,
 *			ERR_RANGE if text is out of terminal bounds,
 *			ERR if other error occurred
 */

int NTLabel::draw() {
	//
	std::lock_guard<std::mutex> lock(_mutex);

	//
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

	//
	int visible_start = 0;
	int visible_length = 0;

	if(_x < 0) {
		visible_start = 0 - _x;
	}

	visible_length = _text.length();

	if(visible_length + _x > max_x) {
		visible_length = max_x - _x;
	}

	// If no visible characters left
	if (visible_length <= 0) {
		result |=  NT_ERR_INVISIBLE;
	}

	// If text is invisible
	if(NT_OK != result) return result;

	// Draw visible portion
	for(int x=visible_start; x<static_cast<int>(visible_length); x++){
		// Перемещаем курсор в позицию x, y и считываем атрибуты
		result = move(_y, _x + static_cast<int>(x));
		//
		chtype ch = inch();					//
		int color_pair = PAIR_NUMBER(ch);	//
		int attributes = ch & A_ATTRIBUTES;	//

		// Если атрибуты для текста
		if( _ntattr & NTA_TEXT_ATTR ){
			if(_text.at(x) != ' '){
				color_pair = _colorPair;
				attributes = _attr;
			}
		}

		// Если атрибуты для пробела
		if( _ntattr & NTA_SPACE_ATTR ){
			if(_text.at(x) == ' '){
				color_pair = _colorPair;
				attributes = _attr;
			}
		}

		// // Готовим символ для вывода
		if( _ntattr & NTA_SPACE_TRANSPARENT ){
			if(_text.at(x) == ' '){
				ch = inch();
			}else{
				ch = _text.at(x);
			}
		}else{
			ch = _text.at(x);
		}

		// Устанавливаем атрибуты, цвет и фон знакоместа
		result = attron(COLOR_PAIR(color_pair) | attributes);

		// Выводим символ
		result = addch(ch);

		// Выключаем атрибуты
		result = attroff(COLOR_PAIR(color_pair) | attributes);
	}

	if (result == ERR) {
		return ERR;
	}

	refresh();
	_changed = false;
	return result;
}

