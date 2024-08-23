#pragma once

#include "ExampleDataItemsFunctions.h"
#include "ExampleSimpleData.h"
#include <ApplicationObject.h>
#include <message_args.h>
#include <list>

#include "Objects.h"

class ExampleDataItems : public ProgramManager::ApplicationObject
{
	std::list<ExampleSimpleData> mItems;
public:
	ExampleDataItems(ProgramManager::DispatcherHolder disp)
		: ProgramManager::ApplicationObject(disp) { SetType<ExampleDataItems>(); }

	void Init() override
	{
		ObjectTypes::Register<ExampleDataItems>(Objects::ExampleDataItems);
		AddFunction(this, &ExampleDataItems::AddItem	, (int)ExampleDataItemsFunctions::AddItem);
		AddFunction(this, &ExampleDataItems::GetItem	, (int)ExampleDataItemsFunctions::GetItem);
		AddFunction(this, &ExampleDataItems::ClearItems	, (int)ExampleDataItemsFunctions::ClearItems);
		AddFunction(this, &ExampleDataItems::Counts		, (int)ExampleDataItemsFunctions::Counts);
	}

	void AddItem(ProgramManager::MessageArgs args)
	{
		ExampleSimpleData data;
		if (args.GetArgument(data)) {
			mItems.push_back(data);
		}
	}

	void GetItem(ProgramManager::MessageArgs & args)
	{
		int id = 0;
		if (args.GetArgument(id)) {
			int i = 0;
			for (auto& item : mItems) {
				if (i == id) {
					args.Arguments.clear();
					args.Arguments.push_back(ProgramManager::Argument::Create(item));
					break;
				}
				++i;
			}
		}
	}

	void ClearItems(ProgramManager::MessageArgs& args)
	{
		mItems.clear();
	}

	void Counts(ProgramManager::MessageArgs& args)
	{
		args.Arguments.push_back(ProgramManager::Argument::Create((int)mItems.size()));
	}
};