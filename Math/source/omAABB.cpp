//////////////////////////////////////////////////////////////////////////
///																		//
// @file   omAABB.cpp													//	
// @Author Raul Portillo (ruulaasz_@hotmail.com)						//
// @date   2015/10/10													//
// @brief  Definition of the omAABB class								//
// @bug	   Not Fully Tested												//
//																		//
//////////////////////////////////////////////////////////////////////////
#if PLATFORM == WINDOWS_MATH
#include "Omicron_WindowsMath.h"  /*!< Funciones matematicas basicas optimisadas para Windows */
#endif
#include "Omicron_PlatformMath.h"

#include "omAABB.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Definicion de la clase omAABB																						//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace OmicronSDK
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Definicion de contructores y destructores																			//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omAABB::omAABB()
	{
		Math::ClearVector(m_vecCenter);
		Math::ClearVector(m_vecDimentions);
		Math::ClearVector(m_Min);
		Math::ClearVector(m_Max);
	}

	omAABB::omAABB(omVector3D & _center, omVector3D & _dimentions)
	{
		m_vecCenter = _center;
		m_vecDimentions = _dimentions;
		m_Min = m_vecCenter - m_vecDimentions;
		m_Max= m_vecCenter + m_vecDimentions;
	}

	omAABB::omAABB(const omAABB& _aabb)
	{
		*this = _aabb;
	}

	omAABB::~omAABB()
	{

	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Sobrecarga de Operadores																								//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omAABB& omAABB::operator= (const omAABB& _aabb)
	{
		m_vecCenter = _aabb.m_vecCenter;
		m_vecDimentions = _aabb.m_vecDimentions;
		m_Min = _aabb.m_Min;
		m_Max = _aabb.m_Max;

		return *this;
	}

	omAABB& omAABB::operator+= (const omAABB& _aabb)
	{
		m_vecCenter += _aabb.m_vecCenter;
		m_vecDimentions += _aabb.m_vecDimentions;
		m_Min += _aabb.m_Min;
		m_Max += _aabb.m_Max;

		return *this;
	}

	omAABB& omAABB::operator-= (const omAABB& _aabb)
	{
		m_vecCenter -= _aabb.m_vecCenter;
		m_vecDimentions -= _aabb.m_vecDimentions;
		m_Min -= _aabb.m_Min;
		m_Max -= _aabb.m_Max;

		return *this;
	}

	omAABB omAABB::operator+ (const omAABB& _aabb)
	{
		omAABB Temp;

		Temp.m_vecCenter = m_vecCenter + _aabb.m_vecCenter;
		Temp.m_vecDimentions = m_vecDimentions + _aabb.m_vecDimentions;
		Temp.m_Max = m_Max + _aabb.m_Max;
		Temp.m_Min = m_Min + _aabb.m_Min;

		return Temp;
	}

	omAABB omAABB::operator- (const omAABB& _aabb)
	{
		omAABB Temp;

		Temp.m_vecCenter = m_vecCenter - _aabb.m_vecCenter;
		Temp.m_vecDimentions = m_vecDimentions - _aabb.m_vecDimentions;
		Temp.m_Max = m_Max - _aabb.m_Max;
		Temp.m_Min = m_Min - _aabb.m_Min;

		return Temp;
	}

	bool omAABB::operator== (const omAABB& _aabb)
	{
		if (m_vecCenter != _aabb.m_vecCenter) return false;
		if (m_vecDimentions != _aabb.m_vecDimentions)return false;

		return true;
	}

	bool omAABB::operator!= (const omAABB& _aabb)
	{
		if (m_vecCenter != _aabb.m_vecCenter) return true;
		if (m_vecDimentions != _aabb.m_vecDimentions)return true;

		return false;
	}
}
