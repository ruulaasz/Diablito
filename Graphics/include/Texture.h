#pragma once
#include <string>
#include <d3d11.h>

using std::string;

class GraphicDevice;

/**
* Directx Texture
*/
class Texture
{
 public:
  Texture();
  ~Texture();
  
  /**
  * Fill an input layout using the vertex shader blob data
  *
  * @param _device
  * Reference to a graphic device
  *
  * @param _route
  * The file route
  *
  */
  void loadFromFile(GraphicDevice* _device, string _route);
  
  ID3D11ShaderResourceView* m_texture;
};