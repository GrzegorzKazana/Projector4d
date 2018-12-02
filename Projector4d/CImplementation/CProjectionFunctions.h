/*
*Author: Grzegorz Kazana
*Date: 28-11-2018
*J�zyki Asemblerowe 2018-2019
*/
#pragma once

#define DLLIMPORT  __declspec(dllimport)
#define DLLEXPORT  __declspec(dllexport)

class DLLEXPORT CImplementations {
	double* projection2dOrtographicMatrix;
	double* projection3dOrtographicMatrix;
	double* projection2dPerspectiveMatrix;
	double* projection3dPerspectiveMatrix;
	double* rotateMatrix;
	double* rotateXMatrix;
	double* rotateYMatrix;
	double* rotateZMatrix;
	double* rotateWMatrix;
public:
	CImplementations();
	void project2dOrtographic(unsigned int cols, unsigned int rows, double* arr, double *outarr);
	void project3dOrtographic(unsigned int cols, unsigned int rows, double* arr, double *outarr);
	void project2dPerspective(unsigned int cols, unsigned int rows, double* arr, double *outarr, double distance);
	void project3dPerspective(unsigned int cols, unsigned int rows, double* arr, double *outarr, double distance);
	void rotate(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle);
	void rotateX(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle);
	void rotateY(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle);
	void rotateZ(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle);
	void rotateW(unsigned int cols, unsigned int rows, double* arr, double* outarr, double angle);
	~CImplementations();
};