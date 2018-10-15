#pragma once
#include "IGraphicsEngine.h"

class GraphicsEngineTests {
public:
	static bool testAll(const IGraphicsEngine & eng);
	static bool testproject2dOrtographic3d(const IGraphicsEngine & eng);
	static bool testproject2dOrtographic4d(const IGraphicsEngine & eng);
	static bool testproject3dOrtographic4d(const IGraphicsEngine & eng);
	static bool testproject2dPerspective3d(const IGraphicsEngine & eng);
	static bool testproject2dPerspective4d(const IGraphicsEngine & eng);
	static bool testproject3dPerspective4d(const IGraphicsEngine & eng);
	static bool testrotate(const IGraphicsEngine & eng);
	static bool testrotateX(const IGraphicsEngine & eng);
	static bool testrotateY(const IGraphicsEngine & eng);
	static bool testrotateZ(const IGraphicsEngine & eng);
};