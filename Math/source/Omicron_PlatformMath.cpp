//////////////////////////////////////////////////////////////////////////
///																		//
// @file   Omicron_PlatformMath.cpp										//	
// @Author Raul Portillo (ruulaasz_@hotmail.com)						//
// @date   2015/22/09													//
// @brief  Definition of non-specific platform math functions			//
// @bug	   No known bugs.												//
//																		//
//////////////////////////////////////////////////////////////////////////

#include "Omicron_PlatformMath.h"


namespace OmicronSDK
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Definicion de constantes para la plataforma matematica standard														//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	const float PlatformMath::PI = atan(1.0f) * 4;
	const float PlatformMath::PI2 = PlatformMath::PI * 2;
	const float PlatformMath::PI4 = PlatformMath::PI * 4;
	const float PlatformMath::HALF_PI = PlatformMath::PI / 2;
	const float PlatformMath::QUARTER_PI = PlatformMath::PI / 4;
	const float PlatformMath::INVERSE_PI = 1 / PlatformMath::PI;
	const float PlatformMath::LOG2 = 0.6847247885631571232991461487557776204606754163374488f;
	const float PlatformMath::EULER_NUMBER = 2.71828182845904523536f;
	const float PlatformMath::EPSILON = 0.0000000000085418781f;
	const float PlatformMath::DELTA = 0.00001f;
	const float PlatformMath::RAD_TO_DEG = 180 / PlatformMath::PI;
	const float PlatformMath::DEG_TO_RAD = PlatformMath::PI / 180;
	const float PlatformMath::MAX_FLOAT32 = 3.4f * (PlatformMath::Pow(10.f, 38.f));	

	bool PlatformMath::IntersectPlanetoPlane(omPlane& _Plane1, omPlane& _Plane2, omVector3D& _CollitionPoint)
	{
		//Calculo de la direccion de la linea de interseccion
		omVector3D DirectionOfIntersectionLine = CrossProduct(_Plane1.m_vecNormal,_Plane2.m_vecNormal);

		//Si es 0, los planos son paralelos y separados o coincidentes, entonces se concideran como intersectados
		if (DotProduct(DirectionOfIntersectionLine,DirectionOfIntersectionLine) > EPSILON)
		{
			//Obtenemos los denominadores para usar la regla de cramer
			float d11 = DotProduct(_Plane1.m_vecNormal,_Plane1.m_vecNormal);
			float d12 = DotProduct(_Plane1.m_vecNormal,_Plane2.m_vecNormal);
			float d22 = DotProduct(_Plane2.m_vecNormal,_Plane2.m_vecNormal);

			float fDenom = d11*d22 - d12*d12;

			//obtenemos las constantes del sistema de ecuaciones
			float k1 = (_Plane1.m_W*d22 - _Plane2.m_W*d12) / fDenom;
			float k2 = (_Plane2.m_W*d11 - _Plane1.m_W*d12) / fDenom;
			_CollitionPoint = _Plane1.m_vecNormal * k1 + _Plane2.m_vecNormal * k2;
			return true;
		}
		return false;
	}

	bool PlatformMath::IntersectPlanetoSphere(omPlane& _Plane, omSphere& _Sphere)
	{
		//Calculamos la distancia de la esfera al plano
		Normalize(_Plane.m_vecNormal);
		float fDist = DotProduct(_Plane.m_vecNormal,_Sphere.m_vecCenter) - _Plane.m_W;

		//Si el centro de la esfera es +/- radio del plano, el plano intersecta la esfera
		if (abs(fDist) <= _Sphere.m_fRadius)
		{
			return true;
		}
		return false;
	}

	bool PlatformMath::IntersectPlanetoRay(omPlane& _Plane, omRay& _Ray, omVector3D& _CollitionPoint)
	{
		//Escalamos el vector direccion
		omVector3D Ray = _Ray.m_vecDirection * MAX_FLOAT32;

		//Calculamos el valor t (de la direccion del rayo hacia el plano)
		float t = (_Plane.m_W - DotProduct(_Plane.m_vecNormal,_Ray.m_vecOrigin)) / DotProduct(_Plane.m_vecNormal,Ray);

		//Si el valor de t oscila entre 0 y 1, significa que hay interseccion, 
		//por lo que calculamos el punto y retornamos 
		if (t >= 0.0f && t <= 1.0f)
		{
			_CollitionPoint = _Ray.m_vecOrigin + (_Ray.m_vecDirection*t);
			return true;
		}

		return false;
	}

	bool PlatformMath::IntersectPlanetoAABB(omPlane& _Plane, omAABB& _AABB)
	{
		//Calculamos la proyeccion del radio de intervalo del AABB en L(t) = b.c+t*p.n
		float fRadius = _AABB.m_vecDimentions[0] * abs(_Plane.m_vecNormal[0]) + _AABB.m_vecDimentions[1] *
			abs(_Plane.m_vecNormal[1]) + _AABB.m_vecDimentions[2] * abs(_Plane.m_vecNormal[2]);

		//Calculamos la distancia del centro de la caja al plano
		float fDistance =DotProduct(_Plane.m_vecNormal,_AABB.m_vecCenter) - _Plane.m_W;

		//La interseccion ocurre cuando la distancia queda en el intervalo [-r,r]
		if (abs(fDistance) <= fRadius && abs(fDistance) >= -fRadius)
		{
			return true;
		}
		return false;
	}

	bool PlatformMath::IntersectSpheretoSphere(omSphere& _Sphere1, omSphere& _Sphere2)
	{
		//Calculamos la distancia cuadrada entre ambos centros
		omVector3D Distance = _Sphere1.m_vecCenter - _Sphere2.m_vecCenter;
		float fSquareDistance = DotProduct(Distance,Distance);

		//las esferas intersectan si la suma de los radios al cuadrado son menores a la distancia cuadratica obtenida
		float fSquareRadius = Square(_Sphere1.m_fRadius + _Sphere2.m_fRadius);

		if (fSquareDistance <= fSquareRadius)
		{
			return true;
		}
		return false;
	}

	bool PlatformMath::IntersectSpheretoPlane(omSphere& _Sphere, omPlane& _Plane)
	{
		//Calculamos la distancia de la esfera al plano
		Normalize(_Plane.m_vecNormal);
		float fDist = DotProduct(_Plane.m_vecNormal,_Sphere.m_vecCenter) - _Plane.m_W;

		//Si el centro de la esfera es +/- radio del plano, el plano intersecta la esfera
		if (abs(fDist) <= _Sphere.m_fRadius)
		{
			return true;
		}
		return false;
	}

	bool PlatformMath::IntersectSpheretoRay(omSphere& _Sphere, omRay& _Ray)
	{
		omVector3D Distance = _Ray.m_vecOrigin - _Sphere.m_vecCenter;
		float b = DotProduct(Distance,_Ray.m_vecDirection);
		float c = DotProduct(Distance,Distance) - (Square(_Sphere.m_fRadius));

		//Salimos si el origen del rayo esta fuera de la esfera (c>0) & apunta hacia una direccion distinta (b>0)
		if (c > 0.0f && b > 0.0f)
		{
			return false;
		}

		//Calculamos el discriminante
		float fDiscriminant = Square(b) - c;

		//Si el rayo no impacta la esfera, el discriminante es negativo
		if (fDiscriminant < 0.0f)
		{
			return false;
		}

		//El rayo entonces esta en interseccion hacia la esfera, por lo que calculamos el punto de impacto
		return true;
	}

	bool PlatformMath::IntersectSpheretoAABB(omSphere& _Sphere, omAABB& _AABB)
	{
		//Calculamos el punto minimo y maximo de la caja
		omVector3D AABBMax = omVector3D(_AABB.m_vecCenter[0] + _AABB.m_vecDimentions[0], _AABB.m_vecCenter[1]
			+ _AABB.m_vecDimentions[1], _AABB.m_vecCenter[2] + _AABB.m_vecDimentions[2]);
		omVector3D AABBMin = omVector3D(_AABB.m_vecCenter[0] - _AABB.m_vecDimentions[0], _AABB.m_vecCenter[1]
			- _AABB.m_vecDimentions[1], _AABB.m_vecCenter[2] - _AABB.m_vecDimentions[2]);

		//Calculamos la distancia cuadrada entre el centro de la esfera y el AABB
		float fSquareDistance = 0.0f;

		for (int i = 0; i < 3; i++)
		{//Para cada axis cuenta cualquier exceso de distancia fuera de los limites de la caja
			float v = _Sphere.m_vecCenter[i];

			if (v < AABBMin[i])
			{
				fSquareDistance += Square(AABBMin[i] - v);
			}

			if (v > AABBMax[i])
			{
				fSquareDistance += Square(v - AABBMax[i]);
			}
		}
		//la esfera y el AABB intersectan si la distancia cuadrada entre ellos es menor al cuadrado del radio
		if (fSquareDistance <= Square(_Sphere.m_fRadius))
		{
			return true;
		}
		return false;
	}

	bool PlatformMath::IntersectRaytoPlane(omRay& _Ray, omPlane& _Plane, omVector3D& _CollitionPoint)
	{
		//Escalamos el vector direccion
		omVector3D Ray = _Ray.m_vecDirection * MAX_FLOAT32;

		//Calculamos el valor t (de la direccion del rayo hacia el plano)
		float t = (_Plane.m_W - DotProduct(_Plane.m_vecNormal,_Ray.m_vecOrigin)) / DotProduct(_Plane.m_vecNormal,Ray);

		//Si el valor de t oscila entre 0 y 1, significa que hay interseccion, 
		//por lo que calculamos el punto y retornamos 
		if (t >= 0.0f && t <= 1.0f)
		{
			_CollitionPoint = _Ray.m_vecOrigin + (_Ray.m_vecDirection*t);
			return true;
		}

		return false;
	}

	bool PlatformMath::IntersectRaytoSphere(omRay& _Ray, omSphere& _Sphere)
	{
		omVector3D Distance = _Ray.m_vecOrigin - _Sphere.m_vecCenter;
		float b = DotProduct(Distance, _Ray.m_vecDirection);
		float c = DotProduct(Distance, Distance) - (Square(_Sphere.m_fRadius));

		//Salimos si el origen del rayo esta fuera de la esfera (c>0) & apunta hacia una direccion distinta (b>0)
		if (c > 0.0f && b > 0.0f)
		{
			return false;
		}

		//Calculamos el discriminante
		float fDiscriminant = Square(b) - c;

		//Si el rayo no impacta la esfera, el discriminante es negativo
		if (fDiscriminant < 0.0f)
		{
			return false;
		}

		//El rayo entonces esta en interseccion hacia la esfera, por lo que calculamos el punto de impacto
		return true;
	}

	bool PlatformMath::IntersectRaytoAABB(omRay& _Ray, omAABB& _AABB, omVector3D& _CollitionPoint)
	{
		//Calculamos el punto minimo y maximo de la caja
		omVector3D AABBMax = omVector3D(_AABB.m_vecCenter[0] + _AABB.m_vecDimentions[0], _AABB.m_vecCenter[1]
			+ _AABB.m_vecDimentions[1], _AABB.m_vecCenter[2] + _AABB.m_vecDimentions[2]);
		omVector3D AABBMin = omVector3D(_AABB.m_vecCenter[0] - _AABB.m_vecDimentions[0], _AABB.m_vecCenter[1]
			- _AABB.m_vecDimentions[1], _AABB.m_vecCenter[2] - _AABB.m_vecDimentions[2]);

		float tmin = 0.0f;
		float tmax = MAX_FLOAT32;

		//Para cada pared
		for (int i = 0; i < 3; i++)
		{
			if (abs(_Ray.m_vecDirection[i]) < EPSILON)
			{
				// el rayo es paralelo al muro. No coliciona si el origen esta contrario al muro
				if (_Ray.m_vecOrigin[i] < AABBMin[i] || _Ray.m_vecOrigin[i] > AABBMax[i])
				{
					return 0;
				}
			}
			else
			{
				// calculamos el valor de interseccion t del ray con el muro mas cercano y lejano
				float ood = 1.0f / _Ray.m_vecDirection[i];
				float t1 = (AABBMin[i] - _Ray.m_vecOrigin[i]) * ood;
				float t2 = (AABBMax[i] - _Ray.m_vecOrigin[i]) * ood;

				// Nos aseguramos que t1 quede con la interseccion mas cercana, y t2 con la mas lejana
				if (t1 > t2)
				{
					Swap(t1, t2);
				}

				// Calculamos la interseccion de los intervalos
				if (t1 > tmin)
				{
					tmin = t1;
				}
				if (t2 > tmax)
				{
					tmax = t2;
				}

				//Si ni existe colicion con el muro, retornamos 
				if (tmin > tmax)
				{
					return 0;
				}
			}
		}
		// el rayo intersecta los 3 muros, retornamos el punto de colicion 
		_CollitionPoint = _Ray.m_vecOrigin + (_Ray.m_vecDirection* tmin);
		return 1;
	}

	bool PlatformMath::IntersectAABBtoAABB(omAABB& _AABB1, omAABB& _AABB2)
	{
		//Salimos si no existe interseccion en un eje, ya que se debe dar en los 3
		if (abs(_AABB1.m_vecCenter[0] - _AABB2.m_vecCenter[0]) >
			(_AABB1.m_vecDimentions[0] + _AABB2.m_vecDimentions[0]))
		{
			return false;
		}
		if (abs(_AABB1.m_vecCenter[1] - _AABB2.m_vecCenter[1]) >
			(_AABB1.m_vecDimentions[1] + _AABB2.m_vecDimentions[1]))
		{
			return false;
		}
		if (abs(_AABB1.m_vecCenter[2] - _AABB2.m_vecCenter[2]) >
			(_AABB1.m_vecDimentions[2] + _AABB2.m_vecDimentions[2]))
		{
			return false;
		}

		return true;
	}

	bool PlatformMath::IntersectAABBtoPlane(omAABB& _AABB, omPlane& _Plane)
	{
		//Calculamos la proyeccion del radio de intervalo del AABB en L(t) = b.c+t*p.n
		float fRadius = _AABB.m_vecDimentions[0] * abs(_Plane.m_vecNormal[0]) +
			_AABB.m_vecDimentions[1] * abs(_Plane.m_vecNormal[1]) +
			_AABB.m_vecDimentions[2] * abs(_Plane.m_vecNormal[2]);

		//Calculamos la distancia del centro de la caja al plano
		float fDistance = DotProduct(_Plane.m_vecNormal,_AABB.m_vecCenter) - _Plane.m_W;

		//La interseccion ocurre cuando la distancia queda en el intervalo [-r,r]
		if (abs(fDistance) <= fRadius && abs(fDistance) >= -fRadius)
		{
			return true;
		}
		return false;
	}

	bool PlatformMath::IntersectAABBtoSphere(omAABB& _AABB, omSphere& _Sphere)
	{
		//Calculamos el punto minimo y maximo de la caja
		omVector3D AABBMax = omVector3D(_AABB.m_vecCenter[0] + _AABB.m_vecDimentions[0], _AABB.m_vecCenter[1]
			+ _AABB.m_vecDimentions[1], _AABB.m_vecCenter[2] + _AABB.m_vecDimentions[2]);
		omVector3D AABBMin = omVector3D(_AABB.m_vecCenter[0] - _AABB.m_vecDimentions[0], _AABB.m_vecCenter[1]
			- _AABB.m_vecDimentions[1], _AABB.m_vecCenter[2] - _AABB.m_vecDimentions[2]);

		//Calculamos la distancia cuadrada entre el centro de la esfera y el AABB
		float fSquareDistance = 0.0f;

		for (int i = 0; i < 3; i++)
		{//Para cada axis cuenta cualquier exceso de distancia fuera de los limites de la caja
			float v = _Sphere.m_vecCenter[i];

			if (v < AABBMin[i])
			{
				fSquareDistance += Square(AABBMin[i] - v);
			}

			if (v > AABBMax[i])
			{
				fSquareDistance += Square(v - AABBMax[i]);
			}
		}

		//la esfera y el AABB intersectan si la distancia cuadrada entre ellos es menor al cuadrado del radio
		if (fSquareDistance <= Square(_Sphere.m_fRadius))
		{
			return true;
		}
		return false;
	}

	bool PlatformMath::IntersectAABBtoRay(omAABB& _AABB, omRay& _Ray, omVector3D& _CollitionPoint)
	{
		//Calculamos el punto minimo y maximo de la caja
		omVector3D AABBMax = omVector3D(_AABB.m_vecCenter[0] + _AABB.m_vecDimentions[0], _AABB.m_vecCenter[1]
			+ _AABB.m_vecDimentions[1], _AABB.m_vecCenter[2] + _AABB.m_vecDimentions[2]);
		omVector3D AABBMin = omVector3D(_AABB.m_vecCenter[0] - _AABB.m_vecDimentions[0], _AABB.m_vecCenter[1]
			- _AABB.m_vecDimentions[1], _AABB.m_vecCenter[2] - _AABB.m_vecDimentions[2]);

		float tmin = 0.0f;
		float tmax = MAX_FLOAT32;

		//Para cada pared
		for (int i = 0; i < 3; i++)
		{
			if (abs(_Ray.m_vecDirection[i]) < EPSILON)
			{
				// el rayo es paralelo al muro. No coliciona si el origen esta contrario al muro
				if (_Ray.m_vecOrigin[i] < AABBMin[i] || _Ray.m_vecOrigin[i] > AABBMax[i])
				{
					return 0;
				}
			}
			else
			{
				// calculamos el valor de interseccion t del ray con el muro mas cercano y lejano
				float ood = 1.0f / _Ray.m_vecDirection[i];
				float t1 = (AABBMin[i] - _Ray.m_vecOrigin[i]) * ood;
				float t2 = (AABBMax[i] - _Ray.m_vecOrigin[i]) * ood;

				// Nos aseguramos que t1 quede con la interseccion mas cercana, y t2 con la mas lejana
				if (t1 > t2)
				{
					Swap(t1, t2);
				}

				// Calculamos la interseccion de los intervalos
				if (t1 > tmin)
				{
					tmin = t1;
				}
				if (t2 > tmax)
				{
					tmax = t2;
				}

				//Si ni existe colicion con el muro, retornamos 
				if (tmin > tmax)
				{
					return 0;
				}
			}
		}
		// el rayo intersecta los 3 muros, retornamos el punto de colicion 
		_CollitionPoint = _Ray.m_vecOrigin + (_Ray.m_vecDirection* tmin);
		return 1;
	}
}

