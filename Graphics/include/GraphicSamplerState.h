#pragma once

class GraphicSamplerState
{
public:
	GraphicSamplerState();
	~GraphicSamplerState();

	void* getPtr() const
	{
		return m_samplerState;
	}

	void** getReference()
	{
		return &m_samplerState;
	}

	void Release()
	{
		if (m_samplerState)
		{
			m_samplerState = nullptr;
		}
	}

private:
	void* m_samplerState;
};