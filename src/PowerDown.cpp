#include "header.h"
#include "templates.h"
#include "PowerDown.h"
#include "PsysasMain.h"
#include "PsysasEnemy.h"

PowerDown::PowerDown(PsysasMain* pEngine, int iMapX, int iMapY, TileManager &m_pTileManager)
	:DisplayableObject(pEngine)
	, m_pMainEngine(pEngine)
	, m_iMapX(iMapX)
	, m_iMapY(iMapY)
	, m_iDir(0)
	, m_pTileManager(&m_pTileManager)
{
	// The ball coordinate will be the centre of the ball
	// Because we start drawing half the size to the top-left.
	m_iStartDrawPosX = -25;
	m_iStartDrawPosY = -25;

	// Record the ball size as both height and width
	m_iDrawWidth = 50;
	m_iDrawHeight = 50;

	// Out item at specific coordinates
	m_iPreviousScreenX = m_iCurrentScreenX = iMapX * 50 + 25 + 25;
	m_iPreviousScreenY = m_iCurrentScreenY = iMapY * 50 + 25 + 40;

	// And make it visible
	SetVisible(true);
}


PowerDown::~PowerDown()
{
}

void PowerDown::SetMovement(int iStartTime, int iEndTime, int iCurrentTime,
	int iStartX, int iStartY, int iEndX, int iEndY)
{
	m_oMover.Setup(iStartX, iStartY, iEndX, iEndY, iStartTime, iEndTime);
	m_oMover.Calculate(iCurrentTime);
	m_iCurrentScreenX = m_oMover.GetX();
	m_iCurrentScreenY = m_oMover.GetY();
}

void PowerDown::Draw()
{
	// Do not draw if it should not be visible
	if (!IsVisible())
		return;

	int iSize = 10;

	m_pMainEngine->DrawScreenOval(
		m_iCurrentScreenX - iSize,
		m_iCurrentScreenY - iSize,
		m_iCurrentScreenX + iSize - 1,
		m_iCurrentScreenY + iSize - 1,
		0x008080);

	// Store the position at which the object was last drawn
	// You MUST do this to ensure that the screen is updated when only drawing movable objects
	// This tells the system where to 'undraw' the object from
	StoreLastScreenPositionForUndraw();
}



void PowerDown::DoUpdate(int iCurrentTime)
{
	m_iPreviousScreenX = m_iCurrentScreenX;
	m_iPreviousScreenY = m_iCurrentScreenY;

	// Iterate through the objects
	// We are looking for one which is too close to us
	DisplayableObject* pObject;

	for (int iObjectId = 0; (pObject = m_pMainEngine->GetDisplayableObject(iObjectId)) != NULL; iObjectId++)
	{
		if (pObject == this || dynamic_cast<PsysasEnemy*>(pObject) != NULL || dynamic_cast<PowerDown*>(pObject) != NULL) // This is us, skip it
			continue;

		// If you need to cast to the sub-class type, you must use dynamic_cast, see lecture 19
		// We are just using base class parts
		int iXDiff = pObject->GetXCentre() - m_iCurrentScreenX;
		int iYDiff = pObject->GetYCentre() - m_iCurrentScreenY;

		// Estimate the size - by re-calculating it
		int iTick = iCurrentTime; // 1 per 20ms
		int iFrame = iTick % 30;
		int iSize = 10 + iFrame;
		if (iFrame > 15)
			iSize = 10 + (30 - iFrame);
		int iSizeOther = iSize; // Assume both the same size

		// Pythagorus' theorum:
		if (((iXDiff*iXDiff) + (iYDiff*iYDiff))
			< ((iSizeOther + iSize)*(iSizeOther + iSize)))
		{
			// Move us to 1,1 and set direction right
			int speed = m_pMainEngine->getStartingSpeed();
			m_iMapX = m_pMainEngine->getStartingPoint();
			m_iMapY = 100;

			m_oMover.Setup(
				m_iMapX, //m_iCurrentScreenX,
				m_iMapY, //m_iCurrentScreenY,
				m_iMapX,
				m_iMapY + 425,
				iCurrentTime,
				iCurrentTime + speed);
			printf("HIT \n");
			m_pMainEngine->ManageLives();

		}
	}

	// Work out current position
	m_oMover.Calculate(iCurrentTime);
	m_iCurrentScreenX = m_oMover.GetX();
	m_iCurrentScreenY = m_oMover.GetY();

	if (m_oMover.HasMovementFinished(iCurrentTime))
	{
		m_oMover.Calculate(iCurrentTime);
		m_iCurrentScreenX = m_oMover.GetX();
		m_iCurrentScreenY = m_oMover.GetY();

		// Respawn
		int speed = m_pMainEngine->getStartingSpeed();
		m_iMapX = m_pMainEngine->getStartingPoint();
		m_iMapY = 100;

		m_oMover.Setup(
			m_iMapX, //m_iCurrentScreenX,
			m_iMapY, //m_iCurrentScreenY,
			m_iMapX,
			m_iMapY + 425,
			iCurrentTime,
			iCurrentTime + speed);
	}


	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();
}

//Makes the player slow down
void PowerDown::SlowDown(){

};