#pragma once

#include "thread_types.h"
#include "ExampleSimpleData.h"

#include <ApplicationObject.h>
#include <dispatcher.h>
#include <message.h>

#include "ConsoleFunctions.h"
#include "Objects.h"

#include <iostream>

class Console
	: public ProgramManager::ApplicationObject
	, public ProgramManager::Dispatcher
{
	std::shared_ptr<ExampleSimpleData> mSimpleData;
public:
	Console(ProgramManager::ApplicationManager* manager) : Dispatcher(ThreadType::Console, manager) { SetType<Console>(); }

	// ------------------------------------------------------------------

	void Init() override
	{
		ObjectTypes::Register<Console>(Objects::Console);
		mDispatcher = ProgramManager::DispatcherHolder(this);

		AddFunction(this, &Console::Display, ConsoleFunctions::Display);


		mSimpleData = std::make_shared<ExampleSimpleData>(ProgramManager::DispatcherHolder(this));
		
		AddObject(mSimpleData);

		for (auto& o : mObjects) {
			o->Init();
		}
	}

	// ------------------------------------------------------------------
	
	void Display(ProgramManager::MessageArgs args)
	{
		std::string data;
		if (args.GetArgument(data))
		{
			using namespace ProgramManager;
			if (data == "SimpleData_1") {
				//Send(Message::Set([](MessageArgs args) {}, MessageArgs()));

				Send(Message::Get(
					ObjectTypes::Get(Objects::ExampleSimpleData)
					, ExampleSimpleDataFunctions::GetData
					, [](MessageArgs args) {
						std::string text;
						int v1 = 0;
						int v2 = 0;
						args.GetArgument(text);
						args.GetArgument(v1);
						args.GetArgument(v2);
						std::cout << "---------------------------------------------------------------------" << std::endl;
						std::cout << "Console | Simple Data (" << text << ", " << v1 << ", " << v2 << ")" << std::endl;
					}
				));
			}
		}
	}
	
	// ------------------------------------------------------------------

	void Update() override
	{

	}
};