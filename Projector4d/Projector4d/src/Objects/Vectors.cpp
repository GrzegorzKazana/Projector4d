/*
*Author: Grzegorz Kazana
*Date: 28-11-2018
*Jêzyki Asemblerowe 2018-2019
*/
#include "stdafx.h"
#include "Vectors.h"
#include "../Exceptions/Exceptions.h"


Vector4d::Vector4d()
	:Matrix(4, 1, 0.0)
{
}

// Vector4d
Vector4d::Vector4d(double x, double y, double z, double w)
	:Matrix(4, 1)
{
	this->set_value(0, 0, x);
	this->set_value(1, 0, y);
	this->set_value(2, 0, z);
	this->set_value(3, 0, w);
}

Vector4d::Vector4d(const Matrix& other)
	:Matrix(other)
{
}

double Vector4d::getX()
{
	return this->get_value(0, 0);
}

double Vector4d::getY()
{
	return this->get_value(1, 0);
}

double Vector4d::getZ()
{
	return this->get_value(2, 0);
}

double Vector4d::getW()
{
	return this->get_value(3, 0);
}

Vector4d Vector4d::fromMatrix(const Matrix & other)
{
	if (other.get_cols() == 1 && other.get_rows() == 4) {
		return Vector4d(other);
	}
	throw Vector4dInitialization(other.get_rows(), other.get_cols());
}

Vector4d::~Vector4d()
{
}

Vector3d::Vector3d()
	:Matrix(3, 1, 0.0)
{
}

// Vector3d
Vector3d::Vector3d(double x, double y, double z)
	:Matrix(3, 1)
{
	this->set_value(0, 0, x);
	this->set_value(1, 0, y);
	this->set_value(2, 0, z);
}

Vector3d::Vector3d(const Matrix & other)
	:Matrix(other)
{
}

double Vector3d::getX()
{
	return this->get_value(0, 0);
}

double Vector3d::getY()
{
	return this->get_value(1, 0);
}

double Vector3d::getZ()
{
	return this->get_value(2, 0);
}

Vector3d Vector3d::fromMatrix(const Matrix & other)
{
	if (other.get_cols() == 1 && other.get_rows() == 3) {
		return Vector3d(other);
	}
	throw Vector3dInitialization(other.get_rows(), other.get_cols());
}

Vector3d::~Vector3d()
{
}

Vector2d::Vector2d()
	:Matrix(2, 1, 0.0)
{
}

// Vector2d
Vector2d::Vector2d(double x, double y)
	:Matrix(2, 1)
{
	this->set_value(0, 0, x);
	this->set_value(1, 0, y);
}

Vector2d::Vector2d(const Matrix& other)
	:Matrix(other)
{
}

double Vector2d::getX()
{
	return this->get_value(0, 0);
}

double Vector2d::getY()
{
	return this->get_value(1, 0);
}

Vector2d Vector2d::fromMatrix(const Matrix & other)
{
	if (other.get_cols() == 1 && other.get_rows() == 2) {
		return Vector2d(other);
	}
	throw Vector2dInitialization(other.get_rows(), other.get_cols());
}

Vector2d::~Vector2d()
{
}