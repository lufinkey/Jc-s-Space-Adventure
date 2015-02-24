
#include "../Level.h"
#include "../Scene.h"
#include "../Util/RandomText.h"

#pragma once

namespace JcAdventure
{
	namespace Levels
	{
		class WeisbrodLevel : public Level
		{
		private:
			class WeisbrodScene : public Scene
			{
			private:
				RandomText introText;
				RandomText victoryText;
			public:
				WeisbrodScene(long waitTime);

				virtual long onFrame(unsigned int frame);
			};

			WeisbrodScene*scene;

		public:
			WeisbrodLevel(const String&name);
			virtual ~WeisbrodLevel();

			virtual void LoadContent();
			virtual void UnloadContent();
			virtual void Update(long gameTime);
			virtual void Draw(Graphics2D&g, long gameTime);
		};
	}
}