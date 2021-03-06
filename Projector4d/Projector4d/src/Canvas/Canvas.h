/*
*Author: Grzegorz Kazana
*Date: 28-11-2018
*J�zyki Asemblerowe 2018-2019
*/
#pragma once
#include <SFML/Graphics.hpp>
#include "../Objects/Vectors.h"
#include "../Objects/Polyherdrons.h"
#include "windows.h"

class Canvas: public sf::RenderWindow
{
	unsigned int width_ = 0;
	unsigned int height_ = 0;
	sf::Font textFont;
	bool fontLoaded = false;
public:
	Canvas(HWND hParent, sf::ContextSettings settings);
	Canvas(sf::VideoMode size_, sf::ContextSettings settings);
	void drawPoint(Vector2d point);
	void drawLine(Vector2d p1, Vector2d p2);
	void draw2dMesh(Mesh2d hedron);
	void drawFps(double fps);
	float scaleWidth(double x);
	float scaleHeight(double y);
	~Canvas();
};

