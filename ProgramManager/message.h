#pragma once

#include "ObjectType.h"
#include "message_args.h"
#include "message_type.h"

#include <functional>

namespace ProgramManager
{
	class ApplicationObject;

	class Message
	{
		size_t mType_ObjectSet;
		size_t mType_ObjectBack;
		std::shared_ptr<ApplicationObject> mObjectBack;
		MessageArgs mArgs;
		std::function<void(MessageArgs)> mFunction;
		int                              mFunctionId_Set  = -1;
		int                              mFunctionId_Back = -1;
		MessageType mType = MessageType::Function;
	public:
		Message(size_t objectTypeSet, MessageArgs args, int functionId = -1)
		{
			mFunctionId_Set	 = functionId;
			mType_ObjectSet  = objectTypeSet;
			mArgs			 = args;
		}

		/*Message(size_t messageFor, size_t messageBack, MessageArgs args, int functionIdFor, int functionIdBack)
		{
			mFunctionIdFor    = functionIdFor;
			mFunctionIdBack   = functionIdBack;
			mType_MessageBack = messageBack;
			mType_MessageFor  = messageFor;
			mArgs			  = args;
		}*/

		Message(std::function<void(MessageArgs)> fn, MessageArgs args)
		{
			mFunction	= fn;
			mArgs		= args;
		}

		/*Message(std::shared_ptr<ApplicationObject> & messageBack, std::function<void(MessageArgs)> fn, MessageArgs args)
		{
			mMessageBack = messageBack;
			mFunction	 = fn;
			mArgs		 = args;
		}*/

		//
		// Funkcia sa pouziva na vratenie spat nejakej hodnoty z ineho objektu do pozadovaneho (toho ktory to prave vyvolava, 
		// alebo ak mame jeho shared pointer)
		// argumenty sa musia naplnit, tzn. to co chceme aby sa vytiahlo z objektu
		//
		Message(size_t objectGet, std::shared_ptr<ApplicationObject>& objectBack, std::function<void(MessageArgs)> fn, MessageArgs args)
		{
			mType_ObjectSet = objectGet;
			mObjectBack		 = objectBack;
			mFunction		 = fn;
			mArgs			 = args;
		}

		//
		// Funkcia sa pouziva na vratenie spat nejakej hodnoty z ineho objektu do pozadovaneho (toho ktory to prave vyvolava, 
		// alebo ak mame jeho shared pointer)
		// argumenty sa nenaplnaju, tie by sa mali naplnit z objektu, z ktoreho chceme nieco
		//
		Message(size_t objectGet, int functionIdGet, std::shared_ptr<ApplicationObject>& objectBack, MessageArgs args)
		{
			mFunctionId_Set = functionIdGet;
			mType_ObjectSet = objectGet;
			mObjectBack = objectBack;
			mArgs = args;
		}

		//
		// 
		//
		Message(size_t objectGet, int functionIdGet, std::function<void(MessageArgs)> fn, MessageArgs args)
		{
			mFunctionId_Set = functionIdGet;
			mType_ObjectSet = objectGet;
			mFunction = fn;
			mArgs = args;
		}

		void SetArguments(MessageArgs args) { mArgs = args; }

		size_t								GetMessageFor	 () const { return mType_ObjectSet; }
		std::shared_ptr<ApplicationObject>	GetMessageBack	 () const { return mObjectBack; }
		MessageArgs							GetArguments	 () const { return mArgs; }
		std::function<void(MessageArgs)>	GetFunction		 () const { return mFunction; }
		int									GetFunctionIdFor () const { return mFunctionId_Set; }
		int									GetFunctionIdBack() const { return mFunctionId_Back; }

		/*void Execute(MessageArgs args = MessageArgs())
		{
			
		}*/

		MessageType GetType() const { return mType; }
	protected:
		friend class Dispatcher;
		void        SetType(MessageType type) { mType = type; }
	};
}