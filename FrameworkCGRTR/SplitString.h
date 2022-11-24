#pragma once

#include <vector>
#include <string>

inline std::vector<std::string> Split(const std::string& str, char delimeter)
{
	std::vector<std::string> subStrings{};
	std::string subStr{};
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] != delimeter)
		{
			subStr.append(1, str[i]);
		}
		else if (str[i] == delimeter && subStr.size() > 0)
		{
			subStrings.push_back(subStr);
			subStr.clear();
		}
	}
	subStrings.push_back(subStr);
	subStr.clear();

	return subStrings;
}