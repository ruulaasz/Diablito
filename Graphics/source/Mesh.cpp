#include "Mesh.h"
#include "DirectXManager.h"

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
	_immediateContext->IASetInputLayout(m_Material->m_vertexShader->m_inputLayout.m_inputLayout);

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
	_immediateContext->DrawIndexed(m_IndexBuffer.getIndexSize(), 0, 0);
}

HRESULT Mesh::createMesh(const GraphicDevice* pDevice, const aiMesh& _mesh)
{
	HRESULT hr = S_OK;
	BufferInfo Info;

	hr = m_IndexBuffer.loadIndexFromMesh(const_cast<aiMesh&>(_mesh));
	if (hr == S_FALSE)
		return S_FALSE;

	Info.D3D11Usage = D3D11_USAGE_DEFAULT;
	Info.ByteWidth = sizeof(unsigned int) * m_IndexBuffer.getIndexSize();
	Info.BindFlags = D3D11_BIND_INDEX_BUFFER;
	Info.CPUAccesFlag = 0;

	ID3D11Device* pD3DDevice = reinterpret_cast<ID3D11Device*>(pDevice->getPtr());

	hr = m_IndexBuffer.create(pDevice);
	if (hr == S_FALSE)
		return S_FALSE;

	hr = m_VertexBuffer.loadVertexFromMesh(const_cast<aiMesh&>(_mesh));
	if (hr == S_FALSE)
		return S_FALSE;

	Info.D3D11Usage = D3D11_USAGE_DEFAULT;
	Info.ByteWidth = sizeof(VertexInfo) * m_VertexBuffer.getVertexSize();
	Info.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	Info.CPUAccesFlag = 0;

	m_VertexBuffer.create(pDevice);

	return S_OK;
}

void Mesh::assignNewTexture(Texture & _texture, FragmentShader * _pixelShader, VertexShader * _vertexShader, int _slot)
{
	m_Material->m_pixelShader = _pixelShader;
	m_Material->m_vertexShader = _vertexShader;
	m_Material->m_textures[_slot] = _texture.m_texture;
}