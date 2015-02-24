
#include "Global.h"

#include "Levels/Intro.h"
#include "Levels/ChambersLevel.h"
#include "Levels/WeisbrodLevel.h"

namespace JcAdventure
{
	Player* Global::playr = NULL;
	Boss* Global::boss = NULL;
	HUD* Global::hud = NULL;
	
	boolean Global::gamePlaying = false;

	long Global::score = 0;

	void Global::loadLevels()
	{
		hud = new HUD();
		ScreenManager::Add(new Levels::Intro("level-intro"));
		ScreenManager::Add(new Levels::ChambersLevel("level-chambers"));
		ScreenManager::Add(new Levels::WeisbrodLevel("level-weisbrod"));
	}
}