
#include "Game.h"
#include "JcAdventure/Global.h"
#include "JcAdventure/TransitionManager.h"
#include "JcAdventure/Screens/TitleScreen.h"

namespace JcAdventure
{
	long Game::lastTapID = 0;
	Game::Game()
	{
		//View::setSize(900,600);
		Game::setBackgroundColor(Color::BLACK);
	}

	Game::~Game()
	{
		//
	}

	void Game::Initialize()
	{
		//
	}

	void Game::LoadContent()
	{
		//setFPS(60);
		scaleToWindow(true, 900, 600);
		AssetManager::loadFont("Fonts/arial.ttf");
		AssetManager::loadFont("Fonts/phatone.ttf");
		AssetManager::loadFont("Fonts/meposa.ttf");

		ScreenManager::Add(new SplashScreen("SplashScreen"));
		ScreenManager::Add(new TitleScreen("TitleScreen"));

		Global::loadLevels();

		ScreenManager::GoToScreen("SplashScreen");
	}

	void Game::UnloadContent()
	{
		//
	}

	void Game::Update(long gameTime)
	{
		ScreenManager::Update(gameTime);
		TransitionManager::Update(gameTime);
	}

	void Game::Draw(Graphics2D&g, long gameTime)
	{
		ScreenManager::Draw(g, gameTime);
		TransitionManager::Draw(g, gameTime);
	}
	
	bool Game::screenTapped()
	{
		/*if(!Game::MouseState(Mouse::LEFTCLICK) && Game::PrevMouseState(Mouse::LEFTCLICK))
		{
			return true;
		}*/
		ArrayList<TouchPoint> touchPoints = Game::getTouchPoints();
		ArrayList<TouchPoint> prevTouchPoints = Game::getPrevTouchPoints();
		if(prevTouchPoints.size()>touchPoints.size())
		{
			for(int i=(prevTouchPoints.size()-1); i>=0; i--)
			{
				TouchPoint point = prevTouchPoints.get(i);
				bool found = false;
				for(int j=(touchPoints.size()-1); j>=0; j--)
				{
					TouchPoint pointCmp = touchPoints.get(j);
					if(point.ID == pointCmp.ID)
					{
						found = true;
						j=0;
					}
				}
				if(!found)
				{
					lastTapID = point.ID;
					return true;
				}
			}
		}
		return false;
	}
	
	long Game::getLastTapID()
	{
		return lastTapID;
	}
}