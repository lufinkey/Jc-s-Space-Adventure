
#include "Projectile.h"
#include "Player.h"
#include "Bosses/Boss.h"
#include "Global.h"

namespace JcAdventure
{
	Projectile::Projectile(float x1, float y1, bool enemy) : GameElement(x1,y1)
	{
		this->enemy = enemy;
		dead = false;
	}

	Projectile::~Projectile()
	{
		//
	}
	
	void Projectile::Update(long gameTime)
	{
		GameElement::Update(gameTime);
		if(!isOnScreen())
		{
			destroy();
		}
	}

	void Projectile::onDestroy()
	{
		//Open for implementation;
	}

	void Projectile::onPlayerCollide(Player*playr)
	{
		//Open for implementation
	}

	void Projectile::onBossCollide(Boss*boss)
	{
		//Open for implementation
	}

	void Projectile::onProjectileCollide(Projectile*projectile)
	{
		//Open for implementation
	}

	bool Projectile::isEnemy()
	{
		return enemy;
	}

	void Projectile::destroy()
	{
		dead = true;
	}

	ArrayList<Projectile*> ProjectileManager::projectiles = ArrayList<Projectile*>();
	
	void ProjectileManager::addProjectile(Projectile*projectile)
	{
		projectiles.add(projectile);
	}

	void ProjectileManager::Update(long gameTime)
	{
		for(int i=0; i<projectiles.size(); i++)
		{
			Projectile*projectile = projectiles.get(i);
			projectile->Update(gameTime);
			if(!projectile->dead)
			{
				if(projectile->enemy)
				{
					if(projectile->isColliding(Global::playr))
					{
						projectile->onPlayerCollide(Global::playr);
					}
				}
				else
				{
					if(Global::boss!=NULL && projectile->isColliding(Global::boss))
					{
						projectile->onBossCollide(Global::boss);
					}
				}
			}
		}

		for(int i=(projectiles.size()-1); i>=0; i--)
		{
			Projectile*projectile = projectiles.get(i);
			if(projectile->dead)
			{
				projectile->onDestroy();
				delete projectile;
				projectiles.remove(i);
			}
		}

		for(int i=0; i<projectiles.size(); i++)
		{
			for(int j=(i+1); j<projectiles.size(); j++)
			{
				Projectile*proj1 = projectiles.get(i);
				Projectile*proj2 = projectiles.get(j);
				if(proj1->isColliding(proj2))
				{
					proj1->onProjectileCollide(proj2);
					proj2->onProjectileCollide(proj1);
				}
			}
		}
	}

	void ProjectileManager::Draw(Graphics2D&g, long gameTime)
	{
		for(int i=0; i<projectiles.size(); i++)
		{
			projectiles.get(i)->Draw(g, gameTime);
		}

		for(int i=(projectiles.size()-1); i>=0; i--)
		{
			Projectile*projectile = projectiles.get(i);
			if(projectile->dead)
			{
				projectile->onDestroy();
				delete projectile;
				projectiles.remove(i);
			}
		}
	}
}