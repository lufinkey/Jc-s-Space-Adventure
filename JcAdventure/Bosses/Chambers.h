
#include "Boss.h"
#include "../Projectile.h"
#include "../Effects/Explosions.h"

#pragma once

namespace JcAdventure
{
	class Chambers : public Boss
	{
	private:
		class RedPen
		{
		private:
			static const float startRot;
			static const float endRot;
			static const float offset;

			class PenProjectile : public Projectile
			{
			private:
				float cosDir;
				float sinDir;
			public:
				PenProjectile(float x1, float y1, float dir);
				virtual ~PenProjectile();

				virtual void Update(long gameTime);
				virtual void Draw(Graphics2D&g, long gameTime);

				virtual void onPlayerCollide(Player*playr);
				virtual void onProjectileCollide(Projectile*projectile);
			};

			Actor*pen;
			bool backing;
			bool slashing;
			float approach;

		public:
			float x,y;
			float Scale;

			RedPen(float x1, float y1);
			virtual ~RedPen();

			virtual void Update(long gameTime);
			virtual void Draw(Graphics2D&g, long gameTime);

			void slash();
			bool isSlashing();
		};

		RedPen*pen;
		long nextBlinkTime;

		Effects::ExplosionEffects*deathSplosions;

		bool alreadyDead;

	public:
		Chambers(float x1, float y1);
		virtual ~Chambers();

		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);

		virtual void onRelease();
		virtual void onAnimationFinish(const String&name);
	};
}