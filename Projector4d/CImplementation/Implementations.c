/*
*Author: Grzegorz Kazana
*Date: 28-11-2018
*Jêzyki Asemblerowe 2018-2019
*/
#include "stdafx.h"
#include <stdlib.h>
#include <math.h>
#undef min

// picks smaller number
int min(int a, int b) {
	return a < b ? a : b;
}

// use this function when matrix is indexed by two indexes, and array is 1d
int calculateMatrixIndex(int col_index, int row_index, int cols) {
	return cols * row_index + col_index;
}

// scales array of doubles of given size in place
void scaleMatrix(int cols, int rows, double* arr, double scale) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			arr[calculateMatrixIndex(j, i, cols)] *= scale;
		}
	}
}

// multiplies two matrices, assumes given output array is correct size
void multiplyMatrix(int cols1, int rows1, double* arr1, int cols2, int rows2, double* arr2, double* outarr) {
	for (int i = 0; i < rows1; i++) {
		for (int j = 0; j < cols2; j++) {
			double sum = 0.0;
			for (int k = 0; k < cols1; k++){
				sum += arr1[calculateMatrixIndex(k, i, cols1)] * arr2[calculateMatrixIndex(j, k, cols2)];
			}
			outarr[calculateMatrixIndex(j, i, cols2)] = sum;
		}
	}
}

// fills given matrix with zeros
void fillZerosMatrix(int cols, int rows, double* arr) {
	for (int i = 0; i< cols*rows; i++) {
		arr[i] = 0.0;
	}
}

// fills given matrix with identity matrix
void fillIdentityMatrix(int cols, int rows, double* arr) {
	fillZerosMatrix(cols, rows, arr);
	for (int i = 0; i < cols; i++) {
		arr[calculateMatrixIndex(i, i, cols)] = 1.0;
	}
}

// fills given matrix with projection matrix
void fillOrtographicProjectionMatrix(int cols, int rows, double* arr) {
	fillZerosMatrix(cols, rows, arr);
	int smaller_dim = min(cols, rows);
	for (int i = 0; i < smaller_dim; i++) {
		arr[calculateMatrixIndex(i, i, cols)] = 1.0;
	}
}

// allocate matrix
double* allocateMatrix(int cols, int rows) {
	return malloc(8 * cols * rows);
}

// free matrix
void deallocateMatrix(double* arr) {
	free(arr);
}

// project matrix
void projectOrtographicImplementation(int cols, int rows, double* arr, double* outarr, int goal_dim) {
	// get projection matrix
	double* projection_matrix = allocateMatrix(rows, goal_dim);
	fillOrtographicProjectionMatrix(rows, goal_dim, projection_matrix);
	// perform projection
	multiplyMatrix(rows, goal_dim, projection_matrix, cols, rows, arr, outarr);
	// deallocate
	deallocateMatrix(projection_matrix);
}

// project matrix
void projectPerspectiveImplementation(int cols, int rows, double* arr, double* outarr, int goal_dim, double distance) {
	// get projection matrix
	double* projection_matrix = allocateMatrix(rows, goal_dim);
	fillOrtographicProjectionMatrix(rows, goal_dim, projection_matrix);
	// calculate perspective scale
	double sliced_coordinate = arr[calculateMatrixIndex(goal_dim, 0, 1)];
	double perspective_scaler = 1.0 / (sliced_coordinate - distance);
	// apply scale to projection matrix
	scaleMatrix(rows, goal_dim, projection_matrix, perspective_scaler);
	// perform projection
	multiplyMatrix(rows, goal_dim, projection_matrix, cols, rows, arr, outarr);
	// deallocate
	deallocateMatrix(projection_matrix);
}

// fills rotation matrix, which rotates specified axis
void fillRotationMatrix(int cols, int rows, double* arr, double angle, int axis1, int axis2) {
	fillIdentityMatrix(cols, rows, arr);
	double cos_angle = cos(angle);
	double sin_angle = sin(angle);
	arr[calculateMatrixIndex(axis1, axis1, cols)] = cos_angle;
	arr[calculateMatrixIndex(axis2, axis2, cols)] = cos_angle;
	arr[calculateMatrixIndex(axis1, axis2, cols)] = sin_angle;
	arr[calculateMatrixIndex(axis2, axis1, cols)] = -sin_angle;
}

// rotates vector
void rotateImplementation(int cols, int rows, double* arr, double* outarr, double angle, int axis0, int axis1) {
	// get rotation matrix
	double* rotation_matrix = allocateMatrix(rows, rows);
	fillRotationMatrix(rows, rows, rotation_matrix, angle, axis0, axis1);
	// perform rotation
	multiplyMatrix(rows, rows, rotation_matrix, cols, rows, arr, outarr);
	// deallocate
	deallocateMatrix(rotation_matrix);
}

// fills double rotation matrix, assumess given matrix is 4x4
void fillDoubleRotationMatrix(int cols, int rows, double* arr, double angle) {
	fillIdentityMatrix(cols, rows, arr);
	double cos_angle = cos(angle);
	double sin_angle = sin(angle);
	arr[calculateMatrixIndex(0, 0, cols)] = cos_angle;
	arr[calculateMatrixIndex(1, 1, cols)] = cos_angle;
	arr[calculateMatrixIndex(2, 2, cols)] = cos_angle;
	arr[calculateMatrixIndex(3, 3, cols)] = cos_angle;
	arr[calculateMatrixIndex(0, 1, cols)] = sin_angle;
	arr[calculateMatrixIndex(2, 3, cols)] = sin_angle;
	arr[calculateMatrixIndex(1, 0, cols)] = -sin_angle;
	arr[calculateMatrixIndex(3, 2, cols)] = -sin_angle;
}

// double rotation implrmrntation only
void rotateWImplementation(int cols, int rows, double* arr, double* outarr, double angle) {
	// get rotation matrix
	double* rotation_matrix = allocateMatrix(rows, rows);
	fillDoubleRotationMatrix(rows, rows, rotation_matrix, angle);
	// perform rotation
	multiplyMatrix(rows, rows, rotation_matrix, cols, rows, arr, outarr);
	// deallocate
	deallocateMatrix(rotation_matrix);
}