#pragma once
#include "Model.h"

class StaticModel : public Model
{
public:
	StaticModel();
	~StaticModel();

	virtual void init();
	virtual void destroy();
	virtual void update(float _DeltaTime);
};