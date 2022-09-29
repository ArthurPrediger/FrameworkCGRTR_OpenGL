#pragma once

#include "Mesh.h"

class Sphere
{
public:
	static Mesh GetMesh(float radius = 1.0f, int latDiv = 12, int longDiv = 24)
	{
		const glm::vec4 base = { 0.0f, 0.0f, radius, 0.0f };
		const float lattitudeAngle = glm::pi<float>() / latDiv;
		const float longitudeAngle = glm::two_pi<float>() / longDiv;

		Mesh::Vertices vertices;
		for (int iLat = 1; iLat < latDiv; iLat++)
		{
			const auto latBase = glm::rotate(glm::mat4(1), (lattitudeAngle * iLat), glm::vec3(1.0f, 0.0f, 0.0f)) * base;
			for (int iLong = 0; iLong < longDiv; iLong++)
			{
				vertices.vertsPos.emplace_back();
				vertices.vertsPos.back() = glm::rotate(glm::mat4(1), (longitudeAngle * iLong), glm::vec3(0.0f, 0.0f, 1.0f)) * latBase;
			}
		}

		const auto iNorthPole = vertices.vertsPos.size();
		vertices.vertsPos.emplace_back();
		vertices.vertsPos.back() = base;
		const auto iSouthPole = vertices.vertsPos.size();
		vertices.vertsPos.emplace_back();
		vertices.vertsPos.back() = -base;

		for (auto& vPos : vertices.vertsPos)
		{
			auto n = glm::normalize(vPos);
			auto u = atan2(n.x, n.z) / glm::two_pi<float>() + 0.5f;
			auto v = n.y * 0.5 + 0.5;

			vertices.vertsTexts.push_back({ u, v });
			vertices.vertsNormals.push_back(n);
		}

		Mesh sphere{ vertices };

		const auto calcIdx = [longDiv](int iLat, int iLong)
		{
			return size_t(iLat * longDiv + iLong);
		};
		std::vector<size_t> indices;
		for (int iLat = 0; iLat < latDiv - 2; iLat++)
		{
			for (int iLong = 0; iLong < longDiv - 1; iLong++)
			{
				indices.push_back(calcIdx(iLat, iLong));
				indices.push_back(calcIdx(iLat + 1, iLong));
				indices.push_back(calcIdx(iLat, iLong + 1));
				indices.push_back(calcIdx(iLat, iLong + 1));
				indices.push_back(calcIdx(iLat + 1, iLong));
				indices.push_back(calcIdx(iLat + 1, iLong + 1));
			}

			indices.push_back(calcIdx(iLat, longDiv - 1));
			indices.push_back(calcIdx(iLat + 1, longDiv - 1));
			indices.push_back(calcIdx(iLat, 0));
			indices.push_back(calcIdx(iLat, 0));
			indices.push_back(calcIdx(iLat + 1, longDiv - 1));
			indices.push_back(calcIdx(iLat + 1, 0));
		}

		for (int iLong = 0; iLong < longDiv - 1; iLong++)
		{
			indices.push_back(iNorthPole);
			indices.push_back(calcIdx(0, iLong));
			indices.push_back(calcIdx(0, iLong + 1));

			indices.push_back(calcIdx(latDiv - 2, iLong + 1));
			indices.push_back(calcIdx(latDiv - 2, iLong));
			indices.push_back(iSouthPole);
		}

		indices.push_back(iNorthPole);
		indices.push_back(calcIdx(0, longDiv - 1));
		indices.push_back(calcIdx(0, 0));

		indices.push_back(calcIdx(latDiv - 2, 0));
		indices.push_back(calcIdx(latDiv - 2, longDiv - 1));
		indices.push_back(iSouthPole);

		std::vector<Group::Face> sphere_faces;

		for (size_t i = 0; i < indices.size(); i += 3)
		{
			Group::Face face{};

			face.posIndex[0] = face.textureIndex[0] = face.normalIndex[0] = indices[i];
			face.posIndex[1] = face.textureIndex[1] = face.normalIndex[1] = indices[i + 1];
			face.posIndex[2] = face.textureIndex[2] = face.normalIndex[2] = indices[i + 2];

			sphere_faces.push_back(face);
		}

		sphere.AddGroup({ "sphere", sphere_faces });

		return sphere;
	}
};