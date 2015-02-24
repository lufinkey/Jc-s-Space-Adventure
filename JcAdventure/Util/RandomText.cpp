
#include "RandomText.h"

namespace JcAdventure
{
	RandomText::RandomText()
	{
		//nothing here
	}

	RandomText::RandomText(const ArrayList<String>&strings)
	{
		this->strings = strings;
	}

	RandomText::~RandomText()
	{
		strings.clear();
	}

	void RandomText::add(const String&string)
	{
		strings.add(string);
	}

	String RandomText::get()
	{
		double randomNum = GameEngine::random();
		int index = (int)(randomNum*strings.size());
		return strings.get(index);
	}
}