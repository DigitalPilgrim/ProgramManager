#pragma once

#include "ObjectType.h"
#include "dispatcher_holder.h"
#include "message_type.h"
#include "function_holder.h"
#include <memory>

namespace ProgramManager {

	class Message;
	struct MessageArgs;

	class ApplicationObject
		: public ObjectType
		, public FunctionHolder
	{
		/*friend class Dispatcher;
		ApplicationObject * mParent = nullptr;*/
		//int mThreadType = -1;
	protected:
		DispatcherHolder mDispatcher;

	public:
		ApplicationObject() {}
		//ApplicationObject(ApplicationObject* parent) : mParent(parent) {}
		ApplicationObject(DispatcherHolder & dispatcher) : mDispatcher(dispatcher) {
			//mThreadType = mDispatcher.GetThreadType();
		}
		/*template <typename T>
		ApplicationObject() : ObjectType<T>() {  }*/ // hazde mi kompilacny error
		virtual ~ApplicationObject() {}

		virtual void Init() {}

		template <typename T>
		bool GetObject(T& object) {
			if (typeid(T).hash_code() == Type) {
				object = *static_cast<T*>(this);
				return true;
			}
			else return false;
		}


		template <typename T>
		bool GetObjectP(T*& object) {
			if (typeid(T).hash_code() == Type) {
				object = static_cast<T*>(this);
				return true;
			}
			else return false;
		}

		//virtual std::shared_ptr<ApplicationObject> Copy() = 0;

		virtual void Set(MessageArgs args, int idFunction = -1);
		virtual void Get(MessageArgs& args, int idFunction = -1);

	private:
		friend class /*ProgramManager::*/MessageResolver;
		void ExecuteMessage(Message& msg, MessageType type);
	};
}

