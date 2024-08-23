#pragma once

#include <ApplicationObject.h>
#include <map>
#include <string>
struct W_Export : public ProgramManager::ApplicationObject
{
	W_Export() { SetType<W_Export>(); }

	std::map<std::string, int> Actions;
	std::string DateCreation;
	std::vector<unsigned char> Image;

	//std::shared_ptr<ApplicationObject> Copy() override { return std::make_shared<WacomYuify_Export>(this); }
};