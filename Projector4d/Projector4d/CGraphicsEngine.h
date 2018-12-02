/*
*Author: Grzegorz Kazana
*Date: 28-11-2018
*Jêzyki Asemblerowe 2018-2019
*/
#pragma once
#include "IGraphicsEngine.h"
#include "CProjectionFunctions.h"

class CGraphicsEngine :
	public IGraphicsEngine
{
	CImplementations* handle;
public:
	CGraphicsEngine();
	using IGraphicsEngine::project2dOrtographic;
	using IGraphicsEngine::project3dOrtographic;
	using IGraphicsEngine::project2dPerspective;
	using IGraphicsEngine::project3dPerspective;
	using IGraphicsEngine::rotate;
	using IGraphicsEngine::rotateX;
	using IGraphicsEngine::rotateY;
	using IGraphicsEngine::rotateZ;
	using IGraphicsEngine::rotateW;
	Vector2d project2dOrtographic(Vector3d point) const override;
	Vector2d project2dOrtographic(Vector4d point) const override;
	Vector3d project3dOrtographic(Vector4d point) const override;
	Vector2d project2dPerspective(Vector3d point, double distance = 2) const override;
	Vector2d project2dPerspective(Vector4d point, double distance = 2) const override;
	Vector3d project3dPerspective(Vector4d point, double distance = 2) const override;
	Vector2d rotate(Vector2d point, double angle) const override;
	Vector3d rotateX(Vector3d point, double angle) const override;
	Vector3d rotateY(Vector3d point, double angle) const override;
	Vector3d rotateZ(Vector3d point, double angle) const override;
	Vector4d rotateW(Vector4d point, double angle) const override;
	~CGraphicsEngine();
};

