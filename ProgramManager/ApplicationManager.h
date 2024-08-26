#pragma once

#include "ApplicationObject.h"
#include <list>
namespace ProgramManager
{
	class Dispatcher;

	class ApplicationManager : public ApplicationObject
	{
	protected:
		std::list < std::shared_ptr<ApplicationObject> > mObjects;
		std::list <Dispatcher *> mDispatchers;
		bool mRun = false;
	public:

		// --------------------------------------------------------------
		ApplicationManager();

		virtual ~ApplicationManager();

		Dispatcher* GetDispatcher(int thread_type);

		// --------------------------------------------------------------

		template <typename T>
		bool CreateDispatcher() 
		{
			if (std::is_convertible<T*, Dispatcher*>::value) {
				mObjects.push_back(std::make_shared<T>(this));
				auto obj = mObjects.back();
				T* disp;
				obj->GetObjectP(/*(T*&)*/disp);
				mDispatchers.push_back(disp);
				return true;
			}
			else return false;
		}

		// --------------------------------------------------------------
	protected:
		void Init() override;
	public:
		// --------------------------------------------------------------
		
		void Run();
		void Stop();
		void WaitForEnd();

		bool GetApplicationObject(std::shared_ptr<ApplicationObject>& obj, size_t type);

		// --------------------------------------------------------------

		void Send(int thread_type, Message msg);

		// --------------------------------------------------------------

	};
}