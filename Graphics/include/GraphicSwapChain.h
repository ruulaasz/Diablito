#pragma once

class GraphicSwapChain
{
public:
	GraphicSwapChain();
	~GraphicSwapChain();

	void* getPtr() const
	{
		return m_swapChain;
	}

	void** getReference()
	{
		return &m_swapChain;
	}

	void Release()
	{
		if (m_swapChain)
		{
			m_swapChain = nullptr;
		}
	}

private:
	void* m_swapChain;
};