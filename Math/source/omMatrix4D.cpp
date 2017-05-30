//////////////////////////////////////////////////////////////////////////
///																		//
// @file   omMatrix4D.cpp												//	
// @Author Raul Portillo (ruulaasz_@hotmail.com)						//
// @date   2015/17/10													//
// @brief  Definition of omMatrix4D Class 								//
// @bug	   No known bugs.												//
//																		//
//////////////////////////////////////////////////////////////////////////
#if PLATFORM == WINDOWS_MATH
#include "Omicron_WindowsMath.h"  /*!< Funciones matematicas basicas optimisadas para Windows */
#endif
#include "Omicron_PlatformMath.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Definicion de la clase omMatrix4D																					//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace OmicronSDK
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Definicion de contructores y destructor																				//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omMatrix4D::omMatrix4D()
	{
		Math::ResetMatrix(*this);
	}

	omMatrix4D::omMatrix4D(const omMatrix4D& _CopyObj)
	{
		*this = _CopyObj;
	}

	omMatrix4D::~omMatrix4D()
	{
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Sobrecarga de Operadores																								//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	omMatrix4D omMatrix4D::operator + (const omMatrix4D& _Matrix4x4)
	{
		omMatrix4D AditionMatrix;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				AditionMatrix.Line[j][i] = Line[j][i] + (_Matrix4x4.Line[j][i]);
			}
		}
		return AditionMatrix;


	}

	omMatrix4D omMatrix4D::operator - (const omMatrix4D& _Matrix4x4)
	{
		omMatrix4D SubtractionMatrix;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				SubtractionMatrix.Line[j][i] = Line[j][i] - (_Matrix4x4.Line[j][i]);
			}
		}
		return SubtractionMatrix;
	}

	omMatrix4D omMatrix4D::operator *	(const omMatrix4D& _Matrix4x4)
	{
		omMatrix4D MultiplicationMatrix;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					MultiplicationMatrix.Line[i][j] += (Line[i][k] * _Matrix4x4.Line[k][j]);
				}
			}
		}

		return MultiplicationMatrix;
	}

	omVector4D omMatrix4D::operator * (omVector4D& _Vector4D)
	{
		omVector4D MultiplicatedVector;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				MultiplicatedVector[i] += (Line[i][j] * _Vector4D[j]);
			}
		}

		return MultiplicatedVector;
	}

	omMatrix4D omMatrix4D::operator *	(float _Value)
	{
		omMatrix4D MultiplicatedMatrix;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				MultiplicatedMatrix.Line[j][i] = Line[j][i] * _Value;
			}
		}
		return MultiplicatedMatrix;
	}

	omMatrix4D& omMatrix4D::operator += (const omMatrix4D& _Matrix4x4)
	{
		omMatrix4D AditionMatrix;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				AditionMatrix.Line[j][i] = Line[j][i] + (_Matrix4x4.Line[j][i]);
			}
		}

		*this = AditionMatrix;

		return *this;
	}

	omMatrix4D& omMatrix4D::operator -= (const omMatrix4D& _Matrix4x4)
	{
		omMatrix4D SubtractionMatrix;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				SubtractionMatrix.Line[j][i] = Line[j][i] - (_Matrix4x4.Line[j][i]);
			}
		}

		*this = SubtractionMatrix;

		return *this;
	}

	omMatrix4D& omMatrix4D::operator *= (const omMatrix4D& _Matrix4x4)
	{
		omMatrix4D MultiplicationMatrix;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					MultiplicationMatrix.Line[i][j] += (Line[i][k] * _Matrix4x4.Line[k][j]);
				}
			}
		}

		*this = MultiplicationMatrix;

		return *this;
	}

	bool omMatrix4D::operator == (const omMatrix4D& _Matrix4x4)
	{
		return (fMatrix[0] == _Matrix4x4.fMatrix[0] &&
			fMatrix[1] == _Matrix4x4.fMatrix[1] &&
			fMatrix[2] == _Matrix4x4.fMatrix[2] &&
			fMatrix[3] == _Matrix4x4.fMatrix[3] &&
			fMatrix[4] == _Matrix4x4.fMatrix[4] &&
			fMatrix[5] == _Matrix4x4.fMatrix[5] &&
			fMatrix[6] == _Matrix4x4.fMatrix[6] &&
			fMatrix[7] == _Matrix4x4.fMatrix[7] &&
			fMatrix[8] == _Matrix4x4.fMatrix[8] &&
			fMatrix[9] == _Matrix4x4.fMatrix[9] &&
			fMatrix[10] == _Matrix4x4.fMatrix[10] &&
			fMatrix[11] == _Matrix4x4.fMatrix[11] &&
			fMatrix[12] == _Matrix4x4.fMatrix[12] &&
			fMatrix[13] == _Matrix4x4.fMatrix[13] &&
			fMatrix[14] == _Matrix4x4.fMatrix[14] &&
			fMatrix[15] == _Matrix4x4.fMatrix[15] ? true : false);
	}

	bool omMatrix4D::operator != (const omMatrix4D& _Matrix4x4)
	{
		return (fMatrix[0] != _Matrix4x4.fMatrix[0] ||
			fMatrix[1] != _Matrix4x4.fMatrix[1] ||
			fMatrix[2] != _Matrix4x4.fMatrix[2] ||
			fMatrix[3] != _Matrix4x4.fMatrix[3] ||
			fMatrix[4] != _Matrix4x4.fMatrix[4] ||
			fMatrix[5] != _Matrix4x4.fMatrix[5] ||
			fMatrix[6] != _Matrix4x4.fMatrix[6] ||
			fMatrix[7] != _Matrix4x4.fMatrix[7] ||
			fMatrix[8] != _Matrix4x4.fMatrix[8] ||
			fMatrix[9] != _Matrix4x4.fMatrix[9] ||
			fMatrix[10] != _Matrix4x4.fMatrix[10] ||
			fMatrix[11] != _Matrix4x4.fMatrix[11] ||
			fMatrix[12] != _Matrix4x4.fMatrix[12] ||
			fMatrix[13] != _Matrix4x4.fMatrix[13] ||
			fMatrix[14] != _Matrix4x4.fMatrix[14] ||
			fMatrix[15] != _Matrix4x4.fMatrix[15] ? true : false);
	}
}