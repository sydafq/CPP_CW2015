#pragma once

#include "BaseEngine.h"
#include "TileManager.h"
#include "PsysasTileManager.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


class PsysasMain :
	public BaseEngine
{
public:
	PsysasMain(void);
	~PsysasMain(void);

	virtual void SetupBackgroundBuffer();
	virtual int InitialiseObjects();
	virtual void DrawStrings();
	virtual void GameAction();
	virtual void KeyDown(int iKeyCode);
	virtual void UndrawObjects();
	virtual void DrawObjects();
	virtual int getStartingPoint();
	virtual int getStartingSpeed();
	virtual int TotalScore();
	virtual int ManageLives();
	virtual int ReadScorefromFile();
	virtual void WriteScoretoFile(int newHighscore);

	// Get a reference to the current tile manager
	PsysasTileManager& GetTileManager() { return m_oTiles; }

private:
	PsysasTileManager m_oTiles;

public:
	// State number
	enum State { stateInit, stateMain, statePaused,stateLost};

	// Work out what this means yourself
	int m_iPauseStarted;		

private:
	State m_state;
	int enemy_StartingPoint;
	int enemy_StartingSpeed;
	int highscore = 0;
	int points = 0;
	int lives = 3;
	int result;
	char data1[100];//Data buffer for writing
	char data2[100];//Data buffer for writing
	char data3[100];//Data buffer for writing
	string readData,line;
	

};

