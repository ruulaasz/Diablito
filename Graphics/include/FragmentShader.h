#pragma once
#include "Shader.h"

class FragmentShader : public Shader
{
public:
	FragmentShader();
	~FragmentShader();

	virtual void init(){};
	virtual void destroy();

	ID3D11PixelShader* m_fragmentShader;

	HRESULT createFragmentShader(WCHAR* _szFileName, LPCSTR _szEntryPoint, LPCSTR _szShaderModel, ID3D11Device* _device);
};