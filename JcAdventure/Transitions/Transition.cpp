
#include "Transition.h"

namespace JcAdventure
{
	namespace Transitions
	{
		Transition::Transition()
		{
			isFinished = false;
		}

		Transition::~Transition()
		{
			//
		}

		void Transition::setFinished()
		{
			isFinished = true;
		}

		bool Transition::finished()
		{
			return isFinished;
		}

		void Transition::Update(long gameTime)
		{
			//open for implementation
		}

		void Transition::Draw(Graphics2D&g, long gameTime)
		{
			//open for implementation
		}
	}
}