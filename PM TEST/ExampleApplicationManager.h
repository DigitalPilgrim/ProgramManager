#pragma once

#include "Console.h"
#include "GUI.h"
#include "Painter.h"
#include "ExampleDataItemsDispatcher.h"

#include <ApplicationManager.h>

class ExampleApplicationManager : public ProgramManager::ApplicationManager
{
public:
	ExampleApplicationManager() : ProgramManager::ApplicationManager() {}

	void Init() override
	{
		if (CreateDispatcher<Console					>()) { std::cout << "Console Created;\n"; }
		if (CreateDispatcher<GUI						>()) { std::cout << "GUI Created;\n"; }
		if (CreateDispatcher<Painter					>()) { std::cout << "Painter Created;\n"; }
		if (CreateDispatcher<ExampleDataItemsDispatcher	>()) { std::cout << "ExampleDataItemsDispatcher Created;\n"; }

		ProgramManager::ApplicationManager::Init();
	}
};