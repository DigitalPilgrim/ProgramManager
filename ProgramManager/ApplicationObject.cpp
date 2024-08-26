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

void ProgramManager::ApplicationObject::ExecuteMessage(Message& msg)
{
	mDispatcher.Send(msg);
}
