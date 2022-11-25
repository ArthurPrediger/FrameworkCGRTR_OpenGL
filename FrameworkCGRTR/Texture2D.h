#pragma once

#include "Bindable.h"
#include <vector>
#include <memory>

class Texture2D : public Bindable
{
public:
	Texture2D(const std::string& texture_path, const std::string& texture_type);
	Texture2D(const std::vector<unsigned char>& image_data, const std::string& texture_name, const std::string& texture_type);
	Texture2D() = delete;
	~Texture2D();
	void Bind() override;
	static std::shared_ptr<Texture2D> Resolve(const std::string& texture_path, const std::string& texture_type);
	static std::shared_ptr<Texture2D> Resolve(const std::vector<unsigned char>& image_data, const std::string& texture_name, const std::string& texture_type);
	static std::string GetUniqueID(const std::string& texture_path, const std::string& texture_type);
	static std::string GetUniqueID(const std::vector<unsigned char>& image_data, const std::string& texture_name, const std::string& texture_type);
	GLuint GetTextureShaderID() const
	{
		return textureID;
	}
	const std::string& GetFilePath() const
	{
		return texture_path;
	}
	void SetBindTarget(std::shared_ptr<Bindable> sp);
private:
	void LoadTexture();
	void LoadTexture(const std::vector<unsigned char>& image_data);
	void SetTextureSlot();
private:
	std::string texture_path;
	std::string texture_type;
	GLuint textureID;
	std::shared_ptr<Bindable> sp = nullptr;
	GLuint location = 0;
	GLuint texture_slot = 0;
};