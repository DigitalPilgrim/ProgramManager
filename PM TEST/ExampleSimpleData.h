#pragma once

#include "ExampleSimpleDataFunctions.h"
#include <ApplicationObject.h>
#include <message_args.h>

#include "Objects.h"

#include <string>
class ExampleSimpleData : public ProgramManager::ApplicationObject
{
	std::string mData_Text1;
	std::string mData_Text2;
	int mData_Int1 = 0;
	int mData_Int2 = 0;
public:
	ExampleSimpleData() { SetType<ExampleSimpleData>(); }
	ExampleSimpleData(std::string text, int d1, int d2) : mData_Text1(text), mData_Int1(d1), mData_Int2(d2) { SetType<ExampleSimpleData>(); }
	ExampleSimpleData(ProgramManager::DispatcherHolder disp)
		: ProgramManager::ApplicationObject(disp) { SetType<ExampleSimpleData>(); }

	void Init() override
	{
		ObjectTypes::Register<ExampleSimpleData>(Objects::ExampleSimpleData);
		AddFunction(this, &ExampleSimpleData::SetTextData, (int)ExampleSimpleDataFunctions::SetTextData);
		AddFunction(this, &ExampleSimpleData::GetTextData, (int)ExampleSimpleDataFunctions::GetTextData);
		AddFunction(this, &ExampleSimpleData::SetDataInt1, (int)ExampleSimpleDataFunctions::SetDataInt1);
		AddFunction(this, &ExampleSimpleData::SetDataInt2, (int)ExampleSimpleDataFunctions::SetDataInt2);
		AddFunction(this, &ExampleSimpleData::GetDataInt1, (int)ExampleSimpleDataFunctions::GetDataInt1);
		AddFunction(this, &ExampleSimpleData::GetDataInt2, (int)ExampleSimpleDataFunctions::GetDataInt2);
	}

private:
	void SetTextData(ProgramManager::MessageArgs args)
	{
		args.GetArgument(mData_Text1);
	}

	void GetTextData(ProgramManager::MessageArgs& args)
	{
		args.Arguments.push_back(ProgramManager::Argument::Create(mData_Text1));
	}

	void SetDataInt1(ProgramManager::MessageArgs args)
	{
		args.GetArgument(mData_Int1);
	}

	void GetDataInt1(ProgramManager::MessageArgs & args)
	{
		args.Arguments.push_back(ProgramManager::Argument::Create(mData_Int1));
	}

	void SetDataInt2(ProgramManager::MessageArgs args)
	{
		args.GetArgument(mData_Int2);
	}

	void GetDataInt2(ProgramManager::MessageArgs& args)
	{
		args.Arguments.push_back(ProgramManager::Argument::Create(mData_Int2));
	}
public:
	std::string GetTextData() const { return mData_Text1; }
	int			GetIntData1() const { return mData_Int1; }
	int			GetIntData2() const { return mData_Int2; }
};