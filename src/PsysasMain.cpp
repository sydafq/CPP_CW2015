#include "header.h"
#include "BaseEngine.h"
#include "PsysasPlayer.h"
#include "PsysasEnemy.h"
#include "PsysasMain.h"
#include "TileManager.h"
#include "JPGImage.h"
#include "PowerDown.h"


PsysasMain::PsysasMain(void)
	:BaseEngine(50)
	, m_state(stateInit) // NEW
{
}

PsysasMain::~PsysasMain(void)
{
}

//Creates the background for the game
void PsysasMain::SetupBackgroundBuffer()
{
	FillBackground(0x000000);

	// NEW SWITCH
	switch (m_state)
	{
	case stateInit: // Reload the level data
		FillBackground(0xffff00);
		{
			char* data[] = {
				"bbbbbbbbbbbbbbb",
				"aaaaaaaaaaaaaaa",
				"aaaaaaaaaaaaaaa",
				"aaaaaaaaaaaaaaa",
				"aaaaaaaaaaaaaaa",
				"aaaaaaaaaaaaaaa",
				"aaaaaaaaaaaaaaa",
				"aaaaaaaaaaaaaaa",
				"aaaaaaaaaaaaaaa",
				"aaaaaaaaaaaaaaa",
				"bbbbbbbbbbbbbbb" };

			// Specify how many tiles wide and high
			m_oTiles.SetSize(15, 11);
			// Set up the tiles
			for (int x = 0; x < 15; x++)
				for (int y = 0; y < 11; y++)
					m_oTiles.SetValue(x, y, data[y][x] - 'a');

			for (int y = 0; y < 11; y++)
			{
				for (int x = 0; x < 15; x++)
					printf("%d ", m_oTiles.GetValue(x, y));
				printf("\n");
			}

			// Specify the screen x,y of top left corner
			m_oTiles.SetBaseTilesPositionOnScreen(25, 40);
		}
		return;

	case stateMain:
		FillBackground(0);
		// Tell it to draw tiles from x1,y1 to x2,y2 in tile array,
		// to the background of this screen
		m_oTiles.DrawAllTiles(this,
			this->GetBackground(),
			0, 0, 14, 10);
		break; // Drop out to the complicated stuff
	case statePaused:
		FillBackground(0);
		m_oTiles.DrawAllTiles(this,
			this->GetBackground(),
			0, 0, 14, 10);
		break;
	} 

}

int PsysasMain::getStartingPoint() {

	enemy_StartingPoint = rand() % 620 + 99;

	return enemy_StartingPoint; 
	
}

int PsysasMain::getStartingSpeed() {

	enemy_StartingSpeed = rand() % 2000 + 1000;

	return enemy_StartingSpeed;

}

/* Overridden GameAction to ensure that objects use the modified time */
void PsysasMain::GameAction()
{
	// If too early to act then do nothing
	if (!IsTimeToAct()) // No sleep, will just keep polling constantly - this is a difference from the base class
		return;

	// Don't act for another 1 tick - this is a difference from the base class
	SetTimeToAct(1);

	// NEW SWITCH - different from the base class
	switch (m_state)
	{
	case stateInit:
	case statePaused:
		break;
	case stateMain:
		// Only tell objects to move when not paused etc
		UpdateAllObjects(GetModifiedTime());
		break;
	case stateLost:
		InitialiseObjects();
		break;
	}
}

int PsysasMain::InitialiseObjects()
{
	int startPoint = getStartingPoint();
	int startSpeed = getStartingSpeed();

	//Loads the highest score
	highscore = ReadScorefromFile();

	// Record the fact that we are about to change the array - so it doesn't get
	//used elsewhere without reloading it
	DrawableObjectsChanged();

	// Destroy any existing objects
	DestroyOldObjects();

	// Creates an array to store the objects
	// Needs to have room for the NULL at the end
	CreateObjectArray(10);
	
	//Object Declaration
	//Declaration of player object
	PsysasPlayer *player = new PsysasPlayer(this);

	//Declaration of enemy object
	PsysasEnemy *enemy = new PsysasEnemy(this, 5, 20,GetTileManager());
	enemy->SetMovement(GetTime(), GetTime() + startSpeed, GetTime(), startPoint, 25, startPoint, 515);

	PsysasEnemy *enemy2 = new PsysasEnemy(this, 5, 20, GetTileManager());
	enemy2->SetMovement(GetTime() + 1500, GetTime() + startSpeed + 1500, GetTime(), startPoint + 25, 25, startPoint + 25, 515);

	PsysasEnemy *enemy3 = new PsysasEnemy(this, 5, 20, GetTileManager());
	enemy3->SetMovement(GetTime() + 2500, GetTime() + startSpeed + 2500, GetTime(), startPoint + 75, 25, startPoint + 75, 515);

	PowerDown *enemy4 = new PowerDown(this, 5, 20, GetTileManager());
	enemy4->SetMovement(GetTime() + 2500, GetTime() + startSpeed + 2500, GetTime(), startPoint + 50, 25, startPoint + 50, 515);

	PowerDown *enemy5 = new PowerDown(this, 5, 20, GetTileManager());
	enemy5->SetMovement(GetTime() + 1000, GetTime() + startSpeed + 1000, GetTime(), startPoint + 100, 25, startPoint + 100, 515);
	
	// You MUST set the array entry after the last one that you create to NULL, so
	//that the system knows when to stop.
	// i.e. The LAST entry has to be NULL. The fact that it is NULL is used in
	//order to work out where the end of the array is.
	StoreObjectInArray(0, player);
	StoreObjectInArray(1, enemy);
	StoreObjectInArray(2, enemy2);
	StoreObjectInArray(3, enemy3);
	StoreObjectInArray(4, enemy4);
	StoreObjectInArray(5, enemy5);
	StoreObjectInArray(6, NULL);

	return 0;
}

int PsysasMain::TotalScore(){

	points++;

	return points;
}

int PsysasMain::ManageLives(){

	lives--;

	if (lives == -1){
		int counter;
		if (points > highscore){
			WriteScoretoFile(points);
		}
		m_state = stateLost;
		lives = 3;
		
	}
	return lives;
}

//LOAD
//Reads the Current HighScore
int PsysasMain::ReadScorefromFile(){

	ifstream myfile("highscore.txt");

		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				stringstream convert(line);//converts from string to int
				convert >> result;
			}
			myfile.close();
		}

		return result;
}

//SAVE
//Writes the scores to a file
void PsysasMain::WriteScoretoFile(int newHighscore){

	ofstream myfile("highscore.txt");

	if (myfile.is_open())
	{
		myfile << newHighscore;
	}


}

/* Draw text labels */
void PsysasMain::DrawStrings()
{
	//Formatting to put int into the string writers
	sprintf(data1, "%d", lives);
	sprintf(data2, "%d", points);
	sprintf(data3, "%d", highscore);

	//printf("Highscore: %d \n", highscore);

	// NEW SWITCH
	switch (m_state)
	{
	case stateInit:
		CopyBackgroundPixels(0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/);
		DrawScreenString(100, 300, "Initialised and waiting for SPACE", 0x0, NULL);
		break;
	case stateMain:
		CopyBackgroundPixels(0/*X*/, 0/*Y*/, GetScreenWidth(), 30/*Height*/);
		DrawScreenString(600, 10, "Running", 0xffffff, NULL);
		DrawScreenString(50, 10, "LIVES:", 0xffffff, NULL);
		DrawScreenString(175, 10, data1, 0xffffff, NULL);
		DrawScreenString(225, 10, "POINTS:", 0xffffff, NULL);
		DrawScreenString(350, 10, data2, 0xffffff, NULL);
		break;
	case statePaused:
		CopyBackgroundPixels(0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/);
		DrawScreenString(600, 10, "Paused", 0xffffff, NULL);
		DrawScreenString(200, 275, "Press SPACE to continue", 0xffffff, NULL);
		break;
	case stateLost:
		CopyBackgroundPixels(0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/);
		DrawScreenString(330, 175, "You Lost", 0xffffff, NULL);
		DrawScreenString(350, 220, "POINTS", 0xffffff, NULL);
		DrawScreenString(375, 250, data2, 0xffffff, NULL);
		DrawScreenString(325, 320, "Highscore", 0xffffff, NULL);
		DrawScreenString(375, 350, data3, 0xffffff, NULL);
		break;
	}
}

/*
Handle any key presses here.
Note that the objects themselves (e.g. player) may also check whether a key is pressed
*/
void PsysasMain::KeyDown(int iKeyCode)
{
	// NEW SWITCH on current state
	switch (iKeyCode)
	{
	case SDLK_ESCAPE: // End program when escape is pressed
		SetExitWithCode(0);
		break;
	case SDLK_SPACE: // SPACE Pauses
		switch (m_state)
		{
		case stateInit:
			// Go to state main
			m_state = stateMain;
			// Force redraw of background
			SetupBackgroundBuffer();
			// Redraw the whole screen now
			Redraw(true);
			break;
		case stateMain:
			// Go to state paused
			m_state = statePaused;
			// Work out what this does. 
			m_iPauseStarted = GetTime();
			// Force redraw of background
			SetupBackgroundBuffer();
			// Redraw the whole screen now
			Redraw(true);
			break;
		case statePaused:
			// Go to state main
			m_state = stateMain;
			// Work out what this does. It will be hard to notice any difference without these, but there is one. Hint: watch the positions and sizes of the objects
			IncreaseTimeOffset(m_iPauseStarted - GetTime());
			// Force redraw of background
			SetupBackgroundBuffer();
			// Redraw the whole screen now
			Redraw(true);
			break;
		case stateLost:
			//Reinitialise the game
			m_state = stateInit;
			// Force redraw of background
			SetupBackgroundBuffer();
			// Redraw the whole screen now
			Redraw(true);
			break;
		} // End switch on current state
		break; // End of case SPACE
	}
}

void PsysasMain::UndrawObjects()
{
	if (m_state != stateInit) // Not in initialise state
		BaseEngine::UndrawObjects();
}

void PsysasMain::DrawObjects()
{
	if (m_state != stateInit) // Not in initialise state
		BaseEngine::DrawObjects();
}
