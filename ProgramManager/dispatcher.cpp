#include "dispatcher.h"

#include "ApplicationManager.h"
#include "message.h"

ProgramManager::Dispatcher::Dispatcher(int thread_type, ApplicationManager* manager)
	: mThreadType(thread_type), mManager(manager)
{
}

// ------------------------------------------------------------------

ProgramManager::Dispatcher::~Dispatcher()
{
}

// ------------------------------------------------------------------

void ProgramManager::Dispatcher::Send(Message msg)
{
	// --------------------------------------------------------------
	// tato cast kodu nie je uplne v poriadku, pretoze ak sa vytvaraju
	// objekty za behu programu, moze si vypitat objekt ktory sa maze
	// inak povedane toto zatial nie je navrhnute (zabezpecene)
	if (msg.GetTypeObjectBack() > 0) {
		std::shared_ptr<ApplicationObject> obj;
		if (mManager->GetApplicationObject(obj, msg.GetTypeObjectBack())) {
			msg.SetObjectBack(obj);
		}
	}
	// --------------------------------------------------------------
	
	std::unique_lock<std::mutex> uLock(mMTX, std::defer_lock);
	do {
		if (uLock.try_lock()) {
			mMessages.push_back(msg);
			uLock.unlock();
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	} while (true);
}

// ------------------------------------------------------------------

void ProgramManager::Dispatcher::ManagerSend(int thread_type, Message msg)
{
	mManager->Send(thread_type, msg);
}

// ------------------------------------------------------------------

void ProgramManager::Dispatcher::AddObject(Object object)
{
	mObjects.push_back(object);
}

// ------------------------------------------------------------------

bool ProgramManager::Dispatcher::RemoveObject(Object& object)
{
	mObjects.remove(object);
	return true;
}

// ------------------------------------------------------------------

bool ProgramManager::Dispatcher::GetObject(Object& object, size_t type)
{
	for (auto obj : mObjects)
	{
		if (obj->Type == type)
		{
			object = obj;
			return true;
		}
	}
	return false;
}

// ------------------------------------------------------------------

void ProgramManager::Dispatcher::Resolve(Message& msg)
{
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
		if (!mManager->GetDispatcherAsApplicationObject(object, msg.GetTypeObjectFor()))
		{
			for (auto obj : mObjects)
			{
				if (obj->Type == msg.GetTypeObjectFor())
				{
					object = obj;
					break;
				}
			}
		}
		
		if (object) {
			object->Set(msg.GetArguments(), msg.GetFunctionIdFor());
		}
	}
	else if (msg.GetType() == MessageType::Get)
	{
		Object getFrom;
		if (!mManager->GetDispatcherAsApplicationObject(getFrom, msg.GetTypeObjectFor()))
		{
			for (auto obj : mObjects)
			{
				if (obj->Type == msg.GetTypeObjectFor())
				{
					getFrom = obj;
					break;
				}
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
					Message new_message = Message::Set(function, args);
					object->ExecuteMessage(new_message);
				}
				else {
					Message new_message = Message::Set(msg.GetMessageBack()->Type, args, msg.GetFunctionIdBack());
					object->ExecuteMessage(new_message);
				}
			}
			else if (function) {
				function(args);
			}
		}
	}
}

// ------------------------------------------------------------------

void ProgramManager::Dispatcher::ResolveMessages()
{
	std::unique_lock<std::mutex> uLock(mMTX, std::defer_lock);
	std::list<Message> messages;
	if (uLock.try_lock())
	{
		messages = mMessages;
		mMessages.clear();
		uLock.unlock();
	}

	for (auto& msg : messages)
	{
		Resolve(msg);
	}
}

// ------------------------------------------------------------------

void ProgramManager::Dispatcher::AfterStop()
{
	if (mThread.joinable()) mThread.join();
}

// ------------------------------------------------------------------

void ProgramManager::Dispatcher::Stop()
{
	Send(Message([this](MessageArgs args) { mRun = false; }, MessageArgs()));
}

// ------------------------------------------------------------------

void ProgramManager::Dispatcher::Run()
{
	if (mThread.joinable()) mThread.join();

	mThread = std::thread([this]() {
		mThreadId = std::this_thread::get_id();
		mRun = true;
		do {
			ResolveMessages();
			Update();
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		} while (mRun);
	});
}

// ------------------------------------------------------------------

void ProgramManager::Dispatcher::RunStep()
{
	ResolveMessages();
	Update();
}

// ------------------------------------------------------------------

