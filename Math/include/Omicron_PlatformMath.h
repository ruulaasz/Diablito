//////////////////////////////////////////////////////////////////////////
///																		//
// @file   Omicron_PlatformMath.h										//	
// @Author Raul Portillo (ruulaasz_@hotmail.com)						//
// @date   2015/22/09													//
// @brief  Declaration of non-specific platform math functions			//
// @bug	   No known bugs.												//
//																		//
//////////////////////////////////////////////////////////////////////////
#pragma once
#include <cmath>
#include "omMacros.h"
#include "omDegrees.h"
#include "omRadians.h"
#include "omVector3D.h"
#include "omVector4D.h"
#include "omMatrix3D.h"
#include "omMatrix4D.h"
#include "omFrustum.h"
#include "omPlane.h"
#include "omAABB.h"
#include "omRay.h"
#include "omSphere.h"

#define MATH_API

namespace OmicronSDK
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Declaracion del enum RotationAxis																					//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	enum eRotationAxis4D
	{
		RA_X = 0,
		RA_Y,
		RA_Z,
		RA_W,
		RA_TotalAxis
	};

	typedef unsigned int uint;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Estructura de funciones para la plataforma matematica estandard														//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	struct PlatformMath
	{
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Constantes matematicas de uso común																					//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		static const float PI;				//<PI Constant>				//
		static const float PI2;				//<2 Times PI Constant>		//
		static const float PI4;				//<4 Times PI Constant>		//
		static const float HALF_PI;			//<1/2 Times PI Constant>	//
		static const float QUARTER_PI;		//<1/2 Times PI Constant>	//
		static const float INVERSE_PI;		//<Inverse PI Constant>		//
		static const float EULER_NUMBER;	//<Euler Number Constant>	//
		static const float LOG2;			//<2 Times LOG Constant>	//
		static const float EPSILON;			//<Epsilon Constant>		//
		static const float DELTA;			//<Delta Constant>		    //
		static const float DEG_TO_RAD;		//<Constante de conversion de grados a radianes>//
		static const float RAD_TO_DEG;		//<Constante de conversion de radianes a grados>//
		static const float MAX_FLOAT32;		//<Numero flotante mas grande>//

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Declaracion de funciones trigonometricas																				//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		static T MATH_API Sin(T _value){ return sin(_value); };		//<Retorna el seno de un tipo de dato cualquiera>//
		template<>
		static float MATH_API Sin(float _value){ return sinf(_value); };		//<Retorna el seno de un flotante>//

		template<typename T>
		static T MATH_API Cos(T _value){ return cos(_value); };		//<Retorna el coseno de un tipo de dato cualquiera>//
		template<>
		static float MATH_API Cos(float _value){ return cosf(_value); };		//<Retorna el coseno de un flotante>//

		template<typename T>
		static T MATH_API Tan(T _value){ return tan(_value); };		//<Retorna la tangente de un tipo de dato cualquiera>//
		template<>
		static float MATH_API Tan(float _value){ return tanf(_value); };		//<Retorna la tangente de un flotante>//

		template<typename T>
		static T MATH_API ArcSin(T _value){ return asin(_value); };	//<Retorna el arcoSeno de un tipo de dato cualquiera>//
		template<>
		static float MATH_API ArcSin(float _value){ return asinf(_value); };	//<Retorna el arcoSeno de un flotante>//

		template<typename T>
		static T MATH_API ArcCos(T _value){ return acos(_value); };	//<Retorna el arcoCoseno de un tipo de dato cualquiera>//
		template<>
		static float MATH_API ArcCos(float _value){ return acosf(_value); };	//<Retorna el arcoCoseno de un flotante>//

		template<typename T>
		static T MATH_API ArcTan(T _value){ return atan(_value); };	//<Retorna el arcTangente de un tipo de dato cualquiera>//
		template<>
		static float MATH_API ArcTan(float _value){ return atanf(_value); };	//<Retorna el arcTangente de un flotante>//

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Declaracion de funciones trigonometricas rapidas																		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		static float MATH_API FastSin(float _value)					//<Retorna el seno de manera rapida>//
		{

			return sinf(_value);

		}

		static float MATH_API FastSin2(float _value)			//<Retorna el seno de manera rapida con mayor presicion>//
		{
			return sinf(_value);			//<Retorna el seno de un flotante de manera rapida con mayor presicion>//
		}

		static float MATH_API FastCos(float _value)				//<Retorna el coseno de manera rapida>//
		{
			return cosf(_value);								//<Retorna el Coseno de un flotante de manera rapida>//
		}

		static float MATH_API FastCos2(float _value)			//<Retorna el coseno de manera rapida con mayor presicion>//
		{
			return cosf(_value);				//<Retorna el Coseno de un flotante de manera rapida>//
		}

		static float MATH_API FastTan(float _value)				//<Retorna la tangente de manera rapida>//
		{
			return atanf(_value);								//<Retorna la tangente de un flotante de manera rapida>//
		}
		static float MATH_API FastTan2(float _value)			//<Retorna la tangente de manera rapida con mayor presicion>//
		{
			return atanf(_value);								//<Retorna la tangente de un flotante de manera rapida con mayor presicion>//
		}

		static float MATH_API FastArcSin(float _value)			//<Retorna el arcoSeno de manera rapida//
		{
			return asinf(_value);									//<el arcoSeno de un flotante de manera rapida>//
		}
		static float MATH_API FastArcSin2(float _value)			//<Retorna el arcoSeno de manera rapida con mayor presicion//
		{
			return asinf(_value);						//<el arcoSeno de un flotante de manera rapida>//
		}

		static float MATH_API FastArcCos(float _value)			//<Retorna el arcoCoseno de manera rapida>//
		{
			return acosf(_value);								//<el arcoSeno de un flotante de manera rapida>//
		}
		static float MATH_API FastArcCos2(float _value)			//<Retorna el arcoCoseno de manera rapida con mayor presicion>//
		{
			return acosf(_value);		//<el arcoSeno de un flotante de manera rapida>//
		}

		static float MATH_API FastArcTan(float _value)			//<Retorna el arcoTangente de manera rapida>//
		{
			return atanf(_value);						//<el arcoTangente de un flotante de manera rapida>//
		}
		static float MATH_API FastArcTan2(float _value)			//<Retorna el arcoTangente de manera rapida con mayor presicion>//
		{
			return atanf(_value);		//<el arcoTangente de un flotante de manera rapida y con mayor presicion>//
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Declaracion de funciones Logaritmicas																				//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		template<typename T, typename Y>
		static T MATH_API LogX(T _value, Y _base){ return log(_value) / log(_base); };//<Retorna el logaritmo de un tipo de dato cualquiera>//
		template<>
		static float MATH_API LogX(float _value, float _base){ return logf(_value) / logf(_base); };//<Retorna el logaritmo de un flotante>//

		template<typename T>
		static T MATH_API LogN(T _value){ return log(_value)/log(2.f); };//<Retorna el logaritmo natural de un tipo de dato cualquiera>//
		template<>
		static float MATH_API LogN(float _value){ return log(_value) / log(2.f); };//<Retorna el logaritmo natural de un flotante>//

		template<typename T>
		static T MATH_API LogE(T _value){ return log2(_value); };//<Retorna el logaritmo base 2 de un tipo de dato cualquiera>//
		template<>
		static float MATH_API LogE(float _value){ return log2(_value); };//<Retorna el logaritmo base 2 de un flotante>//

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Declaracion de funciones de operaciones Matematicas																	//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		static T MATH_API Sqrt(T _value){ return sqrt(_value); };//<Retorna la raiz cuadrada de un tipo de dato cualquiera>//
		template<>
		static float MATH_API Sqrt(float _value)		//<Retorna la raiz cuadrada de un flotante>//
		{
			return sqrt(_value);			//<Retorna la raiz cuadrada de un flotante>//
		}

		template<typename T>
		static T MATH_API InvSqrt(T _value){ return (1 / sqrt(_value)); };//<Retorna la raiz cuadrada inversa de un tipo de dato cualquiera>//
		template<>
		static float MATH_API InvSqrt(float _value){ return (1 / sqrt(_value)); };//<Retorna la raiz cuadrada inversa de un flotante>//

		template<typename T>
		static T MATH_API Square(T _value){ return (_value*_value); };//<Retorna el cuadrado de un tipo de dato cualquiera>//
		template<>
		static float MATH_API Square(float _value)							//<Retorna el cuadrado de un flotante>//
		{
			return (_value*_value);			//<Retorna el cuadrado de un flotante>//
		}

		template<typename T, typename Y>
		static T MATH_API Pow(T _value, Y _pow){ return pow(_value, _pow); };//<Retorna el primer termino elevado al segundo termino tipo de dato cualquiera>//
		template<>
		static float MATH_API Pow(float _value, int _power){ return pow(_value, _power); };//<Retorna el primer termino que es flotante elevado al segundo termino>//

		static unsigned MATH_API Factorial(unsigned _value)
		{
			if (_value == 1)
				return 1;
			else
				return _value* PlatformMath::Factorial(_value - 1);
		};

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Declaracion de operaciones de comparacion 																			//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		static T MATH_API Min(T _value1, T _value2){return (_value1 <= _value2 ? _value1 : _value2); };//<Retorna el numero menor entre 2 datos cualquiera>//

		template<typename T>
		static T MATH_API Max(T _value1, T _value2){ return (_value1 >= _value2 ? _value1 : _value2);};//<Retorna el numero mayor entre 2 datos cualquiera>//
		
		template<typename T>
		static T MATH_API Min3(T _value1, T _value2, T _value3){ return Min(Min(_value1, _value2), _value3) };//<Retorna el numero menor entre 3 datos cualquiera>//

		template<typename T>
		static T MATH_API Max3(T _value1, T _value2, T _value3){ return Max(Max(_value1, _value2), _value3) };//<Retorna el numero mayor entre 3 datos cualquiera>//

		template<typename T>
		static void MATH_API Swap(T& _value1, T& _value2){ std::swap(_value1, _value2); };//<intercambia 2 datos cualquera>//

		static bool MATH_API IntersectPlanetoPlane(omPlane& _Plane1, omPlane& _Plane2, omVector3D& _CollitionPoint);/*!< Colision entre Plano-Plano */

		static bool MATH_API IntersectPlanetoSphere(omPlane& _Plane, omSphere& _Sphere);							/*!< Colision entre Plano-Esfera */

		static bool MATH_API IntersectPlanetoRay(omPlane& _Plane, omRay& _Ray, omVector3D& _CollitionPoint);		/*!< Colision entre Plano-Rayo */

		static bool MATH_API IntersectPlanetoAABB(omPlane& _Plane, omAABB& _AABB);									/*!< Colision entre Plano-AABB */

		static bool MATH_API IntersectSpheretoSphere(omSphere& _Sphere1, omSphere& _Sphere2);						/*!< Colision entre Esfera-Esfera */

		static bool MATH_API IntersectSpheretoPlane(omSphere& _Sphere, omPlane& _Plane);							/*!< Colision entre Esfera-Plano */

		static bool MATH_API IntersectSpheretoRay(omSphere& _Sphere, omRay& _Ray);									/*!< Colision entre Esfera-Rayo */

		static bool MATH_API IntersectSpheretoAABB(omSphere& _Sphere, omAABB& _AABB);								/*!< Colision entre Esfera-AABB */

		static bool MATH_API IntersectRaytoPlane(omRay& _Ray, omPlane& _Plane, omVector3D& _CollitionPoint);		/*!< Colision entre Rayo-Plano */

		static bool MATH_API IntersectRaytoSphere(omRay& _Ray, omSphere& _Sphere);									/*!< Colision entre Rayo-Esfera */

		static bool MATH_API IntersectRaytoAABB(omRay& _Ray, omAABB& _AABB, omVector3D& _CollitionPoint);			/*!< Colision entre Rayo-AABB */

		static bool MATH_API IntersectAABBtoAABB(omAABB& _AABB1, omAABB& _AABB2);									/*!< Colision entre AABB-AABB */

		static bool MATH_API IntersectAABBtoPlane(omAABB& _AABB, omPlane& _Plane);									/*!< Colision entre AABB-Plano */

		static bool MATH_API IntersectAABBtoSphere(omAABB& _AABB, omSphere& _Sphere);								/*!< Colision entre AABB-Esfera */

		static bool MATH_API IntersectAABBtoRay(omAABB& _AABB, omRay& _Ray, omVector3D& _CollitionPoint);			/*!< Colision entre AABB-Rayo */


		//VECTORES
		static float Length(omVector3D& _Vector)
		{
			return Sqrt(Square(_Vector.X) + Square(_Vector.Y) + Square(_Vector.Z));
		}

		static float Length(omVector4D& _Vector)
		{
			return Sqrt(Square(_Vector.X) + Square(_Vector.Y) + Square(_Vector.Z) + Square(_Vector.W));
		}

		static float SquareLength(omVector3D& _Vector)
		{
			return Square(_Vector.X) + Square(_Vector.Y) + Square(_Vector.Z);
		}

		static float SquareLength(omVector4D& _Vector)
		{
			return Square(_Vector.X) + Square(_Vector.Y) + Square(_Vector.Z) +Square(_Vector.W);
		}

		static void Normalize(omVector3D& _Vector)
		{
			float length = Length(_Vector);

			if (length != 0)
				_Vector.X /= length, _Vector.Y /= length, _Vector.Z /= length;
		}

		static void Normalize(omVector4D& _Vector)
		{
			float length = Length(_Vector);

			if (length != 0)
				_Vector.X /= length, _Vector.Y /= length, _Vector.Z /= length, _Vector.W /= length;
		}

		static omVector3D CrossProduct(const omVector3D& _Vector,const omVector3D& _Vector2)
		{
			return omVector3D
			{
				_Vector.Y * _Vector2.Z - _Vector.Z * _Vector2.Y,
				_Vector.Z * _Vector2.X - _Vector.X * _Vector2.Z,
				_Vector.X * _Vector2.Y - _Vector.Y * _Vector2.X
			};
		}

		static omVector4D CrossProduct(const omVector4D& _Vector, const omVector4D& _Vector2)
		{
			return omVector4D
			{
				_Vector.Y * _Vector2.Z - _Vector.Z * _Vector2.Y,
				_Vector.Z * _Vector2.X - _Vector.X * _Vector2.Z,
				_Vector.X * _Vector2.Y - _Vector.Y * _Vector2.X
			};
		}

		static float DotProduct(omVector3D& _Vector, omVector3D& _Vector2)
		{
			return((_Vector.X*_Vector2.X) + (_Vector.Y*_Vector2.Y) + (_Vector.Z*_Vector2.Z));
		}
		static float DotProduct(omVector4D& _Vector, omVector4D& _Vector2)
		{
			return((_Vector.X*_Vector2.X) + (_Vector.Y*_Vector2.Y) + (_Vector.Z*_Vector2.Z) + (_Vector.W * _Vector2.W));
		}

		static void Escalate(omVector3D& _Vector, float _scalar)
		{
			Normalize(_Vector);

			_Vector.X *= _scalar, _Vector.Y *= _scalar, _Vector.Z*=_scalar;
		}

		static void Escalate(omVector4D& _Vector, float _scalar)
		{
			Normalize(_Vector);

			_Vector.X *= _scalar, _Vector.Y *= _scalar, _Vector.Z *= _scalar, _Vector.W *= _scalar;
		}

		static void Truncate(omVector3D& _Vector, float _max)
		{
			float mag = Length(_Vector);

			if (mag > _max)
				Escalate(_Vector, _max);
		}

		static void Truncate(omVector4D& _Vector, float _max)
		{
			float mag = Length(_Vector);

			if (mag > _max)
				Escalate(_Vector, _max);
		}

		static void ClearVector(omVector3D& _Vector)
		{
			memset(&_Vector, 0, sizeof(omVector3D));
		}

		static void ClearVector(omVector4D& _Vector)
		{
			memset(&_Vector, 0, sizeof(omVector4D));
		}

		static void ResetMatrix(omMatrix3D& _Matrix)
		{
			memset(&_Matrix, 0, sizeof(omMatrix3D));
		}

		static void ResetMatrix(omMatrix4D& _Matrix)
		{
			memset(&_Matrix, 0, sizeof(omMatrix4D));
		}

		static omMatrix3D Identity3D()//<Retorna la matriz identidad>//
		{
			omMatrix3D IdentityMatrix;

			ResetMatrix(IdentityMatrix);

			IdentityMatrix.m00 = 1;
			IdentityMatrix.m11 = 1;
			IdentityMatrix.m22 = 1;

			return IdentityMatrix;
		}

		static omMatrix4D Identity4D()//<Retorna la matriz identidad>//
		{
			omMatrix4D IdentityMatrix;

			ResetMatrix(IdentityMatrix);

			IdentityMatrix.m00 = 1;
			IdentityMatrix.m11 = 1;
			IdentityMatrix.m22 = 1;
			IdentityMatrix.m33 = 1;

			return IdentityMatrix;
		}

		static omMatrix3D Transpose(const omMatrix3D& _Matrix3x3)//<retorna la matriz transpuesta>//
		{
			omMatrix3D TransposeMatrix;

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					TransposeMatrix.Line[j][i] = _Matrix3x3.Line[i][j];
				}
			}

			return TransposeMatrix;
		}

		static omMatrix4D Transpose(const omMatrix4D& _Matrix4x4)															//<retorna la matriz transpuesta>//
		{
			omMatrix4D TransposeMatrix;

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					TransposeMatrix.Line[i][j] = _Matrix4x4.Line[j][i];
				}
			}

			return TransposeMatrix;
		}

		static omMatrix3D ScalarMatrix3x3(float _X, float _Y, float _Z)
		{
			omMatrix3D ScalarMatrix = Identity3D();

			ScalarMatrix.m00 *= _X;
			ScalarMatrix.m11 *= _Y;
			ScalarMatrix.m22 *= _Z;

			return ScalarMatrix;
		}

		static omMatrix4D ScalarMatrix4x4(float _X, float _Y, float _Z)
		{
			omMatrix4D ScalarMatrix = Identity4D();

			ScalarMatrix.Line[0][0] = _X;
			ScalarMatrix.Line[1][1] = _Y;
			ScalarMatrix.Line[2][2] = _Z;

			return ScalarMatrix;
		}

		static omMatrix4D TranslationMatrix4x4(float _X, float _Y, float _Z)
		{
			omMatrix4D TranslationMatrix = Identity4D();

			TranslationMatrix.Line[0][3] = _X;
			TranslationMatrix.Line[1][3] = _Y;
			TranslationMatrix.Line[2][3] = _Z;

			return TranslationMatrix;
		}

		static omMatrix3D RotationMatrix3x3( float _radians, eRotationAxis4D Axis)
		{
			omMatrix3D RotationMatrix = Identity3D();

			float fPreCalcCos = Cos(_radians);
			float fPreCalcSin = Sin(_radians);

			if (Axis == RA_X)
			{
				RotationMatrix.m11 = fPreCalcCos;
				RotationMatrix.m12 = fPreCalcSin;
				RotationMatrix.m21 = -fPreCalcSin;
				RotationMatrix.m22 = fPreCalcCos;
			}

			if (Axis == RA_Y)
			{
				RotationMatrix.m00 = fPreCalcCos;
				RotationMatrix.m20 = fPreCalcSin;
				RotationMatrix.m02 = -fPreCalcSin;
				RotationMatrix.m22 = fPreCalcCos;
			}

			if (Axis == RA_Z)
			{
				RotationMatrix.m00 = fPreCalcCos;
				RotationMatrix.m01 = fPreCalcSin;
				RotationMatrix.m10 = -fPreCalcSin;
				RotationMatrix.m11 = fPreCalcCos;
			}

			return omMatrix3D(RotationMatrix);
		}

		static omMatrix4D RotationMatrix4x4(float _radians, eRotationAxis4D Axis)
		{
			omMatrix4D RotationMatrix = Identity4D();

			float fPreCalcCos = Cos(_radians);
			float fPreCalcSin = Sin(_radians);

			if (Axis == RA_X)
			{
				RotationMatrix.Line[1][1] = fPreCalcCos;
				RotationMatrix.Line[2][2] = fPreCalcCos;
				RotationMatrix.Line[1][2] = fPreCalcSin;
				RotationMatrix.Line[2][1] = -fPreCalcSin;
			}

			if (Axis == RA_Y)
			{
				RotationMatrix.Line[0][0] = fPreCalcCos;
				RotationMatrix.Line[2][2] = fPreCalcCos;
				RotationMatrix.Line[0][2] = -fPreCalcSin;
				RotationMatrix.Line[2][0] = fPreCalcSin;
			}

			if (Axis == RA_Z)
			{
				RotationMatrix.Line[0][0] = fPreCalcCos;
				RotationMatrix.Line[1][1] = fPreCalcCos;
				RotationMatrix.Line[0][1] = fPreCalcSin;
				RotationMatrix.Line[1][0] = -fPreCalcSin;
			}

			return omMatrix4D(RotationMatrix);
		}

		static omMatrix4D InverseMatrix4D(omMatrix4D& _Matrix4x4)
		{
			float d = ((_Matrix4x4.m00 * _Matrix4x4.m11 - _Matrix4x4.m01 * _Matrix4x4.m10) * (_Matrix4x4.m22 * _Matrix4x4.m33 - _Matrix4x4.m23 * _Matrix4x4.m32) -
				       (_Matrix4x4.m00 *_Matrix4x4.m12 - _Matrix4x4.m02 * _Matrix4x4.m10) * (_Matrix4x4.m21 * _Matrix4x4.m33 - _Matrix4x4.m23 * _Matrix4x4.m31) +
				       (_Matrix4x4.m00 * _Matrix4x4.m13 - _Matrix4x4.m03 * _Matrix4x4.m10) * (_Matrix4x4.m21 * _Matrix4x4.m32 - _Matrix4x4.m22 * _Matrix4x4.m31) +
				       (_Matrix4x4.m01 * _Matrix4x4.m12 - _Matrix4x4.m02 * _Matrix4x4.m11) * (_Matrix4x4.m20 * _Matrix4x4.m33 - _Matrix4x4.m23 * _Matrix4x4.m30) -
				       (_Matrix4x4.m01 *_Matrix4x4.m13 - _Matrix4x4.m03 *_Matrix4x4.m11) * (_Matrix4x4.m20 *_Matrix4x4.m32 - _Matrix4x4.m22 * _Matrix4x4.m30) +
				       (_Matrix4x4.m02 * _Matrix4x4.m13 - _Matrix4x4.m03 *_Matrix4x4.m12) * (_Matrix4x4.m20 * _Matrix4x4.m31 - _Matrix4x4.m21 * _Matrix4x4.m30));
			
			d = 1 / d;
			
			omMatrix4D Inv;

			Inv.m00 = d *(	_Matrix4x4.m11 * (_Matrix4x4.m22 * _Matrix4x4.m33 - _Matrix4x4.m23 * _Matrix4x4.m32) +
							_Matrix4x4.m12 * (_Matrix4x4.m23 * _Matrix4x4.m31 - _Matrix4x4.m21 * _Matrix4x4.m33) +
							_Matrix4x4.m13 * (_Matrix4x4.m21 * _Matrix4x4.m32 - _Matrix4x4.m22 * _Matrix4x4.m31) );

			Inv.m01 = d *(	_Matrix4x4.m21 * (_Matrix4x4.m02 * _Matrix4x4.m33 - _Matrix4x4.m03 * _Matrix4x4.m32) +
							_Matrix4x4.m22 * (_Matrix4x4.m03 * _Matrix4x4.m31 - _Matrix4x4.m01 * _Matrix4x4.m33) +
							_Matrix4x4.m23 * (_Matrix4x4.m01 * _Matrix4x4.m32 - _Matrix4x4.m02 * _Matrix4x4.m31) );

			Inv.m02 = d *(	_Matrix4x4.m31 * (_Matrix4x4.m02 * _Matrix4x4.m13 - _Matrix4x4.m03 * _Matrix4x4.m12) +
							_Matrix4x4.m32 * (_Matrix4x4.m03 * _Matrix4x4.m11 - _Matrix4x4.m01 * _Matrix4x4.m13) +
							_Matrix4x4.m33 * (_Matrix4x4.m01 * _Matrix4x4.m12 - _Matrix4x4.m02 * _Matrix4x4.m11) );

			Inv.m03 = d *(	_Matrix4x4.m01 * (_Matrix4x4.m13 * _Matrix4x4.m22 - _Matrix4x4.m12 * _Matrix4x4.m23) +
							_Matrix4x4.m02 * (_Matrix4x4.m11 * _Matrix4x4.m23 - _Matrix4x4.m13 * _Matrix4x4.m21) +
							_Matrix4x4.m03 * (_Matrix4x4.m12 * _Matrix4x4.m21 - _Matrix4x4.m11 * _Matrix4x4.m22) );

			Inv.m10 = d *(	_Matrix4x4.m12 * (_Matrix4x4.m20 * _Matrix4x4.m33 - _Matrix4x4.m23 * _Matrix4x4.m30) +
							_Matrix4x4.m13 * (_Matrix4x4.m22 * _Matrix4x4.m30 - _Matrix4x4.m20 * _Matrix4x4.m32) +
							_Matrix4x4.m10 * (_Matrix4x4.m23 * _Matrix4x4.m32 - _Matrix4x4.m22 * _Matrix4x4.m33) );

			Inv.m11 = d *(	_Matrix4x4.m22 * (_Matrix4x4.m00 * _Matrix4x4.m33 - _Matrix4x4.m03 * _Matrix4x4.m30) +
							_Matrix4x4.m23 * (_Matrix4x4.m02 * _Matrix4x4.m30 - _Matrix4x4.m00 * _Matrix4x4.m32) +
							_Matrix4x4.m20 * (_Matrix4x4.m03 * _Matrix4x4.m32 - _Matrix4x4.m02 * _Matrix4x4.m33) );

			Inv.m12 = d *(	_Matrix4x4.m32 * (_Matrix4x4.m00 * _Matrix4x4.m13 - _Matrix4x4.m03 * _Matrix4x4.m10) +
							_Matrix4x4.m33 * (_Matrix4x4.m02 * _Matrix4x4.m10 - _Matrix4x4.m00 * _Matrix4x4.m12) +
							_Matrix4x4.m30 * (_Matrix4x4.m03 * _Matrix4x4.m12 - _Matrix4x4.m02 * _Matrix4x4.m13) );

			Inv.m13 = d *(	_Matrix4x4.m02 * (_Matrix4x4.m13 * _Matrix4x4.m20 - _Matrix4x4.m10 * _Matrix4x4.m23) +
							_Matrix4x4.m03 * (_Matrix4x4.m10 * _Matrix4x4.m22 - _Matrix4x4.m12 * _Matrix4x4.m20) +
							_Matrix4x4.m00 * (_Matrix4x4.m12 * _Matrix4x4.m23 - _Matrix4x4.m13 * _Matrix4x4.m22) );

			Inv.m20 = d *(	_Matrix4x4.m13 * (_Matrix4x4.m20 * _Matrix4x4.m31 - _Matrix4x4.m21 * _Matrix4x4.m30) +
							_Matrix4x4.m10 * (_Matrix4x4.m21 * _Matrix4x4.m33 - _Matrix4x4.m23 * _Matrix4x4.m31) +
							_Matrix4x4.m11 * (_Matrix4x4.m23 * _Matrix4x4.m30 - _Matrix4x4.m20 * _Matrix4x4.m33) );

			Inv.m21 = d *(	_Matrix4x4.m23 * (_Matrix4x4.m00 * _Matrix4x4.m31 - _Matrix4x4.m01 * _Matrix4x4.m30) +
							_Matrix4x4.m20 * (_Matrix4x4.m01 * _Matrix4x4.m33 - _Matrix4x4.m03 * _Matrix4x4.m31) +
							_Matrix4x4.m21 * (_Matrix4x4.m03 * _Matrix4x4.m30 - _Matrix4x4.m00 * _Matrix4x4.m33) );

			Inv.m22 = d *(	_Matrix4x4.m33 * (_Matrix4x4.m00 * _Matrix4x4.m11 - _Matrix4x4.m01 * _Matrix4x4.m10) +
							_Matrix4x4.m30 * (_Matrix4x4.m01 * _Matrix4x4.m13 - _Matrix4x4.m03 * _Matrix4x4.m11) +
							_Matrix4x4.m31 * (_Matrix4x4.m03 * _Matrix4x4.m10 - _Matrix4x4.m00 * _Matrix4x4.m13) );

			Inv.m23 = d *(	_Matrix4x4.m03 * (_Matrix4x4.m11 * _Matrix4x4.m20 - _Matrix4x4.m10 * _Matrix4x4.m21) +
							_Matrix4x4.m00 * (_Matrix4x4.m13 * _Matrix4x4.m21 - _Matrix4x4.m11 * _Matrix4x4.m23) +
							_Matrix4x4.m01 * (_Matrix4x4.m10 * _Matrix4x4.m23 - _Matrix4x4.m13 * _Matrix4x4.m20) );

			Inv.m30 = d *(	_Matrix4x4.m10 * (_Matrix4x4.m22 * _Matrix4x4.m31 - _Matrix4x4.m21 * _Matrix4x4.m32) +
							_Matrix4x4.m11 * (_Matrix4x4.m20 * _Matrix4x4.m32 - _Matrix4x4.m22 * _Matrix4x4.m30) +
							_Matrix4x4.m12 * (_Matrix4x4.m21 * _Matrix4x4.m30 - _Matrix4x4.m20 * _Matrix4x4.m31) );

			Inv.m31 = d *(	_Matrix4x4.m20 * (_Matrix4x4.m02 * _Matrix4x4.m31 - _Matrix4x4.m01 * _Matrix4x4.m32) +
							_Matrix4x4.m21 * (_Matrix4x4.m00 * _Matrix4x4.m32 - _Matrix4x4.m02 * _Matrix4x4.m30) +
							_Matrix4x4.m22 * (_Matrix4x4.m01 * _Matrix4x4.m30 - _Matrix4x4.m00 * _Matrix4x4.m31) );

			Inv.m32 = d *(	_Matrix4x4.m30 * (_Matrix4x4.m02 * _Matrix4x4.m11 - _Matrix4x4.m01 * _Matrix4x4.m12) +
							_Matrix4x4.m31 * (_Matrix4x4.m00 * _Matrix4x4.m12 - _Matrix4x4.m02 * _Matrix4x4.m10) +
							_Matrix4x4.m32 * (_Matrix4x4.m01 * _Matrix4x4.m10 - _Matrix4x4.m00 * _Matrix4x4.m11) );

			Inv.m33 = d *(	_Matrix4x4.m00 * (_Matrix4x4.m11 * _Matrix4x4.m22 - _Matrix4x4.m12 * _Matrix4x4.m21) +
							_Matrix4x4.m01 * (_Matrix4x4.m12 * _Matrix4x4.m20 - _Matrix4x4.m10 * _Matrix4x4.m22) +
							_Matrix4x4.m02 * (_Matrix4x4.m10 * _Matrix4x4.m21 - _Matrix4x4.m11 * _Matrix4x4.m20) );

			return Inv;
		}

		static float DeterminantMatrix(const omMatrix3D& _Matrix3x3)					//<retorna el determinante de una matriz>//
		{
			return	((_Matrix3x3.m00 * _Matrix3x3.m11 * _Matrix3x3.m22) + (_Matrix3x3.m01 * _Matrix3x3.m12 * _Matrix3x3.m20) + (_Matrix3x3.m02 * _Matrix3x3.m10 * _Matrix3x3.m21)) -
				((_Matrix3x3.m02 * _Matrix3x3.m11 * _Matrix3x3.m20) + (_Matrix3x3.m01 * _Matrix3x3.m10 * _Matrix3x3.m22) + (_Matrix3x3.m00 * _Matrix3x3.m12 * _Matrix3x3.m21));
		}

		static float DeterminantMatrix(const omMatrix4D& _Matrix4x4)					//<retorna el determinante de una matriz>//
		{
			return  _Matrix4x4.m03 * _Matrix4x4.m12 * _Matrix4x4.m21 * _Matrix4x4.m30 - _Matrix4x4.m02 * _Matrix4x4.m13 * _Matrix4x4.m21 * _Matrix4x4.m30 -
				_Matrix4x4.m03 * _Matrix4x4.m11 * _Matrix4x4.m22 * _Matrix4x4.m30 + _Matrix4x4.m01 * _Matrix4x4.m13 * _Matrix4x4.m22 * _Matrix4x4.m30 +
				_Matrix4x4.m02 * _Matrix4x4.m11 * _Matrix4x4.m23 * _Matrix4x4.m30 - _Matrix4x4.m01 * _Matrix4x4.m12 * _Matrix4x4.m23 * _Matrix4x4.m30 -
				_Matrix4x4.m03 * _Matrix4x4.m12 * _Matrix4x4.m20 * _Matrix4x4.m31 + _Matrix4x4.m02 * _Matrix4x4.m13 * _Matrix4x4.m20 * _Matrix4x4.m31 +
				_Matrix4x4.m03 * _Matrix4x4.m10 * _Matrix4x4.m22 * _Matrix4x4.m31 - _Matrix4x4.m00 * _Matrix4x4.m13 * _Matrix4x4.m22 * _Matrix4x4.m31 -
				_Matrix4x4.m02 * _Matrix4x4.m10 * _Matrix4x4.m23 * _Matrix4x4.m31 + _Matrix4x4.m00 * _Matrix4x4.m12 * _Matrix4x4.m23 * _Matrix4x4.m31 +
				_Matrix4x4.m03 * _Matrix4x4.m11 * _Matrix4x4.m20 * _Matrix4x4.m32 - _Matrix4x4.m01 * _Matrix4x4.m13 * _Matrix4x4.m20 * _Matrix4x4.m32 -
				_Matrix4x4.m03 * _Matrix4x4.m10 * _Matrix4x4.m21 * _Matrix4x4.m32 + _Matrix4x4.m00 * _Matrix4x4.m13 * _Matrix4x4.m21 * _Matrix4x4.m32 +
				_Matrix4x4.m01 * _Matrix4x4.m10 * _Matrix4x4.m23 * _Matrix4x4.m32 - _Matrix4x4.m00 * _Matrix4x4.m11 * _Matrix4x4.m23 * _Matrix4x4.m32 -
				_Matrix4x4.m02 * _Matrix4x4.m11 * _Matrix4x4.m20 * _Matrix4x4.m33 + _Matrix4x4.m01 * _Matrix4x4.m12 * _Matrix4x4.m20 * _Matrix4x4.m33 +
				_Matrix4x4.m02 * _Matrix4x4.m10 * _Matrix4x4.m21 * _Matrix4x4.m33 - _Matrix4x4.m00 * _Matrix4x4.m12 * _Matrix4x4.m21 * _Matrix4x4.m33 -
				_Matrix4x4.m01 * _Matrix4x4.m10 * _Matrix4x4.m22 * _Matrix4x4.m33 + _Matrix4x4.m00 * _Matrix4x4.m11 * _Matrix4x4.m22 * _Matrix4x4.m33;
		}

		static omMatrix4D LookAtLH(omVector3D _Eye, omVector3D _Focus, omVector3D _Up)
		{
			//Direccion, que es una linea de ti al objeto, no esta perpendicular al vector y de vista
			omVector3D vDir, vRight, vUp, vOffset;
			vDir = _Focus - _Eye;
			Normalize(vDir);

			//Perpendicularizar el vector vista hacia up y vista
			vRight = CrossProduct(_Up, vDir);
			Normalize(vRight);

			//Con esto, el productro cruz con derecha y arriva me da el nuevo vector arriva, que es perpendicular al vector que esta hacia el objeto
			vUp = CrossProduct(vDir,vRight);

			//Esta ultima transformacion terminara convirtiendo los objetos a mi origen, suponiendo que yo soy el origen
			vOffset = omVector4D(
				-DotProduct(vRight,_Eye), //Esta en sentido contrario porque queremos que se conviertan hacia la camara, no al revez
				-DotProduct(vUp,_Eye),
				-DotProduct(vDir,_Eye),
				0);
			
			omMatrix4D MV;
			MV.m00 = vRight.X;
			MV.m10 = vRight.Y;
			MV.m20 = vRight.Z;
			MV.m30 = vOffset.X;
			  
			MV.m01 = vUp.X;
			MV.m11 = vUp.Y;
			MV.m21 = vUp.Z;
			MV.m31 = vOffset.Y;
			  
			MV.m02 = vDir.X;
			MV.m12 = vDir.Y;
			MV.m22 = vDir.Z;
			MV.m32 = vOffset.Z;
			  
			MV.m03 = 0;
			MV.m13 = 0;
			MV.m23 = 0;
			MV.m33 = 1;

			return MV;
		}

		static omMatrix4D PerspectiveFovLH(float _FovAngleY, float _AspectRatio, float _NearZ, float _FarZ)
		{
			//Vamos a comprimir, entre mas sea el angulo, metemos mas geometria a la pantalla
			omMatrix4D MP;

			//Cotagente
			float h = 1.0f / Tan(_FovAngleY / 2);
			float w = h / _AspectRatio;

			MP.m00 = w;
			MP.m11 = h;
			MP.m22 = _FarZ / (_FarZ - _NearZ);
			MP.m32 = -_NearZ * _FarZ / (_FarZ - _NearZ);
			MP.m23 = 1;

			return MP;
		}

	};

#if PLATFORM != WINDOWS_MATH
	typedef omPlatformMath Math;
#endif
}
