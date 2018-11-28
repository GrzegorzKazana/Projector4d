/*
*Author: Grzegorz Kazana
*Date: 28-11-2018
*Jêzyki Asemblerowe 2018-2019
*/
#pragma once

#include "ProjectionFunctionsDll.h"

bool testAll();

bool testMatrixScaling();

bool testMatrixMultiplication();

bool testIdentity();

bool testOrtographicProjectionMatrix();

bool test2dOrtographicProjection();

bool test2dPerspectiveProjection();

bool matrixEqual(unsigned int size, double* arr, double* arr1);