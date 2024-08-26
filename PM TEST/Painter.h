#pragma once

#include "WAYE.h"
#include "thread_types.h"
#include "ApplicationStatistics.h"

#include <ApplicationObject.h>
#include <dispatcher.h>
#include <message.h>

#include "Objects.h"

class Painter
	: public ProgramManager::ApplicationObject
	, public ProgramManager::Dispatcher
{
	std::shared_ptr<ApplicationStatistics> mStatistics;
public:
	Painter(ProgramManager::ApplicationManager * manager) : Dispatcher((int)ThreadType::Painter, manager) { SetType<Painter>(); }

	// ------------------------------------------------------------------

	void Init(std::shared_ptr<ApplicationObject>& obj) override
	{
		ObjectTypes::Register<Painter>(Objects::Painter);
		mDispatcher = ProgramManager::DispatcherHolder(this);


		mStatistics = std::make_shared<ApplicationStatistics>(ProgramManager::DispatcherHolder(this));
		AddObject(mStatistics);

		for (auto& o : mObjects) {
			o->Init();
		}

		AddObject(obj);
	}

	// ------------------------------------------------------------------

	//void Set(ProgramManager::MessageArgs args) override {
	//	// ...
	//}

	// ------------------------------------------------------------------

	/*void Get(ProgramManager::MessageArgs& args) override {
		for (auto & arg : args.Arguments) {
			if (arg->Type == ObjectType::GetStaticType<WacomYuify_Export>()) {
				WacomYuify_Export wy_export;
				wy_export.Actions["Get Function" ] = 1;
				wy_export.Actions["Custom Action"] = 20;
				wy_export.Actions["Test Action"  ] = 33;
				wy_export.DateCreation = "10.2.2024 | Rok Draka";
				arg = std::make_shared<WacomYuify_Export>(wy_export);
			}
		}
	}*/

	// ------------------------------------------------------------------
};