
#include "GameElement.h"
#include "../Game.h"

namespace JcAdventure
{
	GameElement::GameElement(float x1, float y1) : Actor(x1, y1)
	{
		bubbleX = 0;
		bubbleY = 0;
		wordBubbleScale = 1;
		wordBubble = new WordBubble(x1,y1);
		finishSpeechTime = 0;
	}

	GameElement::~GameElement()
	{
		delete wordBubble;
	}

	void GameElement::Update(long gameTime)
	{
		Actor::Update(gameTime);
		if(gameTime<finishSpeechTime)
		{
			wordBubble->x = x + (bubbleX*Scale);
			wordBubble->y = y + (bubbleY*Scale);
			wordBubble->Scale = Scale*wordBubbleScale;
			wordBubble->Update(gameTime);
		}
	}

	void GameElement::Draw(Graphics2D&g, long gameTime)
	{
		Actor::Draw(g, gameTime);
		if(gameTime<finishSpeechTime)
		{
			wordBubble->x = x + (bubbleX*Scale);
			wordBubble->y = y + (bubbleY*Scale);
			wordBubble->Scale = Scale*wordBubbleScale;
			wordBubble->Draw(g, gameTime);
		}
	}

	void GameElement::setWordBubbleOffset(float x1, float y1)
	{
		bubbleX = x1;
		bubbleY = y1;
		if(bubbleX>=0)
		{
			wordBubble->mirror(true);
		}
		else
		{
			wordBubble->mirror(false);
		}
	}

	void GameElement::setWordBubbleScale(float scale)
	{
		wordBubbleScale = scale;
	}

	void GameElement::say(const String&speech, long time)
	{
		finishSpeechTime = Game::getGameTime() + time;
		wordBubble->setText(speech);
	}

	void GameElement::closeBubble()
	{
		finishSpeechTime = Game::getGameTime();
	}
}