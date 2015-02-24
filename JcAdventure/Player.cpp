
#include "Player.h"
#include "../Game.h"
#include "Bosses/Boss.h"

namespace JcAdventure
{
	Player::Beam::Beam(float x1, float y1, float dir) : Projectile(x1, y1, false)
	{
		Scale = 0.3f;
		addAnimation(new Animation("normal", 1, "Images/Jc/projectile.png"));
		changeAnimation("normal", FORWARD);
		cosDir = ((float)cos(degtorad((double)dir)));
		sinDir = -((float)sin(degtorad((double)dir)));
	}

	Player::Beam::~Beam()
	{
		//
	}

	void Player::Beam::Update(long gameTime)
	{
		x += cosDir*20;
		y += sinDir*20;
		Projectile::Update(gameTime);
	}

	void Player::Beam::onBossCollide(Boss*boss)
	{
		boss->hurt(0.05);
		destroy();
	}

	void Player::Beam::onProjectileCollide(Projectile*projectile)
	{
		destroy();
	}

	Player::Player(float x1, float y1) : GameElement(x1,y1)
	{
		Animation*anim = new Animation("normal",5);
		anim->addFrame("Images/Jc/Beetle/beetle1.png");
		anim->addFrame("Images/Jc/Beetle/beetle2.png");
		anim->addFrame("Images/Jc/Beetle/beetle3.png");
		anim->addFrame("Images/Jc/Beetle/beetle2.png");
		addAnimation(anim);
		changeAnimation("normal", FORWARD);
		Scale = 0.3f;
		controlsOn = false;
		setWordBubbleOffset(0,-60);
		//setWordBubbleScale(0.8f);

		health = 1.0;
		hurtFlash = 0;
		hurtFlashRed = false;
		nextHurtFlashTime = 0;

		hurtText.add("ouch!");
		hurtText.add("hey, watch it!");
		hurtText.add("I'm sick of your shit...");
		hurtText.add("Do you think this is a game?");
		hurtText.add("It's clobberin\' time!");
	}

	Player::~Player()
	{
		//
	}

	void Player::Update(long gameTime)
	{
		GameElement::Update(gameTime);

		if(hurtFlash>0)
		{
			if(nextHurtFlashTime<=gameTime)
			{
				if(hurtFlashRed)
				{
					setColor(Color::WHITE);
					hurtFlashRed = false;
					hurtFlash--;
				}
				else
				{
					setColor(Color::RED);
					hurtFlashRed = true;
				}
				nextHurtFlashTime = gameTime + 50;
			}
		}

		if(controlsOn)
		{
			if(Game::KeyPressed(Keys::UPARROW))
			{
				y -= 4;
			}
			if(Game::KeyPressed(Keys::DOWNARROW))
			{
				y += 4;
			}
			if(Game::KeyPressed(Keys::LEFTARROW))
			{
				x -= 4;
			}
			if(Game::KeyPressed(Keys::RIGHTARROW))
			{
				x += 4;
			}
			
			if(Game::screenTapped())
			{
				//TODO fix so that you don't shoot if you tap in a certain area
				#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
					double prevX = (double)Game::PrevTouchX(Game::getLastTapID());
					if(prevX > 450)
					{
						shoot((float)direction((double)x, (double)y, prevX, (double)Game::PrevTouchY(Game::getLastTapID())));
					}
				#else
					double mousex = (double)Game::MouseX();
					if(mousex > 450)
					{
						shoot((float)direction((double)x, (double)y, (double)mousex, (double)Game::MouseY()));
					}
				#endif
			}
			
			ArrayList<TouchPoint> touches = Game::getTouchPoints();
			
			if(touches.size()>0)
			{
				for(int i=0; i<touches.size(); i++)
				{
					TouchPoint point = touches.get(i);
					if(point.x <= 450)
					{
						i = touches.size();
						
						byte dir = getDir(150, 450, point.x, point.y);
						switch(dir)
						{
							case DIR_UP:
							{
								y -= 4;
							}
							break;
							
							case DIR_UPRIGHT:
							{
								y -= 4;
								x += 4;
							}
							break;
							
							case DIR_UPLEFT:
							{
								y -= 4;
								x -= 4;
							}
							break;
							
							case DIR_RIGHT:
							{
								x += 4;
							}
							break;
							
							case DIR_LEFT:
							{
								x -= 4;
							}
							break;
							
							case DIR_DOWNRIGHT:
							{
								y += 4;
								x += 4;
							}
							break;
							
							case DIR_DOWNLEFT:
							{
								y += 4;
								x -= 4;
							}
							break;
							
							case DIR_DOWN:
							{
								y += 4;
							}
							break;
						}
					}
				}
			}
		}
	}

	void Player::Draw(Graphics2D&g, long gameTime)
	{
		GameElement::Draw(g, gameTime);
	}

	void Player::shoot(float dir)
	{
		ProjectileManager::addProjectile(new Beam(x+(50*Scale), y+(30*Scale), dir));
	}

	void Player::hurt(double damage)
	{
		hurtFlash = 4;
		hurtFlashRed = false;
		nextHurtFlashTime = 0;
		health -= damage;
		say(hurtText.get());
	}

	void Player::enableControls(bool toggle)
	{
		controlsOn = toggle;
	}
}