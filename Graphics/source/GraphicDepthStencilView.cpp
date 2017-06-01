#include "GraphicDepthStencilView.h"

GraphicDepthStencilView::GraphicDepthStencilView()
{
	m_depthStencilView = nullptr;
}

GraphicDepthStencilView::~GraphicDepthStencilView()
{
	Release();
}