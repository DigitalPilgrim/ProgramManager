#pragma once

#include "dispatcher_interface.h"
#include <memory>

namespace ProgramManager
{
	class Dispatcher;

	class DispatcherHolder : public DispatcherInterface
	{
		Dispatcher * mDsp = nullptr;

	public:
		DispatcherHolder() {}
		DispatcherHolder(Dispatcher* dsp);

		void Send(Message msg) override;
		void SendSet(Message msg) override;
		void SendGet(Message msg) override;

		virtual void ManagerSendFunction(int thread_type, Message msg) override;
		virtual void ManagerSendSet(int thread_type, Message msg) override;
		virtual void ManagerSendGet(int thread_type, Message msg) override;

		int GetThreadType() const override;
	};
}