// CImplementation.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "CProjectionFunctions.h"

extern "C" void projectOrtographicImplementation(unsigned int cols, unsigned int rows, double* arr, double *outarr, unsigned int goal_dim);
extern "C" void projectPerspectiveImplementation(unsigned int cols, unsigned int rows, double* arr, double *outarr, unsigned int goal_dim, double distance);
extern "C" void rotateImplementation(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle, unsigned int axis0, unsigned int axis1);
extern "C" void rotateWImplementation(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle);

void CImplementations::project2dOrtographic(unsigned int cols, unsigned int rows, double* arr, double *outarr) {
	return projectOrtographicImplementation(cols, rows, arr, outarr, 2);
}

void CImplementations::project3dOrtographic(unsigned int cols, unsigned int rows, double* arr, double *outarr) {
	return projectOrtographicImplementation(cols, rows, arr, outarr, 3);
}

void CImplementations::project2dPerspective(unsigned int cols, unsigned int rows, double* arr, double *outarr, double distance) {
	return projectPerspectiveImplementation(cols, rows, arr, outarr, 2, distance);
}

void CImplementations::project3dPerspective(unsigned int cols, unsigned int rows, double* arr, double *outarr, double distance) {
	projectPerspectiveImplementation(cols, rows, arr, outarr, 3, distance);
}

void CImplementations::rotate(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle) {
	return rotateImplementation(cols, rows, arr, outarr, angle, 0, 1);
}

void CImplementations::rotateX(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle) {
	return rotateImplementation(cols, rows, arr, outarr, angle, 1, 2);
}

void CImplementations::rotateY(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle) {
	return rotateImplementation(cols, rows, arr, outarr, angle, 0, 2);
}

void CImplementations::rotateZ(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle) {
	return rotateImplementation(cols, rows, arr, outarr, angle, 0, 1);
}

void CImplementations::rotateYZ(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle) {
	return rotateImplementation(cols, rows, arr, outarr, angle, 0, 3);
}

void CImplementations::rotateW(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle) {
	return rotateWImplementation(cols, rows, arr, outarr, angle);
}