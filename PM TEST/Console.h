#pragma once

#include "thread_types.h"
#include "ExampleSimpleData.h"

#include <ApplicationObject.h>
#include <message_resolver.h>
#include <dispatcher.h>

#include "Objects.h"

class Console
	: public ProgramManager::ApplicationObject
	, public ProgramManager::MessageResolver
	, public ProgramManager::Dispatcher
{
	std::shared_ptr<ExampleSimpleData> mSimpleData;
public:
	Console(ProgramManager::ApplicationManager* manager) : Dispatcher((int)ThreadType::Console, manager) { SetType<Console>(); }

	// ------------------------------------------------------------------

	void Init() override
	{
		ObjectTypes::Register<Console>(Objects::Console);
		SetMessageResolver(this);
		mDispatcher = ProgramManager::DispatcherHolder(this);
		mSimpleData = std::make_shared<ExampleSimpleData>(ProgramManager::DispatcherHolder(this));
		AddObject(mSimpleData);

		for (auto& o : mObjects) {
			o->Init();
		}
	}

	// ------------------------------------------------------------------
	
	void Display(std::string data)
	{
		using namespace ProgramManager;
		if (data == "Simple Data 1") {
			Send(Message([](MessageArgs args) {}, MessageArgs()));
		}
	}
	
	// ------------------------------------------------------------------

	void Update() override
	{

	}
};