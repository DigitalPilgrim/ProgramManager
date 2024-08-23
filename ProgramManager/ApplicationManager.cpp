#include "ApplicationManager.h"

#include "dispatcher.h"
#include "message.h"

ProgramManager::ApplicationManager::ApplicationManager()
{
	//Init();
}

ProgramManager::ApplicationManager::~ApplicationManager()
{
	Stop();
}

ProgramManager::Dispatcher* ProgramManager::ApplicationManager::GetDispatcher(int thread_type)
{
	Dispatcher* d = nullptr;
	for (auto& disp : mDispatchers)
	{
		if (disp->GetThreadType() == thread_type) {
			d = disp;
			break;
		}
	}
	return d;
}

void ProgramManager::ApplicationManager::Init()
{
	for (auto& disp : mObjects)
	{
		disp->Init();
	}
}

void ProgramManager::ApplicationManager::Run()
{
	mRun = true;
	for (auto& disp : mDispatchers)
	{
		disp->Run();
	}
}

void ProgramManager::ApplicationManager::Stop()
{
	for (auto& disp : mDispatchers)
	{
		disp->Stop();
	}
	for (auto& disp : mDispatchers)
	{
		disp->AfterStop();
	}

	mRun = false;
}

void ProgramManager::ApplicationManager::WaitForEnd()
{
	do {
		std::this_thread::sleep_for(std::chrono::seconds(1));
	} while (mRun);
}

void ProgramManager::ApplicationManager::SendFunction(int thread_type, Message msg)
{
	for (auto& disp : mDispatchers)
	{
		if (disp->GetThreadType() == thread_type) {
			disp->Send(msg);
			break;
		}
	}
}

void ProgramManager::ApplicationManager::SendSet(int thread_type, Message msg)
{
	for (auto& disp : mDispatchers)
	{
		if (disp->GetThreadType() == thread_type) {
			disp->SendSet(msg);
			break;
		}
	}
}

void ProgramManager::ApplicationManager::SendGet(int thread_type, Message msg)
{
	for (auto& disp : mDispatchers)
	{
		if (disp->GetThreadType() == thread_type) {
			disp->SendGet(msg);
			break;
		}
	}
}
