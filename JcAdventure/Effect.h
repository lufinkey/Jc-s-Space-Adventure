
#include "GameElement.h"

#pragma once

namespace JcAdventure
{
	class Effect : public GameElement
	{
		friend class EffectManager;
	private:
		bool dead;
	public:
		Effect(float x1, float y1);
		virtual ~Effect();

		void destroy();

		virtual void onDestroy();
	};

	class EffectManager
	{
	private:
		static ArrayList<Effect*> effects;

	public:
		static void addEffect(Effect*effect);

		static void Update(long gameTime);
		static void Draw(Graphics2D&g, long gameTime);
	};
}