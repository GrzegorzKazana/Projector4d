// Projector4d.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include "GraphicsEngineTests.h"
#include "AsmGraphicsEngine.h"

int main()
{	
	GraphicsEngineTests::testAll(AsmGraphicsEngine());
    return 0;
}

