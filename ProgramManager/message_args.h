#pragma once

#include "Argument.h"

#include <memory>
#include <type_traits>
#include <vector>
namespace ProgramManager
{

	struct MessageArgs
	{
		 std::vector<std::shared_ptr<Argument>> Arguments;
		 MessageArgs() {}

		 MessageArgs(std::shared_ptr<Argument> argument)
		 {
			 Arguments.push_back(argument);
		 }

		 MessageArgs(std::vector<std::shared_ptr<Argument>> args)
			 : Arguments(args) {
		 }


		 /*template <typename T>
		 T GetArgument() {
			 T o;
			 for (auto& arg : Arguments) {
				 if (arg->GetArgument(o)) {
					 break;
				 }
			 }
			 return o;
		 }*/


		 template <typename T>
		 bool GetArgument(T & a) {
			 for (auto& arg : Arguments) {
				 if (arg->GetArgument(a)) {
					 return true;
				 }
			 }
			 return false;
		 }

		 // --------------------------------------------------------

		/*template <typename T>
		static std::shared_ptr<Argument> Create()
		{
			if (std::is_convertible<T*, ApplicationObject*>::value)
			{
				return std::make_shared<Argument>(T());
			}
			else return false;
		}*/
	};
}