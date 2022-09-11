#pragma once

#include "Bindable.h"
#include <memory>

class Texture2D : public Bindable
{
public:
	Texture2D(const std::string& texture_path);
	Texture2D() = delete;
	~Texture2D();
	void Bind() override;
	static std::shared_ptr<Texture2D> Resolve(const std::string& texture_path);
	static std::string GetUniqueID(const std::string& texture_path);
	GLuint GetTextureShaderID() const
	{
		return textureID;
	}
	const std::string& GetFilePath() const
	{
		return texture_path;
	}
private:
	void LoadTexture();
private:
	std::string texture_path;
	GLuint textureID;
};