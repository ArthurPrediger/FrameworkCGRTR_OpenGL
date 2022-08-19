#pragma once

#include "Bindable.h"
#include <unordered_map>
#include <memory>

class BindableSet
{
public:
	static bool Resolve(std::shared_ptr<Bindable> bindable)
	{
		return Get().Resolve_(bindable);
	};
private:
	bool Resolve_(std::shared_ptr<Bindable> bindable)
	{
		const auto i = bindables_set.find(bindable->GetUniqueID());
		
		if (i == bindables_set.end())
		{
			bindables_set[bindable->GetUniqueID()] = bindable;
			return true;
		}
		else
		{
			bindable.reset();
			bindable = i->second;
			return false;
		}
	}
	static BindableSet& Get() 
	{
		static BindableSet bindableSet;

		return bindableSet;
	}
private:
	std::unordered_map<std::string, std::shared_ptr<Bindable>> bindables_set;
};