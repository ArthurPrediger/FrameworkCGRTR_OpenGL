#pragma once

#include "Bindable.h"
#include <type_traits>
#include <memory>
#include <unordered_map>

class BindableSet
{
public:
	template<class T, typename...Params>
	static std::pair<bool, std::shared_ptr<T>> Resolve(Params&&... p)
	{
		static_assert(std::is_base_of<Bindable, T>::value, "Can only resolve classes derived from Bindable");
		return Get().Resolve_<T>(std::forward<Params>(p)...);
	};
private:
	template<class T, typename...Params>
	std::pair<bool, std::shared_ptr<T>> Resolve_(Params&&... p)
	{
		const auto key = T::GetUniqueID(std::forward<Params>(p)...);
		const auto i = bindables_set.find(key);
		
		if (i == bindables_set.end())
		{
			auto bindable = std::make_shared<T>(std::forward<Params>(p)...);
			bindables_set[key] = bindable;
			return { false, bindable };
		}
		else
		{
			return { true, std::static_pointer_cast<T>(i->second) };
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