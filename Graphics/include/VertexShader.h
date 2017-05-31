#pragma once
#include "Shader.h"

class VertexShader : public Shader
{
public:
	VertexShader();
	~VertexShader();

	virtual void init(){};
	virtual void destroy();

	ID3D11VertexShader* m_vertexShader;

	HRESULT createVertexShader(WCHAR* _szFileName, LPCSTR _szEntryPoint, LPCSTR _szShaderModel, ID3D11Device* _device);
};