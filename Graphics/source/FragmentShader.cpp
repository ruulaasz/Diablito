#include "FragmentShader.h"

FragmentShader::FragmentShader()
{

}

FragmentShader::~FragmentShader()
{

}

HRESULT FragmentShader::createFragmentShader(WCHAR* _szFileName, LPCSTR _szEntryPoint, LPCSTR _szShaderModel, ID3D11Device* _device)
{
	HRESULT HandleResult = S_OK;	//<Manejador de Resultados>//
	HandleResult = compileShaderFromFile(_szFileName, _szEntryPoint, _szShaderModel, &m_shaderBlob);

	// Create the vertex shader
	HandleResult = _device->CreatePixelShader(m_shaderBlob->GetBufferPointer(), m_shaderBlob->GetBufferSize(), NULL, &m_fragmentShader);
	if (FAILED(HandleResult))
	{
		m_shaderBlob->Release();
		return HandleResult;
	}

	return HandleResult;
}