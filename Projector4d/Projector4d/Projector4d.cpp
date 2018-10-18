#include "stdafx.h"
#include "resource.h"
#include "windows.h"
#include <string>
#include <SFML/Graphics.hpp>

HWND hButton1;
HWND hButton2;

LRESULT CALLBACK OnEvent(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	std::string sampletext = "SAMPLETEXT";
	std::wstring wsampletext = std::wstring(sampletext.begin(), sampletext.end());

	WNDCLASS WindowClass;
	WindowClass.style = 0;
	WindowClass.lpfnWndProc = &OnEvent;
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.hInstance = hInstance;
	WindowClass.hIcon = NULL;
	WindowClass.hCursor = 0;
	WindowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BACKGROUND);
	WindowClass.lpszMenuName = NULL;
	WindowClass.lpszClassName = wsampletext.c_str();
	RegisterClass(&WindowClass);


	// main window
	HWND hWnd = CreateWindow(wsampletext.c_str(), wsampletext.c_str(), WS_SYSMENU | WS_VISIBLE, 0, 0, 800, 600, NULL, NULL, hInstance, NULL);
	hButton1 = CreateWindow(L"button", L"Label1",
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		300, 200,
		50, 20,
		hWnd, (HMENU)1001,
		hInstance, NULL);
	hButton2 = CreateWindow(L"button", L"Label2",
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
		350, 200,
		50, 20,
		hWnd, (HMENU)1001,
		hInstance, NULL);
	HWND View1 = CreateWindow(L"STATIC", NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, 0, 0, 300, 400, hWnd, NULL, hInstance, NULL);

	sf::RenderWindow SFMLView1(View1);
	sf::CircleShape shape(50);
	shape.setFillColor(sf::Color(100, 250, 50));

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	//ShowWindow(hButton, nCmdShow);
	//UpdateWindow(hButton);

	MSG Message;
	Message.message = ~WM_QUIT;
	while (Message.message != WM_QUIT)
	{
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			// If a message was waiting in the message queue, process it
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
			// SFML rendering code goes here
			// Clear views
			SFMLView1.clear(sf::Color::Black);

			// Draw sprite 1 on view 1
			SFMLView1.draw(shape);

			// Display each view on screen
			SFMLView1.display();
		}
	}

	return Message.wParam;
}

LRESULT CALLBACK OnEvent(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		if ((HWND)lParam == hButton1) {
			MessageBox(hwnd, (LPWSTR)L"Button 1", (LPWSTR)L"Ha!", MB_OK);
		}
		else if ((HWND)lParam == hButton2) {
			MessageBox(hwnd, (LPWSTR)L"Button 2", (LPWSTR)L"Ha!", MB_OK);
		}
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

//// Projector4d.cpp : Defines the entry point for the console application.
////
//#include "stdafx.h"
//#include <iostream>
//#include "GraphicsEngineTests.h"
//#include "AsmGraphicsEngine.h"
//#include "Canvas.h"
//#include <SFML/Graphics.hpp>
//#include "AsmGraphicsEngine.h"
//#include "Polyherdrons.h"
//
//int main()
//{	
//	GraphicsEngineTests::testAll(AsmGraphicsEngine());
//
//	AsmGraphicsEngine eng;
//	sf::ContextSettings settings;
//	settings.antialiasingLevel = 8;
//	Canvas window(settings);
//
//	Mesh3d c;
//	Mesh4d t;
//
//	double angle_offset = 0.0;
//	sf::Clock clock;
//	float lastTime = 0;
//	while (window.isOpen())
//	{
//		sf::Event event_;
//		while (window.pollEvent(event_))
//		{
//			if (event_.type == sf::Event::Closed)
//				window.close();
//		}
//		window.clear();
//
//		auto rotated4d = eng.rotateW(t, -angle_offset);
//		auto projected3d = eng.project3dPerspective(rotated4d, 1.2);
//		auto rotated3d = eng.rotateZ(eng.rotateX(eng.rotateY(projected3d, 1.0), 0.0), 0.0);
//		auto projected2d = eng.project2dPerspective(rotated3d, 1.2);
//
//		window.draw2dMesh(projected2d);
//
//		angle_offset += 0.001;
//
//		window.display();
//		float currentTime = clock.restart().asSeconds();
//		float fps = 1.f / currentTime;
//		lastTime = currentTime;
//		std::cout << "fps: " << fps << std::endl;
//	}
//
//    return 0;
//}

