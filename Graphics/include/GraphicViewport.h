#pragma once

class GraphicViewport
{
public:
	GraphicViewport();
	~GraphicViewport();

	void* getPtr() const
	{
		return m_viewport;
	}

	void** getReference()
	{
		return &m_viewport;
	}

	void Release()
	{
		if (m_viewport)
		{
			m_viewport = nullptr;
		}
	}

	void Set(void* _data);

private:
	void* m_viewport;
};