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

	/*void AddItem(ProgramManager::MessageArgs args)
	{
		ExampleSimpleData data;
		if (args.GetArgument(data)) {
			mItems.push_back(data);
		}
	}*/

	void AddItem(ProgramManager::MessageArgs args)
	{
		using namespace ProgramManager;
		std::string text;
		int val1 = 0;
		int val2 = 0;
		args.GetArgument(text);
		args.GetArgument(val1);
		args.GetArgument(val2);
		mItems.push_back(ExampleSimpleData(text, val1, val2));
	}

	void GetItem(ProgramManager::MessageArgs & args)
	{
		int id = 0;
		if (args.GetArgument(id)) {
			// ------------------------------------------------------------------------------------------------
			// pre prebrati pozadovaneho arguemtnu alebo argumentov pre Get funnkciu, trebe vymazat argumenty
			// predtym nez sa naplnia argumentmi ktore sa maju predat, lebo ak tam zostane ten argument
			// tak sa prenesie dalej do set funkcie ktora s tym ale nemusi ratat. A ani by nemala.
			// 
			// argumenty sa musia vkladat a preberat v rovnakom poradi, inak pri preberani ak sa preberaju
			// argumenty rovnakeho typu, nebudu sediet s hodnotami
			// ------------------------------------------------------------------------------------------------
			args.Arguments.clear();
			int i = 0;
			for (auto& item : mItems) {
				if (i == id) {
					args.Arguments.clear();
					//args.Arguments.push_back(ProgramManager::Argument::Create(item));
					args.Arguments.push_back(ProgramManager::Argument::Create(id));
					args.Arguments.push_back(ProgramManager::Argument::Create(item.GetTextData()));
					args.Arguments.push_back(ProgramManager::Argument::Create(item.GetIntData1()));
					args.Arguments.push_back(ProgramManager::Argument::Create(item.GetIntData2()));
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