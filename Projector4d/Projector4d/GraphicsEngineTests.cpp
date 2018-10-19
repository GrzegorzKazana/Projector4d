#include "stdafx.h"
#include "GraphicsEngineTests.h"
#include <iostream>

bool GraphicsEngineTests::testAll(const IGraphicsEngine & eng)
{
	std::cout << "Testing all" << std::endl;
	bool success = testproject2dOrtographic3d(eng)
		& testproject2dOrtographic4d(eng)
		& testproject3dOrtographic4d(eng)
		& testproject2dPerspective3d(eng)
		& testproject2dPerspective4d(eng)
		& testproject3dPerspective4d(eng)
		& testrotate(eng)
		& testrotateX(eng)
		& testrotateY(eng)
		& testrotateZ(eng)
		& testrotateW(eng);
	return success;
}

bool GraphicsEngineTests::testproject2dOrtographic3d(const IGraphicsEngine & eng)
{
	std::cout << "Testing project2dOrtographic3d" << std::endl;
	Vector3d point(0.7, 3.0, 0.5);
	Vector2d result = eng.project2dOrtographic(point);
	Vector2d target(0.7, 3.0);
	bool success = result==target;
	std::cout << (success?"Succeed":"Failed") << std::endl;
	return success;
}

bool GraphicsEngineTests::testproject2dOrtographic4d(const IGraphicsEngine & eng)
{
	std::cout << "Testing project2dOrtographic4d" << std::endl;
	Vector4d point(0.7, 3.0, 0.5, 0.5);
	Vector2d result = eng.project2dOrtographic(point);
	Vector2d target(0.7, 3.0);
	bool success = result == target;
	std::cout << (success ? "Succeed" : "Failed") << std::endl;
	return success;
}

bool GraphicsEngineTests::testproject3dOrtographic4d(const IGraphicsEngine & eng)
{
	std::cout << "Testing project3dOrtographic4d" << std::endl;
	Vector4d point(0.7, 3.0, 0.6, 0.5);
	Vector3d result = eng.project3dOrtographic(point);
	Vector3d target(0.7, 3.0, 0.6);
	bool success = result == target;
	std::cout << (success ? "Succeed" : "Failed") << std::endl;
	return success;
}

bool GraphicsEngineTests::testproject2dPerspective3d(const IGraphicsEngine & eng)
{
	std::cout << "Testing project2dPerspective3d" << std::endl;
	Vector3d point(0.7, 3.0, 0.5);
	Vector2d result = eng.project2dPerspective(point, 2.0);
	Vector2d target(0.7 / (0.5 - 2.0), 3.0 / (0.5 - 2.0));
	bool success = result == target;
	std::cout << (success ? "Succeed" : "Failed") << std::endl;
	return success;
}

bool GraphicsEngineTests::testproject2dPerspective4d(const IGraphicsEngine & eng)
{
	std::cout << "Testing project2dPerspective4d" << std::endl;
	Vector4d point(0.7, 3.0, 0.6, 0.5);
	Vector2d result = eng.project2dPerspective(point, 2.0);
	Vector2d target(0.7 / (0.5 - 2.0) / (0.6 / (0.5 - 2.0) - 2.0), 3.0 / (0.5 - 2.0) / (0.6 / (0.5 - 2.0) - 2.0));
	bool success = result == target;
	std::cout << (success ? "Succeed" : "Failed") << std::endl;
	return success;
}

bool GraphicsEngineTests::testproject3dPerspective4d(const IGraphicsEngine & eng)
{
	std::cout << "Testing project3dPerspective4d" << std::endl;
	Vector4d point(0.7, 3.0, 0.6, 0.5);
	Vector3d result = eng.project3dPerspective(point, 2.0);
	Vector3d target(0.7 / (0.5 - 2.0), 3.0 / (0.5 - 2.0), 0.6 / (0.5 - 2.0));
	bool success = result == target;
	std::cout << (success ? "Succeed" : "Failed") << std::endl;
	return success;
}

bool GraphicsEngineTests::testrotate(const IGraphicsEngine & eng)
{
	std::cout << "Testing rotate" << std::endl;
	Vector2d point(0.4, -0.5);
	double angle = 0.3;
	Vector2d result = eng.rotate(point, angle);
	Vector2d target(0.529894698978, -0.359460161896);
	bool success = result == target;
	std::cout << (success ? "Succeed" : "Failed") << std::endl;
	return success;
}

bool GraphicsEngineTests::testrotateX(const IGraphicsEngine & eng)
{
	std::cout << "Testing rotateX" << std::endl;
	Vector3d point(0.4, -0.5, 1.0);
	double angle = 0.3;
	Vector3d result = eng.rotateX(point, angle);
	Vector3d target(0.4, -0.773188451220, 0.807576385790);
	bool success = result == target;
	std::cout << (success ? "Succeed" : "Failed") << std::endl;
	return success;
}

bool GraphicsEngineTests::testrotateY(const IGraphicsEngine & eng)
{
	std::cout << "Testing rotateY" << std::endl;
	Vector3d point(0.4, -0.5, 1.0);
	double angle = 0.3;
	Vector3d result = eng.rotateY(point, angle);
	Vector3d target(0.086614388988, -0.5, 1.073544571784);
	bool success = result == target;
	std::cout << (success ? "Succeed" : "Failed") << std::endl;
	return success;
}

bool GraphicsEngineTests::testrotateZ(const IGraphicsEngine & eng)
{
	std::cout << "Testing rotateZ" << std::endl;
	Vector3d point(0.4, -0.5, 1.0);
	double angle = 0.3;
	Vector3d result = eng.rotateZ(point, angle);
	Vector3d target(0.529894698978, -0.359460161896, 1.0);
	bool success = result == target;
	std::cout << (success ? "Succeed" : "Failed") << std::endl;
	return success;
}

bool GraphicsEngineTests::testrotateW(const IGraphicsEngine & eng)
{
	std::cout << "Testing rotateW" << std::endl;
	Vector4d point(0.4, -0.5, 1.0, 0.6);
	double angle = 0.3;
	Vector4d result = eng.rotateW(point, angle);
	Vector4d target(0.529894698978, -0.359460161896, 0.778024365124, 0.868722100132);
	bool success = result == target;
	std::cout << (success ? "Succeed" : "Failed") << std::endl;
	return success;
}
