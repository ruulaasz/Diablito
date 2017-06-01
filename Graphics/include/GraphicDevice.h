#pragma once

class GraphicDevice
{
 public:
	GraphicDevice();
	~GraphicDevice();

	void* getPtr() const
	{
		return m_device;
	}

	void** getReference()
	{
		return &m_device;
	}

	void Release()
	{
		if (m_device)
		{
			m_device = nullptr;
		}
	}

 private:
	void* m_device;
};