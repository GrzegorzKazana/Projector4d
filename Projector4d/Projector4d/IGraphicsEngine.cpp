/*
*Author: Grzegorz Kazana
*Date: 28-11-2018
*Jêzyki Asemblerowe 2018-2019
*/
#include "stdafx.h"
#include "IGraphicsEngine.h"


Mesh2d IGraphicsEngine::project2dOrtographic(Mesh3d hedron) const
{
	std::vector<Vector2d> res;
	for (Vector3d p : hedron.getVertices()) {
		res.push_back(project2dOrtographic(p));
	}
	return Mesh2d(res, std::vector<std::pair<unsigned int, unsigned int>>(hedron.getEdges()));
}

Mesh2d IGraphicsEngine::project2dOrtographic(Mesh4d hedron) const
{
	std::vector<Vector2d> res;
	for (Vector4d p : hedron.getVertices()) {
		res.push_back(project2dOrtographic(p));
	}
	return Mesh2d(res, std::vector<std::pair<unsigned int, unsigned int>>(hedron.getEdges()));
}

Mesh3d IGraphicsEngine::project3dOrtographic(Mesh4d hedron) const
{
	std::vector<Vector3d> res;
	for (Vector4d p : hedron.getVertices()) {
		res.push_back(project3dOrtographic(p));
	}
	return Mesh3d(res, std::vector<std::pair<unsigned int, unsigned int>>(hedron.getEdges()));
}

Mesh2d IGraphicsEngine::project2dPerspective(Mesh3d hedron, double distance) const
{
	std::vector<Vector2d> res;
	for (Vector3d p : hedron.getVertices()) {
		res.push_back(project2dPerspective(p, distance));
	}
	return Mesh2d(res, std::vector<std::pair<unsigned int, unsigned int>>(hedron.getEdges()));
}

Mesh2d IGraphicsEngine::project2dPerspective(Mesh4d hedron, double distance) const
{
	std::vector<Vector2d> res;
	for (Vector4d p : hedron.getVertices()) {
		res.push_back(project2dPerspective(p, distance));
	}
	return Mesh2d(res, std::vector<std::pair<unsigned int, unsigned int>>(hedron.getEdges()));
}

Mesh3d IGraphicsEngine::project3dPerspective(Mesh4d hedron, double distance) const
{
	std::vector<Vector3d> res;
	for (Vector4d p : hedron.getVertices()) {
		res.push_back(project3dPerspective(p, distance));
	}
	return Mesh3d(res, std::vector<std::pair<unsigned int, unsigned int>>(hedron.getEdges()));
}

Mesh2d IGraphicsEngine::rotate(Mesh2d hedron, double angle) const
{
	std::vector<Vector2d> res;
	for (Vector2d p : hedron.getVertices()) {
		res.push_back(rotate(p, angle));
	}
	return Mesh2d(res, std::vector<std::pair<unsigned int, unsigned int>>(hedron.getEdges()));
}

Mesh3d IGraphicsEngine::rotateX(Mesh3d hedron, double angle) const
{
	std::vector<Vector3d> res;
	for (Vector3d p : hedron.getVertices()) {
		res.push_back(rotateX(p, angle));
	}
	return Mesh3d(res, std::vector<std::pair<unsigned int, unsigned int>>(hedron.getEdges()));
}

Mesh3d IGraphicsEngine::rotateY(Mesh3d hedron, double angle) const
{
	std::vector<Vector3d> res;
	for (Vector3d p : hedron.getVertices()) {
		res.push_back(rotateY(p, angle));
	}
	return Mesh3d(res, std::vector<std::pair<unsigned int, unsigned int>>(hedron.getEdges()));
}

Mesh3d IGraphicsEngine::rotateZ(Mesh3d hedron, double angle) const
{
	std::vector<Vector3d> res;
	for (Vector3d p : hedron.getVertices()) {
		res.push_back(rotateZ(p, angle));
	}
	return Mesh3d(res, std::vector<std::pair<unsigned int, unsigned int>>(hedron.getEdges()));
}

Mesh4d IGraphicsEngine::rotateW(Mesh4d hedron, double angle) const
{
	std::vector<Vector4d> res;
	for (Vector4d p : hedron.getVertices()) {
		res.push_back(rotateW(p, angle));
	}
	return Mesh4d(res, std::vector<std::pair<unsigned int, unsigned int>>(hedron.getEdges()));
}
