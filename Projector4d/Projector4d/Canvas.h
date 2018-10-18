#pragma once
#include <SFML/Graphics.hpp>
#include "Vectors.h"
#include "Polyherdrons.h"

class Canvas: public sf::RenderWindow
{
	unsigned int width_ = 0;
	unsigned int height_ = 0;
public:
	Canvas(sf::VideoMode size_, sf::ContextSettings settings);
	void drawPoint(Vector2d point);
	void drawLine(Vector2d p1, Vector2d p2);
	void draw2dMesh(Mesh2d hedron);
	float scaleWidth(double x);
	float scaleHeight(double y);
	~Canvas();
};

