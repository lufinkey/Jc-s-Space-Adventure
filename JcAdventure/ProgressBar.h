
#include "../GameEngine/GameEngine.h"

#pragma once

namespace JcAdventure
{
	class ProgressBar
	{
	private:
		Actor*bar;
		float progress;

	public:
		float x, y;
		float Scale;

		ProgressBar();
		ProgressBar(float x1, float y1);
		virtual ~ProgressBar();

		void setProgress(float progress);
		float getProgress();

		void relativeToView(bool toggle);

		void setAlpha(float alpha);
		float getAlpha();

		void setRotation(float degrees);
		float getRotation();
	};
}