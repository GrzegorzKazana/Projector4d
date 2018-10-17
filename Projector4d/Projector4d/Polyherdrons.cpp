#include "stdafx.h"
#include "Polyherdrons.h"


std::vector<std::pair<unsigned int, unsigned int>> IPolyhedron::getEdges() const
{
	return edge_idx;
}

Cube::Cube()
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

std::vector<Vector3d> Cube::getVertices()
{
	return vertices;
}

Cube::Cube(std::vector<Vector3d> vets)
{
	vertix_n = 8;
	edge_n = 12;
	vertices = vets;
	for (unsigned int i = 0; i < 4; i++) {
		edge_idx.push_back(std::pair<unsigned int, unsigned int>(i, (i + 1) % 4));
		edge_idx.push_back(std::pair<unsigned int, unsigned int>(4 + i, 4 + (i + 1) % 4));
		edge_idx.push_back(std::pair<unsigned int, unsigned int>(i, i + 4));
	}
}

Square::Square()
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

std::vector<Vector2d> Square::getVertices()
{
	return vertices;
}

Square::Square(std::vector<Vector2d> vets)
{
	vertix_n = 4;
	edge_n = 4;
	double default_coor = 0.5;
	vertices = vets;
	for (unsigned int i = 0; i < 4; i++) {
		edge_idx.push_back(std::pair<unsigned int, unsigned int>(i, (i + 1) % 4));
	}
}

Tesseract::Tesseract()
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

std::vector<Vector4d> Tesseract::getVertices()
{
	return vertices;
}

Tesseract::Tesseract(std::vector<Vector4d> vets)
{
	vertix_n = 8;
	edge_n = 12;
	vertices = vets;
	for (unsigned int i = 0; i < 4; i++) {
		// connect 1st cube
		edge_idx.push_back(std::pair<unsigned int, unsigned int>(i, (i + 1) % 4));
		edge_idx.push_back(std::pair<unsigned int, unsigned int>(4 + i, 4 + (i + 1) % 4));
		edge_idx.push_back(std::pair<unsigned int, unsigned int>(i, i + 4));
		// connect 2nd cube
		edge_idx.push_back(std::pair<unsigned int, unsigned int>(8 + i, 8 + (i + 1) % 4));
		edge_idx.push_back(std::pair<unsigned int, unsigned int>(8 + 4 + i, 8 + 4 + (i + 1) % 4));
		edge_idx.push_back(std::pair<unsigned int, unsigned int>(8 + i, 8 + i + 4));
		// connect cubes
		edge_idx.push_back(std::pair<unsigned int, unsigned int>(i, i + 8));
		edge_idx.push_back(std::pair<unsigned int, unsigned int>(4 + i, 4 + i + 8));
	}
}
