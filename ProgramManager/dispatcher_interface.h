#pragma once

namespace ProgramManager
{
	class Message;

	class DispatcherInterface
	{
	public:
		virtual void Send(Message msg) = 0;
		virtual void ManagerSend(int threadt_type, Message msg) = 0;

		virtual int GetThreadType() const = 0;
	};
}