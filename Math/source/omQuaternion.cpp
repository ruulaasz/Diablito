///////////////////////////////////////////////////////////////////////////
///																		//
// @file   omQuaternion.cpp												//	
// @Author Raul Portillo (ruulaasz_@hotmail.com)						//
// @date   2015/18/10													//
// @brief  Class for omQuaternion type structure						//
// @bug	   No known bugs.												//
//																		//
//////////////////////////////////////////////////////////////////////////
#if PLATFORM == WINDOWS_MATH
#include "Omicron_WindowsMath.h"  /*!< Funciones matematicas basicas optimisadas para Windows */
#endif
#include "Omicron_PlatformMath.h"

#include "omVector3D.h"
#include "omMatrix3D.h"
#include "omMatrix4D.h"
#include "omDegrees.h"
#include "omQuaternion.h"


namespace OmicronSDK
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Definicion de contructores y destructor																				//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omQuaternion::omQuaternion(omQuaternion* _H)
	{
		*this = *_H;
	}

	omQuaternion::omQuaternion(omMatrix4D* _Matrix)
	{
		*this = *_Matrix;
	}

	omQuaternion::omQuaternion(omVector3D _Axis, omDegrees _Angle)
	{
		float angleRad = _Angle.GetRadians() * 0.5f;

		float sa(Math::Sin(angleRad));

		// Build a quaternion!
		w = Math::Cos(angleRad);
		x = _Axis.X * sa;
		y = _Axis.Y * sa;
		z = _Axis.Z * sa;
	}

	omQuaternion::omQuaternion(omDegrees _AngleX, omDegrees _AngleY, omDegrees _AngleZ)
	{
		float angle;
		
		angle = _AngleX.GetRadians() * 0.5;
		const float sr = sin(angle);
		const float cr = cos(angle);
		
		angle = _AngleY.GetRadians() * 0.5;
		const float sp = sin(angle);
		const float cp = cos(angle);
		
		angle = _AngleZ.GetRadians() * 0.5;
		const float sy = sin(angle);
		const float cy = cos(angle);
		
		const float cpcy = cp * cy;
		const float spcy = sp * cy;
		const float cpsy = cp * sy;
		const float spsy = sp * sy;
		
		x = (sr * cpcy - cr * spsy);
		y = (cr * spcy + sr * cpsy);
		z = (cr * cpsy - sr * spcy);
		w = (cr * cpcy + sr * spsy);
		
		*this = Normalize(this);
	}

	omQuaternion::omQuaternion(omDegrees _AngleX, omDegrees _AngleY, omDegrees _AngleZ, EulerAngleOrder _Order)
	{
	}

	omQuaternion::~omQuaternion()
	{

	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Definicion de funciones de la clase																					//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omQuaternion omQuaternion::Normalize(omQuaternion* _H)
	{
		float n = _H->x*_H->x + _H->y*_H->y + _H->z*_H->z + _H->w*_H->w;
		
		if (n == 1)
			return _H;
		
		return (*_H *= Math::InvSqrt(n));
	}

	omMatrix4D omQuaternion::ToMatrix4D(omQuaternion* _H)
	{
		omMatrix4D matrix;

		matrix.Line[0][0] = 1.0f - 2.0f*_H->y*_H->y - 2.0f*_H->z*_H->z;
		matrix.Line[0][1] = 2.0f*_H->x*_H->y + 2.0f*_H->z*_H->w;
		matrix.Line[0][2] = 2.0f*_H->x*_H->z - 2.0f*_H->y*_H->w;
		matrix.Line[0][3] = 0.0f;

		matrix.Line[1][0] = 2.0f*_H->x*_H->y - 2.0f*_H->z*_H->w;
		matrix.Line[1][1] = 1.0f - 2.0f*_H->x*_H->x - 2.0f*_H->z*_H->z;
		matrix.Line[1][2] = 2.0f*_H->z*_H->y + 2.0f*_H->x*_H->w;
		matrix.Line[1][3] = 0.0f;

		matrix.Line[2][0] = 2.0f*_H->x*_H->z + 2.0f*_H->y*_H->w;
		matrix.Line[2][1] = 2.0f*_H->z*_H->y - 2.0f*_H->x*_H->w;
		matrix.Line[2][2] = 1.0f - 2.0f*_H->x*_H->x - 2.0f*_H->y*_H->y;
		matrix.Line[2][3] = 0.0f;

		matrix.Line[3][0] = 0.0f;
		matrix.Line[3][1] = 0.0f;
		matrix.Line[3][2] = 0.0f;
		matrix.Line[3][3] = 1.f;

		return matrix;
	}

	omMatrix3D omQuaternion::ToMatrix3D(omQuaternion * _H)
	{
		omMatrix3D matrix;

		matrix.Line[0][0] = 1.0f - 2.0f * _H->y * _H->y - 2.0f * _H->z * _H->z;
		matrix.Line[0][1] = 2.0f * _H->x * _H->y + 2.0f * _H->z * _H->w;
		matrix.Line[0][2] = 2.0f * _H->x * _H->z - 2.0f * _H->y * _H->w;

		matrix.Line[1][0] = 2.0f * _H->x * _H->y - 2.0f * _H->z * _H->w;
		matrix.Line[1][1] = 1.0f - 2.0f * _H->x * _H->x - 2.0f * _H->z * _H->z;
		matrix.Line[1][2] = 2.0f * _H->z * _H->y + 2.0f*_H->x*_H->w;

		matrix.Line[2][0] = 2.0f*_H->x*_H->z + 2.0f*_H->y*_H->w;
		matrix.Line[2][1] = 2.0f*_H->z*_H->y - 2.0f*_H->x*_H->w;
		matrix.Line[2][2] = 1.0f - 2.0f*_H->x*_H->x - 2.0f*_H->y*_H->y;

		return matrix;
	}

	omQuaternion omQuaternion::FromMatrix(omMatrix4D* _Matrix)
	{
		float diag = _Matrix->Line[0][0] + _Matrix->Line[1][1] + _Matrix->Line[2][2] + 1;

		if (diag > 0.0f)
		{
			float scale = Math::Sqrt(diag) * 2.0f; // get scale from diagonal

			x = (_Matrix->Line[1][2] - _Matrix->Line[2][1]) / scale;
			y = (_Matrix->Line[2][0] - _Matrix->Line[0][2]) / scale;
			z = (_Matrix->Line[0][1] - _Matrix->Line[1][0]) / scale;
			w = 0.25f * scale;
		}
		else
		{
			if (_Matrix->Line[0][0] > _Matrix->Line[1][1] && _Matrix->Line[0][0] > _Matrix->Line[2][2])
			{
				// 1st element of diag is greatest value
				// find scale according to 1st element, and double it
				float scale = Math::Sqrt(1.0f + _Matrix->Line[0][0] - _Matrix->Line[1][1] - _Matrix->Line[2][2]) * 2.0f;

				x = 0.25f * scale;
				y = (_Matrix->Line[1][0] + _Matrix->Line[0][1]) / scale;
				z = (_Matrix->Line[0][2] + _Matrix->Line[2][0]) / scale;
				w = (_Matrix->Line[1][2] - _Matrix->Line[2][1]) / scale;
			}
			else if (_Matrix->Line[1][1] > _Matrix->Line[2][2])
			{
				// 2nd element of diag is greatest value
				// find scale according to 2nd element, and double it
				float scale = Math::Sqrt(1.0f + _Matrix->Line[1][1] - _Matrix->Line[0][0] - _Matrix->Line[2][2]) * 2.0f;

				x = (_Matrix->Line[1][0] + _Matrix->Line[0][1]) / scale;
				y = 0.25f * scale;
				z = (_Matrix->Line[2][1] + _Matrix->Line[1][2]) / scale;
				w = (_Matrix->Line[2][0] - _Matrix->Line[0][2]) / scale;
			}
			else
			{
				// 3rd element of diag is greatest value
				// find scale according to 3rd element, and double it
				float scale = Math::Sqrt(1.0f + _Matrix->Line[2][2] - _Matrix->Line[0][0] - _Matrix->Line[1][1]) * 2.0f;

				x = (_Matrix->Line[2][0] + _Matrix->Line[0][2]) / scale;
				y = (_Matrix->Line[2][1] + _Matrix->Line[1][2]) / scale;
				z = 0.25f * scale;
				w = (_Matrix->Line[0][1] - _Matrix->Line[1][0]) / scale;
			}
		}

		return Normalize(this);
	}

	omQuaternion omQuaternion::Lerp(omQuaternion * _H, omQuaternion* _H2, float _Time)
	{
		const float scale = 1.0f - _Time;

		return (*_H*scale + *_H2*_Time);
	}

	omQuaternion omQuaternion::Slerp(omQuaternion * _H, omQuaternion* _H2, float _Time, float _Threshold)
	{
		float angle = DotProduct(_H, _H2);

		// make sure we use the short rotation
		if (angle < 0.0f)
		{
			*_H *= -1.0f;
			angle *= -1.0f;
		}

		if (angle <= (1 - _Threshold)) // spherical interpolation
		{
			float theta = Math::ArcCos(angle);
			float invsintheta = 1 / (Math::Sin(theta));
			float scale = Math::Sin(theta * (1.0f - _Time)) * invsintheta;
			float invscale = Math::Sin(theta * _Time) * invsintheta;
			return ((*_H*scale) + (*_H2*invscale));
		}
		else // linear interploation
			return Lerp(_H, _H2, _Time);
	}

	float omQuaternion::DotProduct(omQuaternion * _H, omQuaternion * _H2)
	{
		return (_H->x * _H2->x) + (_H->y * _H2->y) + (_H->z * _H2->z) + (_H->w * _H2->w);
	}

	void omQuaternion::ResetQuaternion(omQuaternion& _H)
	{
		memset(&_H, 0, sizeof(omQuaternion));
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Sobrecarga de Operadores																								//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omQuaternion omQuaternion::operator*(const omQuaternion & _H)
	{
		omQuaternion Quat;

		Quat.w = _H.w*w - _H.x*x - _H.y*y - _H.z*z;
		Quat.x = _H.w*x + _H.x*w + _H.y*z - _H.z*y;
		Quat.y = _H.w*y + _H.y*w + _H.z*x - _H.x*z;
		Quat.z = _H.w*z + _H.z*w + _H.x*y - _H.y*x;
		return Quat;
	}

	omQuaternion omQuaternion::operator*(const float _value)
	{
		return omQuaternion(_value*x, _value*y, _value*z, _value*w);
	}

	omQuaternion omQuaternion::operator*=(const float _value)
	{
		x *= _value;
		y *= _value;
		z *= _value;
		w *= _value;

		return *this;
	}

	omQuaternion omQuaternion::operator+(const omQuaternion & _H)
	{
		return omQuaternion(x + _H.x, y + _H.y, z + _H.z, w + _H.w);
	}

	bool omQuaternion::operator==(const omQuaternion & _H)
	{
		return ((x == _H.x) && (y == _H.y) && (z == _H.z) && (w == _H.w));
	}

	bool omQuaternion::operator!=(const omQuaternion & _H)
	{
		return !(*this == _H);
	}

	omQuaternion & omQuaternion::operator=(omQuaternion & _H)
	{
		x = _H.x;
		y = _H.y;
		z = _H.z;
		w = _H.w;

		return *this;
	}

	omQuaternion & omQuaternion::operator=(omMatrix4D & _Matrix)
	{
		return(FromMatrix(&_Matrix));
	}
}