#pragma once

#include "WAYE.h"

#include <message_args.h>
#include <ApplicationObject.h>

#include <iostream>
#include <sstream>


class W_Yu : public ProgramManager::ApplicationObject
{
	W_Export mExport;
public:
	W_Yu(ProgramManager::DispatcherHolder disp)
		: ProgramManager::ApplicationObject(disp) {}

	// ------------------------------------------------------------------
	void Export()
	{
		
	}

	void Export(ProgramManager::MessageArgs args) {
		for (auto arg : args.Arguments)
		{
			if (arg->GetArgument(mExport)) {
				std::stringstream actions;
				if (mExport.Actions.size() > 0) {
					for (auto a : mExport.Actions) {
						actions << "\n | Action(" << a.first << ") , count : " << a.second;
					}
				}
				
				std::cout << "Wacom Yuify | Actions : " << mExport.Actions.size()
					<< actions.str()
					<< "\n | creation date : " << mExport.DateCreation;
				/*mDispatcher.ManagerSendFunction(
					ProgramManager::ThreadType::ConsoleApp
					, ProgramManager::Message([](ProgramManager::MessageArgs arguments) {
						std::stringstream actions;
						if (mExport.Actions.size() > 0) {
							for (auto a : mExport.Actions) {
								actions << "\n | Action(" << a.first << ") , count : " << a.second;
							}
						}

						std::cout << "Wacom Yuify | Actions : " << mExport.Actions.size()
							<< actions.str()
							<< "\n | creation date : " << mExport.DateCreation;
						}, args));*/
				break;
			}
		}
	}

	// ------------------------------------------------------------------

	//void Set(ProgramManager::MessageArgs args, int idFunction) override {
	//	for (auto arg : args.Arguments) {
	//		if (arg->GetArgument(mExport)) {
	//			//...
	//		}
	//		// arg->GetObject(...);
	//	}
	//}

	//// ------------------------------------------------------------------

	//void Get(ProgramManager::MessageArgs & args, int idFunction) override {
	//	for (auto & arg : args.Arguments) {
	//		if (arg->Type == mExport.Type) {
	//			arg = ProgramManager::Argument::Create(mExport);
	//		}
	//	}
	//}

	// ------------------------------------------------------------------
};
