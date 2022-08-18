#pragma once

#include <fstream>
#include <iostream>
#include <string>

static void LoadShaderFromFile(const std::string& shader_path, std::string& shader)
{
	std::ifstream shader_file(shader_path);
	
	if (shader_file.is_open())
	{
		std::string line;
		std::getline(shader_file, line);
		shader.append(line + "\n");
		while (!shader_file.eof())
		{
			std::getline(shader_file, line);
			shader.append(line);
		}
	}
}