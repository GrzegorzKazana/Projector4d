#include "stdafx.h"
#include "resource.h"
#include "windows.h"
#include <string>
#include <SFML/Graphics.hpp>
#include "Canvas.h"
#include "AsmGraphicsEngine.h"

const int WIDTH = 800;
const int HEIGHT = 400;
const int CANVAS_WIDTH = 400;
const int CANVAS_HEIGHT = 400;
const int ROW_COUNT = 12;
const int COLUMN_COUNT = 3;

const int GRID_HEIGHT = HEIGHT / ROW_COUNT;
const int GRID_WIDTH = (WIDTH - CANVAS_WIDTH) / COLUMN_COUNT;

// first row (Object: x Cube, x Tesseract)
HWND H_OBJ_TYPE_LABEL;
HWND H_OBJ_TYPE_RADIO_BTN1;
HWND H_OBJ_TYPE_RADIO_BTN2;
// second row (Projection type: x Ortographic, x Perspective)
HWND H_PROJ_TYPE_LABEL;
HWND H_PROJ_TYPE_RADIO_BTN1;
HWND H_PROJ_TYPE_RADIO_BTN2;
// 3rd row (Distance slider)
HWND H_DISTANCE_LABEL;
HWND H_DISTANCE_SLIDER;
// 4th row
/*
SPACER
*/
// 5th row (_ initial angle, angle speed)
HWND H_INIT_ANGLE_LABEL;
HWND H_ANGLE_SPEED_LABEL;
// 6th row (rotation slider, slider)
HWND H_ROT_LABEL;
HWND H_ROT_SLIDER1;
HWND H_ROT_SLIDER2;
// 7th row (rotation slider, slider)
HWND H_ROTX_LABEL;
HWND H_ROTX_SLIDER1;
HWND H_ROTX_SLIDER2;
// 8th row (rotation slider, slider)
HWND H_ROTY_LABEL;
HWND H_ROTY_SLIDER1;
HWND H_ROTY_SLIDER2;
// 9th row (rotation slider, slider)
HWND H_ROTZ_LABEL;
HWND H_ROTZ_SLIDER1;
HWND H_ROTZ_SLIDER2;
// 10th row (rotation slider, slider)
HWND H_ROTW_LABEL;
HWND H_ROTW_SLIDER1;
HWND H_ROTW_SLIDER2;
// 11th row
/*
SPACER
*/
// 12th row (Implementation x ASM, x C)
HWND H_IMPL_LABEL;
HWND H_IMPL_RADIO_BTN1;
HWND H_IMPL_RADIO_BTN2;


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


	// define main window
	HWND hWnd = CreateWindow(wsampletext.c_str(), wsampletext.c_str(), WS_SYSMENU | WS_VISIBLE, 0, 0, WIDTH, HEIGHT, NULL, NULL, hInstance, NULL);
	// row 1
	H_OBJ_TYPE_LABEL = CreateWindow(L"static", L"Object type:", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTERIMAGE, CANVAS_WIDTH, 0, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)(501), hInstance, NULL);
	H_OBJ_TYPE_RADIO_BTN1 = CreateWindow(L"button", L"Cube", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, CANVAS_WIDTH+GRID_WIDTH, 0, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)1001, hInstance, NULL);
	H_OBJ_TYPE_RADIO_BTN2 = CreateWindow(L"button", L"Tesseract", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, CANVAS_WIDTH + 2 * GRID_WIDTH, 0, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)1001, hInstance, NULL);
	// row 2
	H_PROJ_TYPE_LABEL = CreateWindow(L"static", L"Projection type", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTERIMAGE, CANVAS_WIDTH, GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)(501), hInstance, NULL);
	H_PROJ_TYPE_RADIO_BTN1 = CreateWindow(L"button", L"Ortographic", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, CANVAS_WIDTH + GRID_WIDTH, GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)1001, hInstance, NULL);
	H_PROJ_TYPE_RADIO_BTN2 = CreateWindow(L"button", L"Perspective", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, CANVAS_WIDTH + 2 * GRID_WIDTH, GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)1001, hInstance, NULL);
	// row 3
	H_DISTANCE_LABEL = CreateWindow(L"static", L"Distance", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTERIMAGE, CANVAS_WIDTH, 2* GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)(501), hInstance, NULL);
	H_DISTANCE_SLIDER = CreateWindow(L"msctls_trackbar32", L"", WS_CHILD | WS_VISIBLE, CANVAS_WIDTH + GRID_WIDTH, 2 * GRID_HEIGHT, 2 * GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)1001, hInstance, NULL);
	// row 4 (spacer)
	H_DISTANCE_LABEL = CreateWindow(L"static", L"", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTERIMAGE, CANVAS_WIDTH, 3 * GRID_HEIGHT, 3*GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)(501), hInstance, NULL);
	// row 5
	H_ROT_LABEL = CreateWindow(L"static", L"Rotation", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTERIMAGE, CANVAS_WIDTH, 4 * GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)(501), hInstance, NULL);
	H_ROT_SLIDER1 = CreateWindow(L"msctls_trackbar32", L"", WS_CHILD | WS_VISIBLE, CANVAS_WIDTH + GRID_WIDTH, 4 * GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)1001, hInstance, NULL);
	H_ROT_SLIDER2 = CreateWindow(L"msctls_trackbar32", L"", WS_CHILD | WS_VISIBLE, CANVAS_WIDTH + 2*GRID_WIDTH, 4 * GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)1001, hInstance, NULL);
	// row 6
	H_ROTX_LABEL = CreateWindow(L"static", L"Rotation X", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTERIMAGE, CANVAS_WIDTH, 5 * GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)(501), hInstance, NULL);
	H_ROTX_SLIDER1 = CreateWindow(L"msctls_trackbar32", L"", WS_CHILD | WS_VISIBLE, CANVAS_WIDTH + GRID_WIDTH, 5 * GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)1001, hInstance, NULL);
	H_ROTX_SLIDER2 = CreateWindow(L"msctls_trackbar32", L"", WS_CHILD | WS_VISIBLE, CANVAS_WIDTH + 2*GRID_WIDTH, 5 * GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)1001, hInstance, NULL);
	// row 7
	H_ROTY_LABEL = CreateWindow(L"static", L"Rotation Y", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTERIMAGE, CANVAS_WIDTH, 6 * GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)(501), hInstance, NULL);
	H_ROTY_SLIDER1 = CreateWindow(L"msctls_trackbar32", L"", WS_CHILD | WS_VISIBLE, CANVAS_WIDTH + GRID_WIDTH, 6 * GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)1001, hInstance, NULL);
	H_ROTY_SLIDER2 = CreateWindow(L"msctls_trackbar32", L"", WS_CHILD | WS_VISIBLE, CANVAS_WIDTH + 2*GRID_WIDTH, 6 * GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)1001, hInstance, NULL);
	// row 8
	H_ROTZ_LABEL = CreateWindow(L"static", L"Rotation Z", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTERIMAGE, CANVAS_WIDTH, 7 * GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)(501), hInstance, NULL);
	H_ROTZ_SLIDER1 = CreateWindow(L"msctls_trackbar32", L"", WS_CHILD | WS_VISIBLE, CANVAS_WIDTH + GRID_WIDTH, 7 * GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)1001, hInstance, NULL);
	H_ROTZ_SLIDER2 = CreateWindow(L"msctls_trackbar32", L"", WS_CHILD | WS_VISIBLE, CANVAS_WIDTH + 2*GRID_WIDTH, 7 * GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)1001, hInstance, NULL);
	// row 9
	H_ROTW_LABEL = CreateWindow(L"static", L"Rotation W", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTERIMAGE, CANVAS_WIDTH, 8 * GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)(501), hInstance, NULL);
	H_ROTW_SLIDER1 = CreateWindow(L"msctls_trackbar32", L"", WS_CHILD | WS_VISIBLE, CANVAS_WIDTH + GRID_WIDTH, 8 * GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)1001, hInstance, NULL);
	H_ROTW_SLIDER2 = CreateWindow(L"msctls_trackbar32", L"", WS_CHILD | WS_VISIBLE, CANVAS_WIDTH + 2*GRID_WIDTH, 8 * GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)1001, hInstance, NULL);
	// row 10 (spacer)
	H_DISTANCE_LABEL = CreateWindow(L"static", L"", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTERIMAGE, CANVAS_WIDTH, 9 * GRID_HEIGHT, 3 * GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)(501), hInstance, NULL);
	// row 11
	H_IMPL_LABEL = CreateWindow(L"static", L"Implementation:", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTERIMAGE, CANVAS_WIDTH, 10 * GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)(501), hInstance, NULL);
	H_IMPL_RADIO_BTN1 = CreateWindow(L"button", L"ASM", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, CANVAS_WIDTH + GRID_WIDTH, 10 * GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)1001, hInstance, NULL);
	H_IMPL_RADIO_BTN2 = CreateWindow(L"button", L"C", WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, CANVAS_WIDTH + 2 * GRID_WIDTH, 10 * GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)1001, hInstance, NULL);





	// define sfml placeholder
	HWND View1 = CreateWindow(L"STATIC", NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, 0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, hWnd, NULL, hInstance, NULL);

	// init sfml canvas
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	Canvas SFMLView1(View1, settings);

	// define canvas content objets
	Mesh4d t;
	AsmGraphicsEngine eng;
	double angle_offset = 0;

	// display main window
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	// message loop
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

			// SFML animation goes here
			auto rotated4d = eng.rotateW(t, -angle_offset);
			auto projected3d = eng.project3dPerspective(rotated4d, 1.5);
			auto rotated3d = eng.rotateZ(eng.rotateX(eng.rotateY(projected3d, 1.0), 0.0), 0.0);
			auto projected2d = eng.project2dPerspective(rotated3d, 1.5);
			
			SFMLView1.draw2dMesh(projected2d);
			
			angle_offset += 0.001;


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
		//if ((HWND)lParam == hButton1) {
		//	MessageBox(hwnd, (LPWSTR)L"Button 1", (LPWSTR)L"Ha!", MB_OK);
		//}
		//else if ((HWND)lParam == hButton2) {
		//	MessageBox(hwnd, (LPWSTR)L"Button 2", (LPWSTR)L"Ha!", MB_OK);
		//}
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

