#pragma once
#include "vectors.h"

class IGraphicsEngine{
public:
	virtual Vector2d project2dOrtographic(Vector3d point) const = 0;
	virtual Vector2d project2dOrtographic(Vector4d point) const = 0;
	virtual Vector3d project3dOrtographic(Vector4d point) const = 0;
	virtual Vector2d project2dPerspective(Vector3d point, double distance=2) const = 0;
	virtual Vector2d project2dPerspective(Vector4d point, double distance=2) const = 0;
	virtual Vector3d project3dPerspective(Vector4d point, double distance=2) const = 0;
	virtual Vector2d rotate(Vector2d point, double angle) const = 0;
	virtual Vector2d rotateX(Vector3d point, double angle) const = 0;
	virtual Vector2d rotateY(Vector2d point, double angle) const = 0;
	virtual Vector2d rotateZ(Vector2d point, double angle) const = 0;
	virtual ~IGraphicsEngine() = 0 {};
};

