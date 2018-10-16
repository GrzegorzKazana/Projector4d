// ProjectionFunctionsDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <stdlib.h>
#include "ProjectionFunctionsDll.h"

extern "C" int Dej5Asm();
extern "C" void scaleMatrixImplementation(unsigned int cols, unsigned int rows, double* arr, double scale);
extern "C" void multiplyMatrixImplementation(unsigned int cols1, unsigned int rows1, double* arr1, unsigned int cols2, unsigned int rows2, double* arr2, double* outarr);
extern "C" void fillIdentityMatrixImplementation(unsigned int cols, unsigned int rows, double* arr);
extern "C" void fillOrtographicProjectionMatrixImplementation(unsigned int cols, unsigned int rows, double* arr);
extern "C" void projectOrtographicImplementation(unsigned int cols, unsigned int rows, double* arr, double *outarr, unsigned int goal_dim);
extern "C" void projectPerspectiveImplementation(unsigned int cols, unsigned int rows, double* arr, double *outarr, unsigned int goal_dim, double distance);
extern "C" int testIMP(int xd);
extern "C" void rotateImplementation(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle, unsigned int axis0, unsigned int axis1);

int AsmImplementations::dej5()
{
	return Dej5Asm();
}

void AsmImplementations::scaleMatrix(unsigned int cols, unsigned int rows, double* arr, double scale) {
	return scaleMatrixImplementation(cols, rows, arr, scale);
}

void AsmImplementations::multiplyMatrix(unsigned int cols1, unsigned int rows1, double* arr1, unsigned int cols2, unsigned int rows2, double* arr2, double* outarr) {
	return multiplyMatrixImplementation(cols1, rows1, arr1, cols2, rows2, arr2, outarr);
}

void AsmImplementations::fillIdentityMatrix(unsigned int cols, unsigned int rows, double* arr) {
	return fillIdentityMatrixImplementation(cols, rows, arr);
}

void AsmImplementations::fillOrtographicProjectionMatrix(unsigned int cols, unsigned int rows, double* arr) {
	return fillOrtographicProjectionMatrixImplementation(cols, rows, arr);
}

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

int AsmImplementations::test(int xd) {
	return testIMP(xd);
}
