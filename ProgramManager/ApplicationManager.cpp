#include "ApplicationManager.h"

#include "dispatcher.h"
#include "message.h"
#include "ApplicationObject.h"

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

bool ProgramManager::ApplicationManager::GetApplicationObject(std::shared_ptr<ApplicationObject>& obj, size_t type)
{
	for (auto& disp : mObjects) {
		if (disp->Type == type) {
			obj = disp;
			return true;
		}
	}
	for (auto& disp : mDispatchers)
	{
		if (disp->GetObject(obj, type)) {
			return true;
		}
	}
	return false;
}

void ProgramManager::ApplicationManager::Send(int thread_type, Message msg)
{
	for (auto& disp : mDispatchers)
	{
		if (disp->GetThreadType() == thread_type) {
			disp->Send(msg);
			break;
		}
	}
}
