/*!	\file		ntobject.cpp
 *	\brief		Implementation of the NTObject class
 *	\author		Arthur Markaryan
 *	\date		18.04.2025
 *	\copyright	Arthur Markaryan
 */

#include "ntobject.h"

// Constructor
NTObject::NTObject(NTObject *parent, const std::string &name) :
    _parent(parent),
    _name(name)
{
    // Initialization handled in member initializer list
}

// Destructor
NTObject::~NTObject()
{
    // No dynamic resources to free
}

// Sets the parent object
void NTObject::setParent(NTObject *parent)
{
    _parent = parent;
}

// Gets the parent object
NTObject *NTObject::parent() const
{
    return _parent;
}

// Sets the object name
void NTObject::setName(const std::string &name)
{
    _name = name;
}

// Gets the object name
std::string NTObject::name() const
{
    return _name;
}
