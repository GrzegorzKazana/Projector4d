#pragma once
#include <vector>
#include "Matrix.h"
#include "Vectors.h"

class IMeshNd
{
protected:
	unsigned int vertix_n;
	unsigned int edge_n;
	std::vector<std::pair<unsigned int, unsigned int>> edge_idx;
public:
	std::vector<std::pair<unsigned int, unsigned int>> getEdges() const;
	virtual ~IMeshNd() = 0 {};
};

class Mesh2d : public IMeshNd {
	std::vector<Vector2d> vertices;
public:
	Mesh2d();
	std::vector<Vector2d> getVertices();
	Mesh2d(std::vector<Vector2d> vets, std::vector<std::pair<unsigned int, unsigned int>> edges);
};

class Mesh3d : public IMeshNd {
	std::vector<Vector3d> vertices;
public:
	Mesh3d();
	std::vector<Vector3d> getVertices();
	Mesh3d(std::vector<Vector3d> vets, std::vector<std::pair<unsigned int, unsigned int>> edges);
};

class Mesh4d : public IMeshNd {
	std::vector<Vector4d> vertices;
public:
	Mesh4d();
	std::vector<Vector4d> getVertices();
	Mesh4d(std::vector<Vector4d> vets, std::vector<std::pair<unsigned int, unsigned int>> edges);
};

