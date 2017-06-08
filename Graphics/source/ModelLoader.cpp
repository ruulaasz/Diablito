#include "ModelLoader.h"
#include <Importer.hpp>
#include <postprocess.h>
#include "StaticModel.h"
#include <GraphicDevice.h>

ModelLoader::ModelLoader()
{
  m_device = nullptr;
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
  	Assimp::Importer g_importer;
  	const aiScene* g_scene;
  	
  	g_scene = g_importer.ReadFile(_path, aiProcess_ConvertToLeftHanded);
  
  	if (!g_scene || !g_scene->HasMeshes())
  	{
      throw "NullPointer g_scene";
  	}
  
  	for (size_t i = texturesPath.size() - 1; i >= 0; i--)
  	{
  	  if (texturesPath.at(i) == '/' || texturesPath.at(i) == '\\')
  	  	break;
  	  
  	  texturesPath.pop_back();
  	}
  
  	pModel->m_meshes.resize(g_scene->mNumMeshes);
  
  	bool hasMaterials = g_scene->HasMaterials();

  	for (size_t i = 0; i < g_scene->mNumMeshes; ++i)
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
  	  	  
  	  	  pModel->m_meshes[i]->m_vertexBuffer.addVertex(myVertex);
  	  	}
  	  
  	  	pModel->m_meshes[i]->m_vertexBuffer.create(m_device);
  	  
  	  	Material* pMaterial = new Material();
  	  
  	  	if (hasMaterials)
  	  	{
  	  	  aiString pPath;
  	  	  
  	  	  for (size_t k = 1; k < 12; ++k)
  	  	  {
  	  	  	g_scene->mMaterials[g_scene->mMeshes[i]->mMaterialIndex]->GetTexture((aiTextureType)k, 0, &pPath);
  	  	  
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
  	  	  	  
  	  	  	  pMaterial->m_textures[k] = newTexture->m_texture;
  	  	  	}
  	  	  }
  	  	}
  	  
  	  	pModel->m_meshes[i]->m_material = pMaterial;
  	  }
  	  
  	  if (g_scene->mMeshes[i]->HasFaces())
  	  {
  	  	for (size_t j = 0; j < g_scene->mMeshes[i]->mNumFaces; ++j)
  	  	{
  	  	  for (size_t k = 0; k < g_scene->mMeshes[i]->mFaces->mNumIndices; k++)
  	  	  {
  	  	  	pModel->m_meshes[i]->m_indexBuffer.addIndex(g_scene->mMeshes[i]->mFaces[j].mIndices[k]);
  	  	  }
  	  	}
  	  
  	  	pModel->m_meshes[i]->m_indexBuffer.create(m_device);
  	  }
  	}
  }
  
  return pModel;
}

void ModelLoader::init(GraphicDevice * _device)
{
  if (!_device)
  {
  	throw "NullPointer _device";
  }

  m_device = _device;
}