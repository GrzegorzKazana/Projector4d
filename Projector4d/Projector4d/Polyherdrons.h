#pragma once
#include <vector>
#include "Matrix.h"
#include "Vectors.h"

class IPolyhedron
{
protected:
	unsigned int vertix_n;
	unsigned int edge_n;
	std::vector<std::pair<unsigned int, unsigned int>> edge_idx;
public:
	std::vector<std::pair<unsigned int, unsigned int>> getEdges() const;
	virtual ~IPolyhedron() = 0 {};
};

class Square : public IPolyhedron {
	std::vector<Vector2d> vertices;
public:
	Square();
	std::vector<Vector2d> getVertices();
	Square(std::vector<Vector2d> vets);
};

class Cube : public IPolyhedron {
	std::vector<Vector3d> vertices;
public:
	Cube();
	std::vector<Vector3d> getVertices();
	Cube(std::vector<Vector3d> vets);
};

class Tesseract : public IPolyhedron {
	std::vector<Vector4d> vertices;
public:
	Tesseract();
	std::vector<Vector4d> getVertices();
	Tesseract(std::vector<Vector4d> vets);
};

