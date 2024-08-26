#include "dispatcher_holder.h"

#include "message.h"
#include "dispatcher.h"

ProgramManager::DispatcherHolder::DispatcherHolder(Dispatcher* dsp) : mDsp(dsp)
{
}

void ProgramManager::DispatcherHolder::Send(Message msg)
{
	mDsp->Send(msg);
}

void ProgramManager::DispatcherHolder::ManagerSend(int thread_type, Message msg)
{
	mDsp->ManagerSend(thread_type, msg);
}

int ProgramManager::DispatcherHolder::GetThreadType() const
{
	return mDsp->GetThreadType();
}
