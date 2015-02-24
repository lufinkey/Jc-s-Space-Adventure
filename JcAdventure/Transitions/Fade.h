
#include "../../GameEngine/GameEngine.h"
#include "Transition.h"

#pragma once

namespace JcAdventure
{
	namespace Transitions
	{
		class Fade : public Transition
		{
		private:
			bool fadingIn;
			Color color;
			int intervals;
			long totalTime;
			long nextFadeTime;
			float alpha;

		public:
			Fade(long time, int numIntervals, bool fadeIn, const Color&fadeColor);
			virtual ~Fade();

			virtual void Update(long gameTime);
			virtual void Draw(Graphics2D&g, long gameTime);
		};
	}
}