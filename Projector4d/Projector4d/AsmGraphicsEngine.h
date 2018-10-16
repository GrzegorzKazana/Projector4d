#pragma once
#include "IGraphicsEngine.h"

class AsmGraphicsEngine :public IGraphicsEngine
{
public:
	AsmGraphicsEngine();
	 Vector2d project2dOrtographic(Vector3d point) const override;
	 Vector2d project2dOrtographic(Vector4d point) const override;
	 Vector3d project3dOrtographic(Vector4d point) const override;
	 Vector2d project2dPerspective(Vector3d point, double distance = 2) const override;
	 Vector2d project2dPerspective(Vector4d point, double distance = 2) const override;
	 Vector3d project3dPerspective(Vector4d point, double distance = 2) const override;
	 Vector2d rotate(Vector2d point, double angle) const override;
	 Vector2d rotateX(Vector3d point, double angle) const override;
	 Vector2d rotateY(Vector2d point, double angle) const override;
	 Vector2d rotateZ(Vector2d point, double angle) const override;
	~AsmGraphicsEngine();
};

