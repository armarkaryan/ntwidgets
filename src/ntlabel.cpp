// NTLabel.cpp

#include "ntlabel.h"

// Простой конструктор
NTLabel::NTLabel(NTObject* parent, const std::string& name)
	: NTObject(parent, name),
	_text(""),
	_x(0), _y(0),
	_color(nt::color({255, 255, 255})),
	_bgColor(nt::color({0, 0, 0})),
	_transparent(false),
	_changed(true)
{
    // To do... image, width, height, chanals
	notifyObservers();
}

// Полный конструктор
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
    // To do... image, width, height, chanals
	notifyObservers();
}

// Конструктор копирования
NTLabel::NTLabel(const NTLabel& other)
    : NTObject(other.parent(), other.name()),
	  _text(other._text),
      _x(other._x),
      _y(other._y),
	  _color(other._color),
	  _bgColor(other._bgColor),
	  _transparent(other._transparent),
	  _changed(other._changed)
{
    // To do... width, height, chanals
	notifyObservers();
}

// Деструктор
NTLabel::~NTLabel() = default;

// Оператор присваивания
NTLabel& NTLabel::operator=(const NTLabel& other)
{
	if (this != &other) {
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

//
void NTLabel::setx(int x)
{
	_x = x;
	_changed = true;
	notifyObservers();
}

//
int NTLabel::x() const
{
	return _x;
}

//
void NTLabel::sety(int y)
{
	_y = y;
	_changed = true;
	notifyObservers();
}

//
int NTLabel::y() const
{
	return _y;
}

//
void NTLabel::setColor(nt::color color)
{
	_color = color;
	_changed = true;
	notifyObservers();
}

//
nt::color NTLabel::color() const
{
	return _color;
}

//
void NTLabel::setTransparent(bool transparent)
{
	_transparent = transparent;
	_changed = true;
	notifyObservers();
}

//
bool NTLabel::isTransparent() const
{
	return _transparent;
}

//
void NTLabel::draw() {
// Добавить мутекс!
	//if (!_supports_rgb) return false;
	//
	short color_id = 100;
	short colorBg_id = 101;

	//
	short r_text = _color.red; short g_text = _color.green; short b_text = _color.blue;
	short r_bg = _bgColor.red; short g_bg = _bgColor.green; short b_bg = _bgColor.blue;
{
	// Создаем новый цвет в палитре
	init_color(color_id, r_text * 1000 / 255, g_text * 1000 / 255, b_text * 1000 / 255);
	init_color(colorBg_id, r_bg * 1000 / 255, g_bg * 1000 / 255, b_bg * 1000 / 255);

	// Связываем цветовую пару
	init_pair(9, color_id, colorBg_id);

	attron(COLOR_PAIR(9));
	// Предусмотреть, чтобы не печаталась часть строки, выходящая за пределы окна терминала!
	// ...
	mvprintw(_y, _x, "%s", _text.c_str());
	attroff(COLOR_PAIR(9));

	refresh();
}
	//
	_changed = false;
}
