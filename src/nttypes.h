/*!	\file		nttypes.h
 *	\brief		Header file containing basic data types for NT project
 *	\details	Contains the definitions and types.
 *	\author		Arthur Markaryan
 *	\date		09.05.2025
 *	\copyright	Arthur Markaryan
 */

#ifndef _NTTYPES_H_
#define _NTTYPES_H_

/*!	\brief	Standard string library */
#include <string>
/*! \brief  Standard vector library */
#include <vector>

/*!	\brief	ncurses library */
#include <ncurses.h>

/* Error codes */
constexpr int NT_OK					= 0;		/*!< No error - OK */
constexpr int NT_ERR				= (1 << 0);	/*!< General error - ERR */
constexpr int NT_ERR_RANGE_Y		= (1 << 1);	/*!< Range Y error - Y-position out of bounds */
constexpr int NT_ERR_RANGE_X		= (1 << 2);	/*!< Range X error - Y-position out of bounds */
constexpr int NT_ERR_INVISIBLE_Y	= (1 << 3);	/*!< Text is invisible y-coordinates */
constexpr int NT_ERR_INVISIBLE_X	= (1 << 4);	/*!< Text is invisible x-coordinates */

/*!
 *  \namespace nt
 *  \brief     Namespace containing core types for NT project
 */
namespace nt {
	/*!
	 *  \struct Color
	 *  \brief    Structure representing RGB color format
	 */
	struct Color {
		unsigned char red;    /*!< Red color component (0-255) */
		unsigned char green;  /*!< Green color component (0-255) */
		unsigned char blue;   /*!< Blue color component (0-255) */
	};

	/*!
	 *  \struct Image
	 *  \brief    Structure representing symbol map of the image
	 */
	struct Image {
		std::vector<std::string> img;	/*!< Symbol map of the image */
		unsigned int width;				/*!< Image width */
		unsigned int height;			/*!< Image height */
	};

} // namespace nt

#endif // _NTTYPES_H_
