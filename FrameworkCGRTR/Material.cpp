#include "Material.h"
#include "Bindable.h"
#include "ShaderProgram.h"
#include "UniformLocation.h"
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

void Material::BindProperties(std::shared_ptr<ShaderProgram> sp)
{
	for (auto& property : properties)
	{
		if (property.GetPropertyType() == typeid(float).name())
		{
			auto pValue = std::make_shared<float>(dynamic_cast<TemplatedMaterialProperty<float>*>(&property)->property);
			auto unifLoc = UniformLocation<float>::Resolve(sp, property.name, pValue);
			sp->AddUniformLocationBindable(unifLoc);
		}
		else if (property.GetPropertyType() == typeid(glm::vec4).name())
		{
			auto pValue = std::make_shared<glm::vec4>(dynamic_cast<TemplatedMaterialProperty<glm::vec4>*>(&property)->property);
			auto unifLoc = UniformLocation<glm::vec4>::Resolve(sp, property.name, pValue);
			sp->AddUniformLocationBindable(unifLoc);
		}
	}
}
