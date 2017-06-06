#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Material.h"
#include "Texture.h"

class GraphicDeviceContext;

class Mesh
{
public:
	Mesh();
	~Mesh();

	VertexBuffer m_VertexBuffer;
	IndexBuffer m_IndexBuffer;
	Material* m_Material;

	void render(const GraphicDeviceContext* _immediateContext);
	void assignNewTexture(const Texture* _texture, unsigned int _slot);
	void assignNewMaterial(Material* _material);
};