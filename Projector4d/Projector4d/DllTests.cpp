/*
*Author: Grzegorz Kazana
*Date: 28-11-2018
*Jêzyki Asemblerowe 2018-2019
*/
#include "stdafx.h"
#include "DllTests.h"
#include <iostream>

bool testAll()
{
	return testMatrixScaling() & testMatrixMultiplication() & testIdentity() & testOrtographicProjectionMatrix() & test2dOrtographicProjection() & test2dPerspectiveProjection();
}

bool testMatrixScaling()
{
	std::cout << "testing matrix scaling" << std::endl;
	// define matrix
	const unsigned int cols = 4;
	const unsigned int rows = 3;
	const unsigned int size = 12;
	double arr[size] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
	const double scaler = 3;
	// expected result
	double expected_res[size] = { 0, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33};
	// perform function
	AsmImplementations::scaleMatrix(cols, rows, arr, scaler);
	// test for correctness
	bool success = matrixEqual(size, expected_res, arr);
	if (success) {
		std::cout << "success" << std::endl;
	}
	else {
		std::cout << "failure" << std::endl;
	}
	return success;
}

bool testMatrixMultiplication()
{
	std::cout << "testing matrix multiplication" << std::endl;
	// define 1 matrix
	const unsigned int cols1 = 3;
	const unsigned int rows1 = 1;
	const unsigned int size1 = 3;
	double arr1[size1] = { 3,4,2 };
	// define 2 matrix
	const unsigned int cols2 = 4;
	const unsigned int rows2 = 3;
	const unsigned int size2 = 12;
	double arr2[size2] = { 13,9,7,15,8,7,4,6,6,4,0,3 };
	// expected result
	double expected_res[rows1*cols2] = { 83,63,37,75 };
	// result placeholder
	double result[rows1*cols2];
	AsmImplementations::multiplyMatrix(cols1, rows1, arr1, cols2, rows2, arr2, result);
	bool success = matrixEqual(rows1*cols2, expected_res, result);
	if (success) {
		std::cout << "success" << std::endl;
	}
	else {
		std::cout << "failure" << std::endl;
	}
	return success;
}

bool testIdentity()
{
	std::cout << "testing identity" << std::endl;
	// define matrix
	const unsigned int cols = 3;
	const unsigned int rows = 3;
	const unsigned int size = 9;
	double arr[size] = { 0,1,2,3,4,5,6,7,8 };
	// expected result
	double expected_res[size] = { 1,0,0,0,1,0,0,0,1 };
	// perform function
	AsmImplementations::fillIdentityMatrix(cols, rows, arr);
	// test for correctness
	bool success = matrixEqual(size, expected_res, arr);
	if (success) {
		std::cout << "success" << std::endl;
	}
	else {
		std::cout << "failure" << std::endl;
	}
	return success;
}

bool testOrtographicProjectionMatrix()
{
	std::cout << "testing ortographic projection matrix" << std::endl;
	// define matrix
	const unsigned int cols = 4;
	const unsigned int rows = 3;
	const unsigned int size = 12;
	double arr[size] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
	// expected result
	double expected_res[size] = { 1,0,0,0, 0,1,0,0, 0,0,1,0 };
	// perform function
	AsmImplementations::fillOrtographicProjectionMatrix(cols, rows, arr);
	// test for correctness
	bool success = matrixEqual(size, expected_res, arr);
	if (success) {
		std::cout << "success" << std::endl;
	}
	else {
		std::cout << "failure" << std::endl;
	}
	return success;
}

bool test2dOrtographicProjection()
{
	std::cout << "testing ortographic projection" << std::endl;
	// define matrix
	const unsigned int cols = 1;
	const unsigned int rows = 3;
	const unsigned int size = 3;
	double arr[size] = { 1,2,3 };
	const unsigned int goto_dim = 2;
	// expected result
	double expected_res[goto_dim] = { 1,2 };
	// result placeholder
	double result[goto_dim];
	// perform function
	AsmImplementations::project2dOrtographic(cols, rows, arr, result);
	// test for correctness
	bool success = matrixEqual(goto_dim, expected_res, result);
	if (success) {
		std::cout << "success" << std::endl;
	}
	else {
		std::cout << "failure" << std::endl;
	}
	return success;
}

bool test2dPerspectiveProjection()
{
	std::cout << "testing perspective projection" << std::endl;
	// define matrix
	const unsigned int cols = 1;
	const unsigned int rows = 3;
	const unsigned int size = 3;
	double arr[size] = { 1,2,3 };
	const unsigned int goto_dim = 2;
	const double dist = 2.0;
	// expected result
	double expected_res[goto_dim] = { 1,2 };
	// result placeholder
	double result[goto_dim];
	// perform function
	AsmImplementations::project2dPerspective(cols, rows, arr, result, dist);
	// test for correctness
	bool success = matrixEqual(goto_dim, expected_res, result);
	if (success) {
		std::cout << "success" << std::endl;
	}
	else {
		std::cout << "failure" << std::endl;
	}
	return success;
}

bool matrixEqual(unsigned int size, double* arr, double* arr1)
{
	bool ok = true;
	for (unsigned int i = 0; i < size; i++) {
		std::cout << arr[i] << "	" << arr1[i] << std::endl;
		if (abs(arr[i] - arr1[i]) > 0.00000001) {
			ok = false;
		}
	}
	return ok;
}
