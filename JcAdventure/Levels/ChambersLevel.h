
#include "../Level.h"
#include "../Scene.h"
#include "../Util/RandomText.h"

#pragma once

namespace JcAdventure
{
	namespace Levels
	{
		class ChambersLevel : public Level
		{
		private:
			class ChambersScene : public Scene
			{
			private:
				RandomText introText;
				RandomText victoryText;
			public:
				ChambersScene(long waitTime);

				virtual long onFrame(unsigned int frame);
			};

			ChambersScene*scene;

		public:
			ChambersLevel(const String&name);
			virtual ~ChambersLevel();

			virtual void LoadContent();
			virtual void UnloadContent();
			virtual void Update(long gameTime);
			virtual void Draw(Graphics2D&g, long gameTime);
		};
	}
}