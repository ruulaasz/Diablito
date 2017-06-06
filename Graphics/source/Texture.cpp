#include "Texture.h"
#include <DirectXTex.h>

Texture::Texture()
{
	m_texture = NULL;
}

Texture::~Texture()
{
	destroy();
}

void Texture::loadFromFile(ID3D11Device* _device, string _route)
{
	// Load the Texture
	HRESULT hr = S_OK;
	DirectX::ScratchImage Image;
	wstring wide_string = wstring(_route.begin(), _route.end());
	const wchar_t* result = wide_string.c_str();
	hr = DirectX::LoadFromDDSFile(result, NULL, NULL, Image);

	hr = DirectX::CreateShaderResourceView(_device, Image.GetImages(), Image.GetImageCount(), Image.GetMetadata(), &m_texture);
}

void Texture::init()
{

}

void Texture::destroy()
{

}