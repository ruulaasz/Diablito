#include "GraphicDevice.h"

GraphicDevice::GraphicDevice()
{
	m_device = nullptr;
}

GraphicDevice::~GraphicDevice()
{
	Release();
}