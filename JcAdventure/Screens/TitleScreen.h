
#include "../../GameEngine/GameEngine.h"
#include "../Transitions/Blinds.h"

#pragma once

namespace JcAdventure
{
	class SplashScreen : public Screen
	{
	private:
		Actor*logo;
		float alpha;
		long nextFadeTime;
		bool growing;
		bool finishing;
	public:
		SplashScreen(const String&name);
		virtual ~SplashScreen();

		virtual void Initialize();
		virtual void LoadContent();
		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);
	};

	class TitleScreen : public Screen
	{
	private:
		bool optionsDisabled;
		Actor*logo;
		ArrayList<TextActor*> menuOptions;
		bool inTransition;

		static const float logoX;
		
	public:
		TitleScreen(const String&name);
		virtual ~TitleScreen();

		virtual void Initialize();
		virtual void LoadContent();
		virtual void UnloadContent();
		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);
	};
}