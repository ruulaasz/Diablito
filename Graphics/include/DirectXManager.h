#pragma once

#include "FragmentShader.h"
#include "VertexShader.h"
#include "RenderTarget.h"

class DirectXManager
{
public:
	DirectXManager();
	~DirectXManager();

	IDXGISwapChain* m_swapchain;					// the pointer to the swap chain interface
	ID3D11Device* m_device;							// the pointer to our Direct3D device interface
	ID3D11DeviceContext* m_deviceContext;			// the pointer to our Direct3D device context
	RenderTarget m_renderTarget;					// global declaration
	VertexShader m_vertexShader;					// the vertex shader
	FragmentShader m_pixelShader;					// the pixel shader
	D3D_DRIVER_TYPE m_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL m_featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11Texture2D* m_depthStencil = NULL;
	ID3D11DepthStencilView* m_depthStencilView = NULL;
	ID3D11SamplerState* m_samplerState = NULL;
	D3D11_VIEWPORT m_viewport;

	UINT m_width;
	UINT m_height;

	HRESULT createDeviceAndSwapchain(HWND _hwnd, UINT _bufferCount = 1, UINT _sampleDesc = 1);
	HRESULT createRenderTargetView();
	HRESULT createDepthStencilView(UINT _MipLevels = 1, UINT _ArraySize = 1, UINT SampleDesc = 1, UINT _CPUAccessFlags = 0, UINT _MiscFlags = 0);	//<Creacion del Depth stencil texture y depth stencil view>//
	void setViewport(FLOAT _MinDepth = 0.0f, FLOAT _MaxDepth = 1.0f, FLOAT _TopLeftX = 0.0f, FLOAT _TopLeftY = 0.0f);

	void clearScreen(RenderTarget* _renderTarget, float _color[4] = {});
	void cleanDevice();
};

