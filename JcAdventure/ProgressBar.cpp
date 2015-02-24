
#include "ProgressBar.h"

namespace JcAdventure
{
	ProgressBar::ProgressBar()
	{
		x = 0;
		y = 0;
		Scale = 1;
		progress = 0;
		bar = new Actor(x,y);
		//TODO add animations
	}

	ProgressBar::ProgressBar(float x1, float y1)
	{
		x = x1;
		y = y1;
		Scale = 1;
		progress = 0;
		bar = new Actor(x, y);
		//TODO add animations
	}

	ProgressBar::~ProgressBar()
	{
		delete bar;
	}

	void ProgressBar::setProgress(float progress)
	{
		if(progress<0)
		{
			progress = 0;
		}
		else if(progress>1)
		{
			progress = 1;
		}
		this->progress = progress;

		//TODO set animations
	}

	float ProgressBar::getProgress()
	{
		return progress;
	}

	void ProgressBar::relativeToView(bool toggle)
	{
		bar->relativeToView(toggle);
	}

	void ProgressBar::setAlpha(float alpha)
	{
		bar->setAlpha(alpha);
	}

	float ProgressBar::getAlpha()
	{
		return bar->getAlpha();
	}

	void ProgressBar::setRotation(float degrees)
	{
		bar->setRotation(degrees);
	}

	float ProgressBar::getRotation()
	{
		return bar->getRotation();
	}
}