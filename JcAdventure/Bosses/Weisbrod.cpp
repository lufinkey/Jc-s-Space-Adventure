
#include "Weisbrod.h"
#include "../Global.h"

namespace JcAdventure
{
	Weisbrod::Hammer::Hammer(float x1, float y1) : Projectile(x1,y1, true)
	{
		Scale = 0.5f;
		
		addAnimation(new Animation("normal", 1, "Images/Bosses/Weisbrod/hammer.png"));
		changeAnimation("normal", FORWARD);
	}
	
	Weisbrod::Hammer::~Hammer()
	{
		//
	}
	
	void Weisbrod::Hammer::Update(long gameTime)
	{
		Projectile::Update(gameTime);
		x-=10;
	}
	
	void Weisbrod::Hammer::Draw(Graphics2D&g, long gameTime)
	{
		Projectile::Draw(g, gameTime);
	}
	
	void Weisbrod::Hammer::onPlayerCollide(Player*playr)
	{
		playr->hurt(0.05);
		destroy();
	}
	
	void Weisbrod::Hammer::onProjectileCollide(Projectile*projectile)
	{
		if(!projectile->isEnemy())
		{
			destroy();
		}
	}
	
	Weisbrod::Weisbrod(float x1, float y1) : Boss(x1,y1)
	{
		addAnimation(new Animation("normal", 1, "Images/Bosses/Weisbrod/weisbrod.png"));
		
		Scale = 0.5f;
		
		changeAnimation("normal",FORWARD);
		setWordBubbleOffset(-100,-60);
		setWordBubbleScale(0.8f);
		setEyes("Images/Bosses/Chambers/left_eye.png", "Images/Bosses/Chambers/right_eye.png");
		setEyeProperties(-69, -13,12, 31,-13,12);
		
		deathSplosions = NULL;
		alreadyDead = false;
	}
	
	Weisbrod::~Weisbrod()
	{
		if(deathSplosions!=NULL)
		{
			delete deathSplosions;
			deathSplosions = NULL;
		}
	}
	
	void Weisbrod::Update(long gameTime)
	{
		Boss::Update(gameTime);
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
			
			if(randNum>0.95)
			{
				ProjectileManager::addProjectile(new Hammer(x,y));
			}
		}
		
		if(deathSplosions!=NULL)
		{
			deathSplosions->Update(gameTime);
		}
	}
	
	void Weisbrod::Draw(Graphics2D&g, long gameTime)
	{
		Boss::Draw(g, gameTime);
		
		if(deathSplosions!=NULL)
		{
			deathSplosions->Draw(g, gameTime);
		}
	}
	
	void Weisbrod::onRelease()
	{
		//pen->slash();
	}
	
	void Weisbrod::onAnimationFinish(const String&name)
	{
		//
	}
}