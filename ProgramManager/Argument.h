#pragma once

#include "ApplicationObject.h"

#include <memory>

namespace ProgramManager
{
	template <typename T>
	class ObjectMeta;

	// -----------------------------------------------------------

	class ObjectBase
	{
	protected:
		size_t mType = 0;
	public:
		virtual ~ObjectBase() {}

		template <typename T>
		bool GetObject(T& object) {
			if (typeid(T).hash_code() == mType) {
				object = static_cast<ObjectMeta<T>*>(this)->GetObject();
				return true;
			}
			else return false;
		}
	};

	// -----------------------------------------------------------

	template <typename T>
	class ObjectMeta : public ObjectBase
	{
		T mObject;
	public:
		ObjectMeta() { mType = typeid(T).hash_code(); }
		ObjectMeta(T& o) { 
			mObject	 = o;
			mType	 = typeid(T).hash_code();
		}

		T& GetObject() { return mObject; }
	};

	// -----------------------------------------------------------
	// -----------------------------------------------------------

	class Argument : public ApplicationObject
	{
		ObjectBase* mObject = nullptr;
	public:

		/*template <typename T>
		Argument()
		{
			SetType<T>();
			mObject = new ObjectMeta<T>();
		}*/

		template <typename T>
		Argument(T o)
		{
			SetType<T>();
			mObject = new ObjectMeta<T>(o);
		}

		/*template <typename T>
		Argument(T&& o)
		{
			SetType<T>();
			mObject = new ObjectMeta<T>(o);
		}*/

		~Argument()
		{
			if (mObject != nullptr) delete mObject;
		}

		template <typename T>
		bool GetArgument(T& object) {
			if (mObject) {
				return mObject->GetObject(object);
			}
			else return false;
		}

		/*template <typename T>
		static std::shared_ptr<Argument> Create() {
			T o;
			return std::make_shared<Argument>(o);
		}*/

		template <typename T>
		static std::shared_ptr<Argument> Create(T o) {
			return std::make_shared<Argument>(o);
		}
	};
}