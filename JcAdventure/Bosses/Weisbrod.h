
#include "Boss.h"
#include "../Projectile.h"
#include "../Effects/Explosions.h"

#pragma once

namespace JcAdventure
{
	class Weisbrod : public Boss
	{
	private:
		class Hammer : public Projectile
		{
		public:
			Hammer(float x1, float y1);
			virtual ~Hammer();
			
			virtual void Update(long gameTime);
			virtual void Draw(Graphics2D&g, long gameTime);
			
			virtual void onPlayerCollide(Player*playr);
			virtual void onProjectileCollide(Projectile*projectile);
		};
		
		Effects::ExplosionEffects*deathSplosions;
		
		bool alreadyDead;
		
	public:
		Weisbrod(float x1, float y1);
		virtual ~Weisbrod();
		
		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);
		
		virtual void onRelease();
		virtual void onAnimationFinish(const String&name);
	};
}