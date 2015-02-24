
#include "GameElement.h"

#pragma once

namespace JcAdventure
{
	class Player;
	class Boss;

	class Projectile : public GameElement
	{
		friend class ProjectileManager;
	private:
		bool dead;
		bool enemy;
	public:
		Projectile(float x1, float y1, bool enemy=true);
		virtual ~Projectile();
		
		virtual void Update(long gameTime);

		virtual void onPlayerCollide(Player*playr);
		virtual void onBossCollide(Boss*boss);
		virtual void onProjectileCollide(Projectile*projectile);
		virtual void onDestroy();

		bool isEnemy();

		void destroy();
	};

	class ProjectileManager
	{
	public:
		static ArrayList<Projectile*> projectiles;

		static void addProjectile(Projectile*projectile);

		static void Update(long gameTime);
		static void Draw(Graphics2D&g, long gameTime);
	};
}