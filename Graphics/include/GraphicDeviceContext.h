#pragma once
 
class GraphicDeviceContext
{
public:
	GraphicDeviceContext();
	~GraphicDeviceContext();

	void* getPtr() const
	{
		return m_deviceContext;
	}

	void** getReference()
	{
		return &m_deviceContext;
	}

	void Release()
	{
		if (m_deviceContext)
		{
			m_deviceContext = nullptr;
		}
	}

private:
	void* m_deviceContext;
};