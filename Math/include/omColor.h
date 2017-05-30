//////////////////////////////////////////////////////////////////////////
///																		//
// @file   omColor.h													//	
// @Author Raul Portillo (ruulaasz_@hotmail.com)						//
// @date   2015/10/10													//
// @brief  Class for a Color mathematical structure						//
// @bug	   Not Fully Tested												//
//																		//
//////////////////////////////////////////////////////////////////////////
#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Declaracion de la clase omColor																						//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace OmicronSDK
{
	class omColorRGBA
	{
		union Pixel																//< Estructura que almacena la informacion de un pixel>//
		{
			struct 
			{
				unsigned char r, g, b, a;										//< Canales de cada color & alfa 0x00>//
			};

			unsigned long l;													//< Variable que contiene a los colores 0x000000FF>//
		};
					
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Declaracion de contructores y destructores																			//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public:
		explicit omColorRGBA(Pixel _Pixel) : m_Pixel(_Pixel){};					//< Constructor que pide un valor PIXEL predeterminado>//
		omColorRGBA(short _r = 0, short _g = 0, short _b = 0, short _a = 0);	//< Constructor que pide los valores de color del pixel predeterminado>//
		omColorRGBA(const omColorRGBA& _CopyObj);								//< Constructor que crea un objeto copia del objeto recibido>//

		~omColorRGBA();															//< Destructor de la clase>//

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Declaracion de variables miembro de la clase																			//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		Pixel m_Pixel;															//< Contiene la informacion de un solo pixel>//

	
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Declaracion de la Sobrecarga de operadores =,+,-,+=,-=,==,!=															//
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		omColorRGBA& operator=	(const omColorRGBA& _Color);
		omColorRGBA& operator=	(const Pixel& _Pixel);
		omColorRGBA& operator=	(unsigned int _Value);

		omColorRGBA operator+	(const omColorRGBA& _Color);
		omColorRGBA operator-	(const omColorRGBA& _Color);

		omColorRGBA& operator+=	(const omColorRGBA& _Color);
		omColorRGBA& operator-=	(const omColorRGBA& _Color);

		bool operator== (const omColorRGBA& _Color);
		bool operator!= (const omColorRGBA& _Color);
	};
}