#pragma once


#include "thread_types.h"
#include "ExampleDataItems.h"

#include <ApplicationObject.h>
#include <message_resolver.h>
#include <dispatcher.h>

#include "Objects.h"

class ExampleDataItemsDispatcher
	: public ProgramManager::ApplicationObject
	, public ProgramManager::MessageResolver
	, public ProgramManager::Dispatcher
{
	std::shared_ptr<ExampleDataItems> mDatas;
public:
	ExampleDataItemsDispatcher(ProgramManager::ApplicationManager* manager) 
		: Dispatcher((int)ThreadType::DataItemsDisp, manager) { SetType<ExampleDataItemsDispatcher>(); }

	// ------------------------------------------------------------------

	void Init() override
	{
		ObjectTypes::Register< ExampleDataItemsDispatcher>(Objects::ExampleDataItemsDispatcher);
		SetMessageResolver(this);
		mDispatcher = ProgramManager::DispatcherHolder(this);
		mDatas = std::make_shared<ExampleDataItems>(ProgramManager::DispatcherHolder(this));
		
		AddObject(mDatas);

		for (auto& o : mObjects) {
			o->Init();
		}
	}

	// ------------------------------------------------------------------

	void Update() override
	{

	}
};