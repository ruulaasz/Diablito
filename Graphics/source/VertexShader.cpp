#include "VertexShader.h"

VertexShader::VertexShader()
{
	m_vertexShader = NULL;
}

VertexShader::~VertexShader()
{
	destroy();
}

HRESULT VertexShader::createVertexShader(WCHAR* _szFileName, LPCSTR _szEntryPoint, LPCSTR _szShaderModel, ID3D11Device* _device)
{
	HRESULT HandleResult = S_OK;	//<Manejador de Resultados>//
	HandleResult = compileShaderFromFile(_szFileName, _szEntryPoint, _szShaderModel, &m_shaderBlob);

	// Create the vertex shader
	HandleResult = _device->CreateVertexShader(m_shaderBlob->GetBufferPointer(), m_shaderBlob->GetBufferSize(), NULL, &m_vertexShader);
	if (FAILED(HandleResult))
	{
		m_shaderBlob->Release();
		return HandleResult;
	}

	return HandleResult;
}

void VertexShader::destroy()
{
	//m_vertexShader->Release();
}