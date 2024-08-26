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

		virtual void ManagerSend(int thread_type, Message msg) override;

		int GetThreadType() const override;
	};
}