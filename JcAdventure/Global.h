
#include "Player.h"
#include "Bosses/Boss.h"
#include "HUD.h"

#pragma once

namespace JcAdventure
{
	class Global
	{
	public:
		static Player*playr;
		static Boss*boss;
		static HUD*hud;
		
		static boolean gamePlaying;

		static long score;

		static void loadLevels();
	};
}