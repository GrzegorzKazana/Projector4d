// Projector4d.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include "GraphicsEngineTests.h"
#include "AsmGraphicsEngine.h"
#include "Canvas.h"
#include <SFML/Graphics.hpp>
#include "AsmGraphicsEngine.h"

int main()
{	
	GraphicsEngineTests::testAll(AsmGraphicsEngine());

	AsmGraphicsEngine eng;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	Canvas window(settings);

	std::vector<Vector3d> points;
	points.push_back(Vector3d(-0.5, -0.5, 0.5));
	points.push_back(Vector3d(0.5, -0.5, 0.5));
	points.push_back(Vector3d(0.5, 0.5, 0.5));
	points.push_back(Vector3d(-0.5, 0.5, 0.5));
	points.push_back(Vector3d(-0.5, -0.5, -0.5));
	points.push_back(Vector3d(0.5, -0.5, -0.5));
	points.push_back(Vector3d(0.5, 0.5, -0.5));
	points.push_back(Vector3d(-0.5, 0.5, -0.5));
	double angle_offset = 0.0;
	sf::Clock clock;
	float lastTime = 0;
	while (window.isOpen())
	{
		sf::Event event_;
		while (window.pollEvent(event_))
		{
			if (event_.type == sf::Event::Closed)
				window.close();
		}
		window.clear();

		std::vector<Vector2d> projected_points2d;
		for (auto p : points) {
			// rotate 3d
			Vector3d rotated3d = eng.rotateX(p, angle_offset);
			// project 3d to 2d
			auto projected2d = eng.project2dPerspective(rotated3d);
			// display
			window.drawPoint(projected2d);
			projected_points2d.push_back(projected2d);
		}
		//for (int i = 0; i < 4; i++) {
		//	window.drawLine(projected_points2d[(i) % 4], projected_points2d[(i + 1) % 4]);
		//	window.drawLine(projected_points2d[4 + (i) % 4], projected_points2d[4 + (i + 1) % 4]);
		//	window.drawLine(projected_points2d[(i) % 8], projected_points2d[(i + 4) % 8]);

		//	window.drawLine(projected_points2d[8 + (i) % 4], projected_points2d[8 + (i + 1) % 4]);
		//	window.drawLine(projected_points2d[8 + 4 + (i) % 4], projected_points2d[8 + 4 + (i + 1) % 4]);
		//	window.drawLine(projected_points2d[8 + (i) % 8], projected_points2d[8 + (i + 4) % 8]);

		//	window.drawLine(projected_points2d[(i) % 4], projected_points2d[(i + 8)]);
		//	window.drawLine(projected_points2d[4 + (i) % 4], projected_points2d[12 + (i)]);
		//}
		angle_offset += 0.001;

		window.display();
		float currentTime = clock.restart().asSeconds();
		float fps = 1.f / currentTime;
		lastTime = currentTime;
		std::cout << "fps: " << fps << std::endl;
	}

    return 0;
}

