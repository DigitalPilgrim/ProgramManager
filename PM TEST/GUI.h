#pragma once

#include "WAYU.h"
#include "thread_types.h"

#include <ApplicationObject.h>
#include <message_resolver.h>
#include <dispatcher.h>

#include "ExampleSimpleDataFunctions.h"

#include "Objects.h"

class GUI
	: public ProgramManager::ApplicationObject
	, public ProgramManager::MessageResolver
	, public ProgramManager::Dispatcher
{
	int counter = 0;
	int interval = 1;
	std::shared_ptr<W_Yu> mWaYu;
public:
	// ------------------------------------------------------------------
	
	GUI(ProgramManager::ApplicationManager* manager) : Dispatcher((int)ThreadType::GUI, manager) { SetType<GUI>(); }

	// ------------------------------------------------------------------

	void Init() override
	{
		ObjectTypes::Register<GUI>(Objects::GUI);
		SetMessageResolver(this);
		mDispatcher = ProgramManager::DispatcherHolder(this);

		mWaYu = std::make_shared<W_Yu>(ProgramManager::DispatcherHolder(this));
		AddObject(mWaYu);
	}

	// ------------------------------------------------------------------

	void Update() override
	{
		using namespace ProgramManager;

		std::this_thread::sleep_for(std::chrono::milliseconds(interval));

		if (counter >= 0) ++counter;
		else counter = 0;

		if (counter == 0) {
			ManagerSendFunction((int)ThreadType::Console
				, Message(
					[](MessageArgs) { std::cout << "Sending message from GUI to Console after 1 secs.\n"; }
					, MessageArgs()));
			interval = 2;
		}
		else if (counter == 1)
		{
			ManagerSendSet((int)ThreadType::Console
				, Message(
					// musi sa includnut ExampleSimpleData a mozno by bolo dobre mat nejake pole vsetkych typov ktore sa kedy
					// vytvoria aby bolo mozne ziskat pomocou enumu a nemusi sa includovat cely objekt
					ObjectTypes::Get(Objects::ExampleSimpleData)
					, MessageArgs(Argument::Create(std::string("Added text from GUI to Simple Data.")))
					, (int)ExampleSimpleDataFunctions::SetTextData));
		}
		else if (counter == 2)
		{
			ManagerSendGet((int)ThreadType::Console
				, Message( // namiesto Message by tu mohlo byt Message::Get() alebo nieco konkretnejsie
					ObjectTypes::Get(Objects::ExampleSimpleData)
					, (int)ExampleSimpleDataFunctions::GetTextData
					, (std::shared_ptr<ApplicationObject>&)mWaYu
					, MessageArgs(Argument::Create(std::string("Added text from GUI to Simple Data.")))
					));
		}
	}

	// ------------------------------------------------------------------
};