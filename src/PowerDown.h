#pragma once
#include "DisplayableObject.h"
#include "MovementPosition.h"
#include "TileManager.h"

class PsysasMain;

class PowerDown :
	public DisplayableObject
{
public:
	PowerDown(PsysasMain* pEngine, int iMapX, int iMapY, TileManager &pTileManager);
	~PowerDown();
	void Draw();
	void DoUpdate(int iCurrentTime);
	void PowerDown::SetMovement(int iStartTime, int iEndTime, int iCurrentTime,
		int iStartX, int iStartY, int iEndX, int iEndY);
	void SlowDown();

private:
	PsysasMain* m_pMainEngine;
	MovementPosition m_oMover;

	// Pointer to the tile manager - we are going to use this!
	TileManager* m_pTileManager;

	int m_iMapX;
	int m_iMapY;
	int m_iDir;
};

