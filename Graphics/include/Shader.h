#pragma once
#include "InputLayout.h"

class Shader
{
public:
	Shader();
	~Shader();

	ID3DBlob* m_shaderBlob;
	InputLayout m_inputLayout;

	virtual void init() = 0;
	virtual void destroy() = 0;

	HRESULT compileShaderFromFile(WCHAR* _szFileName, LPCSTR _szEntryPoint, LPCSTR _szShaderModel, ID3DBlob** _ppBlobOut);
};