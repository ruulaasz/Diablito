//////////////////////////////////////////////////////////////////////////
///																		//
// @file   omRadians.h													//	
// @Author Raul Portillo (ruulaasz_@hotmail.com)						//
// @date   2015/22/09													//
// @brief  Definition of omRadian Class									//
// @bug	   No known bugs.												//
//																		//
//////////////////////////////////////////////////////////////////////////
#include "omDegrees.h"
#include "omRadians.h"

namespace OmicronSDK
{
	omRadians::~omRadians()
	{

	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Definicion de los diferentes constructores																			//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omRadians::omRadians(float _value)
	{
		m_fRadians = _value;
	}

	omRadians::omRadians(const omRadians& _Obj)
	{
		m_fRadians = _Obj.GetRadians();
	}

	omRadians::omRadians(const omDegrees& _Obj)
	{
		m_fRadians = _Obj.GetRadians();
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Sobrecarga de operador =																								//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omRadians& omRadians::operator= (const omDegrees& _degrees)
	{
		m_fRadians = _degrees.GetRadians();
		return *this;
	}

	omRadians&  omRadians::operator= (const omRadians& _radians)
	{
		m_fRadians = _radians.GetRadians();
		return *this;
	}

	omRadians& omRadians::operator= (float _value)
	{
		m_fRadians = _value;
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Sobrecarga de operador +																								//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omRadians omRadians::operator+ (const omDegrees& _degrees)
	{
		return omRadians(m_fRadians + _degrees.GetRadians());
	}

	omRadians  omRadians::operator+ (const omRadians& _radians)
	{
		return omRadians(m_fRadians + _radians.GetRadians());
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Sobrecarga de operador -																								//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omRadians omRadians::operator- (const omDegrees& _degrees)
	{
		return omRadians(m_fRadians - _degrees.GetRadians());
	}

	omRadians  omRadians::operator- (const omRadians& _radians)
	{
		return omRadians(m_fRadians - _radians.GetRadians());
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Sobrecarga de operador +=																								//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omRadians& omRadians::operator+= (const omDegrees& _degrees)
	{
		m_fRadians += _degrees.GetRadians();
		return *this;
	}

	omRadians&  omRadians::operator+= (const omRadians& _radians)
	{
		m_fRadians += _radians.GetRadians();
		return *this;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Sobrecarga de operador -=																							//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omRadians& omRadians::operator-= (const omDegrees& _degrees)
	{
		m_fRadians -= _degrees.GetRadians();
		return *this;
	}

	omRadians&  omRadians::operator-= (const omRadians& _radians)
	{
		m_fRadians -= _radians.GetRadians();
		return *this;
	}

	bool omRadians::operator==(const omDegrees & _degrees)
	{
		if (m_fRadians == _degrees.GetRadians())
			return true;

		return false;
	}

	bool omRadians::operator==(const omRadians & _radians)
	{
		if (m_fRadians == _radians.m_fRadians)
			return true;

		return false;
	}

	bool omRadians::operator!=(const omDegrees & _degrees)
	{
		if (!m_fRadians == _degrees.GetRadians())
			return true;

		return false;
	}

	bool omRadians::operator!=(const omRadians & _radians)
	{
		if (!m_fRadians == _radians.m_fRadians)
			return true;

		return false;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Definicion de las funciones de la clase																				//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	float omRadians::GetRadians() const
	{
		return m_fRadians;
	}

	float omRadians::GetDegrees() const
	{
		return m_fRadians*PlatformMath::RAD_TO_DEG;
	}

	float omRadians::Unwind() const
	{
		float _loops = m_fRadians / PlatformMath::PI2;

		if (_loops <= PlatformMath::PI2)
			return m_fRadians;

		_loops -= (int) _loops;

		return PlatformMath::PI2 * _loops;
	}
}