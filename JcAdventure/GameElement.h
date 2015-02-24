
#include "../GameEngine/GameEngine.h"
#include "WordBubble.h"

#pragma once

namespace JcAdventure
{
	class GameElement : public Actor
	{
	private:
		WordBubble*wordBubble;
		float bubbleX, bubbleY;
		long finishSpeechTime;
		float wordBubbleScale;
		
	protected:
		void setWordBubbleOffset(float x1, float y1);
		void setWordBubbleScale(float scale);
		
	public:
		GameElement(float x1, float y1);
		virtual ~GameElement();

		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);
		
		void say(const String&speech, long time = 3000);
		void closeBubble();
	};
}