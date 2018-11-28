/*
*Author: Grzegorz Kazana
*Date: 28-11-2018
*Jêzyki Asemblerowe 2018-2019
*/
#pragma once
class Matrix
{
public:
	unsigned int rows = 0;
	unsigned int cols = 0;
	double* data = nullptr;
public:
	Matrix(unsigned int _rows, unsigned int _cols);
	Matrix(unsigned int _rows, unsigned int _cols, double _default_val);
	Matrix(int _rows, int _cols, double *data_array);
	Matrix(const Matrix& other);
	Matrix(Matrix&& other);
	static Matrix copy(const Matrix& other);
	void set_value(unsigned int _r, unsigned int _c, double _val);
	double get_value(unsigned int row, unsigned int col);
	unsigned int get_cols() const;
	unsigned int get_rows() const;
	Matrix operator+(const Matrix& other) const;
	Matrix operator-(const Matrix& other) const;
	Matrix& operator=(Matrix&& other);
	Matrix& operator=(const Matrix& other);
	bool operator==(const Matrix& other);
	~Matrix();
};

