#pragma once
#include <d3d11.h>

class RenderTarget
{
public:
	RenderTarget();
	~RenderTarget();

	ID3D11RenderTargetView* m_renderTarget;
};