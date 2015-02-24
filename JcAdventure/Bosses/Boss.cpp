
#include "Boss.h"

namespace JcAdventure
{
	Boss::Boss(float x1, float y1) : GameElement(x1, y1)
	{
		eye1X = -30;
		eye1Y = -20;
		eye1R = 10;

		eye2X = 30;
		eye2Y = -20;
		eye2R = 10;
		
		eyesCentered = true;

		eye1 = new Actor(x + (eye1X*Scale), y + (eye1Y*Scale));
		eye2 = new Actor(x + (eye2X*Scale), y + (eye2Y*Scale));

		eye1Prev.x = eye1X;
		eye1Prev.y = eye1Y;
		eye2Prev.x = eye2X;
		eye2Prev.y = eye2Y;
		eye1MovePoint.x = eye1X;
		eye1MovePoint.y = eye1Y;
		eye2MovePoint.x = eye2X;
		eye2MovePoint.y = eye2Y;

		prevScale = Scale;

		hasEyes = false;

		health = 1.0;
		hurtFlash = 0;
		hurtFlashRed = false;
		nextHurtFlashTime = 0;
		
		prevCoords = Vector2f(x,y);
	}

	Boss::~Boss()
	{
		delete eye1;
		delete eye2;
	}

	void Boss::Update(long gameTime)
	{
		GameElement::Update(gameTime);
		
		float coordDifX = x - prevCoords.x;
		float coordDifY = y - prevCoords.y;
		prevCoords.x = x;
		prevCoords.y = y;

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

		if(hasEyes)
		{
			if(Scale!=prevScale)
			{
				eye1->x = x + (eye1Prev.x*Scale);
				eye1->y = y + (eye1Prev.y*Scale);
				eye2->x = x + (eye2Prev.x*Scale);
				eye2->y = y + (eye2Prev.y*Scale);
			}
			
			eye1->x += coordDifX;
			eye1->y += coordDifY;
			eye2->x += coordDifX;
			eye2->y += coordDifY;
			
			eye1->Scale = Scale;
			eye2->Scale = Scale;
			//eye1->Update(gameTime);
			//eye2->Update(gameTime);
			
			if(eyesCentered)
			{
				eye1MovePoint.x = eye1X;
				eye1MovePoint.y = eye1Y;
				eye2MovePoint.x = eye2X;
				eye2MovePoint.y = eye2Y;
				
				eye1->moveTo(x + (eye1MovePoint.x*Scale), y + (eye1MovePoint.y*Scale), 10*Scale);
				eye2->moveTo(x + (eye2MovePoint.x*Scale), y + (eye2MovePoint.y*Scale), 10*Scale);
			}
			else
			{
				Vector2f eye1Center = Vector2f(x + (eye1X*Scale), y + (eye1Y*Scale));
				Vector2f eye2Center = Vector2f(x + (eye2X*Scale), y + (eye2Y*Scale));
				double focalDist1 = distance(eye1Center.x, eye1Center.y, focalX, focalY);
				double focalDist2 = distance(eye2Center.x, eye2Center.y, focalX, focalY);
				double eye1Cos = (focalX - eye1Center.x)/focalDist1;
				double eye1Sin = (focalY - eye1Center.y)/focalDist1;
				double eye2Cos = (focalX - eye2Center.x)/focalDist2;
				double eye2Sin = (focalY - eye2Center.y)/focalDist2;
				
				Vector2f eye1Offset = Vector2f((float)(eye1R*eye1Cos), (float)(eye1R*eye1Sin));
				Vector2f eye2Offset = Vector2f((float)(eye2R*eye2Cos), (float)(eye2R*eye2Sin));
				
				eye1MovePoint.x = eye1X + eye1Offset.x;
				eye1MovePoint.y = eye1Y + eye1Offset.y;
				eye2MovePoint.x = eye2X + eye2Offset.x;
				eye2MovePoint.y = eye2Y + eye2Offset.y;

				eye1->moveTo(x + (eye1MovePoint.x*Scale), y + (eye1MovePoint.y*Scale), 5*Scale);
				eye2->moveTo(x + (eye2MovePoint.x*Scale), y + (eye2MovePoint.y*Scale), 5*Scale);
			}
		}
		else
		{
			eye1->x = x + (eye1X*Scale);
			eye1->y = y + (eye1Y*Scale);
			eye2->x = x + (eye2X*Scale);
			eye2->y = y + (eye2Y*Scale);
			
			eye1MovePoint.x = eye1X;
			eye1MovePoint.y = eye1Y;
			eye2MovePoint.x = eye2X;
			eye2MovePoint.y = eye2Y;
		}
		
		if(hasEyes)
		{
			eye1->Update(gameTime);
			eye2->Update(gameTime);
		}
		
		eye1Prev.x = (eye1->x - x)/Scale;
		eye1Prev.y = (eye1->y - y)/Scale;
		eye2Prev.x = (eye2->x - x)/Scale;
		eye2Prev.y = (eye2->y - y)/Scale;
		
		prevScale = Scale;
	}

	void Boss::Draw(Graphics2D&g, long gameTime)
	{
		eye1->x = x + (eye1Prev.x*Scale);
		eye1->y = y + (eye1Prev.y*Scale);
		eye2->x = x + (eye2Prev.x*Scale);
		eye2->y = y + (eye2Prev.y*Scale);
		
		if(hasEyes)
		{
			eye1->Draw(g, gameTime);
			eye2->Draw(g, gameTime);
		}

		GameElement::Draw(g, gameTime);
	}
	
	void Boss::setEyes(const String&eye1Image, const String&eye2Image)
	{
		if(hasEyes)
		{
			Animation*anim = eye1->getAnimation();
			anim->setFrame(0,eye1Image);
			anim = eye2->getAnimation();
			anim->setFrame(0,eye2Image);
		}
		else
		{
			bool success1 = AssetManager::loadImage(eye1Image);
			bool success2 = AssetManager::loadImage(eye2Image);
			if(success1 && success2)
			{
				hasEyes = true;
				Animation*anim = new Animation("normal",1,eye1Image);
				eye1->addAnimation(anim);
				eye1->changeAnimation("normal",FORWARD);
				anim = new Animation("normal",1,eye2Image);
				eye2->addAnimation(anim);
				eye2->changeAnimation("normal",FORWARD);
			}
		}
	}

	void Boss::setEyeProperties(float eye1X,float eye1Y,float eye1R, float eye2X,float eye2Y,float eye2R)
	{
		Vector2f eye1Prog = Vector2f(eye1MovePoint.x - this->eye1X, eye1MovePoint.y - this->eye1Y);
		Vector2f eye2Prog = Vector2f(eye2MovePoint.x - this->eye2X, eye2MovePoint.y - this->eye2Y);

		float eye1MesX = eye1Prog.x/(this->eye1R);
		float eye1MesY = eye1Prog.y/(this->eye1R);
		float eye2MesX = eye2Prog.x/(this->eye2R);
		float eye2MesY = eye2Prog.y/(this->eye2R);

		this->eye1X = eye1X;
		this->eye1Y = eye1Y;
		this->eye1R = eye1R;
		this->eye2X = eye2X;
		this->eye2Y = eye2Y;
		this->eye2R = eye2R;

		eye1->x = x + (eye1X*Scale) + (eye1Prog.x*eye1MesX);
		eye1->y = y + (eye1Y*Scale) + (eye1Prog.y*eye1MesY);
		eye2->x = x + (eye2X*Scale) + (eye2Prog.x*eye2MesX);
		eye2->y = y + (eye2Y*Scale) + (eye2Prog.y*eye2MesY);

		eye1Prev.x = (eye1->x - x)/Scale;
		eye1Prev.y = (eye1->y - y)/Scale;
		eye2Prev.x = (eye2->x - x)/Scale;
		eye2Prev.y = (eye2->y - y)/Scale;

		prevScale = Scale;
		
		prevCoords.x = x;
		prevCoords.y = y;
	}

	void Boss::setFocalPoint(float x1, float y1)
	{
		focalX = x1;
		focalY = y1;
		eyesCentered = false;
	}

	void Boss::centerEyes()
	{
		eyesCentered = true;
	}
	
	void Boss::hurt(double damage)
	{
		hurtFlash = 4;
		hurtFlashRed = false;
		nextHurtFlashTime = 0;
		health -= damage;
	}

	double Boss::getHealth()
	{
		return health;
	}
}