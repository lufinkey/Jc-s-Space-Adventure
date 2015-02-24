
#include "GlobalDefs.h"

#include "Actor/Actor.h"
#include "Actor/Animation.h"
#include "Actor/PrimitiveActor.h"
#include "Actor/TextActor.h"
#include "Actor/WireframeActor.h"

#include "Graphics/Graphics2D.h"

#include "Input/Keys.h"
#include "Input/TouchPoint.h"

#include "Output/Console.h"

//#include "P2P/P2PManager.h"

#include "ScreenManager/MenuScreen.h"
#include "ScreenManager/Screen.h"
#include "ScreenManager/ScreenManager.h"

#include "Sound/Music.h"
#include "Sound/Sound.h"

#include "Util/ArrayList.h"
#include "Util/Bitset.h"
#include "Util/BufferedImage.h"
#include "Util/Color.h"
#include "Util/Font.h"
#include "Util/Image.h"
#include "Util/PixelIterator.h"
#include "Util/PrefManager.h"
#include "Util/String.h"
#include "Util/Thread.h"
#include "Util/Vector2.h"

#include "Application.h"
#include "ApplicationEventListener.h"
#include "AssetManager.h"
#include "BatchLoader.h"
#include "View.h"
#include "ObjCBridge.h"

#pragma once

namespace GameEngine
{
	static double random()
	{
		return (double)rand()/RAND_MAX;
	}
}

using namespace GameEngine;

typedef unsigned char byte;
typedef bool boolean;