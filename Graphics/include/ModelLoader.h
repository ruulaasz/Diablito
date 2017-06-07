#pragma once
#include "Model.h"

enum LoadMode
{
	LoadWith_DEFAULT = 0,
	LoadWith_ASSIMP = 1
};

class GraphicDevice;

class ModelLoader
{
public:
	ModelLoader();
	~ModelLoader();

	Model* LoadStaticModel(string _path, LoadMode _mode = LoadWith_DEFAULT);

	void init(GraphicDevice* _device);

private:
	GraphicDevice* m_device;
};