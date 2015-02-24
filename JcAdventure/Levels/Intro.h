
#include "../Level.h"
#include "../GameElement.h"
#include "../Scene.h"

#pragma once

namespace JcAdventure
{
	namespace Levels
	{
		class Intro : public Level
		{
		private:
			class IntroScene : public Scene
			{
				friend class Intro;
			private:
				Intro*screen;

			public:
				IntroScene(long waitTime, Intro*screen);
				virtual ~IntroScene();

				virtual long onFrame(unsigned int frame);
			};

			class GodHead : public GameElement
			{
			public:
				GodHead(float x1, float y1);
				virtual ~GodHead();
			};

			IntroScene*scene;

			GodHead*austin;
			GodHead*cage;
			GodHead*fsm;
		public:
			Intro(const String&name);
			virtual ~Intro();

			virtual void LoadContent();
			virtual void UnloadContent();
			virtual void Update(long gameTime);
			virtual void Draw(Graphics2D&g, long gameTime);
		};
	}
}