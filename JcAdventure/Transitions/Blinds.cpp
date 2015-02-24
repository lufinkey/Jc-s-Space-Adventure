
#include "Blinds.h"
#include "../../Game.h"

namespace JcAdventure
{
	namespace Transitions
	{
		Blinds::Blinds(long time, int lines)
		{
			if(lines>0 && time>0)
			{
				totalTime = time;
				startTime = Game::getGameTime();
				totalLines = lines;
			}
			else
			{
				setFinished();
			}
		}

		Blinds::~Blinds()
		{
			//
		}

		void Blinds::Draw(Graphics2D&g, long gameTime)
		{
			if(!finished())
			{
				if(gameTime > (startTime+totalTime))
				{
					setFinished();
					startTime = 0;
					totalTime = 0;
					totalLines = 6;
					g.setColor(Color::BLACK);
					g.fillRect(0,0,(float)View::ScaleWidth(),(float)View::ScaleHeight());
				}
				else
				{
					double progress = (double)(gameTime-startTime)/(double)totalTime;
					for(int i=0; i<totalLines; i++)
					{
						float height = ((float)View::ScaleHeight()/totalLines);
						float y = height*i;
						g.setColor(Color::BLACK);
						g.fillRect(0,y,(float)View::ScaleWidth(),(float)(height*progress));
					}
				}
			}
		}
	}
};