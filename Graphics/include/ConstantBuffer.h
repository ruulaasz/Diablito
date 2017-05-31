#pragma once
#include "Buffer.h"

class ConstantBuffer : public Buffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

	virtual void init() {};
	virtual void destroy();
};