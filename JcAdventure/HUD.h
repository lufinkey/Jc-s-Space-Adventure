
#include "../GameEngine/GameEngine.h"

#pragma once

namespace JcAdventure
{
	class HUD
	{
	private:
		TextActor*score;
		TextActor*health;

	public:
		HUD();
		virtual ~HUD();

		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);
	};
}