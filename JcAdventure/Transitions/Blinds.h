
#include "../../GameEngine/GameEngine.h"
#include "Transition.h"

#pragma once

namespace JcAdventure
{
	namespace Transitions
	{
		class Blinds : public Transition
		{
		private:
			long startTime;
			long totalTime;
			int totalLines;

		public:
			Blinds(long time, int lines);
			virtual ~Blinds();

			virtual void Draw(Graphics2D&g, long gameTime);
		};
	}
}