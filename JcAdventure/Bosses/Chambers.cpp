
#include "Chambers.h"
#include "../Global.h"

namespace JcAdventure
{
	const float Chambers::RedPen::startRot = 60;
	const float Chambers::RedPen::endRot = -60;
	const float Chambers::RedPen::offset = 100;

	Chambers::RedPen::PenProjectile::PenProjectile(float x1, float y1, float dir) : Projectile(x1,y1, true)
	{
		float rads = (float)degtorad((double)dir);
		cosDir = cos(rads);
		sinDir = sin(rads);

		Scale = 0.5f;

		addAnimation(new Animation("normal", 1, "Images/Bosses/Chambers/pen_projectile.png"));
		changeAnimation("normal", FORWARD);
	}

	Chambers::RedPen::PenProjectile::~PenProjectile()
	{
		//
	}

	void Chambers::RedPen::PenProjectile::Update(long gameTime)
	{
		Projectile::Update(gameTime);
		x+=10*cosDir;
		y+=10*sinDir;
	}

	void Chambers::RedPen::PenProjectile::Draw(Graphics2D&g, long gameTime)
	{
		Projectile::Draw(g, gameTime);
	}

	void Chambers::RedPen::PenProjectile::onPlayerCollide(Player*playr)
	{
		playr->hurt(0.05);
		destroy();
	}

	void Chambers::RedPen::PenProjectile::onProjectileCollide(Projectile*projectile)
	{
		if(!projectile->isEnemy())
		{
			destroy();
		}
	}

	Chambers::RedPen::RedPen(float x1, float y1)
	{
		x = x1;
		y = y1;
		Scale = 1;
		pen = new Actor(x1, y1);
		Animation*anim = new Animation("normal", 1, "Images/Bosses/Chambers/red_pen.png");
		anim->mirror(true);
		pen->addAnimation(anim);
		pen->changeAnimation("normal", FORWARD);

		backing = false;
		slashing = false;
		approach = 0;
	}

	Chambers::RedPen::~RedPen()
	{
		delete pen;
	}

	void Chambers::RedPen::Update(long gameTime)
	{
		if(backing)
		{
			float newRotation = pen->getRotation()+10;
			approach = (newRotation/startRot)*offset;
			pen->setRotation(newRotation);
			if(newRotation >= startRot)
			{
				backing = false;
				slashing = true;
				approach = 0;
			}
			else
			{
				float rads = (float)degtorad((double)newRotation);
				float cosPen = cos(rads);
				float sinPen = -sin(rads);
				float dist = (float)((pen->width/2)+(approach*Scale));
				pen->x = x - cosPen*dist;
				pen->y = y + sinPen*dist;
			}
		}
		else if(slashing)
		{
			float newRotation = pen->getRotation()-15;
			pen->setRotation(newRotation);

			float rads = (float)degtorad((double)newRotation);
			float cosPen = cos(rads);
			float sinPen = -sin(rads);
			float dist = (float)((pen->width/2)+(offset*Scale));
			pen->x = x - cosPen*dist;
			pen->y = y + sinPen*dist;
			
			if(newRotation <= endRot)
			{
				slashing = false;
			}

			ProjectileManager::addProjectile(new PenProjectile(x - cosPen*dist, y + sinPen*dist, newRotation+180));
		}
		else
		{
			pen->setRotation(0);
			pen->x = x - (pen->width/2);
			pen->y = y;
		}
		pen->Scale = Scale;
		pen->Update(gameTime);
	}

	void Chambers::RedPen::Draw(Graphics2D&g, long gameTime)
	{
		if(!slashing && !backing)
		{
			pen->setRotation(0);
			pen->x = x - (pen->width/2);
			pen->y = y;
		}
		pen->Scale = Scale;
		pen->Draw(g, gameTime);
	}

	void Chambers::RedPen::slash()
	{
		backing = true;
		slashing = false;
		approach = 0;
		pen->setRotation(0);
	}

	bool Chambers::RedPen::isSlashing()
	{
		if(backing || slashing)
		{
			return true;
		}
		return false;
	}

	Chambers::Chambers(float x1, float y1) : Boss(x1,y1)
	{
		addAnimation(new Animation("normal", 1, "Images/Bosses/Chambers/chambers.png"));
		Animation*anim = new Animation("blink",10);
		anim->addFrame("Images/Bosses/Chambers/chambers_blink.png");
		anim->addFrame("Images/Bosses/Chambers/chambers.png");
		anim->addFrame("Images/Bosses/Chambers/chambers_blink.png");
		anim->addFrame("Images/Bosses/Chambers/chambers.png");
		anim->addFrame("Images/Bosses/Chambers/chambers_blink.png");
		anim->addFrame("Images/Bosses/Chambers/chambers.png");
		anim->addFrame("Images/Bosses/Chambers/chambers_blink.png");
		addAnimation(anim);

		Scale = 0.5f;

		changeAnimation("normal",FORWARD);
		setWordBubbleOffset(-100,-60);
		setWordBubbleScale(0.8f);
		setEyes("Images/Bosses/Chambers/left_eye.png", "Images/Bosses/Chambers/right_eye.png");
		setEyeProperties(-76,-22,12, 14,-5,10);
		nextBlinkTime = 0;
		
		pen = new RedPen(x1,y1);
		pen->Scale = 0.2f;
		
		deathSplosions = NULL;
		alreadyDead = false;
	}
	
	Chambers::~Chambers()
	{
		if(deathSplosions!=NULL)
		{
			delete deathSplosions;
			deathSplosions = NULL;
		}
	}

	void Chambers::Update(long gameTime)
	{
		if(nextBlinkTime==0)
		{
			nextBlinkTime = gameTime + (long)(GameEngine::random()*12000);
		}
		else if(gameTime >= nextBlinkTime)
		{
			changeAnimation("blink",FORWARD);
			nextBlinkTime = gameTime + (long)(GameEngine::random()*12000);
		}
		pen->x = x;
		pen->y = y;
		Boss::Update(gameTime);
		pen->Update(gameTime);
		setFocalPoint(Global::playr->x, Global::playr->y);

		if(getHealth()<0 && !alreadyDead)
		{
			alreadyDead = true;
			RectangleF area;
			area.x = x - ((float)width/2);
			area.y = y - ((float)height/2);
			area.width = (float)width;
			area.height = (float)height;
			deathSplosions = new Effects::ExplosionEffects(area);
			say("Nooooooooo!!!!!", 3000);
			Global::gamePlaying = false;
			yvelocity = 0;
		}
		
		if(getHealth()>0 && Global::gamePlaying)
		{
			double randNum = GameEngine::random();
			if(y<50)
			{
				yvelocity = 5;
			}
			else if(y>550)
			{
				yvelocity = -5;
			}
			
			if(yvelocity == 0)
			{
				yvelocity = 5;
			}
			
			if(randNum>0.95 && !pen->isSlashing())
			{
				pen->slash();
			}
		}
		
		if(deathSplosions!=NULL)
		{
			deathSplosions->Update(gameTime);
		}
	}

	void Chambers::Draw(Graphics2D&g, long gameTime)
	{
		Boss::Draw(g, gameTime);
		if(pen->isSlashing())
		{
			pen->Draw(g, gameTime);
		}

		if(deathSplosions!=NULL)
		{
			deathSplosions->Draw(g, gameTime);
		}
	}

	void Chambers::onRelease()
	{
		//pen->slash();
	}

	void Chambers::onAnimationFinish(const String&name)
	{
		if(name.equals("blink"))
		{
			changeAnimation("normal",FORWARD);
		}
	}
}