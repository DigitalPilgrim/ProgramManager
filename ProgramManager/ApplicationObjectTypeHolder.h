#pragma once

#include <typeinfo>
#include <list>

class ObjectTypes
{
	static std::list<std::pair<int, size_t>> mTypes;
	ObjectTypes();
public:

	template <typename T>
	static void Register(int type) { 
		size_t t = typeid(T).hash_code();
		if (Get(type) != t) {
			mTypes.push_back(std::pair<int, size_t>(type, t));
		}
	}

	static size_t Get(int type) {
		for (auto obj : mTypes) {
			if (obj.first == type) {
				return obj.second;
			}
		}
		return 0;
	}
};