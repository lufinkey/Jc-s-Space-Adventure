
#include "../GameElement.h"

#pragma once

namespace JcAdventure
{
	class Joey : public GameElement
	{
	private:


	public:
		Joey(float x1, float y1);
		virtual ~Joey();

		virtual void Update(long gameTime);
		virtual void Draw(Graphics2D&g, long gameTime);
	};
}