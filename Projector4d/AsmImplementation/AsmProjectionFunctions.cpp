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

extern "C" void projectOrtographicImplementation(unsigned int cols, unsigned int rows, double* arr, double *outarr, unsigned int goal_dim, double* matrix_placeholder);
extern "C" void projectPerspectiveImplementation(unsigned int cols, unsigned int rows, double* arr, double *outarr, unsigned int goal_dim, double distance, double* matrix_placeholder);
extern "C" void rotateImplementation(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle, unsigned int axis0, unsigned int axis1, double* matrix_placeholder);
extern "C" void rotateWImplementation(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle, double* matrix_placeholder);

AsmImplementations::AsmImplementations(){
	projection2dOrtographicMatrix = new double[6];
	projection3dOrtographicMatrix = new double[12];
	projection2dPerspectiveMatrix = new double[6];
	projection3dPerspectiveMatrix = new double[12];
	rotateMatrix = new double[4];
	rotateXMatrix = new double[9];
	rotateYMatrix = new double[9];
	rotateZMatrix = new double[9];
	rotateWMatrix = new double[16];
}

void AsmImplementations::project2dOrtographic(unsigned int cols, unsigned int rows, double* arr, double *outarr) {
	return projectOrtographicImplementation(cols, rows, arr, outarr, 2, projection2dOrtographicMatrix);
}

void AsmImplementations::project3dOrtographic(unsigned int cols, unsigned int rows, double* arr, double *outarr) {
	return projectOrtographicImplementation(cols, rows, arr, outarr, 3, projection3dOrtographicMatrix);
}

void AsmImplementations::project2dPerspective(unsigned int cols, unsigned int rows, double* arr, double *outarr, double distance) {
	return projectPerspectiveImplementation(cols, rows, arr, outarr, 2, distance, projection2dPerspectiveMatrix);
}

void AsmImplementations::project3dPerspective(unsigned int cols, unsigned int rows, double* arr, double *outarr, double distance) {
	projectPerspectiveImplementation(cols, rows, arr, outarr, 3, distance, projection3dPerspectiveMatrix);
}

void AsmImplementations::rotate(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle) {
	return rotateImplementation(cols, rows, arr, outarr, angle, 0, 1, rotateMatrix);
}

void AsmImplementations::rotateX(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle) {
	return rotateImplementation(cols, rows, arr, outarr, angle, 1, 2, rotateXMatrix);
}

void AsmImplementations::rotateY(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle) {
	return rotateImplementation(cols, rows, arr, outarr, angle, 0, 2, rotateYMatrix);
}

void AsmImplementations::rotateZ(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle) {
	return rotateImplementation(cols, rows, arr, outarr, angle, 0, 1, rotateZMatrix);
}

void AsmImplementations::rotateW(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle) {
	return rotateWImplementation(cols, rows, arr, outarr, angle, rotateWMatrix);
}

AsmImplementations::~AsmImplementations(){
	delete projection2dOrtographicMatrix;
	delete projection3dOrtographicMatrix;
	delete projection2dPerspectiveMatrix;
	delete projection3dPerspectiveMatrix;
	delete rotateMatrix;
	delete rotateXMatrix;
	delete rotateYMatrix;
	delete rotateZMatrix;
	delete rotateWMatrix;
}
