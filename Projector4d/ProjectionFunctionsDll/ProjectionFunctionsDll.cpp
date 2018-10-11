// ProjectionFunctionsDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "ProjectionFunctionsDll.h"

extern "C" int Dej5Asm();
extern "C" void scaleMatrixImplementation(unsigned int cols, unsigned int rows, double* arr, double scale);
extern "C" void multiplyMatrixImplementation(unsigned int cols1, unsigned int rows1, double* arr1, unsigned int cols2, unsigned int rows2, double* arr2, double* outarr);
extern "C" void fillIdentityMatrixImplementation(unsigned int cols, unsigned int rows, double* arr);
extern "C" int testIMP(int* xd);

int dej5()
{
	return Dej5Asm();
}

void scaleMatrix(unsigned int cols, unsigned int rows, double* arr, double scale) {
	return scaleMatrixImplementation(cols, rows, arr, scale);
}

void multiplyMatrix(unsigned int cols1, unsigned int rows1, double* arr1, unsigned int cols2, unsigned int rows2, double* arr2, double* outarr) {
	return multiplyMatrixImplementation(cols1, rows1, arr1, cols2, rows2, arr2, outarr);
}

void fillIdentityMatrix(unsigned int cols, unsigned int rows, double* arr) {
	return fillIdentityMatrixImplementation(cols, rows, arr);
}

int test(int* xd) {
	return testIMP(xd);
}