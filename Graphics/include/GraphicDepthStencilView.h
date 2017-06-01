#pragma once

class GraphicDepthStencilView
{
public:
	GraphicDepthStencilView();
	~GraphicDepthStencilView();

	void* getPtr() const
	{
		return m_depthStencilView;
	}

	void** getReference()
	{
		return &m_depthStencilView;
	}

	void Release()
	{
		if (m_depthStencilView)
		{
			m_depthStencilView = nullptr;
		}
	}

private:
	void* m_depthStencilView;
};