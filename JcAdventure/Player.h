
#include "GameElement.h"
#include "Util/RandomText.h"
#include "Projectile.h"

#pragma once

namespace JcAdventure
{
	class Player : public GameElement
	{
		friend class HUD;
	private:
		class Beam : public Projectile
		{
		private:
			float cosDir, sinDir;
		public:
			Beam(float x1, float y1, float dir);
			virtual ~Beam();

			virtual void Update(long gameTime);

			virtual void onBossCollide(Boss*boss);
			virtual void onProjectileCollide(Projectile*projectile);
		};

		RandomText hurtText;
		RandomText oneLiners;
		double health;
		byte hurtFlash;
		bool hurtFlashRed;
		bool controlsOn;
		long nextHurtFlashTime;

	public:
		Player(float x1, float y1);
		virtual ~Player();

		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);

		void enableControls(bool toggle);
		void shoot(float dir);
		void hurt(double damage);
	};
}