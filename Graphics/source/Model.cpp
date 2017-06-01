#include "Model.h"
#include "GraphicManager.h"

Model::Model()
{
	m_lastIndex = 0;
}

Model::~Model()
{

}

void Model::createModel(string _path, const aiNode& _node, const aiScene* _scene, const GraphicDevice* _device, VertexShader* _vertexShader, FragmentShader* _pixelShader)
{
	//sacamos los meshes de un modelo en especifico dentro de la escena
	for (uint i = 0; i < _node.mNumMeshes; i++)
	{
		createMesh(_device,*_scene->mMeshes[_node.mMeshes[i]]);

		if (_scene->HasMaterials())
		{
			assignMeshMaterial(_scene->mMaterials[_scene->mMeshes[_node.mMeshes[i]]->mMaterialIndex], i, _path.c_str(), _vertexShader, _pixelShader);
		}
	}

	getTriangles(const_cast<aiNode*>(&_node), _scene);

	setBox();

	setTransformMatrix(const_cast<aiMatrix4x4*>(&_node.mTransformation));
}

void Model::createMesh(const GraphicDevice* _device, const aiMesh& _mesh)
{
	ID3D11Device* pD3DDevice = reinterpret_cast<ID3D11Device*>(_device->getPtr());
	Mesh* pMesh = new Mesh();
	pMesh->createMesh(_device, _mesh);
	m_meshes.push_back(pMesh);
}

void Model::assignMeshMaterial(aiMaterial * _material, int _index, string _path, VertexShader * _vertexShader, FragmentShader * _pixelShader)
{
	aiString Temp;
	string TexturePath;
	m_meshes.at(_index)->m_Material = new Material();
	//pos cada mesh assignamos cada tipo de textura
	for (int i = 0; i < aiTextureType_UNKNOWN; i++)
	{
		Texture* NewTexture = new Texture;

		if (_material->GetTexture((aiTextureType)i, 0, &Temp) == aiReturn::aiReturn_SUCCESS)
		{
			TexturePath.clear();

			string LoadString = Temp.C_Str();

			uint It = LoadString.size() - 1;

			for (; It >= 0; It--)
			{
				if (LoadString[It] == '/' || LoadString[It] == '\\')
					break;
			}

			It++;
			TexturePath.push_back('\\');

			while (It < LoadString.size())
			{
				TexturePath.push_back(LoadString.at(It));
				It++;
			}

			if (TexturePath.at(TexturePath.size() - 4) == '.')
			{
				TexturePath.pop_back();
				TexturePath.pop_back();
				TexturePath.pop_back();
			}

			if (TexturePath.back() != '.')
				TexturePath.push_back('.');

			NewTexture->m_ID.Something = m_ID.Something;
			NewTexture->m_ID.strName = TexturePath;
			NewTexture->m_ID.strFileName = TexturePath + "dds";
			NewTexture->m_ID.strRoute = _path + TexturePath + "dds";
			NewTexture->loadFromFile(reinterpret_cast<ID3D11Device*>(NewTexture->m_ID.Something), NewTexture->m_ID.strRoute);
			NewTexture->init();
		}

		//asigno las texturas al material
		m_meshes.at(_index)->m_Material->m_textures[i] = NewTexture->m_texture;
	}

	//asigno los colores de mi material
	m_meshes.at(_index)->m_Material->createMaterial(_material, _pixelShader, _vertexShader);
}

void Model::setTransformMatrix(aiMatrix4x4 * _transformMatrix)
{
	m_transform.m00 = _transformMatrix->a1;
	m_transform.m01 = _transformMatrix->a2;
	m_transform.m02 = _transformMatrix->a3;
	m_transform.m03 = _transformMatrix->a4;
	  				  
	m_transform.m10 = _transformMatrix->b1;
	m_transform.m11 = _transformMatrix->b2;
	m_transform.m12 = _transformMatrix->b3;
	m_transform.m13 = _transformMatrix->b4;
	  				  
	m_transform.m20 = _transformMatrix->c1;
	m_transform.m21 = _transformMatrix->c2;
	m_transform.m22 = _transformMatrix->c3;
	m_transform.m23 = _transformMatrix->c4;
	  				  
	m_transform.m30 = _transformMatrix->d1;
	m_transform.m31 = _transformMatrix->d2;
	m_transform.m32 = _transformMatrix->d3;
	m_transform.m33 = _transformMatrix->d4;
}

void Model::getTriangles(aiNode * _node, const aiScene * _scene)
{
	for (unsigned int i = 0; i < _node->mNumMeshes; i++)
	{
		for (unsigned int j = 0; j < _scene->mMeshes[_node->mMeshes[i]]->mNumFaces; j++)
		{
			m_triangles.push_back(new Triangle);

			for (int k = 0; k < 3; k++)
			{
				m_triangles.back()->m_vertex->pos.X = _scene->mMeshes[_node->mMeshes[i]]->mVertices[_scene->mMeshes[_node->mMeshes[i]]->mFaces[j].mIndices[k]].x;
				m_triangles.back()->m_vertex->pos.Y = _scene->mMeshes[_node->mMeshes[i]]->mVertices[_scene->mMeshes[_node->mMeshes[i]]->mFaces[j].mIndices[k]].y;
				m_triangles.back()->m_vertex->pos.Z = _scene->mMeshes[_node->mMeshes[i]]->mVertices[_scene->mMeshes[_node->mMeshes[i]]->mFaces[j].mIndices[k]].z;
			}
		}
	}
}

void Model::setBox()
{
	m_boundingBox.m_Min = m_boundingBox.m_Max = m_triangles.back()->m_vertex->pos;

	for (uint i = 0; i < m_triangles.size(); i++)
	{
		//Minimo
		if (m_triangles.at(i)->m_vertex->pos.X < m_boundingBox.m_Min.X)
		{
			m_boundingBox.m_Min.X = m_triangles.at(i)->m_vertex->pos.X;
		}

		if (m_triangles.at(i)->m_vertex->pos.Y < m_boundingBox.m_Min.Y)
		{
			m_boundingBox.m_Min.Y = m_triangles.at(i)->m_vertex->pos.Y;
		}

		if (m_triangles.at(i)->m_vertex->pos.Z < m_boundingBox.m_Min.Z)
		{
			m_boundingBox.m_Min.Z = m_triangles.at(i)->m_vertex->pos.Z;
		}

		//Maximo
		if (m_triangles.at(i)->m_vertex->pos.X > m_boundingBox.m_Max.X)
		{
			m_boundingBox.m_Max.X = m_triangles.at(i)->m_vertex->pos.X;
		}

		if (m_triangles.at(i)->m_vertex->pos.Y > m_boundingBox.m_Max.Y)
		{
			m_boundingBox.m_Max.Y = m_triangles.at(i)->m_vertex->pos.Y;
		}

		if (m_triangles.at(i)->m_vertex->pos.Z > m_boundingBox.m_Max.Z)
		{
			m_boundingBox.m_Max.Z = m_triangles.at(i)->m_vertex->pos.Z;
		}
	}

	omVector3D Temp;

	Temp = m_boundingBox.m_Max - m_boundingBox.m_Min;
	Temp /= 2;

	m_boundingBox.m_vecCenter = Temp + m_boundingBox.m_Min;
}

void Model::render(ID3D11DeviceContext * _immediateContext)
{
	//Rendereamos el mesh del modelo
	for (uint i = 0; i < m_meshes.size(); i++)
	{
		m_meshes.at(i)->render(_immediateContext);
	}
}