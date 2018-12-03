/*
*Author: Grzegorz Kazana
*Date: 28-11-2018
*Jêzyki Asemblerowe 2018-2019
*/
#include "stdafx.h"
#include "CGraphicsEngine.h"
#include "CProjectionFunctions.h"

CGraphicsEngine::CGraphicsEngine()
{
	handle = new CImplementations;
}

Vector2d CGraphicsEngine::project2dOrtographic(Vector3d point)
{
	Vector2d result;
	handle->project2dOrtographic(point.get_cols(), point.get_rows(), point.data, result.data);
	return result;
}

Vector2d CGraphicsEngine::project2dOrtographic(Vector4d point)
{
	return project2dOrtographic(project3dOrtographic(point));
}

Vector3d CGraphicsEngine::project3dOrtographic(Vector4d point)
{
	Vector3d result;
	handle->project3dOrtographic(point.get_cols(), point.get_rows(), point.data, result.data);
	return result;
}

Vector2d CGraphicsEngine::project2dPerspective(Vector3d point, double distance)
{
	Vector2d result;
	handle->project2dPerspective(point.get_cols(), point.get_rows(), point.data, result.data, distance);
	return result;
}

Vector2d CGraphicsEngine::project2dPerspective(Vector4d point, double distance)
{
	return project2dPerspective(project3dPerspective(point, distance), distance);
}

Vector3d CGraphicsEngine::project3dPerspective(Vector4d point, double distance)
{
	Vector3d result;
	handle->project3dPerspective(point.get_cols(), point.get_rows(), point.data, result.data, distance);
	return result;
}

Vector2d CGraphicsEngine::rotate(Vector2d point, double angle)
{
	Vector2d result;
	handle->rotate(point.get_cols(), point.get_rows(), point.data, result.data, angle);
	return result;
}

Vector3d CGraphicsEngine::rotateX(Vector3d point, double angle)
{
	Vector3d result;
	handle->rotateX(point.get_cols(), point.get_rows(), point.data, result.data, angle);
	return result;
}

Vector3d CGraphicsEngine::rotateY(Vector3d point, double angle)
{
	Vector3d result;
	handle->rotateY(point.get_cols(), point.get_rows(), point.data, result.data, angle);
	return result;
}

Vector3d CGraphicsEngine::rotateZ(Vector3d point, double angle)
{
	Vector3d result;
	handle->rotateZ(point.get_cols(), point.get_rows(), point.data, result.data, angle);
	return result;
}

Vector4d CGraphicsEngine::rotateW(Vector4d point, double angle)
{
	Vector4d result;
	handle->rotateW(point.get_cols(), point.get_rows(), point.data, result.data, angle);
	return result;
}

CGraphicsEngine::~CGraphicsEngine()
{
	delete handle;
}
