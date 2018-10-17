#include "stdafx.h"
#include "IGraphicsEngine.h"

Square IGraphicsEngine::project2dOrtographic(Cube hedron) const
{
	std::vector<Vector2d> res;
	for (Vector3d p : hedron.getVertices()) {
		res.push_back(project2dOrtographic(p));
	}
	return Square(res);
}

Square IGraphicsEngine::project2dOrtographic(Tesseract hedron) const
{
	std::vector<Vector2d> res;
	for (Vector4d p : hedron.getVertices()) {
		res.push_back(project2dOrtographic(p));
	}
	return Square(res);
}

Cube IGraphicsEngine::project3dOrtographic(Tesseract hedron) const
{
	std::vector<Vector3d> res;
	for (Vector4d p : hedron.getVertices()) {
		res.push_back(project3dOrtographic(p));
	}
	return Cube(res);
}

Square IGraphicsEngine::project2dPerspective(Cube hedron, double distance) const
{
	std::vector<Vector2d> res;
	for (Vector3d p : hedron.getVertices()) {
		res.push_back(project2dPerspective(p));
	}
	return Square(res);
}

Square IGraphicsEngine::project2dPerspective(Tesseract hedron, double distance) const
{
	std::vector<Vector2d> res;
	for (Vector4d p : hedron.getVertices()) {
		res.push_back(project2dPerspective(p));
	}
	return Square(res);
}

Cube IGraphicsEngine::project3dPerspective(Tesseract hedron, double distance) const
{
	std::vector<Vector3d> res;
	for (Vector4d p : hedron.getVertices()) {
		res.push_back(project3dPerspective(p));
	}
	return Cube(res);
}

Square IGraphicsEngine::rotate(Square hedron, double angle) const
{
	std::vector<Vector2d> res;
	for (Vector2d p : hedron.getVertices()) {
		res.push_back(rotate(p, angle));
	}
	return Square(res);
}

Cube IGraphicsEngine::rotateX(Cube hedron, double angle) const
{
	std::vector<Vector3d> res;
	for (Vector3d p : hedron.getVertices()) {
		res.push_back(rotateX(p, angle));
	}
	return Cube(res);
}

Cube IGraphicsEngine::rotateY(Cube hedron, double angle) const
{
	std::vector<Vector3d> res;
	for (Vector3d p : hedron.getVertices()) {
		res.push_back(rotateY(p, angle));
	}
	return Cube(res);
}

Cube IGraphicsEngine::rotateZ(Cube hedron, double angle) const
{
	std::vector<Vector3d> res;
	for (Vector3d p : hedron.getVertices()) {
		res.push_back(rotateZ(p, angle));
	}
	return Cube(res);
}
