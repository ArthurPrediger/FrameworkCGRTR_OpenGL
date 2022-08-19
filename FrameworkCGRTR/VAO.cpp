#include "VAO.h"
#include "VBO.h"
#include "BindableSet.h"

VAO::VAO(std::vector<std::shared_ptr<VBO>> VBOs)
	:
	Bindable("VAO", "VAO_", BindType::OnDraw),
	vao(NULL)
{
	for (size_t i = 0; i < VBOs.size(); i++)
	{
		uID.append(VBOs[i]->GetUniqueID());
	}
}

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
	auto vao = std::shared_ptr<VAO>(new VAO(VBOs));
	if (BindableSet::Resolve(vao))
	{
		vao->Generate();
		for (size_t i = 0; i < VBOs.size(); i++)
		{
			VBOs[i]->vao = vao->vao;
			VBOs[i]->Bind();
		}
	}
	return vao;
}

void VAO::Generate()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}
