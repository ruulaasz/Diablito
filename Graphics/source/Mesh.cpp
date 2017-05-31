#include "Mesh.h"

Mesh::Mesh()
{
	
}

Mesh::~Mesh()
{

}

void Mesh::render(ID3D11DeviceContext * _immediateContext)
{
	//Seteamos el Shader asignado al Modelo 
	_immediateContext->VSSetShader(m_Material->m_vertexShader->m_vertexShader, NULL, 0);
	_immediateContext->IASetInputLayout(m_Material->m_vertexShader->m_inputLayout.m_vertexLayout);

	//Seteamos el Shader Perteneciente al modelo
	_immediateContext->PSSetShader(m_Material->m_pixelShader->m_fragmentShader, NULL, 0);

	_immediateContext->PSSetShaderResources(0, 8, m_Material->m_textures);

	//Seteamos el VertexBuffer del mesh
	UINT stride = sizeof(VertexInfo);
	UINT offset = 0;
	_immediateContext->IASetVertexBuffers(0, 1, &m_VertexBuffer.m_buffer, &stride, &offset);

	//Seteamos el index buffer del mesh
	_immediateContext->IASetIndexBuffer(m_IndexBuffer.m_buffer, DXGI_FORMAT_R32_UINT, 0);

	//Seteamos la topologia primitiva
	_immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Imprimimos el mesh
	_immediateContext->DrawIndexed(m_IndexBuffer.m_indexNumber, 0, 0);
}

HRESULT Mesh::createMesh(aiMesh & _mesh, ID3D11Device * _device)
{
	HRESULT hr = S_OK;
	BufferInfo Info;

	hr = m_IndexBuffer.loadIndexFromMesh(_mesh);
	if (hr == S_FALSE)
		return S_FALSE;

	Info.D3D11Usage = D3D11_USAGE_DEFAULT;
	Info.ByteWidth = sizeof(unsigned int) * m_IndexBuffer.m_indexNumber;
	Info.BindFlags = D3D11_BIND_INDEX_BUFFER;
	Info.CPUAccesFlag = 0;

	hr = m_IndexBuffer.createIndexBuffer(_device, Info);
	if (hr == S_FALSE)
		return S_FALSE;

	hr = m_VertexBuffer.loadVertexFromMesh(_mesh);
	if (hr == S_FALSE)
		return S_FALSE;

	Info.D3D11Usage = D3D11_USAGE_DEFAULT;
	Info.ByteWidth = sizeof(VertexInfo) * m_VertexBuffer.m_vertexNumber;
	Info.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	Info.CPUAccesFlag = 0;

	m_VertexBuffer.createVertexBuffer(_device, Info);

	return S_OK;
}

void Mesh::assignNewTexture(Texture & _texture, FragmentShader * _pixelShader, VertexShader * _vertexShader, int _slot)
{
	m_Material->m_pixelShader = _pixelShader;
	m_Material->m_vertexShader = _vertexShader;
	m_Material->m_textures[_slot] = _texture.m_texture;
}