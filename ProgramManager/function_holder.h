#pragma once

#include "delegate.h"

#include <list>
#include <vector>
namespace ProgramManager
{
	struct MessageArgs;

	class FunctionHolder
	{
	protected:
		std::vector<Delegate> mFunctions;
	public:

		template <typename T>
		void AddFunction(T* caller, void(T::* f)(MessageArgs), int id = -1)
		{
			mFunctions.push_back(Delegate(caller, f, id));
		}

		template <typename T>
		void AddFunction(T* caller, void(T::* f)(MessageArgs &), int id = -1)
		{
			mFunctions.push_back(Delegate(caller, f, id));
		}

		void ExecuteSet(MessageArgs args, int id = -1);
		void ExecuteGet(MessageArgs& args, int id = -1);
	};
}