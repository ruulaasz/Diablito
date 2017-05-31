#pragma once
#include <d3d11.h>
#include <string>

using namespace std;

struct ID
{
	int iID;
	string strName;
	string strRoute;
	string strFileName;
	void* Something;
};

class Texture
{
public:
	Texture();
	~Texture();

	ID3D11ShaderResourceView* m_texture;
	ID m_ID;

	void init();
	void destroy();
	void loadFromFile(ID3D11Device* _device, string _route);
	ID3D11Texture2D* createAsRenderTarget();
};