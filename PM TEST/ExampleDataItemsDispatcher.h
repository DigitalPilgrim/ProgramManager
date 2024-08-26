#pragma once


#include "thread_types.h"
#include "ExampleDataItems.h"

#include <ApplicationObject.h>
#include <dispatcher.h>
#include <message.h>

#include "Objects.h"

#include <iostream>

class ExampleDataItemsDispatcher
	: public ProgramManager::ApplicationObject
	, public ProgramManager::Dispatcher
{
	std::shared_ptr<ExampleDataItems> mDatas;
public:
	ExampleDataItemsDispatcher(ProgramManager::ApplicationManager* manager) 
		: Dispatcher((int)ThreadType::DataItemsDisp, manager) { SetType<ExampleDataItemsDispatcher>(); }

	// ------------------------------------------------------------------

	void Init(std::shared_ptr<ApplicationObject>& obj) override
	{
		ObjectTypes::Register< ExampleDataItemsDispatcher>(Objects::ExampleDataItemsDispatcher);
		mDispatcher = ProgramManager::DispatcherHolder(this);

		mDatas = std::make_shared<ExampleDataItems>(ProgramManager::DispatcherHolder(this));
		
		AddObject(mDatas);

		for (auto& o : mObjects) {
			o->Init();
		}

		AddObject(obj);
	}

	// ------------------------------------------------------------------
	
	void AddItem(std::string text, int val1, int val2)
	{
		using namespace ProgramManager;
		Send(Message::Set([this](MessageArgs args) { mDatas->AddItem(args); }
			, MessageArgs({Argument::Create(text)
						, Argument::Create(val1)
						, Argument::Create(val2)})));
	}

	void DisplayItem(int id)
	{
		using namespace ProgramManager;

		Send(Message::Get(
			ObjectTypes::Get(Objects::ExampleDataItems)
			, ExampleDataItemsFunctions::GetItem
			, ObjectTypes::Get(Objects::Console)
			, [](MessageArgs args) {
				std::string text;
				int id = -1;
				int value1 = -1;
				int value2 = -1;
				args.GetArgument(id);
				args.GetArgument(text);
				args.GetArgument(value1);
				args.GetArgument(value2);

				std::cout << "DisplayItem() function from ExampleDataItems, called maybe from outside, from any thread\n";
				std::cout << "and sent to Console to display data:\n";
				std::cout << "Item | id : " << id
					<< ", Text : " << text
					<< ", value 1 : " << value1
					<< ", value 2 : " << value2;
				std::cout << std::endl;
			}
			, MessageArgs(Argument::Create(id))
		));

		/*ExampleSimpleData item;
		Send(Message::Get(
			ObjectTypes::Get(Objects::ExampleDataItems)
			, ExampleDataItemsFunctions::GetItem
			, [this](MessageArgs args) {
				ManagerSend(ThreadType::Console
					, Message::Set([](MessageArgs args) {
						int id = 0;
						args.GetArgument(id);
						ExampleSimpleData item;
						if (args.GetArgument(item)) {
							std::cout << "Item | id : " << id
								<< ", Text : "	  << item.GetTextData()
								<< ", value 1 : " << item.GetIntData1()
								<< ", value 2 : " << item.GetIntData2();
						}
					}, args));
			}
		));*/
	}

	void DisplayAllItems()
	{

	}

	void RemoveItem(int id)
	{

	}

	void EditItem(int id, std::string text, int val1, int val2)
	{

	}

	// ------------------------------------------------------------------

	void Update() override
	{

	}
};