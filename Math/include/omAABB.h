//////////////////////////////////////////////////////////////////////////
///																		//
// @file   omAABB.h														//	
// @Author Raul Portillo (ruulaasz_@hotmail.com)						//
// @date   2015/10/10													//
// @brief  Class for a aabb geometry type structure						//
// @bug	   No known bugs.   											//
//																		//
//////////////////////////////////////////////////////////////////////////
#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Declaracion de la clase omAABB																						//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace OmicronSDK
{
	class omVector3D;

	class omAABB
	{
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Declaracion de contructores y destructores																			//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public:
		omAABB();
		omAABB( omVector3D& _center ,  omVector3D& _dimentions);
		omAABB(const omAABB& _aabb);
		~omAABB();

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Declaracion de variables miembro de la clase																			//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		omVector3D m_vecCenter;			//<centro de la caja>//
		omVector3D m_vecDimentions;		//<Distancias del centro hacia las orillas de la caja>//
		omVector3D m_Min;
		omVector3D m_Max;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Declaracion de la Sobrecarga de operadores =,+,-,+=,-=,==,!= 														//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		omAABB& operator= (const omAABB& _aabb);
		omAABB& operator+= (const omAABB& _aabb);
		omAABB& operator-= (const omAABB& _aabb);

		omAABB operator+ (const omAABB& _aabb);
		omAABB operator- (const omAABB& _aabb);

		bool operator == (const omAABB& _aabb);
		bool operator != (const omAABB& _aabb);
	};
}