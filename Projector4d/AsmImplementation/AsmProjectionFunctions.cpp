// ProjectionFunctionsDll.cpp : Defines the exported functions for the DLL application.
//

/*
*Author: Grzegorz Kazana
*Date: 28-11-2018
*Języki Asemblerowe 2018-2019
*/

#include "stdafx.h"
#include <stdlib.h>
#include "AsmProjectionFunctions.h"

extern "C" void projectOrtographicImplementation(unsigned int cols, unsigned int rows, double* arr, double *outarr, unsigned int goal_dim);
extern "C" void projectPerspectiveImplementation(unsigned int cols, unsigned int rows, double* arr, double *outarr, unsigned int goal_dim, double distance);
extern "C" void rotateImplementation(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle, unsigned int axis0, unsigned int axis1);
extern "C" void rotateWImplementation(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle);

void AsmImplementations::project2dOrtographic(unsigned int cols, unsigned int rows, double* arr, double *outarr) {
	return projectOrtographicImplementation(cols, rows, arr, outarr, 2);
}

void AsmImplementations::project3dOrtographic(unsigned int cols, unsigned int rows, double* arr, double *outarr) {
	return projectOrtographicImplementation(cols, rows, arr, outarr, 3);
}

void AsmImplementations::project2dPerspective(unsigned int cols, unsigned int rows, double* arr, double *outarr, double distance) {
	return projectPerspectiveImplementation(cols, rows, arr, outarr, 2, distance);
}

void AsmImplementations::project3dPerspective(unsigned int cols, unsigned int rows, double* arr, double *outarr, double distance) {
	projectPerspectiveImplementation(cols, rows, arr, outarr, 3, distance);
}

void AsmImplementations::rotate(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle) {
	return rotateImplementation(cols, rows, arr, outarr, angle, 0, 1);
}

void AsmImplementations::rotateX(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle) {
	return rotateImplementation(cols, rows, arr, outarr, angle, 1, 2);
}

void AsmImplementations::rotateY(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle) {
	return rotateImplementation(cols, rows, arr, outarr, angle, 0, 2);
}

void AsmImplementations::rotateZ(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle) {
	return rotateImplementation(cols, rows, arr, outarr, angle, 0, 1);
}

void AsmImplementations::rotateYZ(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle) {
	return rotateImplementation(cols, rows, arr, outarr, angle, 0, 3);
}

void AsmImplementations::rotateW(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle) {
	return rotateWImplementation(cols, rows, arr, outarr, angle);
}
