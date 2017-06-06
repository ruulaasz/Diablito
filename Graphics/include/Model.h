#pragma once
#include <vector>
#include "Mesh.h"

using std::vector;
class GraphicDevice;
class GraphicDeviceContext;

class Model
{
public:
	Model();
	~Model();

	vector <Mesh* > m_meshes;
	omMatrix4D m_transform;

	virtual void assignMeshMaterial(Material* _material, unsigned int _index);
	virtual void assignMeshTexture(Texture* _texture, unsigned int _slot, unsigned int _index);
	virtual void setTransformMatrix(aiMatrix4x4* _transformMatrix);

	virtual void init() {};
	virtual void destroy() {};
	virtual void update(float _deltaTime) {};
	virtual void render(const GraphicDeviceContext* _immediateContext);
};