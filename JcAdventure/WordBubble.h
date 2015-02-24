
#include "../GameEngine/GameEngine.h"

#pragma once

namespace JcAdventure
{
	class WordBubble
	{
	private:
		String text;
		Actor*bubble;
		TextActor*speech;
		bool mirrored;

		float alpha;

		float pulsation;
		bool pulseGrowing;
		float wordPulsation;
		bool wordPulseGrowing;

		static const int boxW = 340;
		static const int boxH = 220;
		static const unsigned int textSize = 22;

		void updateBubble();
		void updateSpeech();

	public:
		float x,y;
		float Scale;

		WordBubble(float x1, float y1);
		WordBubble(float x1, float y1, const String&text);
		virtual ~WordBubble();

		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);

		void setText(const String&text);
		void mirror(bool toggle);

		void setAlpha(float alpha);
		float getAlpha();
	};
}