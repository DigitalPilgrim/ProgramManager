#pragma once

#include "dispatcher_interface.h"

#include <mutex>
#include <thread>
#include <chrono>
#include <list>
namespace ProgramManager
{
	class Message;
	class MessageResolver;

	// ------------------------------------------------------------------
	// ------------------------------------------------------------------

	class ApplicationManager;

	class Dispatcher : public DispatcherInterface
	{
		ApplicationManager * mManager = nullptr;
		std::mutex			mMTX;
		std::list<Message>	mMessages;
		std::thread::id		mThreadId;
		std::thread         mThread;
		int					mThreadType = -1;
		bool				mRun = false;
		MessageResolver	  * mResolver = nullptr;
	public:
		Dispatcher(int thread_type, ApplicationManager* manager);

		// --------------------------------------------------------------

		virtual ~Dispatcher();

		// --------------------------------------------------------------

		int GetThreadType() const override { return mThreadType; }

		// --------------------------------------------------------------

		void Send(Message msg) override;
		void SendSet(Message msg) override;
		void SendGet(Message msg) override;

		// --------------------------------------------------------------

		virtual void ManagerSendFunction(int thread_type, Message msg) override;
		virtual void ManagerSendSet     (int thread_type, Message msg) override;
		virtual void ManagerSendGet     (int thread_type, Message msg) override;

		// --------------------------------------------------------------
	private:
		void ResolveMessages(MessageResolver* resolver);
	public:
		// --------------------------------------------------------------

		void AfterStop();
		void Stop();
		void Run();
		void RunStep();
		virtual void Update() {}

		// --------------------------------------------------------------
	protected:
		void SetMessageResolver(MessageResolver* res) { mResolver = res; }

	};
}