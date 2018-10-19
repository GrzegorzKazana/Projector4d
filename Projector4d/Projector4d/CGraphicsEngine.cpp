#include "stdafx.h"
#include "CGraphicsEngine.h"
#include "CProjectionFunctions.h"

CGraphicsEngine::CGraphicsEngine()
{
}

Vector2d CGraphicsEngine::project2dOrtographic(Vector3d point) const
{
	Vector2d result;
	CImplementations::project2dOrtographic(point.get_cols(), point.get_rows(), point.data, result.data);
	return result;
}

Vector2d CGraphicsEngine::project2dOrtographic(Vector4d point) const
{
	Vector2d result;
	CImplementations::project2dOrtographic(point.get_cols(), point.get_rows(), point.data, result.data);
	return result;
}

Vector3d CGraphicsEngine::project3dOrtographic(Vector4d point) const
{
	Vector3d result;
	CImplementations::project3dOrtographic(point.get_cols(), point.get_rows(), point.data, result.data);
	return result;
}

Vector2d CGraphicsEngine::project2dPerspective(Vector3d point, double distance) const
{
	Vector2d result;
	CImplementations::project2dPerspective(point.get_cols(), point.get_rows(), point.data, result.data, distance);
	return result;
}

Vector2d CGraphicsEngine::project2dPerspective(Vector4d point, double distance) const
{
	return project2dPerspective(project3dPerspective(point, distance), distance);
}

Vector3d CGraphicsEngine::project3dPerspective(Vector4d point, double distance) const
{
	Vector3d result;
	CImplementations::project3dPerspective(point.get_cols(), point.get_rows(), point.data, result.data, distance);
	return result;
}

Vector2d CGraphicsEngine::rotate(Vector2d point, double angle) const
{
	Vector2d result;
	CImplementations::rotate(point.get_cols(), point.get_rows(), point.data, result.data, angle);
	return result;
}

Vector3d CGraphicsEngine::rotateX(Vector3d point, double angle) const
{
	Vector3d result;
	CImplementations::rotateX(point.get_cols(), point.get_rows(), point.data, result.data, angle);
	return result;
}

Vector3d CGraphicsEngine::rotateY(Vector3d point, double angle) const
{
	Vector3d result;
	CImplementations::rotateY(point.get_cols(), point.get_rows(), point.data, result.data, angle);
	return result;
}

Vector3d CGraphicsEngine::rotateZ(Vector3d point, double angle) const
{
	Vector3d result;
	CImplementations::rotateZ(point.get_cols(), point.get_rows(), point.data, result.data, angle);
	return result;
}

Vector4d CGraphicsEngine::rotateYZ(Vector4d point, double angle) const
{
	Vector4d result;
	CImplementations::rotateYZ(point.get_cols(), point.get_rows(), point.data, result.data, angle);
	return result;
}

Vector4d CGraphicsEngine::rotateW(Vector4d point, double angle) const
{
	Vector4d result;
	CImplementations::rotateW(point.get_cols(), point.get_rows(), point.data, result.data, angle);
	return result;
}

CGraphicsEngine::~CGraphicsEngine()
{
}
