#pragma once
#include "DisplayableObject.h"

class DemoBObject :
	public DisplayableObject
{
public:
	DemoBObject(BaseEngine* pEngine); // THIS LINE CHANGED!!!
	~DemoBObject(void);
	void Draw();
	void DoUpdate(int iCurrentTime);
};

