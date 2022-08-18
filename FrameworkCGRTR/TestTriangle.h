#pragma once

#include "Drawable.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "ShaderProgram.h"
#include "VAO.h"
#include "VBO.h"

class TestTriangle : public Drawable
{
public:
	TestTriangle()
		:
		Drawable({
		// Positions // Colors
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom Right
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Bottom Left
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f // Top 
		})
	{
		auto vs = std::make_shared<VertexShader>("SimpleVertexShader.txt");
		AddBindable(vs);

		auto fs = std::make_shared<FragmentShader>("SimpleFragmentShader.txt");
		AddBindable(fs);

		auto ps = std::make_shared<ShaderProgram>(*vs, *fs);
		AddBindable(ps);

		auto vao = std::make_shared<VAO>();
		AddBindable(vao);

		auto vbo = std::make_shared<VBO>(*vao, this->vertices);
		AddBindable(vbo);
	}
};