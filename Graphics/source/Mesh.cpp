#include "Mesh.h"
#include "GraphicManager.h"

Mesh::Mesh()
{
	
}

Mesh::~Mesh()
{

}

void Mesh::render(const GraphicDeviceContext* _immediateContext)
{
	ID3D11DeviceContext* pDeviceContext = reinterpret_cast<ID3D11DeviceContext*>(_immediateContext->getPtr());

	//Seteamos el Shader asignado al Modelo 
	pDeviceContext->VSSetShader(m_Material->m_vertexShader->m_vertexShader, NULL, 0);
	pDeviceContext->IASetInputLayout(m_Material->m_vertexShader->m_inputLayout.m_inputLayout);

	//Seteamos el Shader Perteneciente al modelo
	pDeviceContext->PSSetShader(m_Material->m_pixelShader->m_fragmentShader, NULL, 0);
	pDeviceContext->PSSetShaderResources(0, 8, m_Material->m_textures);

	//Seteamos el VertexBuffer del mesh
	UINT stride = sizeof(VertexData);
	UINT offset = 0;
	pDeviceContext->IASetVertexBuffers(0, 1, &m_VertexBuffer.m_buffer, &stride, &offset);

	//Seteamos el index buffer del mesh
	pDeviceContext->IASetIndexBuffer(m_IndexBuffer.m_buffer, DXGI_FORMAT_R32_UINT, 0);

	//Seteamos la topologia primitiva
	pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Imprimimos el mesh
	pDeviceContext->DrawIndexed(m_IndexBuffer.getIndexSize(), 0, 0);
}

void Mesh::assignNewTexture(const Texture* _texture, unsigned int _slot)
{
	m_Material->m_textures[_slot] = _texture->m_texture;
}

void Mesh::assignNewMaterial(Material * _material)
{
	m_Material = _material;
}