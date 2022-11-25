#include "Material.h"
#include "Bindable.h"
#include "Texture2D.h"
#include "ShaderProgram.h"
#include "UniformLocation.h"

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ranges>

Material::Material(const std::string& mtllib_file_name, const std::string& name)
	:
	mtllib_file_name(mtllib_file_name),
	name(name),
	textureMaps({})
{
}

void Material::BindTextureMaps()
{
	for (auto& textureMap : textureMaps)
	{
		textureMap->Bind();
	}
}

void Material::SetBindTarget(std::shared_ptr<ShaderProgram> sp)
{
	for (auto& property : properties)
	{
		if (property->GetPropertyType() == typeid(float).name())
		{
			auto property_casted = std::static_pointer_cast<TemplatedMaterialProperty<float>>(property);
			auto pValue = std::make_shared<float>(property_casted->property);
			auto unifLoc = UniformLocation<float>::Resolve(sp, property->name, pValue);
			property_casted->uniformSetter = pValue;
			sp->AddUniformLocationBindable(unifLoc);
		}
		else if (property->GetPropertyType() == typeid(glm::vec4).name())
		{
			auto property_casted = std::static_pointer_cast<TemplatedMaterialProperty<glm::vec4>>(property);
			auto pValue = std::make_shared<glm::vec4>(property_casted->property);
			auto unifLoc = UniformLocation<glm::vec4>::Resolve(sp, property->name, pValue);
			property_casted->uniformSetter = pValue;
			sp->AddUniformLocationBindable(unifLoc);
		}
	}

	for (auto& texture : textureMaps)
	{
		texture->SetBindTarget(sp);
	}
}

void Material::BindProperties()
{
	for (auto& property : properties)
	{
		property->Bind();
	}
}

bool Material::HasTextureType(const std::string& texture_type) const
{
	return std::ranges::find(texture_types, texture_type) != texture_types.end();
}
