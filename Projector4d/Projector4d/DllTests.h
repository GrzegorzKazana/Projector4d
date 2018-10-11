#pragma once

#include "ProjectionFunctionsDll.h"

bool testAll();

bool testMatrixScaling();

bool testMatrixMultiplication();

bool testIdentity();

bool matrixEqual(unsigned int size, double* arr, double* arr1);