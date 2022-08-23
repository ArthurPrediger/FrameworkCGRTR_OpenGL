#pragma once

#include "Mesh.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "ShaderProgram.h"
#include "VAO.h"
#include "VBO.h"
#include "UniformLocation.h"

class TestDiamond
{
public:
	struct BoxCollider
	{
		glm::vec2 bottomLeft;
		glm::vec2 topRight;
	};
public:
	TestDiamond()
		:
		mesh( Mesh::Vertices{ 
			{ {0.4f, 0.0f, 0.0f}, {0.0f, -0.4f, 0.0f},{-0.4f, 0.0f, 0.0f}, {0.0f, 0.4f, 0.0f} },
			{ {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f} },
			{ {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f} } }),
		transform(std::make_shared<glm::mat4>(glm::identity<glm::mat4>()))
	{
		mesh.AddGroup("TriangleFace", { { {0, 1, 2}, {0, 1, 2}, {0, 1, 2} }, { {2, 3, 0}, {2, 3, 0}, {2, 3, 0} } });

		auto tf = mesh.QueryGroup("TriangleFace");

		std::shared_ptr<VertexShader> vs = VertexShader::Resolve("SimpleVertexShader.txt");
		tf->AddBindable(vs);

		std::shared_ptr<FragmentShader> fs = FragmentShader::Resolve("SimpleFragmentShader.txt");
		tf->AddBindable(fs);

		sp = ShaderProgram::Resolve(vs, fs);
		tf->AddBindable(sp);

		std::shared_ptr<UniformLocation<glm::mat4>> unifLoc = UniformLocation<glm::mat4>::Resolve(sp, "transform", transform);
		sp->AddUniformLocationBindable(unifLoc);

		std::shared_ptr<VBO> vbo = VBO::Resolve(std::move(mesh.GetVerticesFromGroup("TriangleFace")), "TestTriangle");
		tf->AddBindable(vbo);

		std::shared_ptr<VAO> vao = VAO::Resolve({ vbo });
		tf->AddBindable(vao);

		for (const auto& v : mesh.GetVertices().vertsPos)
		{
			if(bc.bottomLeft.x > v.x) bc.bottomLeft.x = v.x;
			if(bc.bottomLeft.y > v.y) bc.bottomLeft.y = v.y;
			if(bc.topRight.x < v.x) bc.topRight.x = v.x;
			if(bc.topRight.y < v.y) bc.topRight.y = v.y;
		}
	}
	void Draw(float dt)
	{
		Bounce(dt);

		mesh.Draw();
	}
	void Bounce(float dt)
	{
		const auto displacement = speed * dt * direction;
		translation += displacement;

		if (translation.x + bc.bottomLeft.x < -1.0f)
		{
			const auto dot = glm::dot(-direction, glm::vec2(1.0f, 0.0f));
			if(dot > 0)
				direction += 2.0f * dot * glm::vec2(1.0f, 0.0f);
		}
		if (translation.y + bc.bottomLeft.y < -1.0f)
		{
			const auto dot = glm::dot(-direction, glm::vec2(0.0f, 1.0f));
			if (dot > 0)
				direction += 2.0f * dot * glm::vec2(0.0f, 1.0f);
		}
		if (translation.x + bc.topRight.x > 1.0f)
		{
			const auto dot = glm::dot(-direction, glm::vec2(-1.0f, 0.0f));
			if (dot > 0)
				direction += 2.0f * dot * glm::vec2(-1.0f, 0.0f);
		}
		if (translation.y + bc.topRight.y > 1.0f)
		{
			const auto dot = glm::dot(-direction, glm::vec2(0.0f, -1.0f));
			if (dot > 0)
				direction += 2.0f * dot * glm::vec2(0.0f, -1.0f);
		}

		*transform = glm::translate(*transform, glm::vec3(displacement, 0.0f));
	}
private:
	Mesh mesh;
	std::shared_ptr<ShaderProgram> sp;
	std::shared_ptr<glm::mat4> transform = nullptr;
	BoxCollider bc = { glm::vec2(0.0f), glm::vec2(0.0f) };
	glm::vec2 translation = glm::vec2(0.0f);
	glm::vec2 direction = glm::normalize(glm::vec2(3.0f, 2.0f));
	float speed = 0.5f;
};