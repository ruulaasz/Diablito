#pragma once
#include <vector>
#include "Mesh.h"

struct Triangle
{
	VertexData m_vertex[3];

	Triangle() {}
};

using std::vector;
class GraphicDevice;

class Model
{
public:
	Model();
	~Model();

	vector <Mesh* > m_meshes;
	omMatrix4D m_transform;
	vector <Triangle* > m_triangles;
	uint m_lastIndex;
	omAABB m_boundingBox;
	ID m_ID;

	virtual void createModel(string _path, const aiNode& _node, const aiScene* _scene, const GraphicDevice* _device, VertexShader* _vertexShader, FragmentShader* _pixelShader);
	virtual void createMesh(const GraphicDevice* _device, const aiMesh& _mesh);
	virtual void assignMeshMaterial(aiMaterial* _material, int _index, string _path, VertexShader* _vertexShader, FragmentShader* _pixelShader);
	virtual void setTransformMatrix(aiMatrix4x4* _transformMatrix);
	virtual void getTriangles(aiNode* _node, const aiScene* _scene);
	virtual void setBox();

	virtual void init() = 0;
	virtual void destroy() = 0;
	virtual void update(float _deltaTime) = 0;
	virtual void render(ID3D11DeviceContext* _immediateContext);
};