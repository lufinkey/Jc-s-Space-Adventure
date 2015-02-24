
#include "Effect.h"

namespace JcAdventure
{
	Effect::Effect(float x1, float y1) : GameElement(x1,y1)
	{
		dead = false;
	}

	Effect::~Effect()
	{
		//
	}

	void Effect::destroy()
	{
		dead = true;
	}

	void Effect::onDestroy()
	{
		//Open for implementation
	}

	ArrayList<Effect*> EffectManager::effects = ArrayList<Effect*>();

	void EffectManager::addEffect(Effect*effect)
	{
		effects.add(effect);
	}

	void EffectManager::Update(long gameTime)
	{
		for(int i=0; i<effects.size(); i++)
		{
			Effect*effect = effects.get(i);
			effect->Update(gameTime);
		}

		for(int i=(effects.size()-1); i>=0; i--)
		{
			Effect*effect = effects.get(i);
			if(effect->dead)
			{
				effect->onDestroy();
				delete effect;
				effects.remove(i);
			}
		}
	}

	void EffectManager::Draw(Graphics2D&g, long gameTime)
	{
		for(int i=0; i<effects.size(); i++)
		{
			effects.get(i)->Draw(g, gameTime);
		}

		for(int i=(effects.size()-1); i>=0; i--)
		{
			Effect*effect = effects.get(i);
			if(effect->dead)
			{
				effect->onDestroy();
				delete effect;
				effects.remove(i);
			}
		}
	}
}