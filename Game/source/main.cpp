#include <queue>
#include <tchar.h>
#include <windows.h>
#include <DirectXTex.h>
#include <Omicron_Math.h>
#include <GraphicManager.h>
#include <ConstantBuffer.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>
#include <Importer.hpp>
#include <postprocess.h>
#include <StaticModel.h>

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
GraphicManager g_Graphics;

HINSTANCE g_hInst = NULL;
HWND g_hWnd = NULL;

ConstantBuffer g_pCBView;
ConstantBuffer g_pCBProj;
ConstantBuffer g_pCBWorld;

omMatrix4D  g_World;
omMatrix4D  g_View;
omMatrix4D  g_Projection;

float g_deltaTime = 0.0f;

//Carga de contenido por Assimp
Assimp::Importer g_importer;
const aiScene* g_scene;

//lista de modelos cargadas
using std::vector;
vector<Model*> g_ModelList;

ID3D11Device* g_pD3DDevice;
IDXGISwapChain* g_pSwapChain;
ID3D11DeviceContext* g_pDeviceContext;
ID3D11DepthStencilView* g_pDepthStencilView;
ID3D11SamplerState* g_pSamplerState;
D3D11_VIEWPORT* g_pViewport;

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

	g_pD3DDevice = reinterpret_cast<ID3D11Device*>(g_Graphics.m_device.getPtr());
	g_pSwapChain = reinterpret_cast<IDXGISwapChain*>(g_Graphics.m_swapchain.getPtr());
	g_pDeviceContext = reinterpret_cast<ID3D11DeviceContext*>(g_Graphics.m_deviceContext.getPtr());
	g_pDepthStencilView = reinterpret_cast<ID3D11DepthStencilView*>(g_Graphics.m_depthStencilView.getPtr());
	g_pSamplerState= reinterpret_cast<ID3D11SamplerState*>(g_Graphics.m_samplerState.getPtr());

	// set the render target as the back buffer
	g_pDeviceContext->OMSetRenderTargets(1, &g_Graphics.m_renderTarget.m_renderTarget, g_pDepthStencilView);

	g_Graphics.setViewport();

	g_pViewport = reinterpret_cast<D3D11_VIEWPORT*>(g_Graphics.m_viewport.getPtr());

	g_pDeviceContext->RSSetViewports(1, g_pViewport);

	return hr;
}

HRESULT InitPipeline()
{
	HRESULT hr = S_OK;

	hr = g_Graphics.m_vertexShader.createVertexShader(L"shaders.fx", "VS", "vs_5_0", g_pD3DDevice);
	hr = g_Graphics.m_pixelShader.createFragmentShader(L"shaders.fx", "PS", "ps_5_0", g_pD3DDevice);

	// set the shader objects
	g_pDeviceContext->VSSetShader(g_Graphics.m_vertexShader.m_vertexShader, 0, 0);
	g_pDeviceContext->PSSetShader(g_Graphics.m_pixelShader.m_fragmentShader, 0, 0);

	hr = g_Graphics.m_vertexShader.m_inputLayout.CreateInputLayoutFromVertexShaderSignature(g_Graphics.m_vertexShader.m_shaderBlob);

	g_Graphics.m_vertexShader.m_inputLayout.createInputLayout(g_Graphics.m_vertexShader.m_shaderBlob, g_pD3DDevice);

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
	hr = g_pCBView.createDirectX(&g_Graphics.m_device, &bd);
	if (FAILED(hr))
		return hr;

	bd.ByteWidth = sizeof(CBProj);
	hr = g_pCBProj.createDirectX(&g_Graphics.m_device, &bd);
	if (FAILED(hr))
		return hr;

	bd.ByteWidth = sizeof(CBWorld);
	hr = g_pCBWorld.createDirectX(&g_Graphics.m_device, &bd);
	if (FAILED(hr))
		return hr;

	// Initialize the world matrices
	g_World = Math::Identity4D();

	// Initialize the view matrix
	omVector4D Eye(0.0f, 1.0f, -1.0f, 1.0f);
	omVector4D At(0.0f, 1.0f, 0.0f, 1.0f);
	omVector4D Up(0.0f, 1.0f, 0.0f, 0.0f);

	g_View = Math::LookAtLH(Eye, At, Up);

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	g_Graphics.m_width = rc.right - rc.left;
	g_Graphics.m_height = rc.bottom - rc.top;

	// Initialize the projection matrix
	g_Projection = Math::PerspectiveFovLH(Math::PI / 2.0f, g_Graphics.m_width / (FLOAT)g_Graphics.m_height, 0.1f, 1000.0f);
}

bool LoadScene(std::string& pFile)
{
	HRESULT HandleResult;

	g_scene = g_importer.ReadFile(pFile, aiProcess_ConvertToLeftHanded);

	if (!g_scene || !g_scene->HasMeshes() )
	{
		return false;
	}

	string texturesPath = pFile;

	size_t i = texturesPath.size() - 1;
	for (; i >= 0; i--)
	{
		if (texturesPath.at(i) == '/' || texturesPath.at(i) == '\\')
			break;

		texturesPath.pop_back();
	}

	//Carguemos meshes
	VertexData myVertex;
	Model* pModel = new StaticModel();
	pModel->m_meshes.resize(g_scene->mNumMeshes);

	bool hasMaterials = g_scene->HasMaterials();

	for (size_t i = 0; i < g_scene->mNumMeshes; ++i) 
	{
		pModel->m_meshes[i] = new Mesh();

		if (g_scene->mMeshes[i]->HasPositions()) 
		{
			for (size_t j = 0; j < g_scene->mMeshes[i]->mNumVertices; ++j) 
			{
				aiMesh* paiMesh = g_scene->mMeshes[i];

				myVertex.pos.X = paiMesh->mVertices[j].x;
				myVertex.pos.Y = paiMesh->mVertices[j].y;
				myVertex.pos.Z = paiMesh->mVertices[j].z;
				myVertex.pos.W = 1;

				if (g_scene->mMeshes[i]->HasNormals()) 
				{
					myVertex.norm.X = paiMesh->mNormals[j].x;
					myVertex.norm.Y = paiMesh->mNormals[j].y;
					myVertex.norm.Z = paiMesh->mNormals[j].z;
				}

				if (g_scene->mMeshes[i]->HasTextureCoords(0)) 
				{
					myVertex.tex.X = paiMesh->mTextureCoords[0][j].x;
					myVertex.tex.Y = paiMesh->mTextureCoords[0][j].y;
				}

				pModel->m_meshes[i]->m_VertexBuffer.addVertex(myVertex);
			}

			pModel->m_meshes[i]->m_VertexBuffer.create(&g_Graphics.m_device);

			Material* pMaterial = new Material();
			pMaterial->m_pixelShader = &g_Graphics.m_pixelShader;
			pMaterial->m_vertexShader = &g_Graphics.m_vertexShader;

			if (hasMaterials)
			{
				aiString pPath;
				g_scene->mMaterials[g_scene->mMeshes[i]->mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE, 0, &pPath);

				if (pPath.length > 0)
				{
					string textureName;
					string temp = pPath.C_Str();

					int i = temp.size() - 1;
					for (; i >= 0; --i)
					{
						if (temp.at(i) == '/' || temp.at(i) == '\\')
							break;

						textureName.push_back(temp.at(i));
					}

					string finalPath = texturesPath;

					size_t j = textureName.size() - 1;
					for (; j >= 0; j--)
					{
						if (textureName.at(j) == '.')
							break;

						finalPath.push_back(textureName.at(j));
					}

					finalPath += ".dds";

					// Load the Texture
					DirectX::ScratchImage Image;
					std::wstring widestr = std::wstring(finalPath.begin(), finalPath.end());
					DirectX::LoadFromDDSFile(widestr.c_str(), NULL, NULL, Image);

					Texture* newTexture = new Texture();

					DirectX::CreateShaderResourceView(g_pD3DDevice, Image.GetImages(), Image.GetImageCount(), Image.GetMetadata(), &newTexture->m_texture);

					pMaterial->m_textures[TextureType_DIFFUSE] =newTexture->m_texture; //g_textureRV.m_texture; 
				}
			}

			pModel->m_meshes[i]->m_Material = pMaterial;
		}

		if (g_scene->mMeshes[i]->HasFaces())
		{
			for (size_t j = 0; j < g_scene->mMeshes[i]->mNumFaces; ++j)
			{
				for (size_t k = 0; k < g_scene->mMeshes[i]->mFaces->mNumIndices; k++)
				{
					pModel->m_meshes[i]->m_IndexBuffer.addIndex(g_scene->mMeshes[i]->mFaces[j].mIndices[k]);
				}
			}

			pModel->m_meshes[i]->m_IndexBuffer.create(&g_Graphics.m_device);
		}
	}

	g_ModelList.push_back(pModel);
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

	//Rellenamos la información de la estructura para establecer la carpeta inicial y los tipos de archivo soportados
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
	{//El usuario seleccionó un archivo
		if (_tcslen(FileName) > 0)
		{//El nombre del archivo no está vacio
			bMustLoad = true;	//Indicamos que debe cargarse el archivo
		}
	}

	//Restablecemos la ruta inicial de la aplicación (esto es porque el diálogo cambia la carpeta de trabajo)
	//NOTA: Si no hicieramos esto aquí, cualquier próxima carga de archivos sin ruta completa fallará dentro de la aplicación, al igual que las escrituras estarán fuera de lugar
	SetCurrentDirectory(CurrentDirectory);

	//Revisamos si se debe de cargar un archivo de mapa
	if (bMustLoad)
	{//Si debe cargarse, así que mandamos llamar la función del mapa para esto

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
	g_World *= Math::RotationMatrix4x4(g_deltaTime/3, RA_Y);

	float colorbk[4] = { 0.0f, 0.2f, 0.4f, 1.0f };
	g_Graphics.clearScreen(&g_Graphics.m_renderTarget, const_cast<float*>(colorbk));

	g_pDeviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Update variables that change once per frame
	CBWorld cbWorld;
	cbWorld.mWorld = Math::Transpose(g_World);
	g_pDeviceContext->UpdateSubresource(g_pCBWorld.m_buffer, 0, NULL, &cbWorld, 0, 0);

	g_pDeviceContext->VSSetConstantBuffers(0, 1, &g_pCBView.m_buffer);
	g_pDeviceContext->VSSetConstantBuffers(1, 1, &g_pCBProj.m_buffer);
	g_pDeviceContext->VSSetConstantBuffers(2, 1, &g_pCBWorld.m_buffer);

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
		if (g_pSwapChain)
		{
			g_pDeviceContext->OMSetRenderTargets(0, 0, 0);

			// Release all outstanding references to the swap chain's buffers.
			g_Graphics.m_renderTarget.m_renderTarget->Release();

			HRESULT hr;
			// Preserve the existing buffer count and format.
			// Automatically choose the width and height to match the client rect for HWNDs.
			hr = g_pSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);

			// Perform error handling here!

			// Get buffer and create a render-target-view.
			ID3D11Texture2D* pBuffer;
			hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
				(void**)&pBuffer);
			// Perform error handling here!

			hr = g_pD3DDevice->CreateRenderTargetView(pBuffer, NULL,
				&g_Graphics.m_renderTarget.m_renderTarget);
			// Perform error handling here!
			pBuffer->Release();

			g_pDeviceContext->OMSetRenderTargets(1, &g_Graphics.m_renderTarget.m_renderTarget, NULL);

			// Set up the viewport.
			g_Graphics.setViewport();

			g_pDeviceContext->RSSetViewports(1, g_pViewport);
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

	LoadModelFromFile();

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