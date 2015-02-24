
#include "TitleScreen.h"
#include "../../Game.h"
#include "../TransitionManager.h"
#include "../Global.h"

namespace JcAdventure
{
	SplashScreen::SplashScreen(const String&name) : Screen(name)
	{
		logo = new Actor((float)View::ScaleWidth()/2, (float)View::ScaleHeight()/2);
		logo->setAlpha(1);
		logo->Scale = 2.0f;
		nextFadeTime = 0;
		alpha = 1;
		growing = true;
		finishing = false;
	}

	SplashScreen::~SplashScreen()
	{
		delete logo;
	}

	void SplashScreen::Initialize()
	{
		logo->addAnimation(new Animation("normal",1,"Images/bps_logo.png"));
		logo->changeAnimation("normal",FORWARD);
	}

	void SplashScreen::LoadContent()
	{
		Game::showBackground(false);
		Game::setBackgroundColor(Color::BLACK);
	}

	void SplashScreen::Update(long gameTime)
	{
		if(nextFadeTime == 0)
		{
			alpha = 1;
			nextFadeTime = gameTime;
			growing = true;
			finishing = false;
		}
		else
		{
			if(gameTime >= nextFadeTime)
			{
				if(finishing)
				{
					finishing = false;
					growing = true;
					nextFadeTime = 0;
					ScreenManager::GoToScreen("TitleScreen");
					return;
				}
				else if(growing)
				{
					alpha -= 0.1f;
				}
				else
				{
					alpha += 0.1f;
				}

				if(alpha <= 0)
				{
					nextFadeTime = gameTime + 500;
					alpha = 0;
					growing = false;
				}
				else if(alpha >= 1)
				{
					nextFadeTime = gameTime + 500;
					alpha = 1;
					growing = true;
					finishing = true;
				}
				else
				{
					nextFadeTime = gameTime + 80;
				}
			}
		}

		if(Game::screenTapped())
		{
			nextFadeTime = gameTime;
			alpha = 1;
			finishing = true;
			growing = true;
		}

		logo->setAlpha(alpha);
	}

	void SplashScreen::Draw(Graphics2D&g, long gameTime)
	{
		logo->setAlpha(alpha);
		logo->Draw(g, gameTime);
	}

	const float TitleScreen::logoX = 200;

	TitleScreen::TitleScreen(const String&name) : Screen(name)
	{
		logo = new Actor((float)View::ScaleWidth()/2, logoX);
		inTransition = false;
	}

	TitleScreen::~TitleScreen()
	{
		delete logo;
		for(int i=0; i<menuOptions.size(); i++)
		{
			delete menuOptions.get(i);
		}
		menuOptions.clear();
	}

	void TitleScreen::Initialize()
	{
		logo->addAnimation(new Animation("normal", 1, "Images/title.png"));
		logo->changeAnimation("normal", FORWARD);
		TextActor*option = new TextActor((float)View::ScaleWidth()/2, 400, "Start Game", AssetManager::getFont("Fonts/phatone.ttf",Font::PLAIN,26), Color::WHITE);
		option->setAlignment(TextActor::ALIGN_CENTER);
		menuOptions.add(option);
	}

	void TitleScreen::LoadContent()
	{
		Game::setBackgroundImage("Images/Backgrounds/space1.png");
		logo->y = View::ScaleHeight() + (float)logo->height/2;
	}

	void TitleScreen::UnloadContent()
	{
		inTransition = false;
		for(int i=0; i<menuOptions.size(); i++)
		{
			menuOptions.get(i)->setColor(Color::WHITE);
		}
	}

	void TitleScreen::Update(long gameTime)
	{
		logo->Update(gameTime);
		if(logo->y > logoX)
		{
			logo->y -= 5;
			if(Game::screenTapped())
			{
				logo->y = logoX;
			}
		}
		else if(logo->y <= logoX)
		{
			logo->y = logoX;
		}
		if(!inTransition && logo->y==logoX)
		{
			for(int i=0; i<menuOptions.size(); i++)
			{
				TextActor*option = menuOptions.get(i);
				option->Update(gameTime);
				if(option->wasClicked() && !option->isClicked())
				{
					inTransition = true;
					String target = "";
					if(option->getText().equals("Start Game"))
					{
						target = "level-intro";
					}
					TransitionManager::addTransition(new Transitions::Blinds(800, 8),target);
				}
				if(option->mouseOver())
				{
					option->setColor(Color::YELLOW);
				}
				else
				{
					option->setColor(Color::WHITE);
				}
			}
		}
	}

	void TitleScreen::Draw(Graphics2D&g, long gameTime)
	{
		logo->Draw(g, gameTime);
		if(logo->y==logoX)
		{
			for(int i=0; i<menuOptions.size(); i++)
			{
				TextActor*option = menuOptions.get(i);
				option->Draw(g, gameTime);
			}
		}
	}
}