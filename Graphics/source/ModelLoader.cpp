#include "ModelLoader.h"
#include "StaticModel.h"
#include <Importer.hpp>
#include <postprocess.h>
#include <GraphicDevice.h>

ModelLoader::ModelLoader()
{
	m_device = NULL;
}

ModelLoader::~ModelLoader()
{

}

Model * ModelLoader::LoadStaticModel(string _path, LoadMode _mode)
{
	string texturesPath = _path;
	VertexData myVertex;
	Model* pModel = new StaticModel();
	
	if (_mode == LoadWith_DEFAULT || _mode == LoadWith_ASSIMP)
	{
		//Carga de contenido por Assimp
		Assimp::Importer g_importer;
		const aiScene* g_scene;
		
		g_scene = g_importer.ReadFile(_path, aiProcess_ConvertToLeftHanded);

		if (!g_scene || !g_scene->HasMeshes())
		{
			return false;
		}

		size_t i = texturesPath.size() - 1;
		for (; i >= 0; i--)
		{
			if (texturesPath.at(i) == '/' || texturesPath.at(i) == '\\')
				break;

			texturesPath.pop_back();
		}

		pModel->m_meshes.resize(g_scene->mNumMeshes);

		bool hasMaterials = g_scene->HasMaterials();
		i = 0;
		for (; i < g_scene->mNumMeshes; ++i)
		{
			pModel->m_meshes[i] = new Mesh();

			if (g_scene->mMeshes[i]->HasPositions())
			{
				for (size_t j = 0; j < g_scene->mMeshes[i]->mNumVertices; ++j)
				{
					aiMesh* paiMesh = g_scene->mMeshes[i];

					myVertex.pos.X = paiMesh->mVertices[j].x;
					myVertex.pos.Y = paiMesh->mVertices[j].y;
					myVertex.pos.Z = paiMesh->mVertices[j].z;
					myVertex.pos.W = 1;

					if (g_scene->mMeshes[i]->HasNormals())
					{
						myVertex.norm.X = paiMesh->mNormals[j].x;
						myVertex.norm.Y = paiMesh->mNormals[j].y;
						myVertex.norm.Z = paiMesh->mNormals[j].z;
					}

					if (g_scene->mMeshes[i]->HasTextureCoords(0))
					{
						myVertex.tex.X = paiMesh->mTextureCoords[0][j].x;
						myVertex.tex.Y = paiMesh->mTextureCoords[0][j].y;
					}

					pModel->m_meshes[i]->m_VertexBuffer.addVertex(myVertex);
				}

				pModel->m_meshes[i]->m_VertexBuffer.create(m_device);

				Material* pMaterial = new Material();

				if (hasMaterials)
				{
					aiString pPath;
					g_scene->mMaterials[g_scene->mMeshes[i]->mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE, 0, &pPath);

					if (pPath.length > 0)
					{
						string textureName;
						string temp = pPath.C_Str();

						for (unsigned int j = temp.size() - 1; j >= 0; --j)
						{
							if (temp.at(j) == '/' || temp.at(j) == '\\')
								break;

							textureName.push_back(temp.at(j));
						}

						string finalPath = texturesPath;

						size_t j = textureName.size() - 1;
						for (; j >= 0; j--)
						{
							if (textureName.at(j) == '.')
								break;

							finalPath.push_back(textureName.at(j));
						}

						finalPath += ".dds";

						// Load the Texture
						Texture* newTexture = new Texture();
						newTexture->loadFromFile(m_device, finalPath);

						pMaterial->m_textures[TextureType_DIFFUSE] = newTexture->m_texture; //g_textureRV.m_texture; 
					}
				}

				pModel->m_meshes[i]->m_Material = pMaterial;
			}

			if (g_scene->mMeshes[i]->HasFaces())
			{
				for (size_t j = 0; j < g_scene->mMeshes[i]->mNumFaces; ++j)
				{
					for (size_t k = 0; k < g_scene->mMeshes[i]->mFaces->mNumIndices; k++)
					{
						pModel->m_meshes[i]->m_IndexBuffer.addIndex(g_scene->mMeshes[i]->mFaces[j].mIndices[k]);
					}
				}

				pModel->m_meshes[i]->m_IndexBuffer.create(m_device);
			}
		}
	}

	return pModel;
}

void ModelLoader::init(GraphicDevice * _device)
{
	m_device = _device;
}