//////////////////////////////////////////////////////////////////////////
///																		//
// @file   omDegrees.h													//	
// @Author Raul Portillo (ruulaasz_@hotmail.com)						//
// @date   2015/22/09													//
// @brief  Class for degree type data									//
// @bug	   No known bugs.												//
//																		//
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Omicron_PlatformMath.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Definicion de la clase omDegrees																						//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace OmicronSDK
{
	class omRadians;

	class omDegrees
	{
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Declaracion de contructores y destructor																				//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public:
		explicit omDegrees(float _value=0.f);	//<constructor para crear un objeto con valores>//
		omDegrees(const omDegrees& _Obj);		//<constructor para crear un objeto copia>//
		omDegrees(omRadians* _Rad);
		~omDegrees();

		float GetRadians() const;				//<transforma de grados a radianes>//
		float GetDegrees() const;				//<transforma de radianes a grados>//
		float Unwind() const;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Definicion de la Sobrecarga de operadores =,+,-,+=,-=																//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		omDegrees& operator= (const omDegrees& _degrees);
		omDegrees& operator= (const omRadians& _radians);
		omDegrees& operator= (float _value);

		omDegrees operator+ (const omDegrees& _degrees);
		omDegrees operator+ (const omRadians& _radians);

		omDegrees operator- (const omDegrees& _degrees);
		omDegrees operator- (const omRadians& _radians);

		omDegrees& operator+= (const omDegrees& _degrees);
		omDegrees& operator+= (const omRadians& _radians);

		omDegrees& operator-= (const omDegrees& _degrees);
		omDegrees& operator-= (const omRadians& _radians);

		bool operator==(const omDegrees& _degrees);
		bool operator==(const omRadians& _radians);

		bool operator!=(const omDegrees& _degrees);
		bool operator!=(const omRadians& _radians);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Declaracion de variables miembro de la clase																			//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	protected:
		float m_fDegrees;		//<variable que guarda el grado>//
	};
}

