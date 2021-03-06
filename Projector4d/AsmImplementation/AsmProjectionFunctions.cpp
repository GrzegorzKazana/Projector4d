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

extern "C" void fillOrtographicProjectionMatrix(unsigned int cols, unsigned int rows, double* arr);
extern "C" void multiplyMatrix(unsigned int cols1, unsigned int rows1, double* arr1, unsigned int cols2, unsigned int rows2, double* arr2, double* outarr);
extern "C" void scaleMatrix(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle);
extern "C" void fillRotationMatrix(unsigned int cols, unsigned int rows, double* arr, double angle, unsigned int axis1, unsigned int axis2);
extern "C" void fillDoubleRotationMatrix(unsigned int cols, unsigned int rows, double* arr, double angle);

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
	fillOrtographicProjectionMatrix(3, 2, projection2dOrtographicMatrix);
	fillOrtographicProjectionMatrix(4, 3, projection3dOrtographicMatrix);
	fillOrtographicProjectionMatrix(3, 2, projection2dPerspectiveMatrix);
	fillOrtographicProjectionMatrix(4, 3, projection3dPerspectiveMatrix);
}

void AsmImplementations::project2dOrtographic(unsigned int cols, unsigned int rows, double* arr, double *outarr) {
	multiplyMatrix(rows, 2, projection2dOrtographicMatrix, cols, rows, arr, outarr);
}

void AsmImplementations::project3dOrtographic(unsigned int cols, unsigned int rows, double* arr, double *outarr) {
	multiplyMatrix(rows, 3, projection3dOrtographicMatrix, cols, rows, arr, outarr);
}

void AsmImplementations::project2dPerspective(unsigned int cols, unsigned int rows, double* arr, double *outarr, double distance) {
	scaleMatrix(rows, 2, projection2dOrtographicMatrix, projection2dPerspectiveMatrix, 1.0 / (arr[2] - distance));
	multiplyMatrix(rows, 2, projection2dPerspectiveMatrix, cols, rows, arr, outarr);
}

void AsmImplementations::project3dPerspective(unsigned int cols, unsigned int rows, double* arr, double *outarr, double distance) {
	scaleMatrix(rows, 3, projection3dOrtographicMatrix, projection3dPerspectiveMatrix, 1.0 / (arr[3] - distance));
	multiplyMatrix(rows, 3, projection3dPerspectiveMatrix, cols, rows, arr, outarr);
}

void AsmImplementations::rotate(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle) {
	fillRotationMatrix(rows, rows, rotateMatrix, angle, 0, 1);
	multiplyMatrix(rows, rows, rotateMatrix, cols, rows, arr, outarr);
}

void AsmImplementations::rotateX(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle) {
	fillRotationMatrix(rows, rows, rotateXMatrix, angle, 1, 2);
	multiplyMatrix(rows, rows, rotateXMatrix, cols, rows, arr, outarr);
}

void AsmImplementations::rotateY(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle) {
	fillRotationMatrix(rows, rows, rotateYMatrix, angle, 0, 2);
	multiplyMatrix(rows, rows, rotateYMatrix, cols, rows, arr, outarr);
}

void AsmImplementations::rotateZ(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle) {
	fillRotationMatrix(rows, rows, rotateZMatrix, angle, 0, 1);
	multiplyMatrix(rows, rows, rotateZMatrix, cols, rows, arr, outarr);
}

void AsmImplementations::rotateW(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle) {
	fillDoubleRotationMatrix(rows, rows, rotateWMatrix, angle);
	multiplyMatrix(rows, rows, rotateWMatrix, cols, rows, arr, outarr);
}

AsmImplementations::~AsmImplementations(){
	delete [] projection2dOrtographicMatrix;
	delete [] projection3dOrtographicMatrix;
	delete [] projection2dPerspectiveMatrix;
	delete [] projection3dPerspectiveMatrix;
	delete [] rotateMatrix;
	delete [] rotateXMatrix;
	delete [] rotateYMatrix;
	delete [] rotateZMatrix;
	delete [] rotateWMatrix;
}
