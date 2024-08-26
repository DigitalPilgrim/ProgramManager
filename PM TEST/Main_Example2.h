#pragma once

#include "ExampleApplicationManager.h"

#include <iostream>

int Example2()
{
	ExampleApplicationManager eam;

	eam.Init();
	eam.Run();

	std::string line;
	std::getline(std::cin, line);

	eam.Stop();
	eam.WaitForEnd();

	return 0;
}