
#include "GameEngine/GameEngine.h"

#pragma once

namespace JcAdventure
{
	class Game : public GameEngine::Application
	{
	private:
		static long lastTapID;
	public:
		Game();
		virtual ~Game();

		virtual void Initialize();
		virtual void LoadContent();
		virtual void UnloadContent();
		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);

		static bool screenTapped();
		static long getLastTapID();
	};
}
