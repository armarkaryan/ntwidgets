/*! \file       digits_16x16.h
 *  \brief      16x16 Images of "0" to "9" digits (header file).
 *  \details    Contains the images of digits from "0" to "9" 16x16 size. Useing in the NT system.
 *  \author     Arthur Markaryan
 *  \date       20.04.2025
 *  \copyright  Arthur Markaryan
 */

#ifndef _DIGITS_16X16_H_
#define _DIGITS_16X16_H_

/*!	\brief	Standard vector library */
#include <vector>
/*!	\brief	Standard string library */
#include <string>

/*!	\brief	Base NT types */
#include "nttypes.h"

// Digit "0"
const struct nt::Image digit_16x16_0 = {
	{	// img
		"                ",
		"     XXXXX      ",
		"    X     X     ",
		"   X     X X    ",
		"   X     X X    ",
		"   X     X  X   ",
		"   X    X   X   ",
		"   X    X    X  ",
		"  X    X     X  ",
		"  X    X     X  ",
		"  X    X     X  ",
		"   X  X      X  ",
		"    X X     X   ",
		"     XXXXXXX    ",
		"                ",
		"                "
	},
	16,	// width
	16	// height
};

// Digit "1"
const struct nt::Image digit_16x16_1 = {
	{	// img
		"                ",
		"          X     ",
		"         XX     ",
		"        X X     ",
		"       X  X     ",
		"     XX  X      ",
		"         X      ",
		"        X       ",
		"        X       ",
		"        X       ",
		"       X        ",
		"       X        ",
		"       X        ",
		"       X        ",
		"       X        ",
		"                "
	},
	16,	// width
	16	// height
};

// Digit "2"
const struct nt::Image digit_16x16_2 = {
	{	// img
		"       XXXXX    ",
		"     XX     X   ",
		"            X   ",
		"             X  ",
		"             X  ",
		"            X   ",
		"            X   ",
		"           X    ",
		"          X     ",
		"       XXX      ",
		"    XXX         ",
		"   X            ",
		"  XXXX          ",
		"      XXX       ",
		"         XXX    ",
		"                "
	},
	16,	// width
	16	// height
};

// Digit "3"
const struct nt::Image digit_16x16_3 = {
	{	// img
		"                ",
		"     XXXXXX     ",
		"    X      X    ",
		"           X    ",
		"         XX     ",
		"      XXX       ",
		"         XX     ",
		"           X    ",
		"           X    ",
		"           X    ",
		"           X    ",
		"           X    ",
		"          X     ",
		"   X    XX      ",
		"    XXXX        ",
		"                "
	},
	16,	// width
	16	// height
};

// Digit "4"
const struct nt::Image digit_16x16_4 = {
	{	// img
		"                ",
		"           X    ",
		"   X       X    ",
		"   X       X    ",
		"   X      X     ",
		"    X     X     ",
		"    X     X     ",
		"    X     X     ",
		"     XXXXXX     ",
		"          X     ",
		"          X     ",
		"          X     ",
		"          X     ",
		"          X     ",
		"           X    ",
		"                "
	},
	16,	// width
	16	// height
};

// Digit "5"
const struct nt::Image digit_16x16_5 = {
	{	// img
		"         XX     ",
		"      XXX       ",
		"    XX          ",
		"    X           ",
		"    X           ",
		"     X  XXX     ",
		"     XXX   X    ",
		"            X   ",
		"            X   ",
		"            X   ",
		"          X     ",
		"          X     ",
		"         X      ",
		"       XX       ",
		"     XX         ",
		"                "
	},
	16,	// width
	16	// height
};

// Digit "6"
const struct nt::Image digit_16x16_6 = {
	{	// img
		"                ",
		"         XXXX   ",
		"       XX       ",
		"      X         ",
		"     X          ",
		"    X XX        ",
		"    X   X       ",
		"   X     X      ",
		"   X      X     ",
		"   X       X    ",
		"  X        X    ",
		"  X       X     ",
		"  X       X     ",
		"   XX     X     ",
		"     XXXXX      ",
		"                "
	},
	16,	// width
	16	// height
};

// Digit "7"
const struct nt::Image digit_16x16_7 = {
	{	// img
		"                ",
		"    XXXXXXX     ",
		"           XX   ",
		"            X   ",
		"            X   ",
		"           X    ",
		"           X    ",
		"         XX     ",
		"       XX       ",
		"      X         ",
		"      X         ",
		"     X          ",
		"    X           ",
		"    X           ",
		"                ",
		"                "
	},
	16,	// width
	16	// height
};

// Digit "8"
const struct nt::Image digit_16x16_8 = {
	{	// img
		"     XXXXXX     ",
		"    X      X    ",
		"   X        X   ",
		"   X        X   ",
		"   X        X   ",
		"   X        X   ",
		"    X      X    ",
		"   X XXXX  X    ",
		"  X      XX X   ",
		"  X         X   ",
		"  X         X   ",
		"  X         X   ",
		"  X         X   ",
		"   XX      X    ",
		"     XXXXXX     ",
		"                "
	},
	16,	// width
	16	// height
};

// Digit "9"
const struct nt::Image digit_16x16_9 = {
	{	// img
		"                ",
		"     XXXXXX     ",
		"    X      X    ",
		"   X       X    ",
		"   X       X    ",
		"   X       X    ",
		"   X       X    ",
		"    XXXXXXX     ",
		"          X     ",
		"        XX      ",
		"       X        ",
		"      X         ",
		"     X          ",
		"   XX           ",
		"                ",
		"                "
	},
	16,	// width
	16	// height
};

// Array of digits image from 0 to 9
const std::vector<nt::Image> digits_16x16 = {
	digit_16x16_0,
	digit_16x16_1,
	digit_16x16_2,
	digit_16x16_3,
	digit_16x16_4,
	digit_16x16_5,
	digit_16x16_6,
	digit_16x16_7,
	digit_16x16_8,
	digit_16x16_9
};

#endif // _DIGITS_16X16_H_
