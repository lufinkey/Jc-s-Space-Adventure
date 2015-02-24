
#include "WeisbrodLevel.h"
#include "../Global.h"
#include "../TransitionManager.h"
#include "../Transitions/Fade.h"
#include "../Bosses/Weisbrod.h"

namespace JcAdventure
{
	namespace Levels
	{
		WeisbrodLevel::WeisbrodScene::WeisbrodScene(long waitTime) : Scene(waitTime)
		{
			introText.add("Are you ready to climb the ladder?");
			introText.add("Hammer power!");
			introText.add("Time for me to keep chippin\' away!");
			introText.add("Welcome to the great land of Weisbrodia!");

			victoryText.add("You have proven yourself worthy.");
		}

		long WeisbrodLevel::WeisbrodScene::onFrame(unsigned int frame)
		{
			switch(frame)
			{
				case 0:
				Global::boss->say(introText.get(), 4000);
				return 5000;
				
				case 1:
				Global::playr->enableControls(true);
				Global::gamePlaying = true;
				stop();
				return 0;
			}
			return 0;
		}

		WeisbrodLevel::WeisbrodLevel(const String&name) : Level(name)
		{
			scene = NULL;
		}

		WeisbrodLevel::~WeisbrodLevel()
		{
			//
		}

		void WeisbrodLevel::LoadContent()
		{
			TransitionManager::addTransition(new Transitions::Fade(800,10,true,Color::BLACK));
			
			if(scene!=NULL)
			{
				delete scene;
				scene = NULL;
			}
			if(Global::playr!=NULL)
			{
				delete Global::playr;
				Global::playr = NULL;
			}
			if(Global::boss!=NULL)
			{
				delete Global::boss;
				Global::boss = NULL;
			}

			scene = new WeisbrodScene(1500);
			Global::playr = new Player(400,300);
			Global::boss = new Weisbrod(800,300);
		}

		void WeisbrodLevel::UnloadContent()
		{
			delete Global::playr;
			Global::playr = NULL;
			
			delete Global::boss;
			Global::boss = NULL;

			delete scene;
			scene = NULL;
		}

		void WeisbrodLevel::Update(long gameTime)
		{
			scene->Update(gameTime);
			Global::boss->Update(gameTime);
			Global::playr->Update(gameTime);
			Global::hud->Update(gameTime);
			ProjectileManager::Update(gameTime);
			EffectManager::Update(gameTime);
		}

		void WeisbrodLevel::Draw(Graphics2D&g, long gameTime)
		{
			scene->Draw(g, gameTime);
			Global::boss->Draw(g, gameTime);
			Global::playr->Draw(g, gameTime);
			Global::hud->Draw(g, gameTime);
			ProjectileManager::Draw(g, gameTime);
			EffectManager::Draw(g, gameTime);
		}
	}
}