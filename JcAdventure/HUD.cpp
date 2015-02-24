
#include "HUD.h"
#include "Global.h"

namespace JcAdventure
{
	HUD::HUD()
	{
		score = new TextActor(10,10,"Score: 0000", AssetManager::getFont("Fonts/phatone.ttf",Font::PLAIN,14), Color::WHITE);
		score->setAlignment(TextActor::ALIGN_TOPLEFT);
		health = new TextActor(890,10,"Health: 100%", AssetManager::getFont("Fonts/phatone.ttf",Font::PLAIN,14), Color::WHITE);
		health->setAlignment(TextActor::ALIGN_TOPRIGHT);
	}

	HUD::~HUD()
	{
		//
	}

	void HUD::Update(long gameTime)
	{
		health->setText((String)"Health: " + ((int)(Global::playr->health*100)) + "%");
		score->setText((String)"Score: " + Global::score);

		health->Update(gameTime);
		score->Update(gameTime);
	}

	void HUD::Draw(Graphics2D&g, long gameTime)
	{
		health->Draw(g, gameTime);
		score->Draw(g, gameTime);
	}
}