#include "function_holder.h"

#include "message_args.h"

void ProgramManager::FunctionHolder::ExecuteSet(MessageArgs args, int id)
{
	if (id >= 0)
	{
		for (auto& f : mFunctions)
		{
			if (f.GetFunctionId() == id)
			{
				f.ExecuteSet(args);
				break;
			}
		}
	}
}

void ProgramManager::FunctionHolder::ExecuteGet(MessageArgs& args, int id)
{
	if (id >= 0)
	{
		for (auto& f : mFunctions)
		{
			if (f.GetFunctionId() == id)
			{
				f.ExecuteGet(args);
				break;
			}
		}
	}
}
