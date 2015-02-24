
#include "Intro.h"
#include "../../Game.h"
#include "../Global.h"
#include "../TransitionManager.h"
#include "../Transitions/Fade.h"

namespace JcAdventure
{
	namespace Levels
	{
		Intro::IntroScene::IntroScene(long waitTime, Intro*screen) : Scene(waitTime)
		{
			this->screen = screen;
		}

		Intro::IntroScene::~IntroScene()
		{
			//
		}

		long Intro::IntroScene::onFrame(unsigned int frame)
		{
			switch(frame)
			{
				case 0:
				screen->cage->closeBubble();
				screen->fsm->closeBubble();
				screen->austin->say("Jc! The universe needs your help!", 4000);
				return 5000;

				case 1:
				screen->austin->closeBubble();
				screen->fsm->closeBubble();
				screen->cage->say("You hold a valuable set of skills. Skills you have acquired over your 4 years",5000);
				return 6000;

				case 2:
				screen->cage->closeBubble();
				screen->austin->closeBubble();
				screen->fsm->say("The gods have spoken. Go forth and fulfill your destiny!", 4000);
				return 5000;

				case 3:
				{
					stop();
					double randNum = GameEngine::random();
					Console::WriteLine(randNum);
					if(randNum>0.5)
					{
						TransitionManager::addTransition(new Transitions::Fade(800,10,false,Color::BLACK), "level-chambers");
					}
					else
					{
						TransitionManager::addTransition(new Transitions::Fade(800,10,false,Color::BLACK), "level-weisbrod");
					}
				}
				return 0;
			}
			return 0;
		}

		Intro::GodHead::GodHead(float x1, float y1) : GameElement(x1,y1)
		{
			setWordBubbleOffset(-100,-120);
		}

		Intro::GodHead::~GodHead()
		{
			//
		}

		Intro::Intro(const String&name) : Level(name)
		{
			cage = NULL;
			austin = NULL;
			fsm = NULL;
			scene = NULL;
		}

		Intro::~Intro()
		{
			if(cage!=NULL)
			{
				delete cage;
				cage = NULL;
			}
			if(austin!=NULL)
			{
				delete austin;
				austin = NULL;
			}
			if(fsm!=NULL)
			{
				delete fsm;
				fsm = NULL;
			}

			if(scene!=NULL)
			{
				delete scene;
				scene = NULL;
			}
		}

		void Intro::LoadContent()
		{
			TransitionManager::addTransition(new Transitions::Fade(800,10,true,Color::BLACK));
			
			if(scene!=NULL)
			{
				delete scene;
			}
			scene = new IntroScene(1500, this);

			if(Global::playr!=NULL)
			{
				delete Global::playr;
				Global::playr = NULL;
			}

			Global::playr = new Player(100,300);

			austin = new GodHead(500, 300);
			austin->Scale = 0.4f;
			austin->addAnimation(new Animation("normal", 1, "Images/Intro/austin.png"));
			austin->changeAnimation("normal",FORWARD);

			fsm = new GodHead(650, 300);
			fsm->Scale = 0.4f;
			fsm->addAnimation(new Animation("normal", 1, "Images/Intro/fsm.png"));
			fsm->changeAnimation("normal",FORWARD);

			cage = new GodHead(800, 300);
			cage->Scale = 0.4f;
			cage->addAnimation(new Animation("normal", 1, "Images/Intro/cage.png"));
			cage->changeAnimation("normal",FORWARD);
		}

		void Intro::UnloadContent()
		{
			delete cage;
			cage = NULL;
			delete austin;
			austin = NULL;
			delete fsm;
			fsm = NULL;

			delete scene;
			scene = NULL;

			delete Global::playr;
			Global::playr = NULL;
		}

		void Intro::Update(long gameTime)
		{
			if(Game::screenTapped())
			{
				scene->jump();
			}
			scene->Update(gameTime);
			fsm->Update(gameTime);
			cage->Update(gameTime);
			austin->Update(gameTime);
			Global::playr->Update(gameTime);
			//ProjectileManager::Update(gameTime);
			//Global::hud->Update(gameTime);
		}

		void Intro::Draw(Graphics2D&g, long gameTime)
		{
			scene->Draw(g, gameTime);
			fsm->Draw(g, gameTime);
			cage->Draw(g, gameTime);
			austin->Draw(g, gameTime);
			Global::playr->Draw(g, gameTime);
			//ProjectileManager::Draw(g, gameTime);
			//Global::hud->Draw(g, gameTime);
		}
	}
}