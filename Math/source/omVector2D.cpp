//////////////////////////////////////////////////////////////////////////
///																		//
// @file   omVector2D.cpp												//	
// @Author Raul Portillo (ruulaasz_@hotmail.com)						//
// @date   2015/17/10													//
// @brief  Definition of omVector2D Class 								//
// @bug	   No known bugs.												//
//																		//
//////////////////////////////////////////////////////////////////////////
#if PLATFORM == WINDOWS_MATH
#include "Omicron_WindowsMath.h"  /*!< Funciones matematicas basicas optimisadas para Windows */
#endif
#include "Omicron_PlatformMath.h"
#include "omVector2D.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Definicion de la clase omVector2D																					//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace OmicronSDK
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Definicion de contructores y destructor																				//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omVector2D::omVector2D(omVector2D& _vector)
	{
		X = _vector.X;
		Y = _vector.Y;
	}

	omVector2D::omVector2D(float _x , float _y )
	{
		X = _x;
		Y = _y;
	}

	omVector2D::~omVector2D()
	{
		
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Sobrecarga de Operadores																								//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omVector2D omVector2D::operator+(const omVector2D& _vector)
	{
		return omVector2D(X + _vector.X, Y + _vector.Y);
	}

	omVector2D omVector2D::operator+=(const omVector2D& _vector)
	{
		X += _vector.X;
		Y += _vector.Y;
		return *this;
	}

	omVector2D omVector2D::operator-(const omVector2D& _vector)
	{
		return omVector2D(X - _vector.X, Y - _vector.Y);
	}

	omVector2D omVector2D::operator-=(const omVector2D& _vector)
	{
		X -= _vector.X;
		Y -= _vector.Y;
		return *this;
	}

	omVector2D omVector2D::operator*(float _scalar)
	{
		return omVector2D();
	}

	float omVector2D::operator*(const omVector2D & _vector)
	{
		return 0.0f;
	}

	omVector2D omVector2D::operator*=(const omVector2D & _vector)
	{
		return omVector2D();
	}

	bool omVector2D::operator ==(const omVector2D& _vector)
	{
		if (X != _vector.X) return false;
		if (Y != _vector.Y) return false;

		return true;
	}

	bool omVector2D::operator !=(const omVector2D& _vector)
	{
		if (X != _vector.X) return true;
		if (Y != _vector.Y) return true;

		return false;
	}
}