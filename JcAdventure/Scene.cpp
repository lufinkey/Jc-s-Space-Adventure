
#include "Scene.h"
#include "../Game.h"

namespace JcAdventure
{
	Scene::Scene()
	{
		playing = true;
		nextSceneTime = 0;
		nextFrame = 0;
	}

	Scene::Scene(long waitTime)
	{
		playing = true;
		nextSceneTime = Game::getGameTime() + waitTime;
		nextFrame = 0;
	}

	Scene::~Scene()
	{
		//
	}

	long Scene::onFrame(unsigned int frame)
	{
		//open for implementation
		return 0;
	}

	void Scene::Update(long gameTime)
	{
		if(playing)
		{
			if(nextSceneTime<=gameTime)
			{
				long waitTime = onFrame(nextFrame);
				if(playing)
				{
					nextSceneTime = gameTime + waitTime;
					nextFrame++;
				}
			}
		}
	}

	void Scene::Draw(Graphics2D&g, long gameTime)
	{
		//open for implementation
	}

	void Scene::jump()
	{
		if(playing)
		{
			long waitTime = onFrame(nextFrame);
			if(playing)
			{
				nextSceneTime = Game::getGameTime() + waitTime;
				nextFrame++;
			}
		}
	}

	void Scene::restart()
	{
		playing = true;
		nextFrame = 0;
		long waitTime = onFrame(nextFrame);
		if(playing)
		{
			nextSceneTime = Game::getGameTime() + waitTime;
			nextFrame++;
		}
	}

	void Scene::restart(long waitTime)
	{
		playing = true;
		nextFrame = 0;
		nextSceneTime = Game::getGameTime() + waitTime;
	}

	void Scene::stop()
	{
		playing = false;
		nextFrame = 0;
		nextSceneTime = 0;
	}
}