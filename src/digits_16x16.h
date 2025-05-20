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
const std::vector<std::string> digit_16x16_5 = {
    " XXXXXX ",
    " X      ",
    " X      ",
    " XXXXX  ",
    "      X ",
    "      X ",
    " X    X ",
    "  XXXX  "
};

// Digit "6"
const std::vector<std::string> digit_16x16_6 = {
    "  XXXX  ",
    " X    X ",
    " X      ",
    " XXXXX  ",
    " X    X ",
    " X    X ",
    " X    X ",
    "  XXXX  "
};

// Digit "7"
const std::vector<std::string> digit_16x16_7 = {
    "  XXXXX ",
    "      X ",
    "      X ",
    "     X  ",
    "    X   ",
    "    X   ",
    "    X   ",
    "    X   "
};

// Digit "8"
const std::vector<std::string> digit_16x16_8 = {
    "  XXXX  ",
    " X    X ",
    " X    X ",
    "  XXXX  ",
    " X    X ",
    " X    X ",
    " X    X ",
    "  XXXX  "
};

// Digit "9"
const std::vector<std::string> digit_16x16_9 = {
    "  XXXX  ",
    " X    X ",
    " X    X ",
    " X    X ",
    "  XXXXX ",
    "      X ",
    " X    X ",
    "  XXXX  "
};

// Array of digits image from 0 to 9
const std::vector<nt::Image> digits_16x16 = {
	digit_16x16_0,
	digit_16x16_1,
	digit_16x16_2,
	digit_16x16_3,
	digit_16x16_4/*,
	digit_16x16_5,
	digit_16x16_6,
	digit_16x16_7,
	digit_16x16_8,
	digit_16x16_9*/
};

#endif // _DIGITS_16X16_H_
