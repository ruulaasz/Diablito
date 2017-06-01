#include "GraphicSamplerState.h"

GraphicSamplerState::GraphicSamplerState()
{
	m_samplerState = nullptr;
}

GraphicSamplerState::~GraphicSamplerState()
{
	Release();
}