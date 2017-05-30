//////////////////////////////////////////////////////////////////////////
///																		//
// @file   omVector2D.h													//	
// @Author Raul Portillo (ruulaasz_@hotmail.com)						//
// @date   2015/17/10													//
// @brief  Class for a vector2D type structure							//
// @bug	   No known bugs.												//
//																		//
//////////////////////////////////////////////////////////////////////////
#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Declaracion de la clase omVector2D																					//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace OmicronSDK
{
	class omVector2D
	{
	public:
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Declaracion de contructores y destructor																				//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		omVector2D(omVector2D& _vector);
		explicit omVector2D(float _x = 0, float _y = 0);
		~omVector2D();

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Declaracion de variables miembro de la clase																			//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		float X;		//<Componente X del vector>//
		float Y;		//<Componente Y del vector>//

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Declaracion de funciones de la clase																					//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		static omVector2D Rotate(const omVector2D& _vector,const float _radians)
		{
			float xt = (_vector.X * Math::Cos(_radians)) - (_vector.Y * Math::Sin(_radians));
			float yt = (_vector.Y * Math::Cos(_radians)) + (_vector.X * Math::Sin(_radians));

			return omVector2D(xt, yt);
		}

		static float Length(const omVector2D& _vector)
		{
			return Math::Sqrt((_vector.X *_vector.X) + (_vector.Y *_vector.Y));
		}

		static float SquareLenght(const omVector2D& _vector)
		{
			return _vector.X *_vector.X + _vector.Y *_vector.Y;
		}

		static omVector2D Normalize(const omVector2D& _vector)
		{
			float mag = Length(_vector);

			return omVector2D(_vector.X / mag, _vector.Y / mag);
		}

		static float DotProduct(const omVector2D& _vector, const omVector2D& _vector2)
		{
			return (_vector.X * _vector2.X) + (_vector.Y * _vector2.Y);
		}

		static omVector2D Escalate(const omVector2D& _vector, const float _scalar)
		{
			omVector2D norm = Normalize(_vector);

			return omVector2D(norm.X * _scalar, norm.Y * _scalar);
		}

		static omVector2D Truncate(omVector2D _vector,const float _max)
		{
			float mag = Length(_vector);

			if (mag > _max)
			{
				return Escalate(_vector, _max);
			}

			return _vector;
		}

		static float getAngle(const omVector2D& _vector)
		{
			return (Math::ArcTan(_vector.Y / _vector.X));
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Sobrecarga de Operadores																								//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		omVector2D operator+(const omVector2D& _vector);

		omVector2D operator+=(const omVector2D& _vector);

		omVector2D operator-(const omVector2D& _vector);

		omVector2D operator-=(const omVector2D& _vector);

		omVector2D operator*(float _scalar);

		float operator*(const omVector2D& _vector);

		omVector2D operator*=(const omVector2D& _vector);

		bool operator ==(const omVector2D& _vector);

		bool operator !=(const omVector2D& _vector);
	};
}

