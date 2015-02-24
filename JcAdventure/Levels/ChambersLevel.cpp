
#include "ChambersLevel.h"
#include "../Global.h"
#include "../TransitionManager.h"
#include "../Transitions/Fade.h"
#include "../Bosses/Chambers.h"

namespace JcAdventure
{
	namespace Levels
	{
		ChambersLevel::ChambersScene::ChambersScene(long waitTime) : Scene(waitTime)
		{
			introText.add("Hope you like annotating!");
			introText.add("We're gonna to have so much fun this year...");

			victoryText.add("I'm sensitive!");
			victoryText.add("You are a bright student");
			victoryText.add("I don't hate you. Honest.");
		}

		long ChambersLevel::ChambersScene::onFrame(unsigned int frame)
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

		ChambersLevel::ChambersLevel(const String&name) : Level(name)
		{
			scene = NULL;
		}

		ChambersLevel::~ChambersLevel()
		{
			//
		}

		void ChambersLevel::LoadContent()
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

			scene = new ChambersScene(1500);
			Global::playr = new Player(400,300);
			Global::boss = new Chambers(800,300);
		}

		void ChambersLevel::UnloadContent()
		{
			delete Global::playr;
			Global::playr = NULL;
			
			delete Global::boss;
			Global::boss = NULL;

			delete scene;
			scene = NULL;
		}

		void ChambersLevel::Update(long gameTime)
		{
			scene->Update(gameTime);
			Global::boss->Update(gameTime);
			Global::playr->Update(gameTime);
			Global::hud->Update(gameTime);
			ProjectileManager::Update(gameTime);
			EffectManager::Update(gameTime);
		}

		void ChambersLevel::Draw(Graphics2D&g, long gameTime)
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