//////////////////////////////////////////////////////////////////////////
///																		//
// @file   omRay.cpp													//	
// @Author Raul Portillo (ruulaasz_@hotmail.com)						//
// @date   2015/10/10													//
// @brief  Definition of the omRay class								//
// @bug	   No known bugs.												//
//																		//
//////////////////////////////////////////////////////////////////////////
#include "omRay.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Definicion de la clase omRay																							//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace OmicronSDK
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Definicion de contructores y destructor																				//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omRay::omRay(const omRay& _ray)
	{
		m_vecOrigin = _ray.m_vecOrigin;
		m_vecDirection = _ray.m_vecDirection;
	}

	omRay::~omRay()
	{

	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Sobrecarga de Operadores																								//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omRay& omRay::operator= (const omRay& _ray)
	{
		m_vecDirection = _ray.m_vecDirection;
		m_vecOrigin = _ray.m_vecOrigin;

		return *this;
	}

	omRay& omRay::operator+= (const omRay& _ray)
	{
		m_vecDirection += _ray.m_vecDirection;
		m_vecOrigin += _ray.m_vecOrigin;

		return *this;
	}

	omRay& omRay::operator-= (const omRay& _ray)
	{
		m_vecDirection -= _ray.m_vecDirection;
		m_vecOrigin -= _ray.m_vecOrigin;

		return *this;
	}

	omRay omRay::operator+ (const omRay& _ray)
	{
		return omRay(m_vecDirection + _ray.m_vecDirection, m_vecOrigin + _ray.m_vecOrigin);
	}

	omRay omRay::operator- (const omRay& _ray)
	{
		return omRay(m_vecDirection - _ray.m_vecDirection, m_vecOrigin - _ray.m_vecOrigin);
	}

	bool omRay::operator== (const omRay& _ray)
	{
		if (m_vecDirection != _ray.m_vecDirection) return false;
		if (m_vecOrigin != _ray.m_vecOrigin)return false;

		return true;
	}

	bool omRay::operator!= (const omRay& _ray)
	{
		if (m_vecDirection != _ray.m_vecDirection) return true;
		if (m_vecOrigin != _ray.m_vecOrigin)return true;

		return false;
	}
}
