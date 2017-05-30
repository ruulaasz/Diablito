//////////////////////////////////////////////////////////////////////////
///																		//
// @file   omRadians.h													//	
// @Author Raul Portillo (ruulaasz_@hotmail.com)						//
// @date   2015/22/09													//
// @brief  Class for radian type data									//
// @bug	   No known bugs.												//
//																		//
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Omicron_PlatformMath.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Definicion de la clase omRadians																						//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace OmicronSDK
{
	class omDegrees;

	class omRadians
	{
	public:
		explicit omRadians(float _value=0.f);//<constructor para crear un objeto con valores>//
		omRadians(const omRadians& _Obj);//<constructor para crear un objeto copia>//
		omRadians(const omDegrees& _Obj);
		~omRadians();

		float GetRadians() const;//<transforma de grados a radianes>//
		float GetDegrees() const;//<transforma de radianes a grados>//
		float Unwind() const;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Definicion de la Sobrecarga de operadores =,+,-,+=,-=																//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		omRadians& operator= (const omDegrees& _degrees);
		omRadians& operator= (const omRadians& _radians);
		omRadians& operator= (float _value);

		omRadians operator+ (const omDegrees& _degrees);
		omRadians operator+ (const omRadians& _radians);

		omRadians operator- (const omDegrees& _degrees);
		omRadians operator- (const omRadians& _radians);

		omRadians& operator+= (const omDegrees& _degrees);
		omRadians& operator+= (const omRadians& _radians);

		omRadians& operator-= (const omDegrees& _degrees);
		omRadians& operator-= (const omRadians& _radians);

		bool operator==(const omDegrees& _degrees);
		bool operator==(const omRadians& _radians);

		bool operator!=(const omDegrees& _degrees);
		bool operator!=(const omRadians& _radians);

	protected:
			float m_fRadians;//<variable que guarda el radian>//
	};
}

