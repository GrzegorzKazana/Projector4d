/*
*Author: Grzegorz Kazana
*Date: 28-11-2018
*Jêzyki Asemblerowe 2018-2019
*/
#pragma once
#include "IGraphicsEngine.h"

class GraphicsEngineTests {
public:
	static bool testAll(IGraphicsEngine* eng);
	static bool testproject2dOrtographic3d(IGraphicsEngine* eng);
	static bool testproject2dOrtographic4d(IGraphicsEngine* eng);
	static bool testproject3dOrtographic4d(IGraphicsEngine* eng);
	static bool testproject2dPerspective3d(IGraphicsEngine* eng);
	static bool testproject2dPerspective4d(IGraphicsEngine* eng);
	static bool testproject3dPerspective4d(IGraphicsEngine* eng);
	static bool testrotate(IGraphicsEngine* eng);
	static bool testrotateX(IGraphicsEngine* eng);
	static bool testrotateY(IGraphicsEngine* eng);
	static bool testrotateZ(IGraphicsEngine* eng);
	static bool testrotateW(IGraphicsEngine* eng);
};