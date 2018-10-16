#include "stdafx.h"
#include "Matrix.h"
#include <algorithm>
#include <iostream>
#include "ProjectionFunctionsDll.h"

inline unsigned int index(unsigned int y, unsigned int x, unsigned int width) {
	return y * width + x;
}

Matrix::Matrix(unsigned int _rows, unsigned int _cols)
	:rows(_rows), cols(_cols)
{
	//initialize data table
	data = new double[rows*cols];
}

Matrix::Matrix(unsigned int _rows, unsigned int _cols, double _default_val)
	:rows(_rows), cols(_cols)
{
	//initialize and fill data table
	data = new double[rows*cols];
	for (unsigned int a = 0; a < rows*cols; a++) {
		data[a] = _default_val;
	}
}

Matrix::Matrix(int _rows, int _cols, double * data_array)
	:rows(_rows), cols(_cols)
{
	data = data_array;
}

Matrix::Matrix(const Matrix & other)
{
	Matrix temp = Matrix::copy(other);
	rows = temp.rows;
	cols = temp.cols;
	data = temp.data;
	temp.data = nullptr;
}

Matrix::Matrix(Matrix&& other)
	:rows(other.rows), cols(other.cols)
{
	data = other.data;
	other.data = nullptr;
}

Matrix Matrix::copy(const Matrix& other)
{
	//create table
	double *arr = new double[other.rows*other.cols];

	//copy values
	for (unsigned int y = 0; y < other.rows; y++) {
		for (unsigned int x = 0; x < other.cols; x++) {
			arr[index(y, x, other.cols)] = other.data[index(y, x, other.cols)];
		}
	}

	return Matrix(other.rows, other.cols, arr);
}

void Matrix::set_value(unsigned int _r, unsigned int _c, double _val)
{
	data[index(_r, _c, cols)] = _val;
}

double Matrix::get_value(unsigned int row, unsigned int col)
{
	return data[index(row, col, cols)];
}

unsigned int Matrix::get_cols() const
{
	return cols;
}

unsigned int Matrix::get_rows() const
{
	return rows;
}

Matrix& Matrix::operator=(Matrix&& other)
{
	std::swap(rows, other.rows);
	std::swap(cols, other.cols);
	std::swap(data, other.data);
	return *this;
}

Matrix & Matrix::operator=(const Matrix & other)
{
	Matrix temp = Matrix::copy(other);
	std::swap(rows, temp.rows);
	std::swap(cols, temp.cols);
	std::swap(data, temp.data);
	return *this;
}

bool Matrix::operator==(const Matrix & other)
{
	if (rows != other.rows || cols != other.cols) {
		return false;
	}
	for (unsigned int i = 0; i < rows*cols; i++) {
		//std::cout << data[i] << other.data[i] << std::endl;
		if (abs(data[i] - other.data[i]) >= std::numeric_limits<float>::epsilon()) {
			return false;
		}
	}
	return true;
}

Matrix::~Matrix()
{
	delete data;
}
