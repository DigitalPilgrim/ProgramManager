#pragma once

#include "dispatcher_interface.h"
//#include "ApplicationObject.h"

#include <mutex>
#include <thread>
#include <chrono>
#include <list>
namespace ProgramManager
{
	class Message;

	// ------------------------------------------------------------------
	// ------------------------------------------------------------------

	class ApplicationManager;
	class ApplicationObject;

	class Dispatcher : public DispatcherInterface
	{
	public:
		typedef std::shared_ptr<ApplicationObject> Object;
		typedef std::list<Object>				   ListOfObjects;
	private:
		ApplicationManager * mManager = nullptr;
		std::mutex			mMTX;
		std::list<Message>	mMessages;
		std::thread::id		mThreadId;
		std::thread         mThread;
		int					mThreadType = -1;
		bool				mRun = false;
	protected:
		ListOfObjects		mObjects;
	public:
		Dispatcher(int thread_type, ApplicationManager* manager);

		// --------------------------------------------------------------

		virtual ~Dispatcher();

		// --------------------------------------------------------------

		int GetThreadType() const override { return mThreadType; }

		// --------------------------------------------------------------

		void Send(Message msg) override;

		// --------------------------------------------------------------

		virtual void ManagerSend(int thread_type, Message msg) override;

		// --------------------------------------------------------------
		// --------------------------------------------------------------

		/*template<typename T>
		bool GetObject(std::shared_ptr<T>& object)
		{
			for (Object o : mObjects) {
				if (o->Type == ObjectType::GetStaticType<T>()) {
					object = std::static_pointer_cast<T>(o);
					return true;
				}
			}
			return false;
		}*/

		// --------------------------------------------------------------

		void AddObject(Object object);
		bool RemoveObject(Object& object);
		bool GetObject(Object& object, size_t type);

		// --------------------------------------------------------------

		void Resolve(Message& msg);

		// --------------------------------------------------------------

	private:
		void ResolveMessages();
	public:
		// --------------------------------------------------------------
		
		//virtual bool GetApplicationObject(std::shared_ptr<ApplicationObject>& obj, size_t objType) { return false; }

		// --------------------------------------------------------------

		void AfterStop();
		void Stop();
		void Run();
		void RunStep();
		virtual void Update() {}

		// --------------------------------------------------------------

	};
}