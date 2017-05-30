//////////////////////////////////////////////////////////////////////////
///																		//
// @file   omVector4D.cpp												//	
// @Author Raul Portillo (ruulaasz_@hotmail.com)						//
// @date   2015/17/10													//
// @brief  Definition of omVector4D Class 								//
// @bug	   No known bugs.												//
//																		//
//////////////////////////////////////////////////////////////////////////
#if PLATFORM == WINDOWS_MATH
#include "Omicron_WindowsMath.h"  /*!< Funciones matematicas basicas optimisadas para Windows */
#endif
#include "Omicron_PlatformMath.h"

#include "omMatrix4D.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Definicion de la clase omVector4D																					//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace OmicronSDK
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Definicion de contructores y destructor																				//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omVector4D::omVector4D(omVector4D& _vector)
	{
		X = _vector.X;
		Y = _vector.Y;
		Z = _vector.Z;
		W = _vector.W;
	}

	omVector4D::omVector4D(omMatrix4D & _Matrix4x4)
	{
		*this = _Matrix4x4;
	}

	omVector4D::omVector4D(omVector3D & _vector)
	{
		*this = _vector;
	}

	omVector4D::~omVector4D()
	{

	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Sobrecarga de Operadores																								//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omVector4D omVector4D::operator- (const omVector4D& _vector)
	{
		omVector4D vecSum;
		vecSum.X = X - _vector.X;
		vecSum.Y = Y - _vector.Y;
		vecSum.Z = Z - _vector.Z;
		vecSum.W = W - _vector.W;

		return vecSum;
	}

	omVector4D omVector4D::operator+ (const omVector4D& _vector)
	{
		omVector4D vecSum;
		vecSum.X = X + _vector.X;
		vecSum.Y = Y + _vector.Y;
		vecSum.Z = Z + _vector.Z;
		vecSum.W = W + _vector.W;

		return vecSum;
	}

	omVector4D omVector4D::operator* (const omVector4D& _vector)
	{
		omVector4D vecSum;
		vecSum.X = X * _vector.X;
		vecSum.Y = Y * _vector.Y;
		vecSum.Z = Z * _vector.Z;
		vecSum.W = W * _vector.W;

		return vecSum;
	}

	bool omVector4D::operator== (const omVector4D& _vector)
	{
		if (X != _vector.X)
			return false;
		if (Y != _vector.Y)
			return false;
		if (Z != _vector.Z)
			return false;
		if (W != _vector.W)
			return false;

		return true;
	}

	bool omVector4D::operator!= (const omVector4D& _vector)
	{
		if (X != _vector.X)
			return true;
		if (Y != _vector.Y)
			return true;
		if (Z != _vector.Z)
			return true;
		if (W != _vector.W)
			return false;

		return false;
	}

	omVector4D & omVector4D::operator=(const omVector3D & _vector)
	{
		X = _vector.X;
		Y = _vector.Y;
		Z = _vector.Z;
		return *this;
	}

	omVector4D & omVector4D::operator=(const omVector4D & _vector)
	{
		X = _vector.X;
		Y = _vector.Y;
		Z = _vector.Z;
		W = _vector.W;

		return *this;
	}

	omVector4D& omVector4D::operator += (const omVector4D& _vector)
	{
		X = X + _vector.X;
		Y = Y + _vector.Y;
		Z = Z + _vector.Z;
		W = W + _vector.W;

		return *this;
	}

	omVector4D& omVector4D::operator -= (const omVector4D& _vector)
	{
		X = X - _vector.X;
		Y = Y - _vector.Y;
		Z = Z - _vector.Z;
		W = W - _vector.W;

		return *this;

	}

	omVector4D& omVector4D::operator *= (const omVector4D& _vector)
	{
		X = X * _vector.X;
		Y = Y * _vector.Y;
		Z = Z * _vector.Z;
		W = W * _vector.W;

		return *this;

	}

	omVector4D omVector4D::operator* (const float& _value)
	{
		return omVector4D(X *= _value, Y *= _value, Z *= _value, W *= _value);
	}

	float& omVector4D::operator[](const int idx)
	{
		return (&X)[idx];
	}

	omVector4D omVector4D::operator*(const omMatrix4D & _Matrix4x4)
	{
		return omVector4D(_Matrix4x4.m00 * X + _Matrix4x4.m01 * Y + _Matrix4x4.m02 * Z + _Matrix4x4.m03 * W,
			_Matrix4x4.m10 * X + _Matrix4x4.m11 * Y + _Matrix4x4.m12 * Z + _Matrix4x4.m13 * W,
			_Matrix4x4.m20 * X + _Matrix4x4.m21 * Y + _Matrix4x4.m22 * Z + _Matrix4x4.m23 * W,
			_Matrix4x4.m30 * X + _Matrix4x4.m31 * Y + _Matrix4x4.m32 * Z + _Matrix4x4.m33 * W);
	}

	omVector4D & omVector4D::operator=(const omMatrix4D & _Matrix4x4)
	{
		X = _Matrix4x4.Line[0][0] * X + _Matrix4x4.Line[1][0] * Y + _Matrix4x4.Line[2][0] * Z + _Matrix4x4.Line[3][0] * W;
		Y = _Matrix4x4.Line[0][1] * X + _Matrix4x4.Line[1][1] * Y + _Matrix4x4.Line[2][1] * Z + _Matrix4x4.Line[3][1] * W;
		Z = _Matrix4x4.Line[0][2] * X + _Matrix4x4.Line[1][2] * Y + _Matrix4x4.Line[2][2] * Z + _Matrix4x4.Line[3][2] * W;
		W = _Matrix4x4.Line[0][3] * X + _Matrix4x4.Line[1][3] * Y + _Matrix4x4.Line[2][3] * Z + _Matrix4x4.Line[3][3] * W;

		return *this;
	}
}
