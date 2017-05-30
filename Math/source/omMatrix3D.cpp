//////////////////////////////////////////////////////////////////////////
///																		//
// @file   omMatrix3D.cpp												//	
// @Author Raul Portillo (ruulaasz_@hotmail.com)						//
// @date   2015/17/10													//
// @brief  Definition of omMatrix3D Class 								//
// @bug	   No known bugs.												//
//																		//
//////////////////////////////////////////////////////////////////////////
#if PLATFORM == WINDOWS_MATH
#include "Omicron_WindowsMath.h"  /*!< Funciones matematicas basicas optimisadas para Windows */
#endif
#include "Omicron_PlatformMath.h"
#include <memory>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Definicion de la clase omMatrix3D																					//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace OmicronSDK
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Definicion de contructores y destructor																				//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omMatrix3D::omMatrix3D()
	{
		Math::ResetMatrix(*this);
	}

	omMatrix3D::omMatrix3D(const omMatrix3D& _CopyObj)
	{
		*this = _CopyObj;
	}

	omMatrix3D::~omMatrix3D()
	{
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Sobrecarga de Operadores																								//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omMatrix3D omMatrix3D::operator + (const omMatrix3D& _Matrix3x3)
	{
		omMatrix3D AditionMatrix;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				AditionMatrix.Line[j][i] = Line[j][i] + (_Matrix3x3.Line[j][i]);
			}
		}

		return AditionMatrix;
	}

	omMatrix3D omMatrix3D::operator - (const omMatrix3D& _Matrix3x3)
	{
		omMatrix3D SubtractionMatrix;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				SubtractionMatrix.Line[j][i] = Line[j][i] - (_Matrix3x3.Line[j][i]);
			}
		}
		return SubtractionMatrix;
	}

	omMatrix3D omMatrix3D::operator *	(const omMatrix3D& _Matrix3x3)
	{
		omMatrix3D MultiplicationMatrix;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					MultiplicationMatrix.Line[j][i] += (Line[k][i] * _Matrix3x3.Line[j][k]);
				}
			}
		}
		return MultiplicationMatrix;
	}

	omMatrix3D omMatrix3D::operator *	(float _Value)
	{
		omMatrix3D MultiplicatedMatrix;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				MultiplicatedMatrix.Line[j][i] = Line[j][i] * _Value;
			}
		}
		return MultiplicatedMatrix;
	}

	omMatrix3D& omMatrix3D::operator += (const omMatrix3D& _Matrix3x3)
	{
		omMatrix3D AditionMatrix;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				AditionMatrix.Line[j][i] = Line[j][i] + (_Matrix3x3.Line[j][i]);
			}
		}

		*this = AditionMatrix;

		return *this;
	}

	omMatrix3D& omMatrix3D::operator -= (const omMatrix3D& _Matrix3x3)
	{
		omMatrix3D SubtractionMatrix;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				SubtractionMatrix.Line[j][i] = Line[j][i] - (_Matrix3x3.Line[j][i]);
			}
		}

		*this = SubtractionMatrix;
		return *this;
	}

	bool omMatrix3D::operator == (const omMatrix3D& _Matrix3x3)
	{
		return (fMatrix[0] == _Matrix3x3.fMatrix[0] &&
			fMatrix[1] == _Matrix3x3.fMatrix[1] &&
			fMatrix[2] == _Matrix3x3.fMatrix[2] &&
			fMatrix[3] == _Matrix3x3.fMatrix[3] &&
			fMatrix[4] == _Matrix3x3.fMatrix[4] &&
			fMatrix[5] == _Matrix3x3.fMatrix[5] &&
			fMatrix[6] == _Matrix3x3.fMatrix[6] &&
			fMatrix[7] == _Matrix3x3.fMatrix[7] &&
			fMatrix[8] == _Matrix3x3.fMatrix[8] &&
			fMatrix[9] == _Matrix3x3.fMatrix[9] ? true : false);
	}

	bool omMatrix3D::operator != (const omMatrix3D& _Matrix3x3)
	{
		return (fMatrix[0] != _Matrix3x3.fMatrix[0] ||
			fMatrix[1] != _Matrix3x3.fMatrix[1] ||
			fMatrix[2] != _Matrix3x3.fMatrix[2] ||
			fMatrix[3] != _Matrix3x3.fMatrix[3] ||
			fMatrix[4] != _Matrix3x3.fMatrix[4] ||
			fMatrix[5] != _Matrix3x3.fMatrix[5] ||
			fMatrix[6] != _Matrix3x3.fMatrix[6] ||
			fMatrix[7] != _Matrix3x3.fMatrix[7] ||
			fMatrix[8] != _Matrix3x3.fMatrix[8] ||
			fMatrix[9] != _Matrix3x3.fMatrix[9] ? true : false);
	}
}