#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Material.h"
#include "Texture.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	VertexBuffer m_VertexBuffer;
	IndexBuffer m_IndexBuffer;
	Material* m_Material;

	void render(ID3D11DeviceContext* _immediateContext);
	HRESULT createMesh(aiMesh& _mesh, ID3D11Device* _device);
	void assignNewTexture(Texture& _texture, FragmentShader* _pixelShader, VertexShader* _vertexShader, int _slot);
};