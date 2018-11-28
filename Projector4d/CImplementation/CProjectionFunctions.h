/*
*Author: Grzegorz Kazana
*Date: 28-11-2018
*Jêzyki Asemblerowe 2018-2019
*/
#pragma once

#define DLLIMPORT  __declspec(dllimport)
#define DLLEXPORT  __declspec(dllexport)

namespace CImplementations {
	void DLLEXPORT project2dOrtographic(unsigned int cols, unsigned int rows, double* arr, double *outarr);
	void DLLEXPORT project3dOrtographic(unsigned int cols, unsigned int rows, double* arr, double *outarr);
	void DLLEXPORT project2dPerspective(unsigned int cols, unsigned int rows, double* arr, double *outarr, double distance);
	void DLLEXPORT project3dPerspective(unsigned int cols, unsigned int rows, double* arr, double *outarr, double distance);
	void DLLEXPORT rotate(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle);
	void DLLEXPORT rotateX(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle);
	void DLLEXPORT rotateY(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle);
	void DLLEXPORT rotateZ(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle);
	void DLLEXPORT rotateYZ(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle);
	void DLLEXPORT rotateW(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle);
}