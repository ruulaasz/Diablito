//////////////////////////////////////////////////////////////////////////
///																		//
// @file   omVector3D.cpp												//	
// @Author Raul Portillo (ruulaasz_@hotmail.com)						//
// @date   2015/17/10													//
// @brief  Definition of omVector3D Class 								//
// @bug	   No known bugs.												//
//																		//
//////////////////////////////////////////////////////////////////////////
#if PLATFORM == WINDOWS_MATH
#include "Omicron_WindowsMath.h"  /*!< Funciones matematicas basicas optimisadas para Windows */
#endif
#include "Omicron_PlatformMath.h"

#include "omMatrix3D.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Definicion de la clase omVector3D																					//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace OmicronSDK
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Definicion de contructores y destructor																				//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omVector3D::omVector3D(float _X, float _Y, float _Z)
	{
		X = _X;
		Y = _Y;
		Z = _Z;
	}

	omVector3D::omVector3D(omVector3D& _vector)
	{
		X = _vector.X;
		Y = _vector.Y;
		Z = _vector.Z;
	}

	omVector3D::omVector3D(omVector4D & _vector)
	{
		*this = _vector;
	}

	omVector3D::~omVector3D()
	{

	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Sobrecarga de Operadores																								//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omVector3D omVector3D::operator- (const omVector3D& _vector)
	{
		omVector3D vecSum;
		vecSum.X = X - _vector.X;
		vecSum.Y = Y - _vector.Y;
		vecSum.Z = Z - _vector.Z;

		return vecSum;
	}

	omVector3D omVector3D::operator+ (const omVector3D& _vector)
	{
		omVector3D vecSum;
		vecSum.X = X + _vector.X;
		vecSum.Y = Y + _vector.Y;
		vecSum.Z = Z + _vector.Z;

		return vecSum;
	}

	omVector3D omVector3D::operator*(const omVector3D & _vector)
	{
		omVector3D vecSum;
		vecSum.X = X * _vector.X;
		vecSum.Y = Y * _vector.Y;
		vecSum.Z = Z * _vector.Z;

		return vecSum;
	}

	bool omVector3D::operator== (const omVector3D& _vector)
	{
		if (X != _vector.X)
			return false;
		if (Y != _vector.Y)
			return false;
		if (Z != _vector.Z)
			return false;

		return true;
	}

	bool omVector3D::operator!= (const omVector3D& _vector)
	{
		if (X != _vector.X)
			return true;
		if (Y != _vector.Y)
			return true;
		if (Z != _vector.Z)
			return true;

		return false;
	}

	omVector3D& omVector3D::operator += (const omVector3D& _vector)
	{
		X = X + _vector.X;
		Y = Y + _vector.Y;
		Z = Z + _vector.Z;

		return *this;
	}

	omVector3D& omVector3D::operator -= (const omVector3D& _vector)
	{
		X = X - _vector.X;
		Y = Y - _vector.Y;
		Z = Z - _vector.Z;

		return *this;

	}

	void omVector3D::operator*=(const omMatrix3D & _matrix)
	{
		omVector3D temp(_matrix.m00 * X + _matrix.m01 * Y + _matrix.m02 * Z,
			_matrix.m10 * X + _matrix.m11 * Y + _matrix.m12 * Z,
			_matrix.m20 * X + _matrix.m21 * Y + _matrix.m22 * Z);

		*this = temp;
	}

	omVector3D omVector3D::operator*(const omMatrix3D & _matrix)
	{
		return omVector3D(	_matrix.m00 * X + _matrix.m01 * Y + _matrix.m02 * Z,
							_matrix.m10 * X + _matrix.m11 * Y + _matrix.m12 * Z,
							_matrix.m20 * X + _matrix.m21 * Y + _matrix.m22 * Z );
	}

	void omVector3D::operator/=(const float & _value)
	{
		X /= _value;
		Y /= _value;
		Z /= _value;
	}

	omVector3D & omVector3D::operator=(const omVector4D & _vector)
	{
		X = _vector.X;
		Y = _vector.Y;
		Z = _vector.Z;

		return *this;
	}

	omVector3D omVector3D::operator* (const float& _value)
	{
		return omVector3D(X * _value, Y * _value, Z * _value);
	}

	void omVector3D::operator*= (const float& _value)
	{
		X *= _value;
		Y *= _value;
		Z *= _value;
	}

	float& omVector3D::operator[](const int idx)
	{
		return (&X)[idx];
	}
}