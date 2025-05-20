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
	false),							// transparent
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
 *	\param		transparent	Initial transparency flag
 */
NTLabel::NTLabel(NTObject* parent, const std::string& name,
				const std::string& text, int x, int y,
				unsigned char colorPair, chtype attr, bool transparent)
	: NTGraphicObject(parent, name, x, y, colorPair, attr, transparent),  // передаём всё родителю
	_text(text)  // инициализируем только своё поле
{
	std::lock_guard<std::mutex> lock(_mutex);
	//notifyObservers();
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
	_colorPair = other._colorPair;
	_attr = other._attr;
	_ntattr = other._ntattr;
	//_changed = other._changed;
	_changed = true;
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

	// Get terminal dimensions
	int max_y, max_x;
	getmaxyx(stdscr, max_y, max_x);

	// Check if position is out of bounds
	if (_y < 0 || _y >= max_y || _x < 0 || _x >= max_x) {
		return NT_ERR_RANGE;  // Position completely out of bounds
	}

	// Calculate visible portion of text
	size_t visible_length = _text.length();
	if (_x + visible_length > static_cast<size_t>(max_x)) {
		visible_length = max_x - _x;
	}

	// If no visible characters left
	if (visible_length <= 0) {
		return NT_ERR_RANGE;
	}

	// Draw visible portion
	int result = ERR;

	for(int i=0; i<static_cast<int>(visible_length); i++){
		//
		chtype ch;
		int color_pair;
		int attributes;
		move(_y, _x+i);

		// Если NTA_ATTR_OVERRIDE, то выводим с заданным цветом и фоном и атрибутами,
		if(_ntattr & NTA_ATTR_OVERRIDE){
			attron(COLOR_PAIR(_colorPair) | _attr);
		}else{
			// в противном случае выводим с текущими атрибутами знакоместа
			ch = inch();
			color_pair = PAIR_NUMBER(ch);
			attributes = ch & A_ATTRIBUTES;
			attron(COLOR_PAIR(color_pair) | attributes);
		}

		// Если символ пробела прозрачный, то не печатаем его,
		if(_ntattr & NTA_TRANSPARENT_SPACE){
			if(_text.at(i) == ' '){
				//continue;
				result = addch(ch);
			}else{
				// иначе печатаем символ или пробел в текущей позиции
				result = addch(_text.at(i));
			}
			//result = addch(_text.at(i));
		}else{
			result = addch(_text.at(i));
		}

		//result = addch(_text.at(i));

		// Выключаем соответствующие атрибуты
		if(_ntattr & NTA_ATTR_OVERRIDE){
			attroff(COLOR_PAIR(_colorPair) | _attr);
		}else{
			// в противном случае выводим с текущими атрибутами знакоместа
			ch = inch();	//?
			color_pair = PAIR_NUMBER(ch);	//?
			attributes = ch & A_ATTRIBUTES;	//?
			attroff(COLOR_PAIR(color_pair) | attributes);
		}
	}

	if (result == ERR) {
		return ERR;
	}

	refresh();
	_changed = false;
	return OK;
}

