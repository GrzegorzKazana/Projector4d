// Projector4d.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include "GraphicsEngineTests.h"
#include "AsmGraphicsEngine.h"
#include "Canvas.h"
#include <SFML/Graphics.hpp>
#include "AsmGraphicsEngine.h"
#include "Polyherdrons.h"

int main()
{	
	GraphicsEngineTests::testAll(AsmGraphicsEngine());

	AsmGraphicsEngine eng;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	Canvas window(settings);

	Mesh3d c;
	Mesh4d t;

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


		window.draw2dMesh(eng.project2dPerspective(eng.rotateY(eng.project3dPerspective(t, 1.5), angle_offset)));

		angle_offset += 0.001;

		window.display();
		float currentTime = clock.restart().asSeconds();
		float fps = 1.f / currentTime;
		lastTime = currentTime;
		std::cout << "fps: " << fps << std::endl;
	}

    return 0;
}

