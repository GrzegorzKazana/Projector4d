/*
*Author: Grzegorz Kazana
*Date: 28-11-2018
*Jêzyki Asemblerowe 2018-2019
*/
#include "stdafx.h"
#include "Polyherdrons.h"


std::vector<std::pair<unsigned int, unsigned int>> IMeshNd::getEdges() const
{
	return edge_idx;
}

Mesh3d::Mesh3d()
{
	vertix_n = 8;
	edge_n = 12;
	double default_coor = 0.5;
	vertices.push_back(Vector3d(default_coor, default_coor, default_coor));
	vertices.push_back(Vector3d(default_coor, default_coor, -default_coor));
	vertices.push_back(Vector3d(default_coor, -default_coor, -default_coor));
	vertices.push_back(Vector3d(default_coor, -default_coor, default_coor));
	vertices.push_back(Vector3d(-default_coor, default_coor, default_coor));
	vertices.push_back(Vector3d(-default_coor, default_coor, -default_coor));
	vertices.push_back(Vector3d(-default_coor, -default_coor, -default_coor));
	vertices.push_back(Vector3d(-default_coor, -default_coor, default_coor));
	for (unsigned int i = 0; i < 4; i++) {
		edge_idx.push_back(std::pair<unsigned int, unsigned int>(i, (i + 1)% 4));
		edge_idx.push_back(std::pair<unsigned int, unsigned int>(4 + i, 4 + (i + 1) % 4));
		edge_idx.push_back(std::pair<unsigned int, unsigned int>(i, i + 4));
	}
}

std::vector<Vector3d> Mesh3d::getVertices()
{
	return vertices;
}

Mesh3d::Mesh3d(std::vector<Vector3d> vets, std::vector<std::pair<unsigned int, unsigned int>> edges)
{
	vertix_n = 8;
	edge_n = 12;
	vertices = vets;
	edge_idx = edges;
}

Mesh2d::Mesh2d()
{
	vertix_n = 4;
	edge_n = 4;
	double default_coor = 0.5;
	vertices.push_back(Vector2d(default_coor, default_coor));
	vertices.push_back(Vector2d(default_coor, -default_coor));
	vertices.push_back(Vector2d(-default_coor, -default_coor));
	vertices.push_back(Vector2d(-default_coor, default_coor));
	for (unsigned int i = 0; i < 4; i++) {
		edge_idx.push_back(std::pair<unsigned int, unsigned int>(i, (i + 1) % 4));
	}
}

std::vector<Vector2d> Mesh2d::getVertices()
{
	return vertices;
}

Mesh2d::Mesh2d(std::vector<Vector2d> vets, std::vector<std::pair<unsigned int, unsigned int>> edges)
{
	vertix_n = 4;
	edge_n = 4;
	double default_coor = 0.5;
	vertices = vets;
	edge_idx = edges;
}

Mesh4d::Mesh4d()
{
	vertix_n = 16;
	edge_n = 32;
	double default_coor = 0.5;
	vertices.push_back(Vector4d(default_coor, default_coor, default_coor, default_coor));
	vertices.push_back(Vector4d(default_coor, default_coor, default_coor, -default_coor));
	vertices.push_back(Vector4d(default_coor, default_coor, -default_coor, -default_coor));
	vertices.push_back(Vector4d(default_coor, default_coor, -default_coor, default_coor));
	vertices.push_back(Vector4d(default_coor, -default_coor, default_coor, default_coor));
	vertices.push_back(Vector4d(default_coor, -default_coor, default_coor, -default_coor));
	vertices.push_back(Vector4d(default_coor, -default_coor, -default_coor, -default_coor));
	vertices.push_back(Vector4d(default_coor, -default_coor, -default_coor, default_coor));
	vertices.push_back(Vector4d(-default_coor, default_coor, default_coor, default_coor));
	vertices.push_back(Vector4d(-default_coor, default_coor, default_coor, -default_coor));
	vertices.push_back(Vector4d(-default_coor, default_coor, -default_coor, -default_coor));
	vertices.push_back(Vector4d(-default_coor, default_coor, -default_coor, default_coor));
	vertices.push_back(Vector4d(-default_coor, -default_coor, default_coor, default_coor));
	vertices.push_back(Vector4d(-default_coor, -default_coor, default_coor, -default_coor));
	vertices.push_back(Vector4d(-default_coor, -default_coor, -default_coor, -default_coor));
	vertices.push_back(Vector4d(-default_coor, -default_coor, -default_coor, default_coor));
	for (unsigned int i = 0; i < 4; i++) {
		// connect 1st cube
		edge_idx.push_back(std::pair<unsigned int, unsigned int>(i, (i + 1) % 4));
		edge_idx.push_back(std::pair<unsigned int, unsigned int>(4 + i, 4 + (i + 1) % 4));
		edge_idx.push_back(std::pair<unsigned int, unsigned int>(i, i + 4));
		// connect 2nd cube
		edge_idx.push_back(std::pair<unsigned int, unsigned int>(8+i, 8+(i + 1) % 4));
		edge_idx.push_back(std::pair<unsigned int, unsigned int>(8+4 + i, 8+4 + (i + 1) % 4));
		edge_idx.push_back(std::pair<unsigned int, unsigned int>(8+i, 8+i + 4));
		// connect cubes
		edge_idx.push_back(std::pair<unsigned int, unsigned int>(i, i+8));
		edge_idx.push_back(std::pair<unsigned int, unsigned int>(4+i, 4+i + 8));
	}
}

std::vector<Vector4d> Mesh4d::getVertices()
{
	return vertices;
}

Mesh4d::Mesh4d(std::vector<Vector4d> vets, std::vector<std::pair<unsigned int, unsigned int>> edges)
{
	vertix_n = 16;
	edge_n = 32;
	vertices = vets;
	edge_idx = edges;
}
