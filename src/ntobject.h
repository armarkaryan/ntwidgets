/*!	\file		ntobject.h
 *	\brief		Base class module for NT (header file).
 *	\details	Contains the NTObject class definitions.
 *	\author		Arthur Markaryan
 *	\date		18.04.2025
 *	\copyright	Arthur Markaryan
 */

#ifndef _NTOBJECT_H_
#define _NTOBJECT_H_

/*!	\brief	Standard vector library */
#include <vector>
/*!	\brief	Standard string library */
#include <string>
/*!	\brief	Standard functional library (for std::function) */
#include <functional>

/*!	\brief	Base NT types */
#include "nttypes.h"

/*!	\class		NTObject
 *	\brief		Base class for NT objects.
 *	\details	Represents the core functionality for objects in the NT system.
 *			Provides parent-child relationships, naming, and observer pattern support.
 */
class NTObject {
public:
	/*!	\brief		Constructor
	 *	\param		parent	Pointer to the parent object (default: nullptr)
	 *	\param		name	Object name (default: empty string)
	 */
	NTObject(NTObject *parent = nullptr, const std::string &name = "");

	/*!	\brief	Virtual destructor to allow proper inheritance */
	~NTObject();

	/*!	\brief		Sets the parent object
	 *	\details	Updates the parent-child relationship.
	 *			Automatically handles removal from previous parent's children list
	 *			and addition to new parent's children list.
	 *	\param		parent	Pointer to the parent object
	 *	\note		Pass nullptr to remove parent relationship
	 */
	void setParent(NTObject *parent);

	/*!	\brief		Gets the parent object
	 *	\return		Pointer to the parent object or nullptr if none exists
	 */
	NTObject *parent() const;

	/*!	\brief		Sets the object name
	 *	\param		name	New name for the object
	 */
	void setName(const std::string &name);

	/*!	\brief		Gets the object name
	 *	\return		Current name of the object
	 */
	std::string name() const;

	/*!	\brief		Callback type definition for observer pattern
	 *	\details	std::function wrapper for void() callbacks
	 */
	using Callback = std::function<void()>;

	/*!	\brief		Adds an observer callback
	 *	\details	The callback will be executed when notifyObservers() is called
	 *	\param		callback	Function to be called on notification
	 *	\note		Marked as const to allow observation even of const objects
	 */
	void addObserver(Callback callback) const {
		_observers.push_back(callback);
	}

	/*!	\brief		Notifies all registered observers
	 *	\details	Executes all registered callbacks in registration order
	 */
	void notifyObservers() {
		for (auto& callback : _observers) {
			callback();
		}
	}

private:
	NTObject *_parent;		/*!< Pointer to parent object */
	std::string _name;		/*!< Object name */

	/*!	\brief		List of observer callbacks
	 *	\details	Marked as mutable to allow modification even in const methods
	 */
	mutable std::vector<Callback> _observers;
};

#endif // _NTOBJECT_H_
