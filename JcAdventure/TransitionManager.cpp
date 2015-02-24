
#include "TransitionManager.h"

namespace JcAdventure
{
	TransitionManager::TransitionInfo::TransitionInfo(Transitions::Transition*transition, const String&target)
	{
		this->transition = transition;
		this->target = target;
	}

	TransitionManager::TransitionInfo::~TransitionInfo()
	{
		if(transition!=NULL)
		{
			delete transition;
			transition = NULL;
		}
	}

	void TransitionManager::TransitionInfo::Update(long gameTime)
	{
		if(transition!=NULL)
		{
			transition->Update(gameTime);
		}
	}

	void TransitionManager::TransitionInfo::Draw(Graphics2D&g, long gameTime)
	{
		if(transition!=NULL)
		{
			transition->Draw(g, gameTime);
		}
	}

	bool TransitionManager::TransitionInfo::finished()
	{
		if(transition!=NULL)
		{
			return transition->finished();
		}
		return false;
	}

	String TransitionManager::TransitionInfo::getTarget()
	{
		return target;
	}

	ArrayList<TransitionManager::TransitionInfo*> TransitionManager::queue = ArrayList<TransitionManager::TransitionInfo*>();

	void TransitionManager::Update(long gameTime)
	{
		while(queue.size()>0 && queue.get(0)->finished())
		{
			String target = queue.get(0)->getTarget();
			delete queue.get(0);
			queue.remove(0);
			if(!target.equals(""))
			{
				ScreenManager::GoToScreen(target);
			}
		}

		if(queue.size()>0)
		{
			queue.get(0)->Update(gameTime);
		}
	}

	void TransitionManager::Draw(Graphics2D&g, long gameTime)
	{
		while(queue.size()>0 && queue.get(0)->finished())
		{
			String target = queue.get(0)->getTarget();
			delete queue.get(0);
			queue.remove(0);
			if(!target.equals(""))
			{
				ScreenManager::GoToScreen(target);
			}
		}

		if(queue.size()>0)
		{
			queue.get(0)->Draw(g, gameTime);
		}
	}

	void TransitionManager::addTransition(Transitions::Transition*transition, String target)
	{
		queue.add(new TransitionInfo(transition,target));
	}
}