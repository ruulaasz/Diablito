#include "DirectXManager.h"

DirectXManager::DirectXManager()
{

}

DirectXManager::~DirectXManager()
{

}

HRESULT DirectXManager::createDeviceAndSwapchain(HWND _hwnd, UINT _bufferCount, UINT _sampleDesc)
{
	HRESULT hr = S_OK;

	RECT rc;
	GetClientRect(_hwnd, &rc);
	m_width = rc.right - rc.left;
	m_height = rc.bottom - rc.top;

	UINT createDeviceFlags = 0;

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};

	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};

	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = _bufferCount;
	sd.BufferDesc.Width = m_width;
	sd.BufferDesc.Height = m_height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = _hwnd;
	sd.SampleDesc.Count = _sampleDesc;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		m_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDeviceAndSwapChain(NULL, m_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &m_swapchain, &m_device, &m_featureLevel, &m_deviceContext);
		if (SUCCEEDED(hr))
			break;
	}

	return hr;
}

HRESULT DirectXManager::createRenderTargetView()
{
	HRESULT hr = S_OK;

	// get the address of the back buffer
	ID3D11Texture2D *pBackBuffer = NULL;
	hr = m_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr))
		return hr;

	// use the back buffer address to create the render target
	hr = m_device->CreateRenderTargetView(pBackBuffer, NULL, &m_renderTarget.m_renderTarget);
	pBackBuffer->Release();
	if (FAILED(hr))
		return hr;

	return hr;
}

HRESULT DirectXManager::createDepthStencilView(UINT _MipLevels, UINT _ArraySize, UINT SampleDesc, UINT _CPUAccessFlags, UINT _MiscFlags)
{
	HRESULT hr = S_OK;

	// Create depth stencil texture
	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = m_width;
	descDepth.Height = m_height;
	descDepth.MipLevels = _MipLevels;
	descDepth.ArraySize = _ArraySize;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = SampleDesc;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = _CPUAccessFlags;
	descDepth.MiscFlags = _MiscFlags;
	hr = m_device->CreateTexture2D(&descDepth, NULL, &m_depthStencil);
	if (FAILED(hr))
		return hr;

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = m_device->CreateDepthStencilView(m_depthStencil, &descDSV, &m_depthStencilView);
	if (FAILED(hr))
		return hr;

	return hr;
}

void DirectXManager::setViewport(FLOAT _MinDepth, FLOAT _MaxDepth, FLOAT _TopLeftX, FLOAT _TopLeftY)
{
	// Set the viewport
	ZeroMemory(&m_viewport, sizeof(D3D11_VIEWPORT));
	m_viewport.MinDepth = _MinDepth;
	m_viewport.MaxDepth = _MaxDepth;
	m_viewport.TopLeftX = _TopLeftX;
	m_viewport.TopLeftY = _TopLeftY;
	m_viewport.Width = (float)m_width;
	m_viewport.Height = (float)m_height;
}

void DirectXManager::clearScreen(RenderTarget* _renderTarget, float _color[4])
{
	m_deviceContext->ClearRenderTargetView(_renderTarget->m_renderTarget, _color);
	m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void DirectXManager::cleanDevice()
{
	if (m_deviceContext) m_deviceContext->ClearState();
	if (m_vertexShader.m_vertexShader) m_vertexShader.m_vertexShader->Release();
	if (m_pixelShader.m_fragmentShader) m_pixelShader.m_fragmentShader->Release();
	if (m_depthStencil) m_depthStencil->Release();
	if (m_depthStencilView) m_depthStencilView->Release();
	if (m_renderTarget.m_renderTarget) m_renderTarget.m_renderTarget->Release();
	if (m_swapchain) m_swapchain->Release();
	if (m_device) m_device->Release();
}
