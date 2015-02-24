
#include "../GameEngine/GameEngine.h"

#pragma once

namespace JcAdventure
{
	class Level : public Screen
	{
	public:
		Level(const String&name);
		virtual ~Level();

		virtual void Initialize();
		virtual void LoadContent();
		virtual void UnloadContent();
		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);
	};
}