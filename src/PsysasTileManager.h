#pragma once

#include "TileManager.h"
class PsysasTileManager :
	public TileManager
{
public:
	PsysasTileManager(void);
	~PsysasTileManager(void);

	virtual void DrawTileAt(
		BaseEngine* pEngine,
		SDL_Surface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const;
};

