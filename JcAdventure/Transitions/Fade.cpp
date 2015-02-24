
#include "Fade.h"

namespace JcAdventure
{
	namespace Transitions
	{
		Fade::Fade(long time, int numIntervals, bool fadeIn, const Color&fadeColor)
		{
			if(numIntervals>0 && time>0)
			{
				totalTime = time;
				intervals = numIntervals;
				fadingIn = fadeIn;
				color = fadeColor;
				nextFadeTime = 0;

				if(fadingIn)
				{
					alpha = 255;
				}
				else
				{
					alpha = 0;
				}
			}
			else
			{
				setFinished();
			}
		}

		Fade::~Fade()
		{
			//
		}

		void Fade::Update(long gameTime)
		{
			if(nextFadeTime == 0)
			{
				nextFadeTime = gameTime + (totalTime/intervals);
			}
			else if(gameTime >= nextFadeTime)
			{
				if(fadingIn)
				{
					if(alpha <= 0)
					{
						setFinished();
					}
					else
					{
						alpha -= ((float)255/(float)intervals);
					}
				}
				else
				{
					if(alpha >= 255)
					{
						setFinished();
					}
					else
					{
						alpha += ((float)255/(float)intervals);
					}
				}
				nextFadeTime = gameTime + (totalTime/intervals);
			}
		}

		void Fade::Draw(Graphics2D&g, long gameTime)
		{
			unsigned char realAlpha = 255;

			if(alpha<=0)
			{
				realAlpha = 0;
			}
			else if(alpha>=255)
			{
				realAlpha = 255;
			}
			else
			{
				realAlpha = (unsigned char)((int)alpha);
			}

			unsigned char oldAlpha = g.getAlpha();
			g.setAlpha(realAlpha);
			g.setColor(Color::BLACK);
			g.fillRect(0,0,(float)View::ScaleWidth(),(float)View::ScaleHeight());
			g.setAlpha(oldAlpha);
		}
	}
}