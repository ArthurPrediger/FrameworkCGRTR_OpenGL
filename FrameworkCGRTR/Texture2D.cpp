#include "Texture2D.h"
#include "BindableSet.h"
#include "stb_image.h"
#include <stdexcept>


Texture2D::Texture2D(const std::string& texture_path)
	:
	Bindable("Texture2D", BindType::OnDraw),
	texture_path(texture_path),
	textureID(NULL)
{
	LoadTexture();
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &textureID);
}

void Texture2D::Bind()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}

std::shared_ptr<Texture2D> Texture2D::Resolve(const std::string& texture_path)
{
	auto pair = BindableSet::Resolve<Texture2D>(texture_path);
	return pair.second;
}

std::string Texture2D::GetUniqueID(const std::string& texture_path)
{
	return "Texture2D_" + texture_path;
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
		GLfloat max_aniso = 0.0f;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max_aniso);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_aniso);

		stbi_image_free(imageData);
	}
}
