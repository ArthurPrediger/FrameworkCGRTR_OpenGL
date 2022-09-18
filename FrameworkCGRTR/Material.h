#pragma once

#include <string>
#include <vector>
#include <memory>

class Material
{
public:
	Material() = delete;
	Material(const std::string& mtllib_file_name, const std::string& name);

	static std::string GetUniqueID(const std::string& mtllib_file_name, const std::string& name)
	{
		return "Material_" + mtllib_file_name + "_" + name;
	};
	const std::string& GetName() const
	{
		return name;
	}
	void BindTextureMaps();
	void BindProperties(std::shared_ptr<class ShaderProgram> sp);
private:
	friend class MTL_Loader;
	struct MaterialProperty
	{
		std::string name;
		virtual const char* GetPropertyType() const = 0;
	};
	template<typename T> 
	struct TemplatedMaterialProperty : public MaterialProperty
	{
		const char* GetPropertyType() const override
		{
			return typeid(property).name();
		};
		T property;
	};
private:
	std::string mtllib_file_name;
	std::string name;
	std::vector<std::shared_ptr<class Bindable>> textureMaps;
	std::vector<MaterialProperty> properties;
};