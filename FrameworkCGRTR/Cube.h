#pragma once

#include "Mesh.h"

class Cube
{
public:
	static Mesh GetMesh(float sideLength = 1.0f)
	{
		const float size = sideLength / 2.0f;

		Mesh::Vertices vertices{};

		vertices.vertsPos = {
			{  size, -size,  size },
			{  size,  size,  size },
			{ -size,  size,  size },
			{ -size, -size,  size },
			{  size, -size, -size },
			{  size,  size, -size },
			{ -size,  size, -size },
			{ -size, -size, -size }
		};

		//vertices.vertsNormals = {
		//	{  0.0f,  0.0f,  1.0f }, // out
		//	{  0.0f,  0.0f, -1.0f }, // in
		//	{  0.0f,  1.0f,  0.0f }, // up
		//	{  0.0f, -1.0f,  0.0f }, // down
		//	{  1.0f, 0.0f,   0.0f }, // right
		//	{ -1.0f, 0.0f,   0.0f }, // left
		//};

		vertices.vertsNormals = {
			{ 1.0f, 1.0f, 1.0f }, // out
			{ 1.0f, 0.0f, 0.0f }, // in
			{ 0.0f, 1.0f, 1.0f }, // up
			{ 1.0f, 1.0f, 0.0f }, // down
			{ 0.0f, 1.0f, 0.0f }, // right
			{ 1.0f, 0.0f, 1.0f }, // left
		};

		vertices.vertsTexts = {
			{ 1.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 0.0f, 1.0f },
			{ 0.0f, 0.0f }
		};

		Mesh mesh{vertices};

		mesh.AddGroup("Front",  { { { 0, 1, 2 }, { 0, 0, 0 }, { 0, 1, 2 } }, { { 2, 3, 0 }, { 0, 0, 0 }, { 2, 3, 0 } } });
		mesh.AddGroup("Back",   { { { 6, 5, 4 }, { 1, 1, 1 }, { 0, 1, 2 } }, { { 6, 4, 7 }, { 1, 1, 1 }, { 2, 3, 0 } } });
		mesh.AddGroup("Top",    { { { 1, 5, 6 }, { 2, 2, 2 }, { 0, 1, 2 } }, { { 6, 2, 1 }, { 2, 2, 2 }, { 2, 3, 0 } } });
		mesh.AddGroup("Bottom", { { { 4, 0, 3 }, { 3, 3, 3 }, { 0, 1, 2 } }, { { 3, 7, 4 }, { 3, 3, 3 }, { 2, 3, 0 } } });
		mesh.AddGroup("Right",  { { { 0, 4, 1 }, { 4, 4, 4 }, { 0, 1, 2 } }, { { 1, 4, 5 }, { 4, 4, 4 }, { 2, 3, 0 } } });
		mesh.AddGroup("Left",   { { { 7, 3, 2 }, { 5, 5, 5 }, { 0, 1, 2 } }, { { 2, 6, 7 }, { 5, 5, 5 }, { 2, 3, 0 } } });

		return mesh;
	}
};