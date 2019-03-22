/*
*Author: Grzegorz Kazana
*Date: 28-11-2018
*Jêzyki Asemblerowe 2018-2019
*/
#include "stdafx.h"
#include "LoggingGraphicsEngine.h"
#include <intrin.h>
#include <string>
#include <fstream>
#include <iostream>


LoggingGraphicsEngine::LoggingGraphicsEngine(IGraphicsEngine * eng, std::string path)
	: engine(eng)
{
	logFile.open(path);
}

Vector2d LoggingGraphicsEngine::project2dOrtographic(Vector3d point)
{
	return engine->project2dOrtographic(point);
}

Vector2d LoggingGraphicsEngine::project2dOrtographic(Vector4d point)
{
	return engine->project2dOrtographic(point);
}

Vector3d LoggingGraphicsEngine::project3dOrtographic(Vector4d point)
{
	return engine->project3dOrtographic(point);
}

Vector2d LoggingGraphicsEngine::project2dPerspective(Vector3d point, double distance)
{
	return engine->project2dPerspective(point, distance);
}

Vector2d LoggingGraphicsEngine::project2dPerspective(Vector4d point, double distance)
{
	return engine->project2dPerspective(point, distance);
}

Vector3d LoggingGraphicsEngine::project3dPerspective(Vector4d point, double distance)
{
	return engine->project3dPerspective(point, distance);
}

Vector2d LoggingGraphicsEngine::rotate(Vector2d point, double angle)
{
	return engine->rotate(point, angle);
}

Vector3d LoggingGraphicsEngine::rotateX(Vector3d point, double angle)
{
	return engine->rotateX(point, angle);
}

Vector3d LoggingGraphicsEngine::rotateY(Vector3d point, double angle)
{
	return engine->rotateY(point, angle);
}

Vector3d LoggingGraphicsEngine::rotateZ(Vector3d point, double angle)
{
	return engine->rotateZ(point, angle);
}

Vector4d LoggingGraphicsEngine::rotateW(Vector4d point, double angle)
{
	unsigned __int64 start = __rdtsc();
	auto result = engine->rotateW(point, angle);
	unsigned __int64 end = __rdtsc();
	unsigned __int64 res = end - start;
	logFile << res << std::endl;
	return result;
}

LoggingGraphicsEngine::~LoggingGraphicsEngine()
{
	delete engine;
	logFile.close();
}
