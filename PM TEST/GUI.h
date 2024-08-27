#pragma once

#include "WAYU.h"
#include "thread_types.h"

#include <ApplicationObject.h>
#include <dispatcher.h>
#include <message.h>

#include "ExampleSimpleDataFunctions.h"
#include "ExampleDataItemsFunctions.h"
#include "ApplicationStatisticsFunctions.h"
#include "ConsoleFunctions.h"

#include "Objects.h"

class GUI
	: public ProgramManager::ApplicationObject
	, public ProgramManager::Dispatcher
{
	int counter = 0;
	int interval = 1000;
	std::shared_ptr<W_Yu> mWaYu;
public:
	// ------------------------------------------------------------------
	
	GUI(ProgramManager::ApplicationManager* manager) : Dispatcher((int)ThreadType::GUI, manager) { SetType<GUI>(); }

	// ------------------------------------------------------------------

	void Init() override
	{
		ObjectTypes::Register<GUI>(Objects::GUI);
		mDispatcher = ProgramManager::DispatcherHolder(this);

		mWaYu = std::make_shared<W_Yu>(ProgramManager::DispatcherHolder(this));
		AddObject(mWaYu);

		for (auto& o : mObjects) {
			o->Init();
		}
	}

	// ------------------------------------------------------------------

	void Update() override
	{
		using namespace ProgramManager;

		std::this_thread::sleep_for(std::chrono::milliseconds(interval));


		if (counter == 0) {
			// Send and display massage in console thread
			ManagerSend(ThreadType::Console
				, Message::Set(
					[](MessageArgs) { std::cout << "Sending message from GUI to Console after 1 secs.\nPress Enter to exit or wait for actions.\n"; }
					, MessageArgs()));
			//interval = 2000;
		}
		else if (counter == 1)
		{
			// Change simple data in Console
			ManagerSend(ThreadType::Console
				, Message::Set(
					ObjectTypes::Get(Objects::ExampleSimpleData)
					, MessageArgs({
						  Argument::Create("qwerty")
						, Argument::Create(333)
						, Argument::Create(777)
						})
					, ExampleSimpleDataFunctions::SetData
				)
			);

			// Add item into ExampleDataItemsDispatcher
			ManagerSend(ThreadType::DataItemsDisp
				, Message::Set(
					ObjectTypes::Get(Objects::ExampleDataItems)
					, MessageArgs({ 
						Argument::Create(std::string("Added item from GUI to Simple Data."))
						, Argument::Create(111) 
						, Argument::Create(888) })
					, ExampleDataItemsFunctions::AddItem));

			// Add action into Painter
			ManagerSend(ThreadType::Painter
				, Message::Set(
					ObjectTypes::Get(Objects::ApplicationStatistics)
					, MessageArgs({
						  Argument::Create(std::string("Added action from GUI to Application Statistics.")) // action
						, Argument::Create(1) // count
						})
					, ApplicationStatisticsFunctions::AddAction));
		}
		else if (counter == 3)
		{
			ManagerSend(ThreadType::Console
				, Message::Set(
					ObjectTypes::Get(Objects::Console)
					, MessageArgs(Argument::Create("SimpleData_1"))
					, ConsoleFunctions::Display
				)
			);

			// myslienka:
			// mozno nebude treba pisat ThreadType, pretoze aj objekt drzi threadType a tym padom ked sa vypita objekt
			// zoberie sa aj tak uz z daneho threadu, takze mozno to nemusi byt.
			// Ale potom nebude mozne vypitat objekt z konkretneho threadu, ak napr. su rovnake objekty vo viacerych
			// threadov. Takze mozno to tak nakoniec musi byt.
			ManagerSend(ThreadType::Painter
				, Message::Get(
					ObjectTypes::Get(Objects::ApplicationStatistics)
					, ApplicationStatisticsFunctions::GetActions
					, ObjectTypes::Get(Objects::Console)
					, [](MessageArgs args) {

						std::map<std::string, int> actions;
						args.GetArgument(actions);

						std::cout << "Display Actions from Console, message sent from GUI\n";
						if (actions.size()) {
							for (auto& a : actions) {
								std::cout << "Action [ " << a.first << " ] = " << a.second << std::endl;
							}
						}
						else std::cout << "No action available.\n";
					}
				)
			);
		}
		else if (counter == 5)
		{
			ManagerSend(ThreadType::DataItemsDisp
				, Message::Get(
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
						std::cout << "--------------------------------------------------------------------\n";
						std::cout << "DisplayItem() functor from GUI, called maybe from GUI thread\n";
						std::cout << "get data from ExampleDataItemsDispatcher\n";
						std::cout << "and sent to Console to display data:\n";
						std::cout << "Item | id : " << id
							<< ", Text : " << text
							<< ", value 1 : " << value1
							<< ", value 2 : " << value2;
						std::cout << std::endl;
						std::cout << "--------------------------------------------------------------------\n";
					}
					, MessageArgs(Argument::Create(0))
				)
			);
		}
		else if (counter == 6) {
			ManagerSend(ThreadType::Console
				, Message::Set(
					[](MessageArgs) { std::cout << "Press enter to Exit: "; }
			, MessageArgs()));
		}


		if (counter >= 0) ++counter;
		else counter = 0;
	}

	// ------------------------------------------------------------------
};