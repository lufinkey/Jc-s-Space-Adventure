
#include "WordBubble.h"

namespace JcAdventure
{
	WordBubble::WordBubble(float x1, float y1)
	{
		x = x1;
		y = y1;
		Scale = 1;
		alpha = 0;
		mirrored = false;
		text = "";
		speech = new TextActor(0,0,"",AssetManager::getFont("Fonts/phatone.ttf",Font::PLAIN,textSize),Color::BLACK);
		speech->setAlignment(TextActor::ALIGN_CENTER);
		speech->setLineSpacing(8);
		bubble = new Actor(0,0);
		Animation*anim = new Animation("right",1,"Images/wordbubble.png");
		bubble->addAnimation(anim);
		anim = new Animation("left",1,"Images/wordbubble.png");
		anim->mirror(true);
		bubble->addAnimation(anim);
		bubble->changeAnimation("right",FORWARD);

		pulsation = 1;
		pulseGrowing = true;
		wordPulsation = 1;
		wordPulseGrowing = true;
	}

	WordBubble::WordBubble(float x1, float y1, const String&text)
	{
		x = x1;
		y = y1;
		Scale = 1;
		alpha = 0;
		mirrored = false;
		this->text = text;
		speech = new TextActor(0,0,"",AssetManager::getFont("Fonts/phatone.ttf",Font::PLAIN,textSize),Color::BLACK);
		speech->setAlignment(TextActor::ALIGN_CENTER);
		speech->setLineSpacing(8);
		bubble = new Actor(0,0);
		Animation*anim = new Animation("right",1,"Images/wordbubble.png");
		bubble->addAnimation(anim);
		anim = new Animation("left",1,"Images/wordbubble.png");
		anim->mirror(true);
		bubble->addAnimation(anim);
		bubble->changeAnimation("right",FORWARD);

		pulsation = 1;
		pulseGrowing = true;
		wordPulsation = 1;
		wordPulseGrowing = true;
	}

	WordBubble::~WordBubble()
	{
		delete speech;
		delete bubble;
	}

	void WordBubble::updateBubble()
	{
		if(mirrored)
		{
			bubble->x = x + (92*Scale)*pulsation;
		}
		else
		{
			bubble->x = x - (92*Scale)*pulsation;
		}
		bubble->y = y - (206*Scale)*pulsation;
		bubble->Scale = Scale*pulsation;
		bubble->setAlpha(alpha);
	}

	void WordBubble::updateSpeech()
	{
		speech->Scale = wordPulsation;
		speech->setText(text);
		speech->setSize((unsigned int)(textSize*Scale));
		speech->formatToBox((int)((float)boxW*Scale),(int)((float)boxH*Scale));
		if(mirrored)
		{
			speech->x = x + (96*Scale)*wordPulsation;
		}
		else
		{
			speech->x = x - (96*Scale)*wordPulsation;
		}
		speech->y = y - (240*Scale)*wordPulsation;
		speech->setAlpha(alpha);
	}
	
	void WordBubble::Update(long gameTime)
	{
		if(pulseGrowing)
		{
			pulsation += 0.002f;
			if(pulsation>1.025)
			{
				pulseGrowing = false;
			}
		}
		else
		{
			pulsation -= 0.002f;
			if(pulsation<0.975)
			{
				pulseGrowing = true;
			}
		}

		if(wordPulseGrowing)
		{
			wordPulsation += 0.002f;
			if(wordPulsation>1.025)
			{
				wordPulseGrowing = false;
			}
		}
		else
		{
			wordPulsation -= 0.002f;
			if(wordPulsation<0.975)
			{
				wordPulseGrowing = true;
			}
		}

		updateBubble();
		updateSpeech();

		bubble->Update(gameTime);
		speech->Update(gameTime);
	}

	void WordBubble::Draw(Graphics2D&g, long gameTime)
	{
		updateBubble();
		updateSpeech();

		bubble->Draw(g, gameTime);
		speech->Draw(g, gameTime);
	}

	void WordBubble::setText(const String&text)
	{
		this->text = text;
	}

	void WordBubble::mirror(bool toggle)
	{
		mirrored = toggle;
		if(mirrored)
		{
			bubble->changeAnimation("left",FORWARD);
		}
		else
		{
			bubble->changeAnimation("right",FORWARD);
		}
	}

	void WordBubble::setAlpha(float alpha)
	{
		if(alpha>1)
		{
			alpha = 1;
		}
		else if(alpha<0)
		{
			alpha = 0;
		}
		this->alpha = alpha;
	}

	float WordBubble::getAlpha()
	{
		return alpha;
	}
}