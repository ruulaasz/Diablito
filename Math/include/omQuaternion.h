///////////////////////////////////////////////////////////////////////////
///																		//
// @file   omQuaternion.h												//	
// @Author Raul Portillo (ruulaasz_@hotmail.com)						//
// @date   2015/18/10													//
// @brief  Class for omQuaternion type structure							//
// @bug	   No known bugs.												//
//																		//
//////////////////////////////////////////////////////////////////////////
#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Declaracion de la clase omQuaternion																					//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace OmicronSDK
{
	class omVector3D;
	class omMatrix3D;
	class omMatrix4D;
	class omDegrees;

	enum EulerAngleOrder
	{
		xyz,
		xzy,
		yxz,
		yzx,
		zxy,
		zyx
	};

	class omQuaternion
	{
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Declaracion de contructores y destructor																				//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public:
		omQuaternion(omQuaternion* _H);
		explicit omQuaternion(float _x = 0, float _y = 0, float _z=0, float _w=0) : x(_x), y(_y), z(_z), w(_w) {};
		omQuaternion(omMatrix4D* _Matrix);
		omQuaternion(omVector3D _Axis, omDegrees _Angle);
		omQuaternion(omDegrees _AngleX, omDegrees _AngleY, omDegrees _AngleZ);
		omQuaternion(omDegrees _AngleX, omDegrees _AngleY, omDegrees _AngleZ, EulerAngleOrder _Order);

		~omQuaternion();

		float x, y, z, w;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Declaracion de funciones de la clase																					//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		omQuaternion Normalize(omQuaternion* _H);
		omMatrix4D ToMatrix4D(omQuaternion* _H);
		omMatrix3D ToMatrix3D(omQuaternion* _H);
		omQuaternion FromMatrix(omMatrix4D* _Mat);
		omQuaternion Lerp(omQuaternion* _H,omQuaternion* _H2, float _Time);
		omQuaternion Slerp(omQuaternion* _H, omQuaternion* _H2, float _Time, float _Threshold);
		float DotProduct(omQuaternion* _H, omQuaternion* _H2);
		void ResetQuaternion(omQuaternion& _H);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Sobrecarga de Operadores																								//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		omQuaternion operator* (const omQuaternion& _H);
		omQuaternion operator* (const float _value);
		omQuaternion operator*=(const float _value);
		omQuaternion operator+(const omQuaternion& _H);
		bool operator==(const omQuaternion& _H);
		bool operator!=(const omQuaternion& _H);
		omQuaternion& operator=(omQuaternion& _H);
		omQuaternion& operator=(omMatrix4D& _Matrix);
	};
}
