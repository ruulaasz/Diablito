//////////////////////////////////////////////////////////////////////////
///																		//
// @file   omVector4D.h													//	
// @Author Raul Portillo (ruulaasz_@hotmail.com)						//
// @date   2015/17/10													//
// @brief  Class for vector4D type structure							//
// @bug	   No known bugs.												//
//																		//
//////////////////////////////////////////////////////////////////////////
#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Declaracion de la clase omVector4D																					//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace OmicronSDK
{
	class omMatrix4D;
	class omVector3D;

	class omVector4D
	{
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Declaracion de contructores y destructor																				//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public:
		explicit omVector4D(float _X = 0.f, float _Y = 0.f, float _Z = 0.f, float _W = 0.0f): X(_X), Y(_Y), Z(_Z), W(_W){};
		omVector4D(omVector4D& _vector);
		omVector4D(omMatrix4D& _Matrix4x4);
		omVector4D(omVector3D& _vector);
		~omVector4D();

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Declaracion de variables miembro de la clase																			//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		float X;	//<Elemento X del vector>//
		float Y;	//<Elemento Y del vector>//
		float Z;	//<Elemento Z del vector>//
		float W;	//<Elemento W del vector>//

		/*static omVector4D Rotate(omVector4D _vector,omDegrees &_Angle, unsigned char _Axis)
		{
			omMatrix4D RotationMatrix;

			RotationMatrix = omMatrix4D::RotationMatrix4x4(_Angle.GetRadians(), (eRotationAxis4D)_Axis);

			return _vector*RotationMatrix;
		}*/

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Sobrecarga de Operadores																								//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		omVector4D operator- (const omVector4D& _vector);
		omVector4D operator+ (const omVector4D& _vector);
		omVector4D operator* (const omVector4D& _vector);
		omVector4D& operator+= (const omVector4D& _vector);
		omVector4D& operator-= (const omVector4D& _vector);
		omVector4D& operator*= (const omVector4D& _vector);
		bool operator== (const omVector4D& _vector);
		bool operator!= (const omVector4D& _vector);

		omVector4D& operator=(const omVector3D& _vector);
		omVector4D& operator=(const omVector4D& _vector);

		omVector4D operator* (const float& _value);
		omVector4D operator*(const omMatrix4D & _Matrix4x4);
		omVector4D& operator=(const omMatrix4D& _Matrix4x4);

		float& operator[](const int idx);
	};

}
