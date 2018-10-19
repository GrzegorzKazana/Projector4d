#include "stdafx.h"
#include "Canvas.h"
#include "Matrix.h"


Canvas::Canvas(HWND hParent, sf::ContextSettings settings)
	:sf::RenderWindow(hParent, settings)
{
	sf::Vector2u size = this->getSize();
	this->width_ = size.x;
	this->height_ = size.y;
}

Canvas::Canvas(sf::VideoMode size_, sf::ContextSettings settings)
	:sf::RenderWindow(size_, "SFML shapes", sf::Style::Default, settings)
{
	sf::Vector2u size = this->getSize();
	this->width_ = size.x;
	this->height_ = size.y;
}

void Canvas::drawPoint(Vector2d vec)
{
	float defult_radius = 5.f;
	sf::CircleShape point(defult_radius);
	point.setOrigin(defult_radius, defult_radius);
	point.setPosition(scaleWidth(vec.getX()), scaleHeight(vec.getY()));
	this->draw(point);
}

void Canvas::drawLine(Vector2d p0, Vector2d p1)
{
	Vector2d p0_scaled = Vector2d(scaleWidth(p0.getX()), scaleHeight(p0.getY()));
	Vector2d p1_scaled = Vector2d(scaleWidth(p1.getX()), scaleHeight(p1.getY()));
	//Vector2d displacement = p1_scaled - p0_scaled;
	Vector2d displacement(p1_scaled.getX() - p0_scaled.getX(), p1_scaled.getY() - p0_scaled.getY());
	float length = sqrt(displacement.getX()*displacement.getX() + displacement.getY()*displacement.getY());
	float width = 4.0f;
	sf::RectangleShape line(sf::Vector2f(length, width));
	line.setOrigin(0.f, width / 2.0);
	line.setPosition(p0_scaled.getX(), p0_scaled.getY());
	line.rotate(180.0 * atan(displacement.getY() / displacement.getX()) / 3.1415 + 180.0 * (displacement.getX()<0 ? 1 : 0));
	this->draw(line);
}

void Canvas::draw2dMesh(Mesh2d hedron)
{
	std::vector<Vector2d> points = hedron.getVertices();
	for (auto p : points) {
		drawPoint(p);
	}
	for (auto edge : hedron.getEdges()) {
		drawLine(points[edge.first], points[edge.second]);
	}
}

void Canvas::drawFps(double fps)
{
	float text_size = 15;
	sf::Font font;
	if (!font.loadFromFile("D:\\Studia\\SEM5\\ja\\Projekt\\Projector4d\\Debug\\arial.ttf"))
	{
		return;
	}
	sf::Text text;
	text.setFont(font);
	text.setString("fps: " + std::to_string(fps));
	text.setCharacterSize(text_size);
	text.setFillColor(sf::Color::White);
	text.setPosition(0.0f, height_ - text_size);
	draw(text);
}

float Canvas::scaleWidth(double x)
// accepts parameter in range <-1,1>, returns in range <0,width>
{
	return (1.0 + x) * this->width_ / 2.0;
}

float Canvas::scaleHeight(double y)
// accepts parameter in range <-1,1>, returns in range <0,height>
{
	return (1.0 + y) * this->height_ / 2.0;
}


Canvas::~Canvas()
{
}
