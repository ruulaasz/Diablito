#pragma once
#include <vector>
#include "Mesh.h"

using namespace std;

struct Triangle
{
	VertexInfo m_vertex[3];

	Triangle() {}
};

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

	virtual void createModel(string _path, aiNode* _node, const aiScene* _scene, ID3D11Device* _device, VertexShader* _vertexShader, FragmentShader* _pixelShader);
	virtual void createMesh(aiMesh* _mesh, ID3D11Device* _device);
	virtual void assignMeshMaterial(aiMaterial* _material, int _index, string _path, VertexShader* _vertexShader, FragmentShader* _pixelShader);
	virtual void setTransformMatrix(aiMatrix4x4* _transformMatrix);
	virtual void getTriangles(aiNode* _node, const aiScene* _scene);
	virtual void setBox();

	virtual void init() = 0;
	virtual void destroy() = 0;
	virtual void update(float _deltaTime) = 0;
	virtual void render(ID3D11DeviceContext* _immediateContext);
};