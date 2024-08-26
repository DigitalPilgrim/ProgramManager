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
		size_t mType_ObjectSet  = 0;
		size_t mType_ObjectBack = 0;
		std::shared_ptr<ApplicationObject> mObjectBack;
		MessageArgs mArgs;
		std::function<void(MessageArgs)> mFunction;
		int                              mFunctionId_Set  = -1;
		int                              mFunctionId_Back = -1;
		MessageType mType = MessageType::Function;

#pragma region Private Constructors

		Message(size_t objectTypeSet, MessageArgs args, int functionId = -1)
		{
			mType = MessageType::Set;
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
			mType = MessageType::Function;
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
			mType = MessageType::Get;
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
			mType = MessageType::Get;
			mFunctionId_Set = functionIdGet;
			mType_ObjectSet = objectGet;
			mObjectBack = objectBack;
			mArgs = args;
		}

		Message(size_t objectGet, int functionIdGet, std::shared_ptr<ApplicationObject>& objectBack, int functionIdBack, MessageArgs args)
		{
			mType = MessageType::Get;
			mFunctionId_Set = functionIdGet;
			mFunctionId_Back = functionIdBack;
			mType_ObjectSet = objectGet;
			mObjectBack = objectBack;
			mArgs = args;
		}

		Message(size_t objectGet, int functionIdGet, size_t objectBack, int functionIdBack, MessageArgs args)
		{
			mType = MessageType::Get;
			mFunctionId_Set = functionIdGet;
			mFunctionId_Back = functionIdBack;
			mType_ObjectSet = objectGet;
			mType_ObjectBack = objectBack;
			mArgs = args;
		}

		Message(size_t objectGet, int functionIdGet, size_t objectBack, std::function<void(MessageArgs)> fn, MessageArgs args)
		{
			mType = MessageType::Get;
			mFunctionId_Set = functionIdGet;
			mType_ObjectSet = objectGet;
			mType_ObjectBack = objectBack;
			mFunction = fn;
			mArgs = args;
		}

		//
		// 
		//
		Message(size_t objectGet, int functionIdGet, std::function<void(MessageArgs)> fn, MessageArgs args)
		{
			mType = MessageType::Get;
			mFunctionId_Set = functionIdGet;
			mType_ObjectSet = objectGet;
			mFunction = fn;
			mArgs = args;
		}

#pragma endregion

	public:
		// ==================================================================================================================================

		// CreateFunction
		static Message Set(
			std::function<void(MessageArgs)> fn // = funktor ktory sa ma vykonat a predaju sa mu vlozene argumenty (args)
			, MessageArgs args)					// = argumenty (volitelne)
		{
			return Message(fn, args);
		}

		// ---------------------------------------------------------------------------------------------------------------------------------

		static Message Set(
			size_t objectTypeSet // = type objektu na ktorom sa zavola dana funkcia(functionId) s argumentmi(args)
			, MessageArgs args	 // = argumenty (musia byt naplnene ak chceme nieco predat, pokial je to funkcia bez argumentov)
			, int functionId)	 // = funkcia ktora sa ma zavolat pre objectTypeSet
		{
			return Message(objectTypeSet, args, functionId);
		}

		// ---------------------------------------------------------------------------------------------------------------------------------

		// CreateGet
		// objectGet	 = type objektu z ktoreho sa naplnia argumenty (args)
		// objectBack	 = objekt pre ktoreho su argumenty urcene (je to realny objekt, avsak je to bezpecne aj ked sa predava do ineho vlakna, pretoze tam sa zavola len z neho dispatcher ktory drzi a preda spat spravu)
		// fn			 = funkcia ktora sa ma zavolat pre objectBack (tzn. zavola sa uz vo vlakne v ktorom lezi objectBack)
		// args			 = argumenty (musia byt naplnene objektmi ktore chceme aby boli naplnene, avsak ich hodnoty nemusia davat zmysel, napr ak chceme naplnit std::string tak ho tam vlozime ako prazdny, a je to na objectGet aby ho naplnil)
		static Message Get(
			size_t objectGet
			, std::shared_ptr<ApplicationObject>& objectBack
			, std::function<void(MessageArgs)> fn
			, MessageArgs args)
		{
			return Message(objectGet, objectBack, fn, args);
		}

		// CreateGet
		// objectGet	 = type objektu z ktoreho sa naplnia argumenty (args)
		// functionIdGet = funkcia z ktorej sa maju zobrat argumenty z objektu objectGet
		// objectBack	 = objekt pre ktoreho su argumenty urcene (je to realny objekt, avsak je to bezpecne aj ked sa predava do ineho vlakna, pretoze tam sa zavola len z neho dispatcher ktory drzi a preda spat spravu)
		// args			 = ak potrebujeme z functionIdGet predat nejaku urcujuci argument napr pre funkciu GetItem(id)
		static Message Get(size_t objectGet, int functionIdGet, std::shared_ptr<ApplicationObject>& objectBack, MessageArgs args = MessageArgs())
		{
			return Message(objectGet, functionIdGet, objectBack, args);
		}

		// CreateGet
		// objectGet	 = type objektu z ktoreho sa naplnia argumenty (args)
		// functionIdGet = funkcia z ktorej sa maju zobrat argumenty z objektu objectGet
		// objectBack	 = objekt pre ktoreho su argumenty urcene (je to realny objekt, avsak je to bezpecne aj ked sa predava do ineho vlakna, pretoze tam sa zavola len z neho dispatcher ktory drzi a preda spat spravu)
		// functionIdBack = funkcia do ktorej sa predaju ziskane argumenty pre objectBack
		// args			  = ak potrebujeme z functionIdGet predat nejaku urcujuci argument napr pre funkciu GetItem(id)
		static Message Get(size_t objectGet, int functionIdGet, std::shared_ptr<ApplicationObject>& objectBack, int functionIdBack, MessageArgs args = MessageArgs())
		{
			return Message(objectGet, functionIdGet, objectBack, functionIdBack, args);
		}

		// CreateGet
		// objectGet	 = type objektu z ktoreho sa naplnia argumenty (args)
		// functionIdGet = funkcia z ktorej sa maju zobrat argumenty z objektu objectGet
		// objectBack	 = objekt pre ktoreho su argumenty urcene
		// functionIdBack = funkcia do ktorej sa predaju ziskane argumenty pre objectBack
		// args			  = ak potrebujeme z functionIdGet predat nejaku urcujuci argument napr pre funkciu GetItem(id)
		static Message Get(size_t objectGet, int functionIdGet, size_t objectBack, int functionIdBack, MessageArgs args = MessageArgs())
		{
			return Message(objectGet, functionIdGet, objectBack, functionIdBack, args);
		}

		// CreateGet
		// objectGet	 = type objektu z ktoreho sa naplnia argumenty (args)
		// functionIdGet = funkcia z ktorej sa maju zobrat argumenty z objektu objectGet
		// objectBack	 = objekt pre ktoreho su argumenty urcene
		// functionBack  = funktor do ktoreho sa predaju ziskane argumenty pre objectBack a zavola ho objectBack
		// args			  = ak potrebujeme z functionIdGet predat nejaku urcujuci argument napr pre funkciu GetItem(id)
		static Message Get(size_t objectGet, int functionIdGet, size_t objectBack, std::function<void(MessageArgs)> fn, MessageArgs args = MessageArgs())
		{
			return Message(objectGet, functionIdGet, objectBack, fn, args);
		}

		// CreateGet
		// objectGet	 = type objektu z ktoreho sa naplnia argumenty (args)
		// functionIdGet = funkcia z ktorej sa maju zobrat argumenty z objektu objectGet
		// fn			 = funktor ktory sa vyvola tam, kde sa berie objektGet, tzn ak je objekt v inom vlakne ako sa vola
		//				   Message::Get() tak funktor sa vola v druhom vlakne
		// args			  = ak potrebujeme z functionIdGet predat nejaku urcujuci argument napr pre funkciu GetItem(id)
		static Message Get(size_t objectGet, int functionIdGet, std::function<void(MessageArgs)> fn, MessageArgs args = MessageArgs())
		{
			return Message(objectGet, functionIdGet, fn, args);
		}

		// ==================================================================================================================================

		void SetArguments(MessageArgs args) { mArgs = args; }

		size_t								GetTypeObjectFor () const { return mType_ObjectSet; }
		size_t								GetTypeObjectBack() const { return mType_ObjectBack; }
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
		void        SetObjectBack(std::shared_ptr<ApplicationObject>& obj) { mObjectBack = obj; }
	};
}