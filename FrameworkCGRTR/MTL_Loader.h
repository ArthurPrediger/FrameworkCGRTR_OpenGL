#pragma once

#include <string>
#include <vector>
#include <memory>

class MTL_Loader
{
public:
	static std::vector<std::shared_ptr<class Material>> LoadMtllib(const std::string& mtllib_path);
};