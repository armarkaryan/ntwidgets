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

/* Error codes */
constexpr int NT_OK		= 0;	/*!< No error - OK */
constexpr int NT_ERR	= -1;	/*!< General error - ERR */
constexpr int NT_ERR_RANGE = -2;	/*!< Range error - out of bounds */

/*!
 *  \namespace nt
 *  \brief     Namespace containing core types for NT project
 */
namespace nt {
	/*!
	 *  \struct color
	 *  \brief    Structure representing RGB color format
	 */
	struct color {
		unsigned char red;    /*!< Red color component (0-255) */
		unsigned char green;  /*!< Green color component (0-255) */
		unsigned char blue;   /*!< Blue color component (0-255) */
	};

	//
	struct Image {
		std::vector<std::string> img;
		unsigned int width;
		unsigned int height;
	};


} // namespace nt

#endif // _NTTYPES_H_
