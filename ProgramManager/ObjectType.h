#pragma once

#include <typeinfo>

namespace ProgramManager
{
	struct ObjectType
	{
		size_t Type = 0;

		ObjectType() {}
		template <typename T>
		ObjectType() { Type = typeid(T).hash_code(); }

		template <typename T>
		void SetType() { Type = typeid(T).hash_code(); }

		template <typename T>
		static size_t GetStaticType() { return typeid(T).hash_code(); }
	};

}