#pragma once

#include "WAYE.h"
#include "Objects.h"
#include "ApplicationStatisticsFunctions.h"

#include <ApplicationObject.h>

#include <map>
#include <string>

struct ApplicationStatistics 
	: public ProgramManager::ApplicationObject
{
	ApplicationStatistics(ProgramManager::DispatcherHolder disp)
	: ProgramManager::ApplicationObject(disp) { SetType<ApplicationStatistics>(); }
	std::string DataCreation;
	std::map<std::string, int> Actions;


	void Init() override
	{
		ObjectTypes::Register<ApplicationStatistics>(Objects::ApplicationStatistics);

		AddFunction(this, &ApplicationStatistics::SetStatistics	 , ApplicationStatisticsFunctions::SetStatistics);
		AddFunction(this, &ApplicationStatistics::GetStatistics	 , ApplicationStatisticsFunctions::GetStatistics);
		AddFunction(this, &ApplicationStatistics::AddAction		 , ApplicationStatisticsFunctions::AddAction);
		AddFunction(this, &ApplicationStatistics::RemoveAction	 , ApplicationStatisticsFunctions::RemoveAction);
		AddFunction(this, &ApplicationStatistics::SetDataCreation, ApplicationStatisticsFunctions::SetCreationData);
		AddFunction(this, &ApplicationStatistics::GetActions	 , ApplicationStatisticsFunctions::GetActions);
	}

private:
	void SetStatistics(ProgramManager::MessageArgs args)
	{
		W_Export wy_export;
		for (auto arg : args.Arguments) {
			if (arg->GetArgument(wy_export)) {
				Actions = wy_export.Actions;
				DataCreation = wy_export.DateCreation;
			}
		}
	}

	void GetStatistics(ProgramManager::MessageArgs & args)
	{
		W_Export wy_export;
		wy_export.Actions = Actions;
		wy_export.DateCreation = DataCreation;
		args.Arguments.push_back(ProgramManager::Argument::Create(wy_export));
	}

	void AddAction(ProgramManager::MessageArgs args)
	{
		int count;
		std::string key;
		if (args.GetArgument(key)) {
			if (args.GetArgument(count)) {
				Actions[key] = count;
			} else {
				if (Actions.find(key) != Actions.end()) {
					Actions[key] += 1;
				}
				else Actions[key] = 1;
			}
		}
	}

	void GetActions(ProgramManager::MessageArgs & args)
	{
		args.Arguments.push_back(ProgramManager::Argument::Create(Actions));
	}

	void RemoveAction(ProgramManager::MessageArgs args)
	{
		std::string key;
		if (args.GetArgument(key)) {
			if (Actions.find(key) != Actions.end()) {
				if (Actions[key] > 0) Actions[key] -= 1;
			}
		}
	}

	void SetDataCreation(ProgramManager::MessageArgs args)
	{
		std::string text;
		if (args.GetArgument(text)) {
			DataCreation = text;
		}
	}
public:

	//void Set(ProgramManager::MessageArgs args, int id = -1) override {
	//	WacomYuify_Export wy_export;

	//	switch ((Functions)args.Function) {
	//		case Functions::AddAction: {
	//			int count = -1;
	//			if (args.GetArgument(count)) {
	//				AddAction(args.GetArgument<std::string>(), count);
	//			} else {
	//				AddAction(args.GetArgument<std::string>());
	//			}
	//			break;
	//		}
	//	}
	//	for (auto& arg : args.Arguments) {
	//		if (arg->GetObject(wy_export)) { SetStatistics(wy_export); }
	//	}
	//}

	//// ------------------------------------------------------------------

	//void Get(ProgramManager::MessageArgs& args, int id = -1) override {
	//	for (auto& arg : args.Arguments) {
	//		if (arg->Type == ObjectType::GetStaticType<WacomYuify_Export>()) {
	//			arg = ProgramManager::Argument::Create(GetStatistics());
	//		}
	//	}
	//}

	// ------------------------------------------------------------------

};