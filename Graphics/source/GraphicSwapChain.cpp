#include "GraphicSwapChain.h"

GraphicSwapChain::GraphicSwapChain()
{
	m_swapChain = nullptr;
}

GraphicSwapChain::~GraphicSwapChain()
{
	Release();
}