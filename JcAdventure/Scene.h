
#include "../GameEngine/GameEngine.h"

#pragma once

namespace JcAdventure
{
	class Scene
	{
	private:
		bool playing;
		long nextSceneTime;
		unsigned int nextFrame;

	public:
		Scene();
		Scene(long waitTime);
		virtual ~Scene();

		virtual long onFrame(unsigned int frame);

		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);

		void jump();
		void restart();
		void restart(long waitTime);
		void stop();
	};
}