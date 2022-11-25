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
	void SetBindTarget(std::shared_ptr<class ShaderProgram> sp);
	void BindProperties();
	bool HasTextureType(const std::string& texture_type) const;
private:
	friend class MTL_Loader;
	struct MaterialProperty
	{
	public:
		std::string name;
		virtual const char* GetPropertyType() const = 0;
		virtual void Bind() = 0;
	};
	template<typename T> 
	struct TemplatedMaterialProperty : public MaterialProperty
	{
		const char* GetPropertyType() const override
		{
			return property_type;
		}
		void Bind() override
		{
			if(uniformSetter)
				*uniformSetter = property;
		}
		T property;
		const char* property_type = typeid(T).name();
		std::shared_ptr<T> uniformSetter = nullptr;
	};
private:
	std::string mtllib_file_name;
	std::string name;
	std::vector<std::string> texture_types;
	std::vector<std::shared_ptr<class Texture2D>> textureMaps;
	std::vector<std::shared_ptr<MaterialProperty>> properties;
};