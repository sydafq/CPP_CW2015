#include "header.h"

#include "PsysasTileManager.h"


PsysasTileManager::PsysasTileManager()
	:TileManager(50,50)
{
}


PsysasTileManager::~PsysasTileManager()
{
}

void PsysasTileManager::DrawTileAt(
	BaseEngine* pEngine,
	SDL_Surface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	switch (GetValue(iMapX, iMapY))
	{
	case 0:
	case 1:
		pEngine->DrawRectangle(
			iStartPositionScreenX,
			iStartPositionScreenY,
			iStartPositionScreenX + GetTileWidth() - 1,
			iStartPositionScreenY + GetTileHeight() - 1,
			pEngine->GetColour(GetValue(iMapX, iMapY)),
			pSurface);
		break;
	case 2:
		pEngine->DrawRectangle(
			iStartPositionScreenX,
			iStartPositionScreenY,
			iStartPositionScreenX + GetTileWidth() - 1,
			iStartPositionScreenY + GetTileHeight() - 1,
			pEngine->GetColour(1),
			pSurface);
		break;
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
		pEngine->DrawRectangle(
			iStartPositionScreenX,
			iStartPositionScreenY,
			iStartPositionScreenX + GetTileWidth() - 1,
			iStartPositionScreenY + GetTileHeight() - 1,
			pEngine->GetColour(0),
			pSurface);
		break;
	}
}