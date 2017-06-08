#pragma once
#include "Model.h"

/**
* Enum of the options for loading models
*/
enum LoadMode
{
  LoadWith_DEFAULT = 0,
  LoadWith_ASSIMP = 1
};

class GraphicDevice;

/**
* Manager class for load and create 3d models 
*/
class ModelLoader
{
 public:
  ModelLoader();
  ~ModelLoader();
  
  /**
  * Initialize the loader
  *
  * @param _device
  * Reference to a graphic device
  *
  */
  void init(GraphicDevice* _device);

  /**
  * Load a model using a path and the mode
  *
  * @param _path
  * String of the model path
  *
  * @param _mode = LoadWith_ASSIMP
  * The tool used to read the data
  *
  */
  Model* LoadStaticModel(string _path, LoadMode _mode = LoadWith_ASSIMP);
 
 private:
  GraphicDevice* m_device;
};