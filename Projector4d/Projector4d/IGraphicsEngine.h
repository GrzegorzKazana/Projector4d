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
	Square project2dOrtographic(Cube hedron) const;
	Square project2dOrtographic(Tesseract hedron) const;
	Cube project3dOrtographic(Tesseract hedron) const;
	Square project2dPerspective(Cube hedron, double distance = 2) const;
	Square project2dPerspective(Tesseract hedron, double distance = 2) const;
	Cube project3dPerspective(Tesseract hedron, double distance = 2) const;
	Square rotate(Square hedron, double angle) const;
	Cube rotateX(Cube hedron, double angle) const;
	Cube rotateY(Cube hedron, double angle) const;
	Cube rotateZ(Cube hedron, double angle) const;
	virtual ~IGraphicsEngine() = 0 {};
};

