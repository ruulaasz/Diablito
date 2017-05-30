#include <windows.h>
#include <DirectXTex.h>
#include <Omicron_Math.h>
#include <DirectXManager.h>
#include <ConstantBuffer.h>
#include <Texture.h>

//define the screen resolution
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

using namespace OmicronSDK;
using namespace DirectX;

struct SimpleVertex
{
	omVector3D Pos;
	omVector2D Tex;
};

struct CBView
{
	omMatrix4D mView;
};

struct CBProj
{
	omMatrix4D mProjection;
};

struct CBWorld
{
	omMatrix4D mWorld;
};

// global declarations
DirectXManager g_Graphics;

HINSTANCE g_hInst = NULL;
HWND g_hWnd = NULL;

Texture g_textureRV;

ConstantBuffer g_indexBuffer;
ConstantBuffer g_vertexBuffer;
ConstantBuffer g_pCBView;
ConstantBuffer g_pCBProj;
ConstantBuffer g_pCBWorld;

omMatrix4D  g_World;
omMatrix4D  g_View;
omMatrix4D  g_Projection;

float g_deltaTime = 0.0f;

// this function initializes and prepares Direct3D for use
HRESULT InitD3D(HWND hWnd)
{
	HRESULT hr = S_OK;

	hr = g_Graphics.createDeviceAndSwapchain(hWnd);
	if (FAILED(hr))
		return hr;

	hr = g_Graphics.createRenderTargetView();
	if (FAILED(hr))
		return hr;

	hr = g_Graphics.createDepthStencilView();
	if (FAILED(hr))
		return hr;

	// set the render target as the back buffer
	g_Graphics.m_deviceContext->OMSetRenderTargets(1, &g_Graphics.m_renderTarget.m_renderTarget, g_Graphics.m_depthStencilView);

	g_Graphics.setViewport();

	g_Graphics.m_deviceContext->RSSetViewports(1, &g_Graphics.m_viewport);

	return hr;
}

HRESULT InitPipeline()
{
	HRESULT hr = S_OK;

	hr = g_Graphics.m_vertexShader.createVertexShader(L"shaders.fx", "VS", "vs_5_0", g_Graphics.m_device);
	hr = g_Graphics.m_pixelShader.createFragmentShader(L"shaders.fx", "PS", "ps_5_0", g_Graphics.m_device);

	// set the shader objects
	g_Graphics.m_deviceContext->VSSetShader(g_Graphics.m_vertexShader.m_vertexShader, 0, 0);
	g_Graphics.m_deviceContext->PSSetShader(g_Graphics.m_pixelShader.m_fragmentShader, 0, 0);

	// create the input layout object
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	UINT numElements = ARRAYSIZE(ied);

	hr = g_Graphics.m_device->CreateInputLayout(ied, numElements, 
		g_Graphics.m_vertexShader.m_shaderBlob->GetBufferPointer(), 
		g_Graphics.m_vertexShader.m_shaderBlob->GetBufferSize(), 
		&g_Graphics.m_vertexShader.m_inputLayout.m_vertexLayout);

	if (FAILED(hr))
	{
		MessageBoxW(NULL,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}
}

HRESULT InitContent()
{
	HRESULT hr = S_OK;

	// create a triangle using the VERTEX struct
	SimpleVertex OurVertices[] =
	{
		{ omVector3D(-1.0f, 1.0f, -1.0f), omVector2D(0.0f, 0.0f) },
		{ omVector3D(1.0f, 1.0f, -1.0f), omVector2D(1.0f, 0.0f) },
		{ omVector3D(1.0f, 1.0f, 1.0f), omVector2D(1.0f, 1.0f) },
		{ omVector3D(-1.0f, 1.0f, 1.0f), omVector2D(0.0f, 1.0f) },

		{ omVector3D(-1.0f, -1.0f, -1.0f), omVector2D(0.0f, 0.0f) },
		{ omVector3D(1.0f, -1.0f, -1.0f), omVector2D(1.0f, 0.0f) },
		{ omVector3D(1.0f, -1.0f, 1.0f), omVector2D(1.0f, 1.0f) },
		{ omVector3D(-1.0f, -1.0f, 1.0f), omVector2D(0.0f, 1.0f) },

		{ omVector3D(-1.0f, -1.0f, 1.0f), omVector2D(0.0f, 0.0f) },
		{ omVector3D(-1.0f, -1.0f, -1.0f), omVector2D(1.0f, 0.0f) },
		{ omVector3D(-1.0f, 1.0f, -1.0f), omVector2D(1.0f, 1.0f) },
		{ omVector3D(-1.0f, 1.0f, 1.0f), omVector2D(0.0f, 1.0f) },

		{ omVector3D(1.0f, -1.0f, 1.0f), omVector2D(0.0f, 0.0f) },
		{ omVector3D(1.0f, -1.0f, -1.0f), omVector2D(1.0f, 0.0f) },
		{ omVector3D(1.0f, 1.0f, -1.0f), omVector2D(1.0f, 1.0f) },
		{ omVector3D(1.0f, 1.0f, 1.0f), omVector2D(0.0f, 1.0f) },

		{ omVector3D(-1.0f, -1.0f, -1.0f), omVector2D(0.0f, 0.0f) },
		{ omVector3D(1.0f, -1.0f, -1.0f), omVector2D(1.0f, 0.0f) },
		{ omVector3D(1.0f, 1.0f, -1.0f), omVector2D(1.0f, 1.0f) },
		{ omVector3D(-1.0f, 1.0f, -1.0f), omVector2D(0.0f, 1.0f) },

		{ omVector3D(-1.0f, -1.0f, 1.0f), omVector2D(0.0f, 0.0f) },
		{ omVector3D(1.0f, -1.0f, 1.0f), omVector2D(1.0f, 0.0f) },
		{ omVector3D(1.0f, 1.0f, 1.0f), omVector2D(1.0f, 1.0f) },
		{ omVector3D(-1.0f, 1.0f, 1.0f), omVector2D(0.0f, 1.0f) },
	};

	// create the vertex buffer
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;                // write access access by CPU and GPU
	bd.ByteWidth = sizeof(SimpleVertex) * 24;             // size is the VERTEX struct * 3
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
	bd.CPUAccessFlags = 0;						// allow CPU to write in buffer

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = OurVertices;

	hr = g_vertexBuffer.createConstantBuffer(g_Graphics.m_device, &bd, &InitData);
	if (FAILED(hr))
	{
		MessageBoxW(NULL,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Create index buffer
	WORD indices[] =
	{
		3,1,0,
		2,1,3,

		6,4,5,
		7,4,6,

		11,9,8,
		10,9,11,

		14,12,13,
		15,12,14,

		19,17,16,
		18,17,19,

		22,20,21,
		23,20,22
	};

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * 36;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = indices;

	hr = g_indexBuffer.createConstantBuffer(g_Graphics.m_device, &bd, &InitData);
	if (FAILED(hr))
		return hr;

	//	// Create the sample state
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = g_Graphics.m_device->CreateSamplerState(&sampDesc, &g_Graphics.m_samplerState);
	if (FAILED(hr))
		return hr;

	// Create the constant buffers
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(CBView);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	hr = g_pCBView.createConstantBuffer(g_Graphics.m_device, &bd);
	if (FAILED(hr))
		return hr;

	bd.ByteWidth = sizeof(CBProj);
	hr = g_pCBProj.createConstantBuffer(g_Graphics.m_device, &bd);
	if (FAILED(hr))
		return hr;

	bd.ByteWidth = sizeof(CBWorld);
	hr = g_pCBWorld.createConstantBuffer(g_Graphics.m_device, &bd);
	if (FAILED(hr))
		return hr;

	// Load the Texture
	DirectX::ScratchImage Image;
	hr = DirectX::LoadFromDDSFile(L"seafloor.dds", NULL, NULL, Image);
	if (FAILED(hr))
		return hr;

	hr = DirectX::CreateShaderResourceView(g_Graphics.m_device, Image.GetImages(), Image.GetImageCount(), Image.GetMetadata(), &g_textureRV.m_texture);
	if (FAILED(hr))
		return hr;

	// Initialize the world matrices
	g_World = Math::Identity4D();

	// Initialize the view matrix
	omVector4D Eye(0.0f, 0.0f, -6.0f, 1.0f);
	omVector4D At(0.0f, 0.0f, 0.0f, 1.0f);
	omVector4D Up(0.0f, 1.0f, 0.0f, 0.0f);

	g_View = Math::LookAtLH(Eye, At, Up);

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	g_Graphics.m_width = rc.right - rc.left;
	g_Graphics.m_height = rc.bottom - rc.top;

	// Initialize the projection matrix
	g_Projection = Math::PerspectiveFovLH(Math::PI / 2.0f, g_Graphics.m_width / (FLOAT)g_Graphics.m_height, 0.01f, 100.0f);
}

// this is the function used to render a single frame
void RenderFrame(void)
{	
	static DWORD dwTimeStart = 0;
	DWORD dwTimeCur = GetTickCount();
	if (dwTimeStart == 0)
		dwTimeStart = dwTimeCur;
	g_deltaTime = (dwTimeCur - dwTimeStart) / 1000.0f;
	
	CBView cbView;
	cbView.mView = Math::Transpose(g_View);
	g_Graphics.m_deviceContext->UpdateSubresource(g_pCBView.m_buffer, 0, NULL, &cbView, 0, 0);

	CBProj cbProj;
	cbProj.mProjection = Math::Transpose(g_Projection);
	g_Graphics.m_deviceContext->UpdateSubresource(g_pCBProj.m_buffer, 0, NULL, &cbProj, 0, 0);

	// Rotate cube around the origin
	g_World = Math::Identity4D();
	g_World = Math::RotationMatrix4x4(g_deltaTime, RA_X);
	g_World *= Math::RotationMatrix4x4(g_deltaTime, RA_Z);

	float colorbk[4] = { 0.0f, 0.2f, 0.4f, 1.0f };
	g_Graphics.clearScreen(&g_Graphics.m_renderTarget, const_cast<float*>(colorbk));

	g_Graphics.m_deviceContext->IASetInputLayout(g_Graphics.m_vertexShader.m_inputLayout.m_vertexLayout);
	g_Graphics.m_deviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// select which vertex buffer to display
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	g_Graphics.m_deviceContext->IASetVertexBuffers(0, 1, &g_vertexBuffer.m_buffer, &stride, &offset);
	// Set index buffer
	g_Graphics.m_deviceContext->IASetIndexBuffer(g_indexBuffer.m_buffer , DXGI_FORMAT_R16_UINT, 0);

	// Update variables that change once per frame
	CBWorld cbWorld;
	cbWorld.mWorld = Math::Transpose(g_World);
	g_Graphics.m_deviceContext->UpdateSubresource(g_pCBWorld.m_buffer, 0, NULL, &cbWorld, 0, 0);

	g_Graphics.m_deviceContext->VSSetShader(g_Graphics.m_vertexShader.m_vertexShader, NULL, 0);
	g_Graphics.m_deviceContext->VSSetConstantBuffers(0, 1, &g_pCBView.m_buffer);
	g_Graphics.m_deviceContext->VSSetConstantBuffers(1, 1, &g_pCBProj.m_buffer);
	g_Graphics.m_deviceContext->VSSetConstantBuffers(2, 1, &g_pCBWorld.m_buffer);

	g_Graphics.m_deviceContext->PSSetShader(g_Graphics.m_pixelShader.m_fragmentShader, NULL, 0);
	g_Graphics.m_deviceContext->PSSetShaderResources(0, 1, &g_textureRV.m_texture);
	g_Graphics.m_deviceContext->PSSetSamplers(0, 1, &g_Graphics.m_samplerState);

	g_Graphics.m_deviceContext->DrawIndexed(36, 0, 0);

	// switch the back buffer and the front buffer
	g_Graphics.m_swapchain->Present(0, 0);
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// sort through and find what code to run for the message given
	switch (message)
	{
		// this message is read when the window is closed
	case WM_DESTROY:
	{
		// close the application entirely
		PostQuitMessage(0);
		return 0;
	} break;

	case WM_SIZE:
		if (g_Graphics.m_swapchain)
		{
			g_Graphics.m_deviceContext->OMSetRenderTargets(0, 0, 0);

			// Release all outstanding references to the swap chain's buffers.
			g_Graphics.m_renderTarget.m_renderTarget->Release();

			HRESULT hr;
			// Preserve the existing buffer count and format.
			// Automatically choose the width and height to match the client rect for HWNDs.
			hr = g_Graphics.m_swapchain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);

			// Perform error handling here!

			// Get buffer and create a render-target-view.
			ID3D11Texture2D* pBuffer;
			hr = g_Graphics.m_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D),
				(void**)&pBuffer);
			// Perform error handling here!

			hr = g_Graphics.m_device->CreateRenderTargetView(pBuffer, NULL,
				&g_Graphics.m_renderTarget.m_renderTarget);
			// Perform error handling here!
			pBuffer->Release();

			g_Graphics.m_deviceContext->OMSetRenderTargets(1, &g_Graphics.m_renderTarget.m_renderTarget, NULL);

			// Set up the viewport.
			g_Graphics.setViewport();

			g_Graphics.m_deviceContext->RSSetViewports(1, &g_Graphics.m_viewport);
		}
		return 1;
	}

	// Handle any messages the switch statement didn't
	return DefWindowProc(hWnd, message, wParam, lParam);
}


// the entry point for any Windows program
int WINAPI wWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow)
{
	// the handle for the window, filled by a function
	HWND hWnd;
	// this struct holds information for the window class
	WNDCLASSEXW wc;
	// clear out the window class for use
	ZeroMemory(&wc, sizeof(WNDCLASSEXW));

	// fill in the struct with the needed information
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = L"RenderTest";

	// register the window class
	if (!RegisterClassExW(&wc))
		return E_FAIL;

	g_hInst = hInstance;

	RECT wr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };    // set the size, but not the position
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    // adjust the size
	
   // create the window and use the result as the handle
	g_hWnd = CreateWindowExW(NULL,
		L"RenderTest",    // name of the window class
		L"Diablito",   // title of the window
		WS_OVERLAPPEDWINDOW,    // window style
		CW_USEDEFAULT,    // x-position of the window
		CW_USEDEFAULT,    // y-position of the window
		wr.right - wr.left, wr.bottom - wr.top,    // set window to new resolution
		NULL,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		hInstance,    // application handle
		NULL);    // used with multiple windows, NULL

	if (!g_hWnd)
		return E_FAIL;

	// display the window on the screen
	ShowWindow(g_hWnd, nCmdShow);

	InitD3D(g_hWnd);
	InitPipeline();
	InitContent();

	// enter the main loop:
	// this struct holds Windows event messages
	MSG msg = { 0 };

	// Enter the infinite message loop
	while (TRUE)
	{
		// Check to see if any messages are waiting in the queue
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// translate keystroke messages into the right format
			TranslateMessage(&msg);

			// send the message to the WindowProc function
			DispatchMessage(&msg);

			// check to see if it's time to quit
			if (msg.message == WM_QUIT)
				break;
		}
		else
		{
			// Run game code here
			RenderFrame();
		}
	}

	g_Graphics.cleanDevice();

	// return this part of the WM_QUIT message to Windows
	return msg.wParam;
}