/*
*Author: Grzegorz Kazana
*Date: 28-11-2018
*Języki Asemblerowe 2018-2019
*/

#include "stdafx.h"
#include "resource.h"
#include <windows.h>
#include <CommCtrl.h>
#include <string>
#include <SFML/Graphics.hpp>
#include "src/Canvas/Canvas.h"
#include "src/GraphicsEngines/AsmGraphicsEngine.h"
#include "src/GraphicsEngines/CGraphicsEngine.h"
#include "src/GraphicsEngines/LoggingGraphicsEngine.h"
#include "src/GraphicsEngines/GraphicsEngineTests.h"
#include <fstream>
# define M_PI 3.14159265358979323846

// sizes of gui elements
const int WIDTH = 800;
const int HEIGHT = 439;
const int CANVAS_WIDTH = 400;
const int CANVAS_HEIGHT = 400;
const int ROW_COUNT = 13;
const int COLUMN_COUNT = 3;
const int CONTROLS_PADDING = 0;
const int GRID_HEIGHT = (HEIGHT - 2*CONTROLS_PADDING) / ROW_COUNT;
const int GRID_WIDTH = (WIDTH - CANVAS_WIDTH - 2 * CONTROLS_PADDING) / COLUMN_COUNT;

// gui handles
// 1st row (Implementation x ASM, x C)
HWND H_IMPL_LABEL;
HWND H_IMPL_RADIO_BTN1;
HWND H_IMPL_RADIO_BTN2;
// 2nd row (Object: x Cube, x Tesseract)
HWND H_OBJ_TYPE_LABEL;
HWND H_OBJ_TYPE_RADIO_BTN1;
HWND H_OBJ_TYPE_RADIO_BTN2;
// 3rd row (Projection type: x Ortographic, x Perspective)
HWND H_PROJ_TYPE_LABEL;
HWND H_PROJ_TYPE_RADIO_BTN1;
HWND H_PROJ_TYPE_RADIO_BTN2;
// 4th row
HWND H_RESET_BUTTON;
// 5th row
/*
SPACER
*/
// 6th row (_ initial angle, angle speed)
HWND H_INIT_ANGLE_LABEL;
HWND H_ANGLE_SPEED_LABEL;
// 7th row (rotation slider, slider)
HWND H_ROT_LABEL;
HWND H_ROT_SLIDER1;
HWND H_ROT_SLIDER2;
// 8th row (rotation slider, slider)
HWND H_ROTX_LABEL;
HWND H_ROTX_SLIDER1;
HWND H_ROTX_SLIDER2;
// 9th row (rotation slider, slider)
HWND H_ROTY_LABEL;
HWND H_ROTY_SLIDER1;
HWND H_ROTY_SLIDER2;
// 10th row (rotation slider, slider)
HWND H_ROTZ_LABEL;
HWND H_ROTZ_SLIDER1;
HWND H_ROTZ_SLIDER2;
// 11th row (rotation slider, slider)
HWND H_ROTW_LABEL;
HWND H_ROTW_SLIDER1;
HWND H_ROTW_SLIDER2;
// 12th row (Distance slider)
HWND H_DISTANCE_LABEL;
HWND H_DISTANCE_SLIDER;

// settings
bool asm_impl = true;
bool cube_obj = true;
bool ort_proj = true;
bool show_fps = true;

// initial rotation offsets
double init_rot = 0;
double init_rotX = 0;
double init_rotY = 0;
double init_rotZ = 0;
double init_rotW = 0;

// rotation speeds
double rot_speed = 0;
double rotX_speed = 0;
double rotY_speed = 0;
double rotZ_speed = 0;
double rotW_speed = 0;

// rotation offsets
double rot_offset = 0;
double rotX_offset = 0;
double rotY_offset = 0;
double rotZ_offset = 0;
double rotW_offset = 0;

// perspective projection distance
double distance = 1.5;

// selected graphics engine
IGraphicsEngine* eng = new AsmGraphicsEngine;
//IGraphicsEngine* eng = new CGraphicsEngine;

LRESULT CALLBACK OnEvent(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	std::string sampletext = "Projector4d";
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
	H_IMPL_LABEL = CreateWindow(L"static", L" Implementation:", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTERIMAGE, CANVAS_WIDTH, 0 * GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)(501), hInstance, NULL);
	H_IMPL_RADIO_BTN1 = CreateWindow(L"button", L"ASM", WS_CHILD | WS_VISIBLE | WS_GROUP | BS_AUTORADIOBUTTON, CANVAS_WIDTH + GRID_WIDTH, 0 * GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)1011, hInstance, NULL);
	H_IMPL_RADIO_BTN2 = CreateWindow(L"button", L"C", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, CANVAS_WIDTH + 2 * GRID_WIDTH, 0 * GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)1012, hInstance, NULL);
	SendMessage(H_IMPL_RADIO_BTN1, BM_SETCHECK, BST_CHECKED, 0);
	// row 2
	H_OBJ_TYPE_LABEL = CreateWindow(L"static", L" Object type:", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTERIMAGE, CANVAS_WIDTH, 1*GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)(501), hInstance, NULL);
	H_OBJ_TYPE_RADIO_BTN1 = CreateWindow(L"button", L"Cube", WS_CHILD | WS_VISIBLE | WS_GROUP | BS_AUTORADIOBUTTON, CANVAS_WIDTH+GRID_WIDTH, 1 * GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)1021, hInstance, NULL);
	H_OBJ_TYPE_RADIO_BTN2 = CreateWindow(L"button", L"Tesseract", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, CANVAS_WIDTH + 2 * GRID_WIDTH, 1 * GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)1022, hInstance, NULL);
	SendMessage(H_OBJ_TYPE_RADIO_BTN1, BM_SETCHECK, BST_CHECKED, 0);
	// row 3
	H_PROJ_TYPE_LABEL = CreateWindow(L"static", L" Projection type", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTERIMAGE, CANVAS_WIDTH, 2*GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)(501), hInstance, NULL);
	H_PROJ_TYPE_RADIO_BTN1 = CreateWindow(L"button", L"Ortographic", WS_CHILD | WS_VISIBLE | WS_GROUP | BS_AUTORADIOBUTTON, CANVAS_WIDTH + GRID_WIDTH, 2*GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)1031, hInstance, NULL);
	H_PROJ_TYPE_RADIO_BTN2 = CreateWindow(L"button", L"Perspective", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, CANVAS_WIDTH + 2 * GRID_WIDTH, 2*GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)1032, hInstance, NULL);
	SendMessage(H_PROJ_TYPE_RADIO_BTN1, BM_SETCHECK, BST_CHECKED, 0);
	// row 4 (spacer)
	CreateWindow(L"static", L"", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTERIMAGE, CANVAS_WIDTH, 3 * GRID_HEIGHT, 2 * GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)(501), hInstance, NULL);
	H_RESET_BUTTON = CreateWindow(L"button", L"Start", WS_CHILD | WS_VISIBLE | WS_TABSTOP, CANVAS_WIDTH + 2*GRID_WIDTH, 3 * GRID_HEIGHT, (int)(0.9 * GRID_WIDTH), GRID_HEIGHT, hWnd, (HMENU)(1041), hInstance, NULL);
	// row 5 (spacer)
	CreateWindow(L"static", L"", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTERIMAGE, CANVAS_WIDTH, 4 * GRID_HEIGHT, 3 * GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)(501), hInstance, NULL);
	// row 6
	CreateWindow(L"static", L"", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTERIMAGE, CANVAS_WIDTH, 5 * GRID_HEIGHT, 1 * GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)(501), hInstance, NULL);
	CreateWindow(L"static", L"Initial angle", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTERIMAGE | SS_CENTER, CANVAS_WIDTH + GRID_WIDTH, 5 * GRID_HEIGHT, 1 * GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)(501), hInstance, NULL);
	CreateWindow(L"static", L"Angle speed", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTERIMAGE | SS_CENTER, CANVAS_WIDTH + 2*GRID_WIDTH, 5 * GRID_HEIGHT, 1 * GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)(501), hInstance, NULL);
	// row 7
	H_ROT_LABEL = CreateWindow(L"static", L" Rotation", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTERIMAGE, CANVAS_WIDTH, 6 * GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)(501), hInstance, NULL);
	H_ROT_SLIDER1 = CreateWindowEx(0, TRACKBAR_CLASS, L"trackbar control", WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS, CANVAS_WIDTH + GRID_WIDTH, 6 * GRID_HEIGHT, (int)(0.95 * GRID_WIDTH), GRID_HEIGHT, hWnd, (HMENU)1071, hInstance, NULL);
	H_ROT_SLIDER2 = CreateWindowEx(0, TRACKBAR_CLASS, L"trackbar control", WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS, CANVAS_WIDTH + (int)(1.95*GRID_WIDTH), 6 * GRID_HEIGHT, (int)(0.95 * GRID_WIDTH), GRID_HEIGHT, hWnd, (HMENU)1072, hInstance, NULL);
	SendMessage(H_ROT_SLIDER1, TBM_SETRANGE, (WPARAM)TRUE, (LPARAM)MAKELONG(0, 100));
	SendMessage(H_ROT_SLIDER2, TBM_SETRANGE, (WPARAM)TRUE, (LPARAM)MAKELONG(0, 10));
	SendMessage(H_ROT_SLIDER1, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)50);
	SendMessage(H_ROT_SLIDER2, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)5);
	// row 8
	H_ROTX_LABEL = CreateWindow(L"static", L" Rotation X", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTERIMAGE, CANVAS_WIDTH, 7 * GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)(501), hInstance, NULL);
	H_ROTX_SLIDER1 = CreateWindowEx(0, TRACKBAR_CLASS, L"trackbar control", WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS, CANVAS_WIDTH + GRID_WIDTH, 7 * GRID_HEIGHT, (int)(0.95 * GRID_WIDTH), GRID_HEIGHT, hWnd, (HMENU)1081, hInstance, NULL);
	H_ROTX_SLIDER2 = CreateWindowEx(0, TRACKBAR_CLASS, L"trackbar control", WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS, CANVAS_WIDTH + (int)(1.95*GRID_WIDTH), 7 * GRID_HEIGHT, (int)(0.95 * GRID_WIDTH), GRID_HEIGHT, hWnd, (HMENU)1082, hInstance, NULL);
	SendMessage(H_ROTX_SLIDER1, TBM_SETRANGE, (WPARAM)TRUE, (LPARAM)MAKELONG(0, 100));
	SendMessage(H_ROTX_SLIDER2, TBM_SETRANGE, (WPARAM)TRUE, (LPARAM)MAKELONG(0, 10));
	SendMessage(H_ROTX_SLIDER1, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)50);
	SendMessage(H_ROTX_SLIDER2, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)5);
	// row 9
	H_ROTY_LABEL = CreateWindow(L"static", L" Rotation Y", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTERIMAGE, CANVAS_WIDTH, 8 * GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)(501), hInstance, NULL);
	H_ROTY_SLIDER1 = CreateWindowEx(0, TRACKBAR_CLASS, L"trackbar control", WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS, CANVAS_WIDTH + GRID_WIDTH, 8 * GRID_HEIGHT, (int)(0.95 * GRID_WIDTH), GRID_HEIGHT, hWnd, (HMENU)1091, hInstance, NULL);
	H_ROTY_SLIDER2 = CreateWindowEx(0, TRACKBAR_CLASS, L"trackbar control", WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS, CANVAS_WIDTH + (int)(1.95*GRID_WIDTH), 8 * GRID_HEIGHT, (int) (0.95 * GRID_WIDTH), GRID_HEIGHT, hWnd, (HMENU)1092, hInstance, NULL);
	SendMessage(H_ROTY_SLIDER1, TBM_SETRANGE, (WPARAM)TRUE, (LPARAM)MAKELONG(0, 100));
	SendMessage(H_ROTY_SLIDER2, TBM_SETRANGE, (WPARAM)TRUE, (LPARAM)MAKELONG(0, 10));
	SendMessage(H_ROTY_SLIDER1, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)50);
	SendMessage(H_ROTY_SLIDER2, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)5);
	// row 10
	H_ROTZ_LABEL = CreateWindow(L"static", L" Rotation Z", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTERIMAGE, CANVAS_WIDTH, 9 * GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)(501), hInstance, NULL);
	H_ROTZ_SLIDER1 = CreateWindowEx(0, TRACKBAR_CLASS, L"trackbar control", WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS, CANVAS_WIDTH + GRID_WIDTH, 9 * GRID_HEIGHT, (int)(0.95 * GRID_WIDTH), GRID_HEIGHT, hWnd, (HMENU)1101, hInstance, NULL);
	H_ROTZ_SLIDER2 = CreateWindowEx(0, TRACKBAR_CLASS, L"trackbar control", WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS, CANVAS_WIDTH + (int)(1.95*GRID_WIDTH), 9 * GRID_HEIGHT, (int)(0.95 * GRID_WIDTH), GRID_HEIGHT, hWnd, (HMENU)1102, hInstance, NULL);
	SendMessage(H_ROTZ_SLIDER1, TBM_SETRANGE, (WPARAM)TRUE, (LPARAM)MAKELONG(0, 100));
	SendMessage(H_ROTZ_SLIDER2, TBM_SETRANGE, (WPARAM)TRUE, (LPARAM)MAKELONG(0, 10));
	SendMessage(H_ROTZ_SLIDER1, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)50);
	SendMessage(H_ROTZ_SLIDER2, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)5);
	// row 11
	H_ROTW_LABEL = CreateWindow(L"static", L" Rotation W", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTERIMAGE, CANVAS_WIDTH, 10 * GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)(501), hInstance, NULL);
	H_ROTW_SLIDER1 = CreateWindowEx(0, TRACKBAR_CLASS, L"trackbar control", WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS, CANVAS_WIDTH + GRID_WIDTH, 10 * GRID_HEIGHT, (int)(0.95 * GRID_WIDTH), GRID_HEIGHT, hWnd, (HMENU)1111, hInstance, NULL);
	H_ROTW_SLIDER2 = CreateWindowEx(0, TRACKBAR_CLASS, L"trackbar control", WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS, CANVAS_WIDTH + (int)(1.95*GRID_WIDTH), 10 * GRID_HEIGHT, (int)(0.95 * GRID_WIDTH), GRID_HEIGHT, hWnd, (HMENU)1112, hInstance, NULL);
	SendMessage(H_ROTW_SLIDER1, TBM_SETRANGE, (WPARAM)TRUE, (LPARAM)MAKELONG(0, 100));
	SendMessage(H_ROTW_SLIDER2, TBM_SETRANGE, (WPARAM)TRUE, (LPARAM)MAKELONG(0, 10));
	SendMessage(H_ROTW_SLIDER1, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)50);
	SendMessage(H_ROTW_SLIDER2, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)5);
	// row 12
	H_DISTANCE_LABEL = CreateWindow(L"static", L" Distance", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTERIMAGE, CANVAS_WIDTH, 11 * GRID_HEIGHT, GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)(501), hInstance, NULL);
	H_DISTANCE_SLIDER = CreateWindowEx(0, TRACKBAR_CLASS,L"trackbar control", WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS, CANVAS_WIDTH + GRID_WIDTH, 11 * GRID_HEIGHT, (int)(1.9 * GRID_WIDTH), GRID_HEIGHT, hWnd, (HMENU)1121, hInstance, NULL);
	SendMessage(H_DISTANCE_SLIDER, TBM_SETRANGE, (WPARAM)TRUE, (LPARAM)MAKELONG(0, 100));
	SendMessage(H_DISTANCE_SLIDER, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)5);
	// spacer, hides inactive line under controls
	CreateWindow(L"static", L"", WS_CHILD | WS_VISIBLE | WS_TABSTOP | SS_CENTERIMAGE, CANVAS_WIDTH, 12 * GRID_HEIGHT, 3 * GRID_WIDTH, GRID_HEIGHT, hWnd, (HMENU)(501), hInstance, NULL);


	// define sfml placeholder
	HWND hView = CreateWindow(L"STATIC", NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, 0, 0, CANVAS_WIDTH, CANVAS_HEIGHT, hWnd, NULL, hInstance, NULL);

	// init sfml canvas
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	Canvas hCanvas(hView, settings);

	// define canvas content objets
	Mesh4d tesseract;
	Mesh3d cube;

	// fps measurement
	sf::Clock clock;
	float lastTime = 0;

	if (!GraphicsEngineTests::testAll(eng)) {
		MessageBox(hWnd, L"Tests falied", L"Tests falied", MB_OKCANCEL);
	}	
	//delete eng;

	//eng = new AsmGraphicsEngine;
	//std::ofstream fpsFile("asm_fps.txt");

	//eng = new CGraphicsEngine;
	//std::ofstream fpsFile("c_fps.txt");

	//eng = new LoggingGraphicsEngine(eng, "asm_ticks.txt");

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
			hCanvas.clear(sf::Color::Black);

			// SFML animation goes here
			if (cube_obj) {
				auto rotated3d = eng->rotateZ(eng->rotateY(eng->rotateX(cube, init_rotX + rotX_offset), init_rotY + rotY_offset), init_rotZ + rotZ_offset);
				auto projected2d = ort_proj ? eng->project2dOrtographic(rotated3d) : eng->project2dPerspective(rotated3d, distance);
				auto rotated2d = eng->rotate(projected2d, init_rot + rot_offset);
				hCanvas.draw2dMesh(rotated2d);
			}
			else {
				auto rotated4d = eng->rotateW(tesseract, init_rotW + rotW_offset);
				auto projected3d = ort_proj ? eng->project3dOrtographic(rotated4d) : eng->project3dPerspective(rotated4d, distance);
				auto rotated3d = eng->rotateZ(eng->rotateY(eng->rotateX(projected3d, init_rotX + rotX_offset), init_rotY + rotY_offset), init_rotZ + rotZ_offset);
				auto projected2d = ort_proj ? eng->project2dOrtographic(rotated3d) : eng->project2dPerspective(rotated3d, distance);
				auto rotated2d = eng->rotate(projected2d, init_rot + rot_offset);
				hCanvas.draw2dMesh(rotated2d);
			}
			
			// rotation animation
			rot_offset += rot_speed;
			rotX_offset += rotX_speed;
			rotY_offset += rotY_speed;
			rotZ_offset += rotZ_speed;
			rotW_offset += rotW_speed;

			// measure fps
			if (show_fps) {
				float currentTime = clock.restart().asSeconds();
				float fps = 1.f / currentTime;
				lastTime = currentTime;
				hCanvas.drawFps(fps);
				//fpsFile << fps << "\n";
			}

			// Display each view on screen
			hCanvas.display();
		}
	}
	//fpsFile.close();
	return Message.wParam;
}

// event handling
LRESULT CALLBACK OnEvent(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	int num = -1;
	switch (msg) {
	case WM_CLOSE:
		delete eng;
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		if ((HWND)lParam == H_RESET_BUTTON) {
			// reset slider positions
			SendMessage(H_ROT_SLIDER1, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)50);
			SendMessage(H_ROT_SLIDER2, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)5);
			SendMessage(H_ROTX_SLIDER1, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)50);
			SendMessage(H_ROTX_SLIDER2, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)5);
			SendMessage(H_ROTY_SLIDER1, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)50);
			SendMessage(H_ROTY_SLIDER2, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)5);
			SendMessage(H_ROTZ_SLIDER1, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)50);
			SendMessage(H_ROTZ_SLIDER2, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)5);
			SendMessage(H_ROTW_SLIDER1, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)50);
			SendMessage(H_ROTW_SLIDER2, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)5);
			SendMessage(H_DISTANCE_SLIDER, TBM_SETRANGE, (WPARAM)TRUE, (LPARAM)MAKELONG(0, 100));
			SendMessage(H_DISTANCE_SLIDER, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)5);
			// reset offsets, speed rotations
			rot_offset  = 0;
			rotX_offset = 0;
			rotY_offset = 0;
			rotZ_offset = 0;
			rotW_offset = 0;
			rot_speed = 0;
			rotX_speed = 0;
			rotY_speed = 0;
			rotZ_speed = 0;
			rotW_speed = 0;
			init_rot = 0;
			init_rotX = 0;
			init_rotY = 0;
			init_rotZ = 0;
			init_rotW = 0;
			distance = 1.5;
			// get values of radio buttons
			asm_impl = IsDlgButtonChecked(hwnd, 1011) == BST_CHECKED && IsDlgButtonChecked(hwnd, 1012) == BST_UNCHECKED;
			cube_obj = IsDlgButtonChecked(hwnd, 1021) == BST_CHECKED && IsDlgButtonChecked(hwnd, 1022) == BST_UNCHECKED;
			ort_proj = IsDlgButtonChecked(hwnd, 1031) == BST_CHECKED && IsDlgButtonChecked(hwnd, 1032) == BST_UNCHECKED;
			delete eng;
			if (asm_impl) {
				eng = new AsmGraphicsEngine;
			}
			else {
				eng = new CGraphicsEngine;
			}
		}
		break;
	case WM_HSCROLL:
		// slider actions
		if ((HWND)lParam == H_ROT_SLIDER1) {
			num = SendMessage(H_ROT_SLIDER1, TBM_GETPOS, 0, 0);
			// scaled between <-PI, PI>
			init_rot = (((2.0 * num) / 100.0) - 1.0) * M_PI;
		}
		else if ((HWND)lParam == H_ROT_SLIDER2) {
			num = SendMessage(H_ROT_SLIDER2, TBM_GETPOS, 0, 0);
			// scaled between <-0.01,0.01>
			rot_speed = (((2.0 * num) / 10.0) - 1.0) * 0.01;
		}
		else if ((HWND)lParam == H_ROTX_SLIDER1) {
			num = SendMessage(H_ROTX_SLIDER1, TBM_GETPOS, 0, 0);
			// scaled between <-PI, PI>
			init_rotX = (((2.0 * num) / 100.0) - 1.0) * M_PI;
		}
		else if ((HWND)lParam == H_ROTX_SLIDER2) {
			num = SendMessage(H_ROTX_SLIDER2, TBM_GETPOS, 0, 0);
			// scaled between <-0.01,0.01>
			rotX_speed = (((2.0 * num) / 10.0) - 1.0) * 0.01;
		}
		else if ((HWND)lParam == H_ROTY_SLIDER1) {
			num = SendMessage(H_ROTY_SLIDER1, TBM_GETPOS, 0, 0);
			// scaled between <-PI, PI>
			init_rotY = (((2.0 * num) / 100.0) - 1.0) * M_PI;
		}
		else if ((HWND)lParam == H_ROTY_SLIDER2) {
			num = SendMessage(H_ROTY_SLIDER2, TBM_GETPOS, 0, 0);
			// scaled between <-0.01,0.01>
			rotY_speed = (((2.0 * num) / 10.0) - 1.0) * 0.01;
		}
		else if ((HWND)lParam == H_ROTZ_SLIDER1) {
			num = SendMessage(H_ROTZ_SLIDER1, TBM_GETPOS, 0, 0);
			// scaled between <-PI, PI>
			init_rotZ = (((2.0 * num) / 100.0) - 1.0) * M_PI;
		}
		else if ((HWND)lParam == H_ROTZ_SLIDER2) {
			num = SendMessage(H_ROTZ_SLIDER2, TBM_GETPOS, 0, 0);
			// scaled between <-0.01,0.01>
			rotZ_speed = (((2.0 * num) / 10.0) - 1.0) * 0.01;
		}
		else if ((HWND)lParam == H_ROTW_SLIDER1) {
			num = SendMessage(H_ROTW_SLIDER1, TBM_GETPOS, 0, 0);
			// scaled between <-PI, PI>
			init_rotW = (((2.0 * num) / 100.0) - 1.0) * M_PI;
		}
		else if ((HWND)lParam == H_ROTW_SLIDER2) {
			num = SendMessage(H_ROTW_SLIDER2, TBM_GETPOS, 0, 0);
			// scaled between <-0.01,0.01>
			rotW_speed = (((2.0 * num) / 10.0) - 1.0) * 0.01;
		}
		else if ((HWND)lParam == H_DISTANCE_SLIDER) {
			num = SendMessage(H_DISTANCE_SLIDER, TBM_GETPOS, 0, 0);
			// scaled between <1.3, 5.3>
			distance = ((num) / 100.0) * 4.0 + 1.3;
		}
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}
