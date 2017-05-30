//////////////////////////////////////////////////////////////////////////
///																		//
// @file   omDegrees.cpp												//	
// @Author Raul Portillo (ruulaasz_@hotmail.com)						//
// @date   2015/22/09													//
// @brief  Definition of omDegree Class									//
// @bug	   No known bugs.												//
//																		//
//////////////////////////////////////////////////////////////////////////
#include "omRadians.h"
#include "omDegrees.h"

namespace OmicronSDK
{
	omDegrees::~omDegrees()
	{

	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Definicion de los diferentes constructores																			//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omDegrees::omDegrees(float _value)
	{
		m_fDegrees = _value;
	}

	omDegrees::omDegrees(const omDegrees& _Obj)
	{
		m_fDegrees = _Obj.GetDegrees();
	}

	omDegrees::omDegrees(omRadians* _Rad)
	{
		m_fDegrees = _Rad->GetDegrees();
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Sobrecarga de operador =																								//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omDegrees& omDegrees::operator= (const omDegrees& _degrees)
	{
		m_fDegrees = _degrees.GetDegrees();
		return *this;
	}

	omDegrees&  omDegrees::operator= (const omRadians& _radians)
	{
		m_fDegrees = _radians.GetDegrees();
		return *this;
	}

	omDegrees& omDegrees::operator= (float _value)
	{
		m_fDegrees = _value;
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Sobrecarga de operador +																								//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omDegrees omDegrees::operator+ (const omDegrees& _degrees)
	{
		return omDegrees(m_fDegrees + _degrees.GetDegrees());
	}

	omDegrees  omDegrees::operator+ (const omRadians& _radians)
	{
		return omDegrees(m_fDegrees + _radians.GetDegrees());
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Sobrecarga de operador -																								//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omDegrees omDegrees::operator- (const omDegrees& _degrees)
	{
		return omDegrees(m_fDegrees - _degrees.GetDegrees());
	}

	omDegrees  omDegrees::operator- (const omRadians& _radians)
	{
		return omDegrees(m_fDegrees - _radians.GetDegrees());
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Sobrecarga de operador +=																								//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omDegrees& omDegrees::operator+= (const omDegrees& _degrees)
	{
		m_fDegrees += _degrees.GetDegrees();
		return *this;
	}

	omDegrees&  omDegrees::operator+= (const omRadians& _radians)
	{
		m_fDegrees += _radians.GetDegrees();
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Sobrecarga de operador -=																							//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omDegrees& omDegrees::operator-= (const omDegrees& _degrees)
	{
		m_fDegrees -= _degrees.GetDegrees();
		return *this;
	}

	omDegrees&  omDegrees::operator-= (const omRadians& _radians)
	{
		m_fDegrees -= _radians.GetDegrees();
		return *this;
	}

	bool omDegrees::operator==(const omDegrees & _degrees)
	{
		if (m_fDegrees == _degrees.m_fDegrees)
			return true;

		return false;
	}

	bool omDegrees::operator==(const omRadians & _radians)
	{
		if (m_fDegrees == _radians.GetDegrees())
			return true;

		return false;
	}

	bool omDegrees::operator!=(const omDegrees & _degrees)
	{
		if (!m_fDegrees == _degrees.m_fDegrees)
			return true;

		return false;
	}

	bool omDegrees::operator!=(const omRadians & _radians)
	{
		if (!m_fDegrees == _radians.GetDegrees())
			return true;

		return false;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Definicion de las funciones de la clase																				//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	float omDegrees::GetRadians() const
	{
		return m_fDegrees*PlatformMath::DEG_TO_RAD;
	}

	float omDegrees::GetDegrees() const
	{
		return m_fDegrees;
	}

	float omDegrees::Unwind() const
	{
		float _loops=m_fDegrees/360.f;

		if (_loops <= 1.f)
			return m_fDegrees;

		_loops-=(int)_loops;

		return 360 * _loops;
	}
}