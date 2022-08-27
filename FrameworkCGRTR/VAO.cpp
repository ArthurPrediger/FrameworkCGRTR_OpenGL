#include "VAO.h"
#include "VBO.h"
#include "BindableSet.h"

VAO::VAO(std::vector<std::shared_ptr<VBO>> VBOs)
	:
	Bindable("VAO", BindType::OnDraw),
	vao(NULL)
{}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &vao);
}

void VAO::Bind()
{
	glBindVertexArray(vao);
}

std::shared_ptr<VAO> VAO::Resolve(std::vector<std::shared_ptr<VBO>> VBOs)
{
	auto pair = BindableSet::Resolve<VAO>(VBOs);
	if (!pair.first)
	{
		pair.second->Generate();
		for (size_t i = 0; i < VBOs.size(); i++)
		{
			VBOs[i]->vao = pair.second->vao;
			VBOs[i]->Bind();
		}
	}
	return pair.second;
}

std::string VAO::GetUniqueID(std::vector<std::shared_ptr<class VBO>> VBOs)
{
	std::string uID = "VAO_";

	for (size_t i = 0; i < VBOs.size(); i++)
	{
		uID.append(VBOs[i]->GetName());
	}

	return uID;
};

void VAO::Generate()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}
