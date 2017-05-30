//////////////////////////////////////////////////////////////////////////
///																		//
// @file   omDegrees.cpp												//	
// @Author Raul Portillo (ruulaasz_@hotmail.com)						//
// @date   2015/22/09													//
// @brief  Definition of omDegree Class									//
// @bug	   No known bugs.												//
//																		//
//////////////////////////////////////////////////////////////////////////
#if PLATFORM == WINDOWS_MATH
#include "Omicron_WindowsMath.h"  /*!< Funciones matematicas basicas optimisadas para Windows */
#endif
#include "Omicron_PlatformMath.h"

#include "omPlane.h"
#include "omAABB.h"

namespace OmicronSDK
{
	omFrustum::omFrustum()
	{
	}


	omFrustum::~omFrustum()
	{
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Definicion de las funciones de la clase																				//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void omFrustum::setCamInternals(omDegrees angle, float ratio, float nearD, float farD)
	{
		// store the information
		this->ratio = ratio;
		this->angle = new omDegrees(angle);
		this->nearD = nearD;
		this->farD = farD;

		// compute width and height of the near and far plane sections
		tang = (float)tan(angle.GetRadians() * 0.5);
		nh = nearD * tang;
		nw = nh * ratio;
		fh = farD  * tang;
		fw = fh * ratio;
	}

	//cada que la perspectiva cambie o la ventana sea rezize se debe llamar
	void omFrustum::setCamInternals(omRadians angle, float ratio, float nearD, float farD)
	{
		// store the information
		this->ratio = ratio;
		this->angle = new omDegrees(&angle);
		this->nearD = nearD;
		this->farD = farD;

		// compute width and height of the near and far plane sections
		tang = (float)tan(angle.GetRadians() * 0.5);
		nh = nearD * tang;
		nw = nh * ratio;
		fh = farD  * tang;
		fw = fh * ratio;
	}

	void omFrustum::setCamDef(omVector4D & _Position, omVector4D & _Look, omVector4D & _Up)
	{
		omVector4D nc, fc, X, Y, Z;

		// compute the Z axis of camera
		// this axis points in the opposite direction from
		// the looking direction
		Z = _Position - _Look;
		Math::Normalize(Z);

		// X axis of camera with given "up" vector and Z axis
		X = _Up * Z;
		Math::Normalize(X);

		// the real "up" vector is the cross product of Z and X
		Y = Z * X;

		m_Planes[NEARP].SetNormalAndPoint(Z*-1, nc);
		m_Planes[FARP].SetNormalAndPoint(Z, fc);

		omVector4D aux, normal;

		aux = (nc + Y*nh) - _Position;
		Math::Normalize(aux);
		normal = aux * X;
		m_Planes[TOP].SetNormalAndPoint(normal, nc + Y*nh);

		aux = (nc - Y*nh) - _Position;
		Math::Normalize(aux);
		normal = X * aux;
		m_Planes[BOTTOM].SetNormalAndPoint(normal, nc - Y*nh);

		aux = (nc - X*nw) - _Position;
		Math::Normalize(aux);
		normal = aux * Y;
		m_Planes[LEFT].SetNormalAndPoint(normal, nc - X*nw);

		aux = (nc + X*nw) - _Position;
		Math::Normalize(aux);
		normal = Y * aux;
		m_Planes[RIGHT].SetNormalAndPoint(normal, nc + X*nw);
	}
}