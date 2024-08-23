#include "delegate.h"

#include "message_args.h"

void ProgramManager::Delegate::ExecuteSet(MessageArgs args)
{
	mDelegate->ExecuteSet(args);
}

void ProgramManager::Delegate::ExecuteGet(MessageArgs& args)
{
	mDelegate->ExecuteGet(args);
}
