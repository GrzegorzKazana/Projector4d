/*
*Author: Grzegorz Kazana
*Date: 28-11-2018
*Jêzyki Asemblerowe 2018-2019
*/
#pragma once
#include "Matrix.h"

class Vector2d : public Matrix
{
public:
	Vector2d();
	Vector2d(double x, double y);
	Vector2d(const Matrix& other);
	double getX();
	double getY();
	static Vector2d fromMatrix(const Matrix &other);
	~Vector2d();
};

class Vector3d :
	public Matrix
{
public:
	Vector3d();
	Vector3d(double x, double y, double z);
	Vector3d(const Matrix& other);
	double getX();
	double getY();
	double getZ();
	static Vector3d fromMatrix(const Matrix &other);
	~Vector3d();
};

class Vector4d :
	public Matrix
{
public:
	Vector4d();
	Vector4d(double x, double y, double z, double w);
	Vector4d(const Matrix& other);
	double getX();
	double getY();
	double getZ();
	double getW();
	static Vector4d fromMatrix(const Matrix &other);
	~Vector4d();
};

