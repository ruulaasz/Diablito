//////////////////////////////////////////////////////////////////////////
///																		//
// @file   Omicron_PlatformMath.h										//	
// @Author Raul Portillo (ruulaasz_@hotmail.com)						//
// @date   2015/22/09													//
// @brief  Declaration of Windows specific platform math functions		//
// @bug	   No known bugs.												//
//																		//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Cabezeras necesesarias para la compilacion																			//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Omicron_PlatformMath.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Estructura de funciones para la plataforma matematica																//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace OmicronSDK
{
	struct omWindowsMath : public PlatformMath
	{
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Declaracion de funciones trigonometricas																				//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		static float MATH_API Sin(float _value)//<Retorna el seno de un flotante>//
		{
			return sinf(_value);		//<Retorna el seno de un flotante>//
		}

		static float MATH_API Sin(omRadians& _radians)//<Retorna el seno de un omAngle>//
		{
			return sinf(_radians.GetRadians());		//<Retorna el seno de un flotante>//
		}

		static float MATH_API Sin(omDegrees& _degrees)//<Retorna el seno de un omAngle>//
		{
			return sinf(_degrees.GetRadians());		//<Retorna el seno de un flotante>//
		}

		static float MATH_API Cos(float _value)//<Retorna el coseno de un flotante>//
		{
			return cosf(_value);		//<Retorna el coseno de un flotante>//
		}
		static float MATH_API Cos(omRadians& _radians)//<Retorna el seno de un omAngle>//
		{
			return cosf(_radians.GetRadians());		//<Retorna el seno de un flotante>//
		}
		static float MATH_API Cos(omDegrees& _degrees)//<Retorna el seno de un omAngle>//
		{
			return cosf(_degrees.GetRadians());		//<Retorna el seno de un flotante>//
		}

		static float MATH_API Tan(float _value)//<Retorna la tangente de un flotante>//
		{
			return tanf(_value);		//<Retorna la tangente de un flotante>//
		}
		static float MATH_API Tan(omRadians& _radians)//<Retorna el seno de un omAngle>//
		{
			return tanf(_radians.GetRadians());		//<Retorna el seno de un flotante>//
		}
		static float MATH_API Tan(omDegrees& _degrees)//<Retorna el seno de un omAngle>//
		{
			return tanf(_degrees.GetRadians());		//<Retorna el seno de un flotante>//
		}

		static float MATH_API ArcSin(float _value)//<Retorna el arcoSeno de un flotante>//
		{
			return asinf(_value);		//<Retorna el arcoSeno de un flotante>//
		}

		static float MATH_API ArcSin(omRadians& _radians)//<Retorna el seno de un omAngle>//
		{
			return asinf(_radians.GetRadians());		//<Retorna el arcoseno de un flotante>//
		}

		static float MATH_API ArcSin(omDegrees& _degrees)//<Retorna el seno de un omAngle>//
		{
			return asinf(_degrees.GetRadians());		//<Retorna el seno de un flotante>//
		}

		static float MATH_API ArcCos(float _value)//<Retorna el arcoCoseno de un flotante>//
		{
			return acosf(_value);						//<Retorna el arcoCoseno de un flotante>//
		}

		static float MATH_API ArcCos(omRadians& _radians)//<Retorna el seno de un omAngle>//
		{
			return acosf(_radians.GetRadians());		//<Retorna el seno de un flotante>//
		}

		static float MATH_API ArcCos(omDegrees& _degrees)//<Retorna el seno de un omAngle>//
		{
			return acosf(_degrees.GetRadians());		//<Retorna el seno de un flotante>//
		}

		static float MATH_API ArcTan(float _value)//<Retorna el arcTangente de un flotante>//
		{
			return atanf(_value);		//<Retorna el arcoTangente de un flotante>//
		}
		static float MATH_API ArcTan(omRadians& _radians)//<Retorna el seno de un omAngle>//
		{
			return atanf(_radians.GetRadians());		//<Retorna el seno de un flotante>//
		}

		static float MATH_API ArcTan(omDegrees& _degrees)//<Retorna el seno de un omAngle>//
		{
			return atanf(_degrees.GetRadians());		//<Retorna el seno de un flotante>//
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Declaracion de funciones trigonometricas rapidas																		//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		static float MATH_API FastSin(float _value)//<Retorna el seno de manera rapida>//
		{
			float fSin = _value;//<Primer elemento de la serie de taylor x para seno>//
			float fBasePow = Pow(_value, 3);//<guardamos el valor de x al cubo >//
			float fXPow2 = Pow(_value, 2);//<guardamos el valor de x al cuadrado >//

			fSin -= (0.166666666667f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fSin += (0.008333333333f * fBasePow);

			return fSin;	//<Retorna el seno de un flotante de manera rapida>//
		}
		static float MATH_API FastSin2(float _value)//<Retorna el seno de manera rapida con mayor presicion>//
		{
			float fSin = _value;//<Primer elemento de la serie de taylor x para seno>//
			float fBasePow = Pow(_value, 3); //<guardamos el valor de x al cubo >//
			float fXPow2 = Pow(_value, 2);//<guardamos el valor de x al cuadrado >//

			fSin -= (0.166666666667f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fSin += (0.008333333333f * fBasePow);
			fBasePow *= fXPow2;
			fSin -= (0.000198412698f * fBasePow);
			fBasePow *= fXPow2;
			fSin += (0.000002755732f * fBasePow);
			fBasePow *= fXPow2;
			fSin -= (0.000000025052f * fBasePow);

			return fSin;	//<Retorna el seno de un flotante de manera rapida con mayor presicion>//
		}


		static float MATH_API FastSin(omRadians& _radians)//<Retorna el seno de manera rapida>//
		{
			float fSin = _radians.GetRadians();//<Primer elemento de la serie de taylor x para seno>//
			float fBasePow = Pow(fSin, 3);//<guardamos el valor de x al cubo >//
			float fXPow2 = Pow(fSin, 2);//<guardamos el valor de x al cuadrado >//

			fSin -= (0.166666666667f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fSin += (0.008333333333f * fBasePow);

			return fSin;	//<Retorna el seno de un flotante de manera rapida>//
		}

		static float MATH_API FastSin2(omRadians& _radians)//<Retorna el seno de manera rapida con mayor presicion>//
		{
			float fSin = _radians.GetRadians();//<Primer elemento de la serie de taylor x para seno>//
			float fBasePow = Pow(fSin, 3); //<guardamos el valor de x al cubo >//
			float fXPow2 = Pow(fSin, 2);//<guardamos el valor de x al cuadrado >//

			fSin -= (0.166666666667f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fSin += (0.008333333333f * fBasePow);
			fBasePow *= fXPow2;
			fSin -= (0.000198412698f * fBasePow);
			fBasePow *= fXPow2;
			fSin += (0.000002755732f * fBasePow);
			fBasePow *= fXPow2;
			fSin -= (0.000000025052f * fBasePow);

			return fSin;	//<Retorna el seno de un flotante de manera rapida con mayor presicion>//
		}

		static float MATH_API FastSin(omDegrees& _degrees)//<Retorna el seno de manera rapida>//
		{
			float fSin = _degrees.GetRadians();//<Primer elemento de la serie de taylor x para seno>//
			float fBasePow = Pow(fSin, 3);//<guardamos el valor de x al cubo >//
			float fXPow2 = Pow(fSin, 2);//<guardamos el valor de x al cuadrado >//

			fSin -= (0.166666666667f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fSin += (0.008333333333f * fBasePow);

			return fSin;	//<Retorna el seno de un flotante de manera rapida>//
		}

		static float MATH_API FastSin2(omDegrees& _degrees)//<Retorna el seno de manera rapida con mayor presicion>//
		{
			float fSin = _degrees.GetRadians();//<Primer elemento de la serie de taylor x para seno>//
			float fBasePow = Pow(fSin, 3); //<guardamos el valor de x al cubo >//
			float fXPow2 = Pow(fSin, 2);//<guardamos el valor de x al cuadrado >//

			fSin -= (0.166666666667f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fSin += (0.008333333333f * fBasePow);
			fBasePow *= fXPow2;
			fSin -= (0.000198412698f * fBasePow);
			fBasePow *= fXPow2;
			fSin += (0.000002755732f * fBasePow);
			fBasePow *= fXPow2;
			fSin -= (0.000000025052f * fBasePow);

			return fSin;	//<Retorna el seno de un flotante de manera rapida con mayor presicion>//
		}

		static float MATH_API FastCos(float _value)//<Retorna el coseno de manera rapida>//
		{
			float fCos = 1;//<Primer elemento de la serie de taylor 1 para coseno>//
			float fBasePow = Pow(_value, 2);//<guardamos el valor de x al cuadrado >//
			float fXPow2 = Pow(_value, 2);//<guardamos el valor de x al cuadrado >//

			fCos -= (0.500000000000f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fCos += (0.041666666667f * fBasePow);

			return fCos;	//<Retorna el Coseno de un flotante de manera rapida>//
		}
		static float MATH_API FastCos2(float _value)//<Retorna el coseno de manera rapida con mayor presicion>//
		{
			float fCos = 1;//<Primer elemento de la serie de taylor 1 para Coseno>//
			float fBasePow = Pow(_value, 2); //<guardamos el valor de x al cuadrado >//
			float fXPow2 = Pow(_value, 2);//<guardamos el valor de x al cuadrado >//

			fCos -= (0.500000000000f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fCos += (0.041666666667f * fBasePow);
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fCos -= (0.001388888889f * fBasePow);
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fCos += (0.000024801587f * fBasePow);
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fCos -= (0.000000275573f * fBasePow);

			return fCos;	//<Retorna el Coseno de un flotante de manera rapida>//
		}

		static float MATH_API FastCos(omRadians& _radians)//<Retorna el seno de manera rapida>//
		{
			float fCos = 1;//<Primer elemento de la serie de taylor 1 para coseno>//
			float fBasePow = Pow(_radians.GetRadians(), 2);//<guardamos el valor de x al cuadrado >//
			float fXPow2 = Pow(_radians.GetRadians(), 2);//<guardamos el valor de x al cuadrado >//

			fCos -= (0.500000000000f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fCos += (0.041666666667f * fBasePow);

			return fCos;	//<Retorna el Coseno de un flotante de manera rapida>//
		}

		static float MATH_API FastCos2(omRadians& _radians)//<Retorna el seno de manera rapida con mayor presicion>//
		{
			float fCos = 1;//<Primer elemento de la serie de taylor 1 para Coseno>//
			float fBasePow = Pow(_radians.GetRadians(), 2); //<guardamos el valor de x al cuadrado >//
			float fXPow2 = Pow(_radians.GetRadians(), 2);//<guardamos el valor de x al cuadrado >//

			fCos -= (0.500000000000f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fCos += (0.041666666667f * fBasePow);
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fCos -= (0.001388888889f * fBasePow);
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fCos += (0.000024801587f * fBasePow);
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fCos -= (0.000000275573f * fBasePow);

			return fCos;	//<Retorna el Coseno de un flotante de manera rapida>//
		}

		static float MATH_API FastCos(omDegrees& _degrees)//<Retorna el seno de manera rapida>//
		{
			{
				float fCos = 1;//<Primer elemento de la serie de taylor 1 para coseno>//
				float fBasePow = Pow(_degrees.GetRadians(), 2);//<guardamos el valor de x al cuadrado >//
				float fXPow2 = Pow(_degrees.GetRadians(), 2);//<guardamos el valor de x al cuadrado >//

				fCos -= (0.500000000000f * fBasePow);//<desalloramos la serie >//
				fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
				fCos += (0.041666666667f * fBasePow);

				return fCos;	//<Retorna el Coseno de un flotante de manera rapida>//
			}
		}
		static float MATH_API FastCos2(omDegrees& _degrees)//<Retorna el seno de manera rapida con mayor presicion>//
		{
			{
				float fCos = 1;//<Primer elemento de la serie de taylor 1 para Coseno>//
				float fBasePow = Pow(_degrees.GetRadians(), 2); //<guardamos el valor de x al cuadrado >//
				float fXPow2 = Pow(_degrees.GetRadians(), 2);//<guardamos el valor de x al cuadrado >//

				fCos -= (0.500000000000f * fBasePow);//<desalloramos la serie >//
				fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
				fCos += (0.041666666667f * fBasePow);
				fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
				fCos -= (0.001388888889f * fBasePow);
				fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
				fCos += (0.000024801587f * fBasePow);
				fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
				fCos -= (0.000000275573f * fBasePow);

				return fCos;	//<Retorna el Coseno de un flotante de manera rapida>//
			}
		}

		static float MATH_API FastTan(float _value)//<Retorna la tangente de manera rapida>//
		{
			float fSin = FastSin(_value);
			float fCos = FastCos(_value);

			return fSin / fCos;	//<Retorna la tangente de un flotante de manera rapida>//
		}

		static float MATH_API FastTan2(float _value)//<Retorna la tangente de manera rapida con mayor presicion>//
		{
			float fSin = FastSin2(_value);
			float fCos = FastCos2(_value);

			return fSin / fCos;	//<Retorna la tangente de un flotante de manera rapida con mayor presicion>//
		}

		static float MATH_API FastTan(omRadians& _radians)//<Retorna el seno de manera rapida>//
		{
			float fSin = FastSin(_radians.GetRadians());
			float fCos = FastCos(_radians.GetRadians());

			return fSin / fCos;	//<Retorna la tangente de un flotante de manera rapida>//
		}
		static float MATH_API FastTan2(omRadians& _radians)//<Retorna el seno de manera rapida con mayor presicion>//
		{
			float fSin = FastSin2(_radians.GetRadians());
			float fCos = FastCos2(_radians.GetRadians());

			return fSin / fCos;	//<Retorna la tangente de un flotante de manera rapida con mayor presicion>//
		}

		static float MATH_API FastTan(omDegrees& _degrees)//<Retorna el seno de manera rapida>//
		{
			float fSin = FastSin(_degrees.GetRadians());
			float fCos = FastCos(_degrees.GetRadians());

			return fSin / fCos;	//<Retorna la tangente de un flotante de manera rapida>//
		}

		static float MATH_API FastTan2(omDegrees& _degrees)//<Retorna el seno de manera rapida con mayor presicion>//
		{
			float fSin = FastSin2(_degrees.GetRadians());
			float fCos = FastCos2(_degrees.GetRadians());

			return fSin / fCos;	//<Retorna la tangente de un flotante de manera rapida con mayor presicion>//
		}

		static float MATH_API FastArcSin(float _value)//<Retorna el arcoSeno de manera rapida//
		{
			float fArcSin = _value;
			float fBasePow = Pow(_value, 3); //<guardamos el valor de x al cubo >//
			float fXPow2 = Pow(_value, 2);//<guardamos el valor de x al cuadrado >//

			fArcSin += (0.166666666667f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcSin += (0.075000000000f * fBasePow);

			return fArcSin;	//<el arcoSeno de un flotante de manera rapida>//
		}
		static float MATH_API FastArcSin2(float _value)//<Retorna el arcoSeno de manera rapida con mayor presicion//
		{
			float fArcSin = _value;
			float fBasePow = Pow(_value, 3); //<guardamos el valor de x al cubo >//
			float fXPow2 = Pow(_value, 2);//<guardamos el valor de x al cuadrado >//

			fArcSin += (0.166666666667f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcSin += (0.075000000000f * fBasePow);
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcSin += (0.044642857143f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcSin += (0.030381944444f * fBasePow);
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcSin += (0.022372159091f * fBasePow);//<desalloramos la serie >//

			return fArcSin;	//<el arcoSeno de un flotante de manera rapida>//
		}

		static float MATH_API FastArcSin(omRadians& _radians)//<Retorna el seno de manera rapida>//
		{
			float fArcSin = _radians.GetRadians();
			float fBasePow = Pow(fArcSin, 3); //<guardamos el valor de x al cubo >//
			float fXPow2 = Pow(fArcSin, 2);//<guardamos el valor de x al cuadrado >//

			fArcSin += (0.166666666667f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcSin += (0.075000000000f * fBasePow);

			return fArcSin;	//<el arcoSeno de un flotante de manera rapida>//
		}
		static float MATH_API FastArcSin2(omRadians& _radians)//<Retorna el seno de manera rapida con mayor presicion>//
		{
			float fArcSin = _radians.GetRadians();
			float fBasePow = Pow(_radians.GetRadians(), 3); //<guardamos el valor de x al cubo >//
			float fXPow2 = Pow(_radians.GetRadians(), 2);//<guardamos el valor de x al cuadrado >//

			fArcSin += (0.166666666667f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcSin += (0.075000000000f * fBasePow);
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcSin += (0.044642857143f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcSin += (0.030381944444f * fBasePow);
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcSin += (0.022372159091f * fBasePow);//<desalloramos la serie >//

			return fArcSin;	//<el arcoSeno de un flotante de manera rapida>//
		}

		static float MATH_API FastArcSin(omDegrees& _degrees)//<Retorna el seno de manera rapida>//
		{
			float fArcSin = _degrees.GetRadians();
			float fBasePow = Pow(fArcSin, 3); //<guardamos el valor de x al cubo >//
			float fXPow2 = Pow(fArcSin, 2);//<guardamos el valor de x al cuadrado >//

			fArcSin += (0.166666666667f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcSin += (0.075000000000f * fBasePow);

			return fArcSin;	//<el arcoSeno de un flotante de manera rapida>//
		}
		static float MATH_API FastArcSin2(omDegrees& _degrees)//<Retorna el seno de manera rapida con mayor presicion>//
		{
			float fArcSin = _degrees.GetRadians();
			float fBasePow = Pow(_degrees.GetRadians(), 3); //<guardamos el valor de x al cubo >//
			float fXPow2 = Pow(_degrees.GetRadians(), 2);//<guardamos el valor de x al cuadrado >//

			fArcSin += (0.166666666667f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcSin += (0.075000000000f * fBasePow);
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcSin += (0.044642857143f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcSin += (0.030381944444f * fBasePow);
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcSin += (0.022372159091f * fBasePow);//<desalloramos la serie >//

			return fArcSin;	//<el arcoSeno de un flotante de manera rapida>//
		}

		static float MATH_API FastArcCos(float _value)//<Retorna el arcoCoseno de manera rapida>//
		{
			float fArcCos = HALF_PI;
			float fBasePow = Pow(_value, 3); //<guardamos el valor de x al cubo >//
			float fXPow2 = Pow(_value, 2);//<guardamos el valor de x al cuadrado >//

			fArcCos -= (0.166666666667f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcCos -= (0.075000000000f * fBasePow);

			return fArcCos;	//<el arcoSeno de un flotante de manera rapida>//
		}
		static float MATH_API FastArcCos2(float _value)//<Retorna el arcoCoseno de manera rapida con mayor presicion>//
		{
			float fArcCos = HALF_PI;
			float fBasePow = Pow(_value, 3); //<guardamos el valor de x al cubo >//
			float fXPow2 = Pow(_value, 2);//<guardamos el valor de x al cuadrado >//

			fArcCos -= (0.166666666667f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcCos -= (0.075000000000f * fBasePow);
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcCos -= (0.044642857143f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcCos -= (0.030381944444f * fBasePow);
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcCos -= (0.022372159091f * fBasePow);//<desalloramos la serie >//

			return fArcCos;	//<el arcoSeno de un flotante de manera rapida>//
		}

		static float MATH_API FastArcCos(omRadians& _radians)//<Retorna el seno de manera rapida>//
		{
			float fArcCos = HALF_PI;
			float fBasePow = Pow(_radians.GetRadians(), 3); //<guardamos el valor de x al cubo >//
			float fXPow2 = Pow(_radians.GetRadians(), 2);//<guardamos el valor de x al cuadrado >//

			fArcCos -= (0.166666666667f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcCos -= (0.075000000000f * fBasePow);

			return fArcCos;	//<el arcoSeno de un flotante de manera rapida>//
		}
		static float MATH_API FastArcCos2(omRadians& _radians)//<Retorna el seno de manera rapida con mayor presicion>//
		{
			float fArcCos = HALF_PI;
			float fBasePow = Pow(_radians.GetRadians(), 3); //<guardamos el valor de x al cubo >//
			float fXPow2 = Pow(_radians.GetRadians(), 2);//<guardamos el valor de x al cuadrado >//

			fArcCos -= (0.166666666667f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcCos -= (0.075000000000f * fBasePow);
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcCos -= (0.044642857143f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcCos -= (0.030381944444f * fBasePow);
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcCos -= (0.022372159091f * fBasePow);//<desalloramos la serie >//

			return fArcCos;	//<el arcoSeno de un flotante de manera rapida>//
		}

		static float MATH_API FastArcCos(omDegrees& _degrees)//<Retorna el seno de manera rapida>//
		{
			float fArcCos = HALF_PI;
			float fBasePow = Pow(_degrees.GetRadians(), 3); //<guardamos el valor de x al cubo >//
			float fXPow2 = Pow(_degrees.GetRadians(), 2);//<guardamos el valor de x al cuadrado >//

			fArcCos -= (0.166666666667f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcCos -= (0.075000000000f * fBasePow);

			return fArcCos;	//<el arcoSeno de un flotante de manera rapida>//
		}
		static float MATH_API FastArcCos2(omDegrees& _degrees)//<Retorna el seno de manera rapida con mayor presicion>//
		{
			float fArcCos = HALF_PI;
			float fBasePow = Pow(_degrees.GetRadians(), 3); //<guardamos el valor de x al cubo >//
			float fXPow2 = Pow(_degrees.GetRadians(), 2);//<guardamos el valor de x al cuadrado >//

			fArcCos -= (0.166666666667f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcCos -= (0.075000000000f * fBasePow);
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcCos -= (0.044642857143f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcCos -= (0.030381944444f * fBasePow);
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcCos -= (0.022372159091f * fBasePow);//<desalloramos la serie >//

			return fArcCos;	//<el arcoSeno de un flotante de manera rapida>//
		}

		static float MATH_API FastArcTan(float _value)//<Retorna el arcoTangente de manera rapida>//
		{
			float fArcTan = _value;
			float fBasePow = Pow(_value, 3); //<guardamos el valor de x al cubo >//
			float fXPow2 = Pow(_value, 2);//<guardamos el valor de x al cuadrado >//

			fArcTan -= (0.333333333333f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcTan += (0.200000000000f * fBasePow);

			return fArcTan;	//<el arcoTangente de un flotante de manera rapida>//
		}
		static float MATH_API FastArcTan2(float _value)//<Retorna el arcoTangente de manera rapida con mayor presicion>//
		{
			float fArcTan = _value;
			float fBasePow = Pow(_value, 3); //<guardamos el valor de x al cubo >//
			float fXPow2 = Pow(_value, 2);//<guardamos el valor de x al cuadrado >//

			fArcTan -= (0.333333333333f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcTan += (0.200000000000f * fBasePow);
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcTan -= (0.142857142857f * fBasePow);
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcTan += (0.111111111111f * fBasePow);
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcTan -= (0.090909090909f * fBasePow);

			return fArcTan;	//<el arcoTangente de un flotante de manera rapida y con mayor presicion>//
		}

		static float MATH_API FastArcTan(omRadians& _radians)//<Retorna el seno de manera rapida>//
		{
			float fArcTan = _radians.GetRadians();
			float fBasePow = Pow(fArcTan, 3); //<guardamos el valor de x al cubo >//
			float fXPow2 = Pow(fArcTan, 2);//<guardamos el valor de x al cuadrado >//

			fArcTan -= (0.333333333333f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcTan += (0.200000000000f * fBasePow);

			return fArcTan;	//<el arcoTangente de un flotante de manera rapida>//
		}
		static float MATH_API FastArcTan2(omRadians& _radians)//<Retorna el seno de manera rapida con mayor presicion>//
		{
			float fArcTan = _radians.GetRadians();
			float fBasePow = Pow(fArcTan, 3); //<guardamos el valor de x al cubo >//
			float fXPow2 = Pow(fArcTan, 2);//<guardamos el valor de x al cuadrado >//

			fArcTan -= (0.333333333333f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcTan += (0.200000000000f * fBasePow);
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcTan -= (0.142857142857f * fBasePow);
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcTan += (0.111111111111f * fBasePow);
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcTan -= (0.090909090909f * fBasePow);

			return fArcTan;	//<el arcoTangente de un flotante de manera rapida y con mayor presicion>//
		}

		static float MATH_API FastArcTan(omDegrees& _degrees)//<Retorna el seno de manera rapida>//
		{
			float fArcTan = _degrees.GetRadians();
			float fBasePow = Pow(fArcTan, 3); //<guardamos el valor de x al cubo >//
			float fXPow2 = Pow(fArcTan, 2);//<guardamos el valor de x al cuadrado >//

			fArcTan -= (0.333333333333f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcTan += (0.200000000000f * fBasePow);

			return fArcTan;	//<el arcoTangente de un flotante de manera rapida>//
		}
		static float MATH_API FastArcTan2(omDegrees& _degrees)//<Retorna el seno de manera rapida con mayor presicion>//
		{
			float fArcTan = _degrees.GetRadians();
			float fBasePow = Pow(fArcTan, 3); //<guardamos el valor de x al cubo >//
			float fXPow2 = Pow(fArcTan, 2);//<guardamos el valor de x al cuadrado >//

			fArcTan -= (0.333333333333f * fBasePow);//<desalloramos la serie >//
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcTan += (0.200000000000f * fBasePow);
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcTan -= (0.142857142857f * fBasePow);
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcTan += (0.111111111111f * fBasePow);
			fBasePow *= fXPow2;//<actualizamos nuestro exponente de x>//
			fArcTan -= (0.090909090909f * fBasePow);

			return fArcTan;	//<el arcoTangente de un flotante de manera rapida y con mayor presicion>//
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Declaracion de funciones Logaritmicas																				//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		static float MATH_API Log(float _value, float _base)//<Retorna el logaritmo de un flotante>//
		{
			return logf(_value) / logf(_base);		//<Retorna el logaritmo de un flotante>//
		}

		static float MATH_API LogN(float _value)//<Retorna el logaritmo natural de un flotante>//
		{
			return logf(_value)/logf(2);					//<Retorna el logaritmo de un flotante>//
		}

		static float MATH_API Log2(float _value)//<Retorna el logaritmo base 2 de un flotante>//
		{
			return log2f(_value);					//<Retorna el logaritmo base 2 de un flotante>//
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Declaracion de funciones de operaciones Matematicas																	//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		static float MATH_API Sqrt(float _value)//<Retorna la raiz cuadrada de un flotante>//
		{
			return sqrt(_value);			//<Retorna la raiz cuadrada de un flotante>//
		}

		static float MATH_API InvSqrt(float _value)//<Retorna la raiz cuadrada inversa de un flotante>//
		{
			return (1 / sqrt(_value));		//<Retorna la raiz cuadrada inversa de un flotante>//
		}

		static float MATH_API Square(float _value)//<Retorna el cuadrado de un flotante>//
		{
			return (_value*_value);			//<Retorna el cuadrado de un flotante>//
		}

		static float MATH_API Pow(float _value, int _power)//<Retorna el primer termino que es flotante elevado al segundo termino>//
		{
			return pow(_value, _power);		//<Retorna el primer termino que es flotante elevado al segundo termino>//
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Declaracion de operaciones de comparacion 																			//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		static T MATH_API Min(T _value1, T _value2){ return (_value1 <= _value2 ? _value1 : _value2); }//<Retorna el numero menor entre 2 datos cualquiera>//

		template<typename T>
		static T MATH_API Max(T _value1, T _value2){ return (_value1 >= _value2 ? _value1 : _value2);}//<Retorna el numero mayor entre 2 datos cualquiera>//

		template<typename T>
		static T MATH_API Min3(T _value1, T _value2, T _value3) { return Min(Min(_value1, _value2), _value3); }//<Retorna el numero menor entre 3 datos cualquiera>//

		template<typename T>
		static T MATH_API Max3(T _value1, T _value2, T _value3) { return Max(Max(_value1, _value2), _value3); }//<Retorna el numero mayor entre 3 datos cualquiera>//

		template<typename T>
		static void MATH_API Swap(T& _value1, T& _value2){ std::swap(_value1, _value2); }//<intercambia 2 datos cualquera>//
	};

#if PLATFORM == WINDOWS_MATH
	typedef omWindowsMath Math;
#endif
}
