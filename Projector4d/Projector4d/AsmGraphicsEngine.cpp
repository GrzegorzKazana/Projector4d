#include "stdafx.h"
#include "AsmGraphicsEngine.h"
#include "ProjectionFunctionsDll.h"

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

Vector2d AsmGraphicsEngine::rotate(Vector2d point) const
{
	return Vector2d();
}

Vector2d AsmGraphicsEngine::rotateX(Vector3d point) const
{
	return Vector2d();
}

Vector2d AsmGraphicsEngine::rotateY(Vector2d point) const
{
	return Vector2d();
}

Vector2d AsmGraphicsEngine::rotateZ(Vector2d point) const
{
	return Vector2d();
}

AsmGraphicsEngine::~AsmGraphicsEngine()
{
}
