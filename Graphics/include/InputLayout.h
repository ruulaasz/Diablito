#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>

class InputLayout
{
public:
	InputLayout();
	~InputLayout();

	virtual void init(){};
	virtual void destroy();

	HRESULT CreateInputLayoutFromVertexShaderSignature(ID3DBlob* _pVSBlob);//creamos aun layoutarray, 
	HRESULT createInputLayout(ID3DBlob* _VSBlob,  ID3D11Device* _device);

	D3D11_INPUT_ELEMENT_DESC* m_layoutArray;
	unsigned int m_layoutElements;

	ID3D11InputLayout* m_inputLayout;
};