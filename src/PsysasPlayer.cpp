#include "header.h"
#include "templates.h"

#include "PsysasPlayer.h"

PsysasPlayer::PsysasPlayer(BaseEngine* pEngine)
	:DisplayableObject(pEngine)
{
	// Current and previous coordinates for the object - set them the same initially
	m_iCurrentScreenX = m_iPreviousScreenX = 100;
	m_iCurrentScreenY = m_iPreviousScreenY = 500;

	// The object coordinate will be the top left of the object
	m_iStartDrawPosX = 0;
	m_iStartDrawPosY = 0;

	// Record the PsysasPlayer size as both height and width
	m_iDrawWidth = 100;
	m_iDrawHeight = 30;

	// And make it visible
	SetVisible(true);
}


PsysasPlayer::~PsysasPlayer()
{
}


void PsysasPlayer::Draw(void)
{
	GetEngine()->DrawScreenRectangle(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		0x00ff00);
	// This will store the position at which the object was drawn
	// so that the background can be drawn over the top.
	// This will then remove the object from the screen.
	StoreLastScreenPositionForUndraw();
}

void PsysasPlayer::DoUpdate(int iCurrentTime)
{
	// Change position if player presses a key
	if (GetEngine()->IsKeyPressed(SDLK_LEFT))
		m_iCurrentScreenX -= 1;
	if (GetEngine()->IsKeyPressed(SDLK_RIGHT))
		m_iCurrentScreenX += 1;
	if (m_iCurrentScreenX < 78)
		m_iCurrentScreenX = 78;
	if (m_iCurrentScreenX >= GetEngine()->GetScreenWidth() - m_iDrawWidth -78)
		m_iCurrentScreenX = GetEngine()->GetScreenWidth() - m_iDrawWidth - 78;
	if (m_iCurrentScreenY < 0)
		m_iCurrentScreenY = 0;

	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();
}