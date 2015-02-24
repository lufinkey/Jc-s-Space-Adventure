
#include "../../GameEngine/GameEngine.h"

#pragma once

namespace JcAdventure
{
	namespace Transitions
	{
		class Transition
		{
		private:
			bool isFinished;
		protected:
			void setFinished();
		public:
			Transition();
			virtual ~Transition();

			bool finished();

			virtual void Update(long gameTime);
			virtual void Draw(Graphics2D&g, long gameTime);
		};
	}
}