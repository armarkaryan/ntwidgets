/*! \file       nlgraphicobject.h
 *  \brief      NTGraphicObject module (header file).
 *  \details    Contains the NTGraphicObject class definitions in the NT system.
 *  \author     Arthur Markaryan
 *  \date       13.05.2025
 *  \copyright  Arthur Markaryan
 */

#ifndef _NTGRAPHICOBJECT_H_
#define _NTGRAPHICOBJECT_H_

/*! \brief  Mutex library */
#include <mutex>

/*! \brief  Base NT object */
#include "ntobject.h"
/*!	\brief	Base NT types */
#include "nttypes.h"

class NTGraphicObject : public NTObject {
public:
	/*!	\brief		Default constructor
	 *	\param		parent	Pointer to the parent object (default: nullptr)
	 *	\param		name	Label name (default: empty string)
	 */
	NTGraphicObject(NTObject* parent = nullptr, const std::string& name = "");

	/*!	\brief		Parameterized constructor
	 *	\param		parent		Pointer to the parent object
	 *	\param		name		Graphic Object name
	 *	\param		x			Initial X position
	 *	\param		y			Initial Y position
	 *	\param		color		Initial text color
	 *	\param		bgColor		Initial background color
	 *	\param		transparent	Initial transparency flag
	 */
	NTGraphicObject(NTObject* parent, const std::string& name,
				   int x, int y,
				   nt::color color, nt::color bgColor,
				   bool transparent);

/*!	\brief		Copy constructor
 *	\param		other	Reference to source NTLabel object
 */
NTGraphicObject(const NTGraphicObject& other);

	virtual ~NTGraphicObject() = default;

/*!	\brief		Assignment operator
 *	\param		other	Reference to source NTLabel object
 *	\return		Reference to the assigned NTLabel object
 */
NTGraphicObject& operator=(const NTGraphicObject& other);

	/*! \brief      Sets the X coordinate
	 *  \param      x   New X coordinate value
	 */
	void setx(int x);

	/*! \brief      Gets the X coordinate
	 *  \return     Current X coordinate value
	 */
	int x() const;

	/*! \brief      Sets the Y coordinate
	 *  \param      y   New Y coordinate value
	 */
	void sety(int y);

	/*! \brief      Gets the Y coordinate
	 *  \return     Current Y coordinate value
	 */
	int y() const;

	/*! \brief      Sets the X, Y coordinate
	 *  \param[in]	x   New X coordinate value
	 *	\param[in]	y   New Y coordinate value
	 */
	void setPosition(int x, int y);

	/*! \brief      Sets the text color
	 *  \param      color   New text color value
	 */
	void setColor(nt::color color);

	/*! \brief      Gets the text color
	 *  \return     Current text color value
	 */
	nt::color color() const;

	/*! \brief      Sets the background color
	 *  \param      color   New background color value
	 */
	void setBgColor(nt::color bgColor);

	/*! \brief      Gets the background color
	 *  \return     Current background color value
	 */
	nt::color bgColor() const;

	/*! \brief      Sets the transparency flag
	 *  \param      transparent New transparency value
	 */
	void setTransparent(bool transparent);

	/*! \brief      Gets the image transparency flag
	 *  \return     true if transparent false otherwise
	 */
	bool transparent() const;

	/*! \brief      Gets the Text Label changed flag
	 *  \return     true if changed false otherwise
	 */
	bool isChanged() const;

	// Виртуальный метод для отрисовки (должен быть переопределен)
	virtual int draw() = 0;

protected:
	mutable std::mutex _mutex;	/*!< Thread-safe mutex */
	unsigned short _x;			/*!< X coordinate */
	unsigned short _y;			/*!< Y coordinate */
	nt::color _color;			/*!< Text Color */
	nt::color _bgColor;			/*!< Background Color */
	bool _transparent;			/*!< Transparency flag */
	bool _changed;				/*!< Changed flag */
};
#endif // _NTGRAPHICOBJECT_H_
