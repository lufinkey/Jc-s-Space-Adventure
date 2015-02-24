
#include "Transitions/Transition.h"

#pragma once

namespace JcAdventure
{
	class TransitionManager
	{
	private:
		class TransitionInfo
		{
		private:
			Transitions::Transition*transition;
			String target;

		public:
			TransitionInfo(Transitions::Transition*transition, const String&target);
			virtual ~TransitionInfo();

			virtual void Update(long gameTime);
			virtual void Draw(Graphics2D&g, long gameTime);

			bool finished();
			String getTarget();
		};

		static ArrayList<TransitionInfo*> queue;

	public:
		static void Update(long gameTime);
		static void Draw(Graphics2D&g, long gameTime);
		
		static void addTransition(Transitions::Transition*transition, String target = "");
	};
}