
#include "../../GameEngine/GameEngine.h"

#pragma once

namespace JcAdventure
{
	class RandomText
	{
	private:
		ArrayList<String> strings;

	public:
		RandomText();
		RandomText(const ArrayList<String>&strings);
		virtual ~RandomText();

		void add(const String&string);
		String get();
	};
}