#pragma once
#include "Model.h"

enum LoadMode
{
	Load_DEFAULT = 0,
	Load_ASSIMP = 1
};

class GraphicDevice;

class ModelLoader
{
public:
	ModelLoader();
	~ModelLoader();

	Model* LoadStaticModel(string _path, LoadMode _mode = Load_DEFAULT);

	void init(GraphicDevice* _device);

private:
	GraphicDevice* m_device;
};

