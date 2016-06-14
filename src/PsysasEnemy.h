#pragma once
#include "DisplayableObject.h"
#include "MovementPosition.h"
#include "TileManager.h"

class PsysasMain;

class PsysasEnemy :
	public DisplayableObject
{
public:
	PsysasEnemy(PsysasMain* pEngine, int iMapX, int iMapY, TileManager &pTileManager);
	~PsysasEnemy();
	void Draw();
	void DoUpdate(int iCurrentTime);
	void PsysasEnemy::SetMovement(int iStartTime, int iEndTime, int iCurrentTime,
		int iStartX, int iStartY, int iEndX, int iEndY);
	void AddPoints();

private:
	PsysasMain* m_pMainEngine;
	MovementPosition m_oMover;
	bool pointFlag = false;

	// Pointer to the tile manager - we are going to use this!
	TileManager* m_pTileManager;

	int m_iMapX;
	int m_iMapY;
	int m_iDir;
};

