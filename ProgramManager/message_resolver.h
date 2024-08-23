#pragma once

#include "ApplicationObject.h"
#include "message.h"
#include <list>

namespace ProgramManager
{
	/* --------------------------------------------------------------------------------------- //
		MessageResolver vyhodit a vsetko vlozit do Dispatchera mozno
	// --------------------------------------------------------------------------------------- */
	class MessageResolver
	{
	public:
		typedef std::shared_ptr<ApplicationObject> Object;
		typedef std::list<Object>				   ListOfObjects;
		typedef std::vector<Object>                VectorOfObjects;

	protected:
		ListOfObjects mObjects;

	public:
		MessageResolver() {}

		// -------------------------------------------------------

		void SetObjects(ListOfObjects objects)
		{
			mObjects = objects;
		}

		// -------------------------------------------------------

		void AddObject(Object object)
		{
			mObjects.push_back(object);
		}

		// -------------------------------------------------------
		template<typename T>
		bool GetObject(std::shared_ptr<T> & object)
		{
			for (Object o : mObjects) {
				if (o->Type == ObjectType::GetStaticType<T>()) {
					object = std::static_pointer_cast<T>(o);
					return true;
				}
			}
			return false;
		}

		// -------------------------------------------------------

		bool RemoveObject(Object & object)
		{
			mObjects.remove(object);
			return true;
			/*for (Object o : mObjects) {
				if (o.get() == object.get()) {
					
				}
			}*/
		}

		// -------------------------------------------------------

		void Resolve(Message & msg)
		{
			/*
				Message sa musi delit na Set message a normalnu message
				Set message naplna argumenty
				normalna message uz ma argumenty naplnene uz len poslat

				Send(Message(SendFrom, [SendTo](MessageArgs args) {
						SendTo->Export(args);
					}, MessageArgs(arguments));

				SendBack(Message( Dispatcher::Painter
							, (size_t type) sendFrom
							, (size_t type) sendTo
							, arguments
							));

				SendBack(Message( Dispatcher::Painter
							, (size_t type) sendFrom
							, [sendTo](MessageArgs args) {
								sendTo->Export(...);
							}
							, arguments
							));

				Send(Message(Dispatcher::Painter
							, (size_t type) sendTo
							, arguments)); {
					for (arg : arguments) {
						if (sendTo->Conatin(arg)) {
							sendTo->Set(arg);
						}
					}
				}

				napr.
				if (msg.IsSet()) {
					MessageArgs args = msg.GetArguments();
					// vytiahny argumenty

				}
			*/

			Object object;

			if (msg.GetType() == MessageType::Function)
			{
				auto function = msg.GetFunction();
				if (function)
				{
					function(msg.GetArguments());
				}
			}
			else if (msg.GetType() == MessageType::Set)
			{
				for (auto obj : mObjects)
				{
					if (obj->Type == msg.GetMessageFor())
					{
						object = obj;
						break;
					}
				}

				if (object) {
					object->Set(msg.GetArguments(), msg.GetFunctionIdFor());
				}
			}
			else if (msg.GetType() == MessageType::Get)
			{
				Object getFrom;
				for (auto obj : mObjects)
				{
					if (obj->Type == msg.GetMessageFor())
					{
						getFrom = obj;
						break;
					}
				}
				if (getFrom) {
					auto args = msg.GetArguments();
					getFrom->Get(args, msg.GetFunctionIdFor());
					auto function = msg.GetFunction();

					object = msg.GetMessageBack();
					if (object)
					{
						if (function) {
							Message new_message(function, args);
							object->ExecuteMessage(new_message, MessageType::Function);
						}
						else {
							Message new_message(msg.GetMessageBack()->Type, args, msg.GetFunctionIdBack());
							object->ExecuteMessage(new_message, MessageType::Set);
						}
					}
					else if (function) {
						function(args);
					}
				}
			}

			/*Object object;
			VectorOfObjects arguments;
			MessageArgs args = msg.GetArguments();
			for (auto obj : mObjects)
			{
				if (obj->Type == msg.GetMessageFor().Type)
				{
					object = obj;
					break;
				}
			}
			for (auto arg : args.Arguments)
			{
				for (auto obj : mObjects)
				{
					if (arg->Type == obj->Type)
					{
						arguments.push_back(obj);
					}
				}
			}

			if (object)
			{
				object->ExecuteMessage();
			}
			else 
			{
				msg.SetArguments(args);
			}*/
		}

		// -------------------------------------------------------

	};
}