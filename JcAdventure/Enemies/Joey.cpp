
#include "Joey.h"

namespace JcAdventure
{
	Joey::Joey(float x1, float y1) : GameElement(x1, y1)
	{
		//
	}

	Joey::~Joey()
	{
		//
	}

	void Joey::Update(long gameTime)
	{
		GameElement::Update(gameTime);
	}
	
	void Joey::Draw(Graphics2D&g, long gameTime)
	{
		GameElement::Draw(g, gameTime);
	}
}