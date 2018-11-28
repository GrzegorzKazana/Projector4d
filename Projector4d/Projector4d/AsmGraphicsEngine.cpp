/*
*Author: Grzegorz Kazana
*Date: 28-11-2018
*Jêzyki Asemblerowe 2018-2019
*/
#include "stdafx.h"
#include "AsmGraphicsEngine.h"
#include "AsmProjectionFunctions.h"

AsmGraphicsEngine::AsmGraphicsEngine()
{
}

Vector2d AsmGraphicsEngine::project2dOrtographic(Vector3d point) const
{
	Vector2d result;
	AsmImplementations::project2dOrtographic(point.get_cols(), point.get_rows(), point.data, result.data);
	return result;
}

Vector2d AsmGraphicsEngine::project2dOrtographic(Vector4d point) const
{
	Vector2d result;
	AsmImplementations::project2dOrtographic(point.get_cols(), point.get_rows(), point.data, result.data);
	return result;
}

Vector3d AsmGraphicsEngine::project3dOrtographic(Vector4d point) const
{
	Vector3d result;
	AsmImplementations::project3dOrtographic(point.get_cols(), point.get_rows(), point.data, result.data);
	return result;
}

Vector2d AsmGraphicsEngine::project2dPerspective(Vector3d point, double distance) const
{
	Vector2d result;
	AsmImplementations::project2dPerspective(point.get_cols(), point.get_rows(), point.data, result.data, distance);
	return result;
}

Vector2d AsmGraphicsEngine::project2dPerspective(Vector4d point, double distance) const
{
	return project2dPerspective(project3dPerspective(point, distance), distance);
}

Vector3d AsmGraphicsEngine::project3dPerspective(Vector4d point, double distance) const
{
	Vector3d result;
	AsmImplementations::project3dPerspective(point.get_cols(), point.get_rows(), point.data, result.data, distance);
	return result;
}

Vector2d AsmGraphicsEngine::rotate(Vector2d point, double angle) const
{
	Vector2d result;
	AsmImplementations::rotate(point.get_cols(), point.get_rows(), point.data, result.data, angle);
	return result;
}

Vector3d AsmGraphicsEngine::rotateX(Vector3d point, double angle) const
{
	Vector3d result;
	AsmImplementations::rotateX(point.get_cols(), point.get_rows(), point.data, result.data, angle);
	return result;
}

Vector3d AsmGraphicsEngine::rotateY(Vector3d point, double angle) const
{
	Vector3d result;
	AsmImplementations::rotateY(point.get_cols(), point.get_rows(), point.data, result.data, angle);
	return result;
}

Vector3d AsmGraphicsEngine::rotateZ(Vector3d point, double angle) const
{
	Vector3d result;
	AsmImplementations::rotateZ(point.get_cols(), point.get_rows(), point.data, result.data, angle);
	return result;
}

Vector4d AsmGraphicsEngine::rotateYZ(Vector4d point, double angle) const
{
	Vector4d result;
	AsmImplementations::rotateYZ(point.get_cols(), point.get_rows(), point.data, result.data, angle);
	return result;
}

Vector4d AsmGraphicsEngine::rotateW(Vector4d point, double angle) const
{
	Vector4d result;
	AsmImplementations::rotateW(point.get_cols(), point.get_rows(), point.data, result.data, angle);
	return result;
}

AsmGraphicsEngine::~AsmGraphicsEngine()
{
}
