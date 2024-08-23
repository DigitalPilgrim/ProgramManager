#include "dispatcher.h"

#include "ApplicationManager.h"
#include "message.h"
#include "message_resolver.h"

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

void ProgramManager::Dispatcher::SendSet(Message msg)
{
	msg.SetType(MessageType::Set);
	Send(msg);
}

// ------------------------------------------------------------------

void ProgramManager::Dispatcher::SendGet(Message msg)
{
	msg.SetType(MessageType::Get);
	Send(msg);
}

// ------------------------------------------------------------------

void ProgramManager::Dispatcher::ManagerSendFunction(int thread_type, Message msg)
{
	mManager->SendFunction(thread_type, msg);
}

// ------------------------------------------------------------------

void ProgramManager::Dispatcher::ManagerSendSet(int thread_type, Message msg)
{
	mManager->SendSet(thread_type, msg);
}

// ------------------------------------------------------------------

void ProgramManager::Dispatcher::ManagerSendGet(int thread_type, Message msg)
{
	mManager->SendGet(thread_type, msg);
}

// ------------------------------------------------------------------

void ProgramManager::Dispatcher::ResolveMessages(MessageResolver* resolver)
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
		resolver->Resolve(msg);
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
			ResolveMessages(mResolver);
			Update();
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		} while (mRun);
	});
}

// ------------------------------------------------------------------

void ProgramManager::Dispatcher::RunStep()
{
	ResolveMessages(mResolver);
	Update();
}

// ------------------------------------------------------------------

