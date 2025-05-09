#ifndef _NTTYPES_H_
#define _NTTYPES_H_

/*!	\file		nttypes.h
 *	\brief		Header file containing basic data types for NT project
 *	\details	Contains the definitions and types.
 *	\author		Arthur Markaryan
 *	\date		09.05.2025
 *	\copyright	Arthur Markaryan
 */

/*!	\brief	Standard string library */
#include <string>

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

} // namespace nt

#endif // _NTTYPES_H_
