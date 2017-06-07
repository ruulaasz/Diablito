#include "InputLayout.h"

InputLayout::InputLayout()
{
	m_layoutArray = NULL;
	m_inputLayout = NULL;
	m_layoutElements = 0;
}

InputLayout::~InputLayout()
{
	destroy();
}

HRESULT InputLayout::CreateInputLayoutFromVertexShaderSignature(ID3D11Device* _device, ID3DBlob* _pShaderBlob)
{
	// Reflect shader info
	ID3D11ShaderReflection* pVertexShaderReflection = NULL;
	if (FAILED(D3DReflect(_pShaderBlob->GetBufferPointer(), _pShaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**) &pVertexShaderReflection)))
	{
		return S_FALSE;
	}

	// Get shader info
	D3D11_SHADER_DESC shaderDesc;
	pVertexShaderReflection->GetDesc(&shaderDesc);

	m_layoutArray = new D3D11_INPUT_ELEMENT_DESC[shaderDesc.InputParameters];
	m_layoutElements = shaderDesc.InputParameters;

	// Read input layout description from shader info
	for (int i = 0; i < (int)shaderDesc.InputParameters; i++)
	{
		D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
		pVertexShaderReflection->GetInputParameterDesc(i, &paramDesc);

		// fill out input element desc
		D3D11_INPUT_ELEMENT_DESC elementDesc;
		elementDesc.SemanticName = paramDesc.SemanticName;
		elementDesc.SemanticIndex = paramDesc.SemanticIndex;
		elementDesc.InputSlot = 0;
		elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		elementDesc.InstanceDataStepRate = 0;

		// determine DXGI format
		if (paramDesc.Mask == 1)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
		}
		else if (paramDesc.Mask <= 3)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
		}
		else if (paramDesc.Mask <= 7)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
		}
		else if (paramDesc.Mask <= 15)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		}

		//save element desc
		m_layoutArray[i] = elementDesc;
	}

	if (!m_layoutArray)
		return S_FALSE;

	return createInputLayout(_pShaderBlob, _device);
}

HRESULT InputLayout::createInputLayout(ID3DBlob* _VSBlob,  ID3D11Device* _device)
{
	HRESULT HandleResult = S_OK;	//<Manejador de Resultados>//
	// Create the input layout
	HandleResult = _device->CreateInputLayout(m_layoutArray, m_layoutElements, _VSBlob->GetBufferPointer(),
		_VSBlob->GetBufferSize(), &m_inputLayout);
	//_pVSBlob->Release();

	if (FAILED(HandleResult))
		return HandleResult;

	return HandleResult;
}

void InputLayout::destroy()
{
	delete [] m_layoutArray;

	if (m_inputLayout)
		m_inputLayout->Release();
}
