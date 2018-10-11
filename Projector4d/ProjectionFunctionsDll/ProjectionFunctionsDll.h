#pragma once

#define DLLIMPORT  __declspec(dllimport)
#define DLLEXPORT  __declspec(dllexport)

extern "C" int DLLEXPORT dej5();
extern "C" void DLLEXPORT scaleMatrix(unsigned int cols, unsigned int rows, double* arr, double scale);
extern "C" void DLLEXPORT multiplyMatrix(unsigned int cols1, unsigned int rows1, double* arr1, unsigned int cols2, unsigned int rows2, double* arr2, double* outarr);
extern "C" void DLLEXPORT fillIdentityMatrix(unsigned int cols, unsigned int rows, double* arr);
extern "C" int DLLEXPORT test(int* xd);