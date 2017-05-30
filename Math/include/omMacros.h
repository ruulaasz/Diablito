#pragma once

/************************************************************************/
/* inclucion de cabeceras necesarias para la compilacion                */
/************************************************************************/
#include <stdio.h>
#include <iostream>

/************************************************************************/
/* crea de manera automatica una variable miembro de una clase con su	*/
/* respectivo Set & Get													*/
/************************************************************************/
#define SET_AND_GET(Type, a)				\
	public:									\
	Type get##a##()							\
				{return m_##a##;}			\
	void set##a##(Type B)					\
				{m_##a## = B;}				\
	protected:								\
	Type m_##a##;							\
	public:

/************************************************************************/
/* soMacros para alojamiento de memoria en versiones DEBUG y RELEASE      */
/************************************************************************/
#if defined(_DEBUG)
#	define OM_NEW new
#	define OM_DELETE delete
#	define OM_DELETE_ARRAY delete []
#else
#	define OM_NEW new
#	define OM_DELETE delete
#	define OM_DELETE_ARRAY delete []
#endif

/************************************************************************/
/* soMacros para alojamiento de memoria seguros                           */
/************************************************************************/
#if !defined(SAFE_DELETE)
#define SAFE_DELETE(x) if(x) SOE_DELETE x; x=NULL;
#endif

#if !defined(SAFE_DELETE_ARRAY)
#define SAFE_DELETE_ARRAY(x) if (x) SOE_DELETE_ARRAY x; x=NULL; 
#endif

#if !defined(SAFE_RELEASE)
#define SAFE_RELEASE(x) if(x) x->Release(); x=NULL;
#endif

/************************************************************************/
/* soMacros para el control de errores en modo Debug                      */
/************************************************************************/
#if defined(_DEBUG)
#	define REPORT_ERROR(x) std::cout<<(x)<<std::endl;
#else
#	define REPORT_ERROR(x)
#endif

/************************************************************************/
/* soMacros de tipos de función                    					    */
/************************************************************************/
#ifndef VARARGS
#define VARARGS			__cdecl					//Funciones con argumentos variables
#endif
#ifndef CDECL
#define CDECL			__cdecl					//Funciones en Standard C
#endif
#ifndef STDCALL
#define STDCALL			__stdcall				//Convención de llamada Standard
#endif
#ifndef FORCEINLINE
#define FORCEINLINE		__forceinline			//Forza a que el código esté inline
#endif
#ifndef FORCENOINLINE
#define FORCENOINLINE	__declspec(noinline)	//Forza a que el código NO esté inline
#endif
#ifndef RESTRICT
#define RESTRICT		__restrict				//Restrict indica al compilador que un simbolo no tiene alias en el ambito actual
#endif