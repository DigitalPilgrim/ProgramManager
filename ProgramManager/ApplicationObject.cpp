#include "ApplicationObject.h"

#include "message_args.h"
#include "message.h"

void ProgramManager::ApplicationObject::Set(MessageArgs args, int idFunction)
{
	ExecuteSet(args, idFunction);
}

void ProgramManager::ApplicationObject::Get(MessageArgs& args, int idFunction)
{
	ExecuteGet(args, idFunction);
}

void ProgramManager::ApplicationObject::ExecuteMessage(Message& msg, MessageType type)
{
	switch (type)
	{
	case MessageType::Set:		mDispatcher.SendSet(msg); break;
	case MessageType::Get:		mDispatcher.SendGet(msg); break;
	case MessageType::Function: mDispatcher.Send(msg); break;
	}
}
