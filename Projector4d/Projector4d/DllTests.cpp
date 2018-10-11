#include "stdafx.h"
#include "DllTests.h"
#include <iostream>

bool testAll()
{
	return testMatrixScaling() & testMatrixMultiplication() & testIdentity();
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
	scaleMatrix(cols, rows, arr, scaler);
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
	multiplyMatrix(cols1, rows1, arr1, cols2, rows2, arr2, result);
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
	fillIdentityMatrix(cols, rows, arr);
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

bool matrixEqual(unsigned int size, double* arr, double* arr1)
{
	for (auto i = 0; i < size; i++) {
		//std::cout << arr[i] << "	" << arr1[i] << std::endl;
		if (abs(arr[i] - arr1[i]) > 0.00000001) {
			return false;
		}
	}
	return true;
}
