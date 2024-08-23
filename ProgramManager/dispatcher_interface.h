#pragma once

namespace ProgramManager
{
	class Message;

	class DispatcherInterface
	{
	public:
		virtual void Send(Message msg) = 0;
		virtual void SendSet(Message msg) = 0;
		virtual void SendGet(Message msg) = 0;

		virtual void ManagerSendFunction(int thread_type, Message msg) = 0;
		virtual void ManagerSendSet(int thread_type, Message msg) = 0;
		virtual void ManagerSendGet(int thread_type, Message msg) = 0;

		virtual int GetThreadType() const = 0;
	};
}