//////////////////////////////////////////////////////////////////////////
///																		//
// @file   omColor.cpp													//	
// @Author Raul Portillo (ruulaasz_@hotmail.com)						//
// @date   2015/10/10													//
// @brief Definition of the omColor class								//
// @bug	   Not Fully Tested												//
//																		//
//////////////////////////////////////////////////////////////////////////
#include "omColor.h"

namespace OmicronSDK
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Definicion de contructores y destructor																				//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omColorRGBA::omColorRGBA(short _r, short _g, short _b, short _a)
	{																	//< Constructor que pide los valores de color del pixel predeterminado>//
		m_Pixel.r = (unsigned char)_r;
		m_Pixel.g = (unsigned char) _g;
		m_Pixel.b = (unsigned char) _b;
		m_Pixel.a = (unsigned char) _a;
	}

	omColorRGBA::omColorRGBA(const omColorRGBA& _CopyObj)
	{																	//< Constructor que crea un objeto copia del objeto recibido>//
		m_Pixel = _CopyObj.m_Pixel;
	}

	omColorRGBA::~omColorRGBA()
	{

	}
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Declaracion de la Sobrecarga de operadores =,+,-,+=,-=																//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omColorRGBA& omColorRGBA::operator = (const omColorRGBA& _Color)
	{
		m_Pixel = _Color.m_Pixel;
		return *this;
	}

	omColorRGBA& omColorRGBA::operator = (const Pixel& _Pixel)
	{
		m_Pixel = _Pixel;
		return *this;
	}

	omColorRGBA& omColorRGBA::operator = (unsigned int _Value)
	{
		m_Pixel.l = _Value;
		return *this;
	}

	omColorRGBA omColorRGBA::operator + (const omColorRGBA& _Color)
	{
		return omColorRGBA(m_Pixel.r + _Color.m_Pixel.r, m_Pixel.g + _Color.m_Pixel.g, m_Pixel.b + _Color.m_Pixel.b, m_Pixel.a + _Color.m_Pixel.a);
	}

	omColorRGBA omColorRGBA::operator - (const omColorRGBA& _Color)
	{
		return omColorRGBA(m_Pixel.r - _Color.m_Pixel.r, m_Pixel.g - _Color.m_Pixel.g, m_Pixel.b - _Color.m_Pixel.b, m_Pixel.a - _Color.m_Pixel.a);
	}

	omColorRGBA& omColorRGBA::operator += (const omColorRGBA& _Color)
	{
		m_Pixel.r += _Color.m_Pixel.r;
		m_Pixel.g += _Color.m_Pixel.g; 
		m_Pixel.b += _Color.m_Pixel.b;
		m_Pixel.a += _Color.m_Pixel.a;

		return *this;
	}

	omColorRGBA& omColorRGBA::operator -= (const omColorRGBA& _Color)
	{
		m_Pixel.r -= _Color.m_Pixel.r;
		m_Pixel.g -= _Color.m_Pixel.g;
		m_Pixel.b -= _Color.m_Pixel.b;
		m_Pixel.a -= _Color.m_Pixel.a;

		return *this;
	}

	bool omColorRGBA::operator == (const omColorRGBA& _Color)
	{
		return (m_Pixel.l == _Color.m_Pixel.l ? true : false);
	}

	bool omColorRGBA::operator != (const omColorRGBA& _Color)
	{
		return (m_Pixel.l != _Color.m_Pixel.l ? false : true);
	}
}