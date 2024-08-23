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

void ProgramManager::DispatcherHolder::SendSet(Message msg)
{
	mDsp->SendSet(msg);
}

void ProgramManager::DispatcherHolder::SendGet(Message msg)
{
	mDsp->SendGet(msg);
}

void ProgramManager::DispatcherHolder::ManagerSendFunction(int thread_type, Message msg)
{
	mDsp->ManagerSendFunction(thread_type, msg);
}

void ProgramManager::DispatcherHolder::ManagerSendSet(int thread_type, Message msg)
{
	mDsp->ManagerSendSet(thread_type, msg);
}

void ProgramManager::DispatcherHolder::ManagerSendGet(int thread_type, Message msg)
{
	mDsp->ManagerSendGet(thread_type, msg);
}

int ProgramManager::DispatcherHolder::GetThreadType() const
{
	return mDsp->GetThreadType();
}
