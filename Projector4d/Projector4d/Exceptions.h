#pragma once
#include <exception>
#include <string>

//BaseException is a class containing message
//that is initialized when exception is thrown
class BaseException :public std::exception {
	std::string message;
public:
	BaseException() :message("Exception occured") {};
	BaseException(std::string _mes) :message(_mes) {};
	std::string get_message() {
		return message;
	}
	~BaseException() {};
};

//thrown when matrices cant be multiplied
class MatrixMultiplicationException: public BaseException {
public:
	MatrixMultiplicationException(unsigned int rows1, unsigned int cols1, unsigned int rows2, unsigned int cols2)
		:BaseException("Matrix multiplication error occured.\nMatrix dimentions:	"+ std::to_string(rows1) + "x" + std::to_string(cols1)+ " and "+ std::to_string(rows2) + "x" + std::to_string(cols2)){};
};

//thrown when attempting to read matrix out of range
class MatrixIndexOutOfRange : public BaseException {
public:
	MatrixIndexOutOfRange(unsigned int rows, unsigned int cols, unsigned int row_idx, unsigned int cols_idx)
		:BaseException("Matrix call out of range.\n Call was:	" + std::to_string(row_idx) + "," + std::to_string(cols_idx) + "	while matrix dimentions are:	" + std::to_string(rows) + "x" + std::to_string(cols)) {};
};

//thrown when matrices are of diffrent size, but should be the same
class MatrixUnmatchedDimensions :public BaseException {
public:
	MatrixUnmatchedDimensions(unsigned int rows1, unsigned int cols1, unsigned int rows2, unsigned int cols2)
		:BaseException("Operation on matrices with unmatched dimensions.\nMatrix dimentions:	" + std::to_string(rows1) + "x" + std::to_string(cols1) + " and " + std::to_string(rows2) + "x" + std::to_string(cols2)) {};
};

//thrown when coundnt find image file on disk
class SourceImageNotFound :public BaseException {
public:
	SourceImageNotFound(std::string path)
		:BaseException("Failed to load image at:\n"+path) {};
};

//thrown when attempting to read label that is out of index
class LabelNotFound :public BaseException {
public:
	LabelNotFound(int idx)
		:BaseException("Couldn't find label at index:	" + std::to_string(idx)) {};
};

//thrown when attempting to read image that is out of index
class ImageNotFound :public BaseException {
public:
	ImageNotFound(int idx)
		:BaseException("Couldn't find image at index:	" + std::to_string(idx)) {};
};

//thrown when state file doesnt match initialized network
class UnsuccessfulStateLoad :public BaseException {
public:
	UnsuccessfulStateLoad()
		:BaseException("Inapropriate state file") {};
};

//thrown when vector2d cant be constructed from matrix
class Vector2dInitialization : public BaseException {
public:
	Vector2dInitialization(unsigned int rows1, unsigned int cols1)
		:BaseException("Failed to initialize 2d vector with matrix.\nMatrix dimentions:	" + std::to_string(rows1) + "x" + std::to_string(cols1)) {};
};

//thrown when vector3d cant be constructed from matrix
class Vector3dInitialization : public BaseException {
public:
	Vector3dInitialization(unsigned int rows1, unsigned int cols1)
		:BaseException("Failed to initialize 3d vector with matrix.\nMatrix dimentions:	" + std::to_string(rows1) + "x" + std::to_string(cols1)) {};
};

//thrown when vector4d cant be constructed from matrix
class Vector4dInitialization : public BaseException {
public:
	Vector4dInitialization(unsigned int rows1, unsigned int cols1)
		:BaseException("Failed to initialize 4d vector with matrix.\nMatrix dimentions:	" + std::to_string(rows1) + "x" + std::to_string(cols1)) {};
};