#pragma once

#include "Console.h"

#include <ApplicationManager.h>

#include <iostream>
#include <string>

/* ================================================================================================================ //
	Tento example bezi v jednom treade, je mozne ho spustit mutlithreadovo, ale vypis nie je synchronny
	takze sa vacsinou zobrazi oneskorene a tym padom to zle vyzera.
	Pre spustenie multithreadovo treba zakomentovat kod dsp->RunStep(); a ostatne odkomentovat

	Je to velmi jednoduchy projekt kde bezi iba Console Dispatcher ktory manazuje svoje spravy, je to jedna ukazka
	z moznych pouziti.
// ================================================================================================================ */

class MainExample1 : public ProgramManager::ApplicationManager
{
public:
	MainExample1() : ProgramManager::ApplicationManager() {}

	void Init() override
	{
		if (CreateDispatcher<Console>()) {
			std::cout << "Console Created;\n";
		}
		else { std::cout << "Consolde create failed;\n"; }

		ProgramManager::ApplicationManager::Init();
	}
};

// ================================================================================================================

bool is_number(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

// ================================================================================================================

void Example1()
{
	MainExample1 main;
	main.Init();
	ProgramManager::Dispatcher* dsp = main.GetDispatcher((int)ThreadType::Console);

	int run = true;

	std::cout << "# =========================================== #\n";
	std::cout << "# Example 1                                   #\n";
	std::cout << "# =========================================== #\n";
	
	//main.Run();
	using namespace ProgramManager;
	do {
		dsp->RunStep();
		std::cout << "# ------------------------------------------- #\n";
		std::cout << "# 1) Edit data | 2) Show data | 3) exit\n";
		std::string edit;
		std::getline(std::cin, edit);
		if (edit == "1") {
			std::cout << "# 1) Set text | 2) set int 1 | 3) set int 2\n";
			edit.clear();
			std::getline(std::cin, edit);
			if (is_number(edit)) {
				int e = std::atoi(edit.c_str());
				switch (e) {
					case 1: {
						std::cout << "Enter the text: ";
						edit.clear();
						std::getline(std::cin, edit);
						main.Send(ThreadType::Console
										 , Message::Set(ObjectTypes::Get(Objects::ExampleSimpleData) /*ObjectType::GetStaticType<ExampleSimpleData>()*/
																, MessageArgs(Argument::Create(edit))
																, ExampleSimpleDataFunctions::SetTextData)
						);
						break;
					}
					case 2: {
						std::cout << "Enter data int 1: ";
						edit.clear();
						std::getline(std::cin, edit);
						if (is_number(edit)) {
							int data = std::atoi(edit.c_str());
							main.Send(ThreadType::Console
									, Message::Set(
										ObjectTypes::Get(Objects::ExampleSimpleData) //ObjectType::GetStaticType<ExampleSimpleData>()
										, MessageArgs(Argument::Create(data))
										, ExampleSimpleDataFunctions::SetDataInt1)
							);
						}
						break;
					}
					case 3: {
						std::cout << "Enter data int 2: ";
						edit.clear();
						std::getline(std::cin, edit);
						if (is_number(edit)) {
							int data = std::atoi(edit.c_str());
							main.Send(ThreadType::Console
								, Message::Set(
									ObjectTypes::Get(Objects::ExampleSimpleData) //ObjectType::GetStaticType<ExampleSimpleData>()
									, MessageArgs(Argument::Create(data))
									, ExampleSimpleDataFunctions::SetDataInt2)
							);
						}
						break;
					}
				}
			}
			
		}
		else if (edit == "2") {
			std::cout << "# 1) Show text | 2) Show int 1 | 3) Show int 2\n";
			std::string edit;
			std::getline(std::cin, edit);
			if (is_number(edit)) {
				int e = std::atoi(edit.c_str());
				switch (e) {
				case 1: {
					std::cout << "Text data: ";
					
					main.Send(ThreadType::Console
						, Message::Get(
							ObjectTypes::Get(Objects::ExampleSimpleData) //ObjectType::GetStaticType<ExampleSimpleData>()
							, ExampleSimpleDataFunctions::GetTextData
							, [](MessageArgs args) {
								std::string text;
								if (args.GetArgument(text)) {
									std::cout << text << std::endl;
								} else {
									std::cout << "not found;\n";
								}
							})
					);
					break;
				}
				case 2: {
					std::cout << "Data int 1: ";
					main.Send(ThreadType::Console
						, Message::Get(ObjectTypes::Get(Objects::ExampleSimpleData) //ObjectType::GetStaticType<ExampleSimpleData>()
							, ExampleSimpleDataFunctions::GetDataInt1
							, [](MessageArgs args) {
								int data;
								if (args.GetArgument(data)) {
									std::cout << data << std::endl;
								}
								else {
									std::cout << "not found;\n";
								}
							})
					);
					break;
				}
				case 3: {
					std::cout << "Data int 2: ";
					main.Send((int)ThreadType::Console
						, Message::Get(ObjectTypes::Get(Objects::ExampleSimpleData) //ObjectType::GetStaticType<ExampleSimpleData>()
							, ExampleSimpleDataFunctions::GetDataInt2
							, [](MessageArgs args) {
								int data;
								if (args.GetArgument(data)) {
									std::cout << data << std::endl;
								}
								else {
									std::cout << "not found;\n";
								}
							})
					);
					break;
				}
				}
			}
		}
		else {
			run = false;
		}

	} while (run);

	std::cout << "# =========================================== #\n";
	std::cout << "# Ende                                        #\n";
	std::cout << "# =========================================== #\n";

	//main.Stop();
	//main.WaitForEnd();

	std::cout << "# =========================================== #\n";
}