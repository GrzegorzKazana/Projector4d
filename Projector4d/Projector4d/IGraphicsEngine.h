/*
*Author: Grzegorz Kazana
*Date: 28-11-2018
*Jêzyki Asemblerowe 2018-2019
*/
#pragma once
#include "vectors.h"
#include "Polyherdrons.h"

class IGraphicsEngine{
public:
	virtual Vector2d project2dOrtographic(Vector3d point) const = 0;
	virtual Vector2d project2dOrtographic(Vector4d point) const = 0;
	virtual Vector3d project3dOrtographic(Vector4d point) const = 0;
	virtual Vector2d project2dPerspective(Vector3d point, double distance=2) const = 0;
	virtual Vector2d project2dPerspective(Vector4d point, double distance=2) const = 0;
	virtual Vector3d project3dPerspective(Vector4d point, double distance=2) const = 0;
	virtual Vector2d rotate(Vector2d point, double angle) const = 0;
	virtual Vector3d rotateX(Vector3d point, double angle) const = 0;
	virtual Vector3d rotateY(Vector3d point, double angle) const = 0;
	virtual Vector3d rotateZ(Vector3d point, double angle) const = 0;
	virtual Vector4d rotateYZ(Vector4d point, double angle) const = 0;
	virtual Vector4d rotateW(Vector4d point, double angle) const = 0;
	Mesh2d project2dOrtographic(Mesh3d hedron) const;
	Mesh2d project2dOrtographic(Mesh4d hedron) const;
	Mesh3d project3dOrtographic(Mesh4d hedron) const;
	Mesh2d project2dPerspective(Mesh3d hedron, double distance = 2) const;
	Mesh2d project2dPerspective(Mesh4d hedron, double distance = 2) const;
	Mesh3d project3dPerspective(Mesh4d hedron, double distance = 2) const;
	Mesh2d rotate(Mesh2d hedron, double angle) const;
	Mesh3d rotateX(Mesh3d hedron, double angle) const;
	Mesh3d rotateY(Mesh3d hedron, double angle) const;
	Mesh3d rotateZ(Mesh3d hedron, double angle) const;
	Mesh4d rotateW(Mesh4d hedron, double angle) const;
	virtual ~IGraphicsEngine() = 0 {};
};

