#include <tchar.h>
#include <windows.h>
#include <DirectXTex.h>
#include <ModelLoader.h>
#include <Omicron_Math.h>
#include <GraphicManager.h>
#include <ConstantBuffer.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>
#include <StaticModel.h>

//define the screen resolution
#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720

using namespace OmicronSDK;
using namespace DirectX;
using std::vector;

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

struct CBColor
{
	omVector4D mColor;
};

// global declarations
GraphicManager g_Graphics;

HINSTANCE g_hInst = NULL;
HWND g_hWnd = NULL;

ConstantBuffer g_pCBView;
ConstantBuffer g_pCBProj;
ConstantBuffer g_pCBWorld;
ConstantBuffer g_pCBColor;

omMatrix4D  g_World;
omMatrix4D  g_View;
omMatrix4D  g_Projection;

float g_deltaTime = 0.0f;
float colorbk[4] = { 0.0f, 0.2f, 0.4f, 1.0f };

//lista de modelos cargados
vector<Model*> g_ModelList;

ID3D11Device* g_pD3DDevice;
IDXGISwapChain* g_pSwapChain;
ID3D11DeviceContext* g_pDeviceContext;
ID3D11DepthStencilView* g_pDepthStencilView;
ID3D11SamplerState* g_pSamplerState;
D3D11_VIEWPORT* g_pViewport;

ModelLoader g_modelLoader;

Texture2D g_renderTexture[8];
RenderTarget g_renderTarget[8];
VertexShader g_vertexShader[8];
FragmentShader g_pixelShader[8];

unsigned int g_currentVertexShader = 0;
unsigned int g_currentPixelShader = 0;
unsigned int g_currentRenderTarget = 0;

// this function initializes and prepares Direct3D for use
HRESULT InitD3D(HWND hWnd)
{
	HRESULT hr = S_OK;

	g_Graphics.init(hWnd);

	g_pD3DDevice = reinterpret_cast<ID3D11Device*>(g_Graphics.m_device.getPtr());
	g_pSwapChain = reinterpret_cast<IDXGISwapChain*>(g_Graphics.m_swapchain.getPtr());
	g_pDeviceContext = reinterpret_cast<ID3D11DeviceContext*>(g_Graphics.m_deviceContext.getPtr());
	g_pDepthStencilView = reinterpret_cast<ID3D11DepthStencilView*>(g_Graphics.m_depthStencilView.getPtr());
	g_pSamplerState= reinterpret_cast<ID3D11SamplerState*>(g_Graphics.m_samplerState.getPtr());
	g_pViewport = reinterpret_cast<D3D11_VIEWPORT*>(g_Graphics.m_viewport.getPtr());

	return hr;
}

HRESULT LoadShaders()
{
	HRESULT hr = S_OK;

	g_vertexShader[0].createVertexShader(g_pD3DDevice, L"shaders.fx", "VS", "vs_5_0");
	g_vertexShader[0].m_inputLayout.createInputLayoutFromVertexShaderSignature(g_pD3DDevice, g_vertexShader[0].m_shaderBlob);
	g_pixelShader[0].createFragmentShader(&g_Graphics.m_device, L"shaders.fx", "PS", "ps_5_0");

	g_vertexShader[1].createVertexShader(g_pD3DDevice, L"test.fx", "VS", "vs_5_0");
	g_vertexShader[1].m_inputLayout.createInputLayoutFromVertexShaderSignature(g_pD3DDevice, g_vertexShader[1].m_shaderBlob);
	g_pixelShader[1].createFragmentShader(&g_Graphics.m_device, L"test.fx", "PS", "ps_5_0");

	g_renderTarget[0] = g_Graphics.m_renderTarget;
	g_renderTexture[0] = g_Graphics.m_backBuffer;

	for (size_t i = 1; i < 8; ++i)
	{
		g_renderTexture[i].CreateAsRenderTarget(&g_Graphics.m_device, g_Graphics.m_width, g_Graphics.m_height);
		g_Graphics.createRenderTargetView(&g_renderTarget[i], &g_renderTexture[i]);
	}

	return hr;
}

HRESULT InitContent()
{
	HRESULT hr = S_OK;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

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
	hr = g_pD3DDevice->CreateSamplerState(&sampDesc, &g_pSamplerState);
	if (FAILED(hr))
		return hr;

	// Create the constant buffers
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(CBView);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;

	g_pCBView.create(&g_Graphics.m_device, &bd);
	if (FAILED(hr))
		return hr;

	bd.ByteWidth = sizeof(CBProj);
	g_pCBProj.create(&g_Graphics.m_device, &bd);
	if (FAILED(hr))
		return hr;

	bd.ByteWidth = sizeof(CBWorld);
	g_pCBWorld.create(&g_Graphics.m_device, &bd);
	if (FAILED(hr))
		return hr;

	bd.ByteWidth = sizeof(CBColor);
	g_pCBColor.create(&g_Graphics.m_device, &bd);
	if (FAILED(hr))
		return hr;

	// Initialize the world matrices
	g_World = Math::Identity4D();

	// Initialize the view matrix
	omVector4D Eye(0.0f, 1.0f, -1.5f, 1.0f);
	omVector4D At(0.0f, 1.0f, 0.0f, 1.0f);
	omVector4D Up(0.0f, 1.0f, 0.0f, 0.0f);

	g_View = Math::LookAtLH(Eye, At, Up);

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	g_Graphics.m_width = rc.right - rc.left;
	g_Graphics.m_height = rc.bottom - rc.top;

	// Initialize the projection matrix
	g_Projection = Math::PerspectiveFovLH(Math::PI / 2.0f, g_Graphics.m_width / (FLOAT)g_Graphics.m_height, 0.1f, 1000.0f);

	return hr;
}

bool LoadScene(std::string& pFile)
{
	Model* pModel;
	pModel = g_modelLoader.LoadStaticModel(pFile);

	if(!pModel)
	{
		return false;
	}

	g_ModelList.push_back(pModel);
	return true;
}

void LoadModelFromFile()
{
	OPENFILENAME ofn;
	TCHAR CurrentDirectory[MAX_PATH];
	bool bMustLoad = false;
	memset(&ofn, 0, sizeof(ofn));

	TCHAR* FileName = new TCHAR[MAX_PATH];

	//Obtenemos el directorio actual, pera reestablecerlo cuando lo requiramos
	GetCurrentDirectory(MAX_PATH, CurrentDirectory);

	//Rellenamos la informaci�n de la estructura para establecer la carpeta inicial y los tipos de archivo soportados
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrInitialDir = TEXT("resources\\models");
	//ofn.lpstrFilter = TEXT("PK3 File\0*.PK3\0All\0*.*\0");
	ofn.lpstrFile = FileName;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	//Abrimos el dialogo para seleccionar un archivo
	if (GetOpenFileName(&ofn))
	{//El usuario seleccion� un archivo
		if (_tcslen(FileName) > 0)
		{//El nombre del archivo no est� vacio
			bMustLoad = true;	//Indicamos que debe cargarse el archivo
		}
	}

	//Restablecemos la ruta inicial de la aplicaci�n (esto es porque el di�logo cambia la carpeta de trabajo)
	//NOTA: Si no hicieramos esto aqu�, cualquier pr�xima carga de archivos sin ruta completa fallar� dentro de la aplicaci�n, al igual que las escrituras estar�n fuera de lugar
	SetCurrentDirectory(CurrentDirectory);

	//Revisamos si se debe de cargar un archivo de mapa
	if (bMustLoad)
	{//Si debe cargarse, as� que mandamos llamar la funci�n del mapa para esto

		string Temp;
		for (size_t i = 0; FileName[i] != '\0'; i++)
		{
			Temp.push_back(FileName[i]);
		}

		LoadScene(Temp);
	}

	//Eliminamos el buffer de nombre de archivo
	OM_DELETE_ARRAY(FileName);
}

// this is the function used to render a single frame
void RenderFrame(void)
{	
	ID3D11RenderTargetView* pRenderTargets[8];
	for (size_t i = 0; i < 8; ++i)
	{
		pRenderTargets[i] = g_renderTarget[i].m_renderTarget;
	}

	g_pDeviceContext->OMSetRenderTargets(8, pRenderTargets, g_pDepthStencilView);
	g_pDeviceContext->OMSetDepthStencilState(g_Graphics.m_depthStencilState, 1);
	g_pDeviceContext->RSSetState(g_Graphics.m_rasterizerState[2]);
	g_pDeviceContext->RSSetViewports(1, g_pViewport);

	for (size_t i = 0; i < 8; ++i)
	{
		g_Graphics.clearScreen(&g_renderTarget[i], const_cast<float*>(colorbk));
	}

	g_pDeviceContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	static DWORD dwTimeStart = 0;
	DWORD dwTimeCur = GetTickCount();
	if (dwTimeStart == 0)
		dwTimeStart = dwTimeCur;
	g_deltaTime = (dwTimeCur - dwTimeStart) / 1000.0f;
	
	CBView cbView;
	cbView.mView = Math::Transpose(g_View);
	g_pDeviceContext->UpdateSubresource(g_pCBView.m_buffer, 0, NULL, &cbView, 0, 0);

	CBProj cbProj;
	cbProj.mProjection = Math::Transpose(g_Projection);
	g_pDeviceContext->UpdateSubresource(g_pCBProj.m_buffer, 0, NULL, &cbProj, 0, 0);

	// Rotate cube around the origin
	g_World = Math::Identity4D();
	g_World *= Math::RotationMatrix4x4(g_deltaTime / 3, RA_Y);

	// Update variables that change once per frame
	CBWorld cbWorld;
	cbWorld.mWorld = Math::Transpose(g_World);
	g_pDeviceContext->UpdateSubresource(g_pCBWorld.m_buffer, 0, NULL, &cbWorld, 0, 0);

	CBColor cbColor;
	cbColor.mColor = omVector4D(0.3f, 0.0f, 0.2f, 1.0f);
	g_pDeviceContext->UpdateSubresource(g_pCBColor.m_buffer, 0, NULL, &cbColor, 0, 0);

	//Seteamos el VShader asignado al Modelo 
	g_pDeviceContext->VSSetShader(g_vertexShader[g_currentVertexShader].m_vertexShader, NULL, 0);
	g_pDeviceContext->IASetInputLayout(g_vertexShader[g_currentVertexShader].m_inputLayout.m_inputLayout);
	//Seteamos el PShader Perteneciente al modelo
	g_pDeviceContext->PSSetShader(g_pixelShader[g_currentPixelShader].m_fragmentShader, NULL, 0);

	g_pDeviceContext->VSSetConstantBuffers(0, 1, &g_pCBView.m_buffer);
	g_pDeviceContext->VSSetConstantBuffers(1, 1, &g_pCBProj.m_buffer);
	g_pDeviceContext->VSSetConstantBuffers(2, 1, &g_pCBWorld.m_buffer);
	g_pDeviceContext->VSSetConstantBuffers(3, 1, &g_pCBColor.m_buffer);

	g_pDeviceContext->PSSetSamplers(0, 1, &g_pSamplerState);
	
	g_ModelList.at(0)->render(&g_Graphics.m_deviceContext);
	// switch the back buffer and the front buffer
	g_pSwapChain->Present(0, 0);
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
	{
		
	} break;
		
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
	LoadShaders();
	InitContent();
	g_modelLoader.init(&g_Graphics.m_device);

	string path = "resources\\models\\Bassilisk\\Basillisk.dae";
	LoadScene(path);

	Texture Normals;
	path = "resources\\models\\Bassilisk\\c3270_n.dds";
	Normals.loadFromFile(&g_Graphics.m_device, path);

	g_ModelList.at(0)->assignMeshTexture(&Normals, TextureType_NORMALS, 0);

	path = "resources\\models\\Bassilisk\\c3270_s.dds";
	Normals.loadFromFile(&g_Graphics.m_device, path);
	g_ModelList.at(0)->assignMeshTexture(&Normals, TextureType_SPECULAR, 0);

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