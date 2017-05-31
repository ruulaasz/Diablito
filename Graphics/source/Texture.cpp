#include "Texture.h"
#include <DirectXTex.h>

Texture::Texture()
{
	m_texture = NULL;
}

Texture::~Texture()
{

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

ID3D11Texture2D * Texture::createAsRenderTarget()
{
	D3D11_TEXTURE2D_DESC desc;
	ID3D11Texture2D* pTexture;
	memset(&desc, 0, sizeof(D3D11_TEXTURE2D_DESC));

	desc.Width = 0;
	desc.Height = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_RENDER_TARGET;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	((ID3D11Device*)m_ID.Something)->CreateTexture2D(&desc, NULL, &pTexture);

	return pTexture;
}

void Texture::init()
{

}

void Texture::destroy()
{

}