//////////////////////////////////////////////////////////////////////////
///																		//
// @file   omPlane.cpp													//	
// @Author Raul Portillo (ruulaasz_@hotmail.com)						//
// @date   2015/10/10													//
// @brief  Definition of the omPlane class								//
// @bug	   No known bugs.												//
//																		//
//////////////////////////////////////////////////////////////////////////
#if PLATFORM == WINDOWS_MATH
#include "Omicron_WindowsMath.h"  /*!< Funciones matematicas basicas optimisadas para Windows */
#endif
#include "Omicron_PlatformMath.h"

#include "omPlane.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Definicion de la clase omPlane																						//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace OmicronSDK
{
	omPlane::omPlane()
	{
	}

	omPlane::omPlane(omVector3D _Normal, omVector3D _Point)
	{
		m_vecNormal = _Normal;
		m_vecPoint = _Point;
		m_W = Math::Length(m_vecPoint);
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Definicion de contructores y destructor																				//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omPlane::omPlane(const omPlane& _plane)
	{
		m_vecPoint = _plane.m_vecPoint;
		m_vecNormal.X = _plane.m_vecNormal.X;
		m_vecNormal.Y = _plane.m_vecNormal.Y;
		m_vecNormal.Z = _plane.m_vecNormal.Z;
		m_W = _plane.m_W;
	}

	omPlane::~omPlane()
	{

	}

	void omPlane::SetNormalAndPoint(omVector3D _Normal, omVector3D _Point)
	{
		m_vecNormal = _Normal;
		m_vecPoint = _Point;

		m_W = Math::Length(m_vecPoint);
	}

	void omPlane::SetNormalAndPoint(omVector4D _Normal, omVector4D _Point)
	{
		m_vecNormal = _Normal;
		m_vecPoint = _Point;

		m_W = Math::Length(m_vecPoint);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Sobrecarga de Operadores																								//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omPlane& omPlane::operator= (const omPlane& _plane)
	{
		m_vecNormal = _plane.m_vecNormal;
		m_vecPoint = _plane.m_vecPoint;
		m_W = _plane.m_W;

		return *this;
	}

	omPlane& omPlane::operator+= (const omPlane& _plane)
	{
		m_vecNormal += _plane.m_vecNormal;
		m_vecPoint += _plane.m_vecPoint;
		m_W += _plane.m_W;

		return *this;
	}

	omPlane& omPlane::operator-= (const omPlane& _plane)
	{
		m_vecNormal -= _plane.m_vecNormal;
		m_vecPoint -= _plane.m_vecPoint;
		m_W -= _plane.m_W;

		return *this;
	}
	
	omPlane omPlane::operator+ (const omPlane& _plane)
	{
		return omPlane(m_vecNormal + _plane.m_vecNormal, m_vecPoint + _plane.m_vecPoint);
	}

	omPlane omPlane::operator- (const omPlane& _plane)
	{
		return omPlane(m_vecNormal - _plane.m_vecNormal, m_vecPoint - _plane.m_vecPoint);
	}

	bool omPlane::operator== (const omPlane& _plane)
	{
		if (m_vecNormal != _plane.m_vecNormal) return false;
		if (m_vecPoint != _plane.m_vecPoint)return false;
		if (m_W != _plane.m_W)return false;

		return true;
	}

	bool omPlane::operator!= (const omPlane& _plane)
	{
		if (m_vecNormal != _plane.m_vecNormal) return true;
		if (m_vecPoint != _plane.m_vecPoint)return true;
		if (m_W != _plane.m_W)return true;
		return false;
	}
}
