
#include "../GameElement.h"

#pragma once

namespace JcAdventure
{
	class Boss : public GameElement
	{
	private:
		Actor*eye1;
		Actor*eye2;
		float focalX, focalY;
		float eye1X,eye1Y,eye1R;
		float eye2X,eye2Y,eye2R;
		
		Vector2f prevCoords;

		Vector2f eye1MovePoint;
		Vector2f eye2MovePoint;

		Vector2f eye1Prev;
		Vector2f eye2Prev;

		float prevScale;

		bool eyesCentered;
		bool hasEyes;

		byte hurtFlash;
		bool hurtFlashRed;
		long nextHurtFlashTime;

		double health;

	protected:
		void setEyes(const String&eye1Image, const String&eye2Image);
		void setEyeProperties(float eye1X,float eye1Y,float eye1R, float eye2X,float eye2Y,float eye2R);

	public:
		Boss(float x1, float y1);
		virtual ~Boss();

		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);

		void setFocalPoint(float x1, float y1);
		void centerEyes();

		void hurt(double damage);

		double getHealth();
	};
}