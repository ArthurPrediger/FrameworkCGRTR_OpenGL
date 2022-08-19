#pragma once

#include "Mesh.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "ShaderProgram.h"
#include "VAO.h"
#include "VBO.h"

class TestTriangle : public Mesh
{
public:
	TestTriangle()
		:
		Mesh({
		// Positions // Colors
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom Right
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Bottom Left
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f // Top 
		})
	{
		std::shared_ptr<VertexShader> vs = VertexShader::Resolve("SimpleVertexShader.txt");
		AddBindable(vs);

		std::shared_ptr<FragmentShader> fs = FragmentShader::Resolve("SimpleFragmentShader.txt");
		AddBindable(fs);

		std::shared_ptr<ShaderProgram> ps = ShaderProgram::Resolve(vs, fs);
		AddBindable(ps);

		std::shared_ptr<VBO> vbo = VBO::Resolve(vertices, "TestTriangle");
		AddBindable(vbo);

		std::shared_ptr<VAO> vao = VAO::Resolve({vbo});
		AddBindable(vao);
	}
};