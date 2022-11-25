#include "Texture2D.h"
#include "BindableSet.h"
#include "ShaderProgram.h"
#include "stb_image.h"
#include <stdexcept>


Texture2D::Texture2D(const std::string& texture_path, const std::string& texture_type)
	:
	Bindable("Texture2D", BindType::OnDraw),
	texture_path(texture_path),
	textureID(NULL),
	texture_type(texture_type)
{
	LoadTexture();
	SetTextureSlot();
}

Texture2D::Texture2D(const std::vector<unsigned char>& image_data, const std::string& texture_name, const std::string& texture_type)
	:
	Bindable("Texture2D", BindType::OnDraw),
	texture_path(texture_name),
	textureID(NULL),
	texture_type(texture_type)
{
	LoadTexture(image_data);
	SetTextureSlot();
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &textureID);
}

void Texture2D::Bind()
{
	glUniform1i(location, texture_slot);
	glActiveTexture(GL_TEXTURE0 + texture_slot);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

std::shared_ptr<Texture2D> Texture2D::Resolve(const std::string& texture_path, const std::string& texture_type)
{
	auto pair = BindableSet::Resolve<Texture2D>(texture_path, texture_type);
	return pair.second;
}

std::shared_ptr<Texture2D> Texture2D::Resolve(const std::vector<unsigned char>& image_data, const std::string& texture_name, const std::string& texture_type)
{
	auto pair = BindableSet::Resolve<Texture2D>(image_data, texture_name, texture_type);
	return pair.second;
}

std::string Texture2D::GetUniqueID(const std::string& texture_path, const std::string& texture_type)
{
	return "Texture2D_" + texture_path;
}

std::string Texture2D::GetUniqueID(const std::vector<unsigned char>& image_data, const std::string& texture_name, const std::string& texture_type)
{
	return "Texture2D_" + texture_name;
}

void Texture2D::SetBindTarget(std::shared_ptr<Bindable> sp)
{
	this->sp = sp;

	location = glGetUniformLocation(std::static_pointer_cast<ShaderProgram>(sp)->GetShaderProgramID(), texture_type.c_str());
}

void Texture2D::LoadTexture()
{
	int x, y, channelsInFile;
	int forceChannels = 4;
	glEnable(GL_TEXTURE_2D);
	unsigned char* imageData = stbi_load(texture_path.c_str(), &x, &y, &channelsInFile, forceChannels);

	if (!imageData)
	{
		throw std::runtime_error("Failed to load texture with texture path: " + texture_path);
	}
	if ( (x % 2 != 0) || (y % 2 != 0))
	{
		throw std::runtime_error("Loaded texture, with texture path: " + texture_path + ", has at least one dimension which isn't a power of two.");
	}
	else
	{
		glGenTextures(1, &textureID);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		GLfloat max_aniso = 16.0f;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_aniso);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_aniso);

		stbi_image_free(imageData);
	}
}

void Texture2D::LoadTexture(const std::vector<unsigned char>& image_data)
{
	if (image_data.size() < 1)
	{
		throw std::runtime_error("Passed in texture data with name: " + texture_path + ", has no valid data.");
	}
	if ((image_data.size() % 2 != 0))
	{
		throw std::runtime_error("Passed in texture data with name: " + texture_path + ", doesn't have valid dimensions.");
	}
	else
	{
		glGenTextures(1, &textureID);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, GLsizei(image_data.size() / 8), GLsizei(image_data.size() / 8), 0, GL_RGBA, GL_UNSIGNED_BYTE, &image_data.front());
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		GLfloat max_aniso = 16.0f;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_aniso);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_aniso);
	}
}

void Texture2D::SetTextureSlot()
{
	if (texture_type == "diffuse_texture") texture_slot = 0;
	else if (texture_type == "specular_texture") texture_slot = 1;
}
