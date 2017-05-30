//////////////////////////////////////////////////////////////////////////
///																		//
// @file   omSpehre.cpp													//	
// @Author Raul Portillo (ruulaasz_@hotmail.com)						//
// @date   2015/10/10													//
// @brief  Definition of the omSphere class								//
// @bug	   No known bugs.												//
//																		//
//////////////////////////////////////////////////////////////////////////
#include "omSphere.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Definicion de la clase omSphere																						//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace OmicronSDK
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Definicion de contructores y destructor																				//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omSphere::omSphere(const omSphere& _sphere)
	{
		m_fRadius = _sphere.m_fRadius;
		m_vecCenter.X = _sphere.m_vecCenter.X;
		m_vecCenter.Y = _sphere.m_vecCenter.Y;
		m_vecCenter.Z = _sphere.m_vecCenter.Z;
	}

	omSphere::~omSphere()
	{

	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Sobrecarga de Operadores																								//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omSphere& omSphere::operator= (const omSphere& _sphere)
	{
		m_vecCenter = _sphere.m_vecCenter;
		m_fRadius = _sphere.m_fRadius;

		return *this;
	}

	omSphere& omSphere::operator+= (const omSphere& _sphere)
	{
		m_vecCenter += _sphere.m_vecCenter;
		m_fRadius += _sphere.m_fRadius;

		return *this;
	}

	omSphere& omSphere::operator-= (const omSphere& _sphere)
	{
		m_vecCenter -= _sphere.m_vecCenter;
		m_fRadius -= _sphere.m_fRadius;

		return *this;
	}

	omSphere omSphere::operator+ (const omSphere& _sphere)
	{
		return omSphere((m_vecCenter + _sphere.m_vecCenter), (m_fRadius + _sphere.m_fRadius));
	}

	omSphere omSphere::operator- (const omSphere& _sphere)
	{
		return omSphere((m_vecCenter - _sphere.m_vecCenter), (m_fRadius - _sphere.m_fRadius));
	}

	bool omSphere::operator== (const omSphere& _sphere)
	{
		if (m_vecCenter != _sphere.m_vecCenter) return false;
		if (m_fRadius != _sphere.m_fRadius)return false;

		return true;
	}

	bool omSphere::operator!= (const omSphere& _sphere)
	{
		if (m_vecCenter != _sphere.m_vecCenter) return true;
		if (m_fRadius != _sphere.m_fRadius)return true;

		return false;
	}
}

