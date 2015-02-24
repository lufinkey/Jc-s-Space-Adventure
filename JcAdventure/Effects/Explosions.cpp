
#include "Explosions.h"

namespace JcAdventure
{
	namespace Effects
	{
		Explosion::Explosion(float x1, float y1) : Effect(x1,y1)
		{
			int explosionNum = (int)(GameEngine::random()*3);
			ArrayList<int> frames;
			switch(explosionNum)
			{
				default:
				for(int i=0; i<6; i++)
				{
					frames.add(i);
				}
				break;

				case 1:
				for(int i=6; i<12; i++)
				{
					frames.add(i);
				}
				break;

				case 2:
				for(int i=12; i<18; i++)
				{
					frames.add(i);
				}
				break;
			}

			Animation*anim = new Animation("normal", 10, 3,6, frames);
			anim->addFrame("Images/Misc/explosion.png");
			addAnimation(anim);
			changeAnimation("normal",FORWARD);
		}

		Explosion::~Explosion()
		{
			//
		}

		void Explosion::onAnimationFinish(const String&name)
		{
			destroy();
		}

		ExplosionEffects::ExplosionEffects(const RectangleF&area) : Scene()
		{
			this->area = area;
		}

		ExplosionEffects::~ExplosionEffects()
		{
			//
		}

		long ExplosionEffects::onFrame(unsigned int frame)
		{
			float randX = area.x + ((float)GameEngine::random()*area.width);
			float randY = area.y + ((float)GameEngine::random()*area.height);

			switch(frame)
			{
				case 4:
				stop();

				default:
				EffectManager::addEffect(new Explosion(randX, randY));
				break;
			}
			return 200;
		}
	}
}