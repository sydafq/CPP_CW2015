#pragma once
#include "DisplayableObject.h"

class PsysasPlayer :
	public DisplayableObject
{
public:
	PsysasPlayer(BaseEngine* pEngine);
	~PsysasPlayer();
	void Draw();
	void DoUpdate(int iCurrentTime);

};

