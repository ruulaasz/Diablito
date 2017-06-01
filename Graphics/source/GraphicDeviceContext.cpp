#include "GraphicDeviceContext.h"

GraphicDeviceContext::GraphicDeviceContext()
{
	m_deviceContext = nullptr;
}

GraphicDeviceContext::~GraphicDeviceContext()
{
	Release();
}