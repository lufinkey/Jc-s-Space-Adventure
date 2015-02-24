
#include "../Effect.h"
#include "../Scene.h"

#pragma once

namespace JcAdventure
{
	namespace Effects
	{
		class Explosion : public Effect
		{
		public:
			Explosion(float x1, float y1);
			virtual ~Explosion();

			virtual void onAnimationFinish(const String&name);
		};

		class ExplosionEffects : public Scene
		{
		private:
			RectangleF area;
		public:
			ExplosionEffects(const RectangleF&area);
			virtual ~ExplosionEffects();

			virtual long onFrame(unsigned int frame);
		};
	}
}