
#include "../forwards.h"
#include "../GlobalDefs.h"
#include "../Util/String.h"
#include "../Util/ArrayList.h"
#include "../Graphics/Graphics2D.h"

#pragma once

namespace GameEngine
{
	const unsigned char NO_CHANGE = 0;
	const unsigned char FORWARD = 1;
	const unsigned char BACKWARD = 2;
	const unsigned char STOPPED = 3;

	class Animation
	{
		friend class Actor;
	private:
		int frames;
		ArrayList<String> names;

		int currentFrame;
		int recentFrame;

		bool isMirrored;
		bool isMirroredVertical;
		int rows;
		int cols;

		int*sequence;

		Vector2i imageSize;

		int animType;

		int width;
		int height;

		unsigned char direction;
	public:
		static const int TYPE_MULTIFILE = 0;
		static const int TYPE_SINGLEFILE = 1;
		static const int TYPE_SPECFRAME_SINGLEFILE = 2;

		int fps;
		String name;

		Animation(const Animation& anim);
		Animation(String n,int speed);
		Animation(String n,int speed,String frame);
		Animation(String n,int speed,int xFrames,int yFrames);
		Animation(String n,int speed,int xFrames,int yFrames,ArrayList<int> seq);
		virtual ~Animation();

		void mirror(bool toggle);
		void mirrorVertical(bool toggle);
		bool mirrored();
		bool mirroredVertical();

		int getWidth();
		int getHeight();
		Vector2i getSize();
    
		void addFrame(String fName);
		void setFrame(int frameNo, const String&fImage);
		
		BufferedImage*getCurrentImage();
		int getCols();
		int getRows();
		int getType();

		
		void drawFrame(Actor*a,Graphics2D& g, float x1, float y1, double scale);
		void drawFrame(Actor*a, Graphics2D& g, int fNum, float x1, float y1, double scale);
		void drawFrame(Actor*a,Graphics2D& g,int fNum, float x1, float y1, double scale, bool relativeToScreen);
		void drawFrame(Actor*a,Graphics2D& g,int fNum, float x1, float y1, float x2, float y2);
		void nextFrame(Actor*a,Graphics2D& g, float x1, float y1, double scale, bool relativeToScreen=true);

		void setCurrentFrame(int fNum);
		int getLastFrame();
		int getCurrentFrame();
		unsigned char getDirection();
    
		ArrayList<String> getAllFilenames();

		Animation& operator=(const Animation& anim);
	};
}