#pragma once

#define DLLIMPORT  __declspec(dllimport)
#define DLLEXPORT  __declspec(dllexport)

namespace AsmImplementations {
	int DLLEXPORT dej5();
	void DLLEXPORT scaleMatrix(unsigned int cols, unsigned int rows, double* arr, double scale);
	void DLLEXPORT multiplyMatrix(unsigned int cols1, unsigned int rows1, double* arr1, unsigned int cols2, unsigned int rows2, double* arr2, double* outarr);
	void DLLEXPORT fillIdentityMatrix(unsigned int cols, unsigned int rows, double* arr);
	void DLLEXPORT fillOrtographicProjectionMatrix(unsigned int cols, unsigned int rows, double* arr);
	void DLLEXPORT project2dOrtographic(unsigned int cols, unsigned int rows, double* arr, double *outarr);
	void DLLEXPORT project3dOrtographic(unsigned int cols, unsigned int rows, double* arr, double *outarr);
	void DLLEXPORT project2dPerspective(unsigned int cols, unsigned int rows, double* arr, double *outarr, double distance);
	void DLLEXPORT project3dPerspective(unsigned int cols, unsigned int rows, double* arr, double *outarr, double distance);
	void DLLEXPORT rotate(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle);
	void DLLEXPORT rotateX(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle);
	void DLLEXPORT rotateY(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle);
	void DLLEXPORT rotateZ(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle);
	void DLLEXPORT rotateYZ(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle);
	int DLLEXPORT test(int xd);
}