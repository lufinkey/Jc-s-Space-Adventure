
#include "WireframeActor.h"
#include "Actor.h"
#include "../Application.h"
#include "../View.h"
#include "../Output/Console.h"
#ifdef __APPLE__
#include "TargetConditionals.h"
#endif

namespace GameEngine
{
	bool WireframeActor::checkHover(float x1, float y1)
	{
		float mousex = 0;
		float mousey = 0;
		if(relative)
		{
			mousex = ((float)x1 + View::x);
    		mousey = ((float)y1 + View::y);
		}
		else
		{
    		mousex = x1;
    		mousey = y1;
		}
		if(mousex>x && mousex<(x+width) && mousey>y && mousey<y+height)
	    {
	    	return true;
	    }
	    return false;
	}
	
	void WireframeActor::drawActor(Graphics2D& g,long gameTime,float x1, float y1,double scale)
	{
		if(relative)
		{
			if(visible)
			{
				g.setColor(color);
				if(filled)
				{
					g.fillRect((x1 - View::x),(y1 - View::y),(float)(width*scale),(float)(height*scale));
				}
				else
				{
					g.drawRect((x1 - View::x),(y1 - View::y),(float)(width*scale),(float)(height*scale));
				}
			}
		}
		else
		{
			if(visible)
			{
				g.setColor(color);
				if(filled)
				{
					g.fillRect((x1),(y1),(float)(width*scale),(float)(height*scale));
				}
				else
				{
					g.drawRect((x1),(y1),(float)(width*scale),(float)(height*scale));
				}
			}
	    }
	}
		
	WireframeActor::WireframeActor(float x1, float y1, int w, int h) //Constructor to pass in x,y,width,height
	{
		x=x1;
		y=y1;
		width=w;
		height=h;
		xprev=0;
		yprev=0;
		xvelocity=0;
		yvelocity=0;
		xSpeed=0;
		ySpeed=0;
		color=Color::BLACK;
		mouseover = false;
		prevMouseover = false;
		visible=false;
		filled=false;
		clicked=false;
		prevclicked=false;
		relative = true;
		touchId = 0;
		currentTouchId = 0;
			
		actorType=2;
			
		for(int i=0; i<totalEvents; i++)
	    {
	        enabledEvents[i]=true;
	    }
	}
	
	WireframeActor::~WireframeActor()
	{
		//
	}
		
	void WireframeActor::setVisible(bool toggle) //toggles visibility of wireframe
	{
		visible = toggle;
	}
		
	void WireframeActor::setFilled(bool toggle) //toggles whether wireframe is filled
	{
		filled = toggle;
	}
		
	void WireframeActor::setColor(const Color&c) //changes color of wireframe
	{
	    color = c;
	}
		
	Color WireframeActor::getColor() //returns color of wireframe
	{
	    return color;
	}

	Rect WireframeActor::getCollideOverlapArea(Actor*a2)
	{
		Rectangle r1;
		r1.x = (int)(a2->x - ((float)a2->width/2));
		r1.y = (int)(a2->y - ((float)a2->height/2));
		r1.width = a2->width;
		r1.height = a2->height;
		Rectangle r2;
		r2.x = (int)x;
		r2.y = (int)y;
		r2.width = width;
		r2.height = height;
		
		Rect overlap;
		
		if(rectsColliding(a2))
		{
			if(r1.x <= r2.x)
			{
				if((r1.x + r1.width) <= (r2.x + r2.width))
				{
					overlap.left = r2.x - r1.x;
					overlap.right = r1.width;
				}
				else
				{
					overlap.left = r2.x - r1.x;
					overlap.right = overlap.left + r2.width;
				}
			}
			else
			{
				if((r1.x + r1.width) <= (r2.x + r2.width))
				{
					overlap.left = 0;
					overlap.right = r1.width;
				}
				else
				{
					overlap.left = 0;
					overlap.right = (r2.x + r2.width) - r1.x;
				}
			}
			
			if(r1.y <= r2.y)
			{
				if((r1.y + r1.height) <= (r2.y + r2.height))
				{
					overlap.top = r2.y - r1.y;
					overlap.bottom = r1.height;
				}
				else
				{
					overlap.top = r2.y - r1.y;
					overlap.bottom = overlap.top + r2.height;
				}
			}
			else
			{
				if((r1.y + r1.height)<= (r2.y + r2.height))
				{
					overlap.top = 0;
					overlap.bottom = r1.height;
				}
				else
				{
					overlap.top = 0;
					overlap.bottom = (r2.y + r2.height) - r1.y;
				}
			}
		}
		else
		{
			overlap.left = -1;
			overlap.top = -1;
			overlap.right = -1;
			overlap.bottom = -1;
		}
		return overlap;
	}

    bool WireframeActor::isColliding(Actor*collide)
	{
		Rect collideOverlap = getCollideOverlapArea(collide);
		
		if(collideOverlap.left != -1)
		{
			
			int w = collideOverlap.right - collideOverlap.left;
			int h = collideOverlap.bottom - collideOverlap.top;
			
			float x1 = ((float)collideOverlap.left/collide->Scale);
			float y1 = ((float)collideOverlap.top/collide->Scale);
			
			float incr1 = (float)(1/collide->Scale);
			
			float pntX1 = x1;
			float pntY1 = y1;
			
			for(int cntY = 0; cntY<h; cntY++)
			{
				pntX1 = x1;
				for(int cntX = 0; cntX<w; cntX++)
				{
					if(collide->pixelAtPoint((int)(pntX1),(int)(pntY1)))
					{
						return true;
					}
					pntX1+=incr1;
				}
				pntY1+=incr1;
			}
			return false;
		}
		return false;
	}
	    
	bool WireframeActor::rectsColliding(WireframeActor*collide) //checks if bounding boxes are colliding
	{
	    int left1, left2;
	    int right1, right2;
	    int top1, top2;
	    int bottom1, bottom2;
	
	    left1 = (int)x;
	    left2 = (int)collide->x;
	    right1 = (int)x+width;
	    right2 = (int)collide->x + collide->width;
	    top1 = (int)y;
	    top2 = (int)collide->y;
	    bottom1 = (int)y+height;
	    bottom2 = (int)collide->y + collide->height;
	
	    if (bottom1 < top2)
	    {
	        return false;
	    }
	    if (top1 > bottom2)
	    {
	        return false;
	    }
	
	    if (right1 < left2)
	    {
	        return false;
	    }
	    if (left1 > right2)
	    {
	        return false;
	    }
	
	    return true;
	}
	    
	bool WireframeActor::rectsColliding(Actor*collide) //checks if bounding boxes are colliding
	{
	    int left1, left2;
	    int right1, right2;
	    int top1, top2;
	    int bottom1, bottom2;
	
	    left1 = (int)x;
	    left2 = (int)collide->x-(collide->width/2);
	    right1 = (int)x+width;
	    right2 = (int)collide->x+(collide->width/2);
	    top1 = (int)y;
	    top2 = (int)collide->y-(collide->height/2);
	    bottom1 = (int)y+height;
	    bottom2 = (int)collide->y+(collide->height/2);
	
	    if (bottom1 < top2)
	    {
	        return false;
	    }
	    if (top1 > bottom2)
	    {
	        return false;
	    }
	
	    if (right1 < left2)
	    {
	        return false;
	    }
	    if (left1 > right2)
	    {
	        return false;
	    }
	
	    return true;
	}
		
	bool WireframeActor::circlesColliding(WireframeActor*collide) //checks if "bounding circles" are colliding
	{
		double r1 = distanceUnSqr(x,y,x+(width/2),y+(height/2));
		double r2 = distanceUnSqr(collide->x,collide->y,collide->x+(collide->width/2),collide->y+(collide->height/2));
		double dist = r1+r2;
		double realDist = distanceUnSqr(x+(width/2),y+(height/2),collide->x+(collide->width/2),collide->y+(collide->height/2));
		if(realDist<dist)
		{
			return true;
		}
		return false;
	}
		
	bool WireframeActor::circlesColliding(Actor*collide) //checks if "bounding circles" are colliding
	{
		double r1 = distanceUnSqr(x,y,x+(width/2),y+(height/2));
		double r2 = distanceUnSqr(collide->x,collide->y,collide->x-(collide->width/2),collide->y-(collide->height/2));
		double dist = r1+r2;
		double realDist = distanceUnSqr(x+(width/2),y+(height/2),collide->x,collide->y);
		if(realDist<dist)
		{
			return true;
		}
		return false;
	}
		
	bool WireframeActor::circlesColliding(WireframeActor*collide, double mult) //checks if "bounding circles" are colliding. can specify circle scale. 1.0 by default
	{
		double r1 = distanceUnSqr(x,y,x+(width/2),y+(height/2));
		double r2 = distanceUnSqr(collide->x,collide->y,collide->x+(collide->width/2),collide->y+(collide->height/2));
		double dist = (r1+r2)*mult;
		double realDist = mult*distanceUnSqr(x+(width/2),y+(height/2),collide->x+(collide->width/2),collide->y+(collide->height/2));
		if(realDist<dist)
		{
			return true;
		}
		return false;
	}
		
	bool WireframeActor::circlesColliding(Actor*collide, double mult) //checks if "bounding circles" are colliding. can specify circle scale. 1.0 by default
	{
		double r1 = distanceUnSqr(x,y,x+(width/2),y+(height/2));
		double r2 = distanceUnSqr(collide->x,collide->y,collide->x-(collide->width/2),collide->y-(collide->height/2));
		double dist = (r1+r2)*mult;
		double realDist = mult*distanceUnSqr(x+(width/2),y+(height/2),collide->x,collide->y);
		if(realDist<dist)
		{
			return true;
		}
		return false;
	}
		
	void WireframeActor::Update(long gameTime) //WireframeActor's default update. velocity variables change velocity of WireframeActor
	{
		prevclicked = clicked;

	    x += (float)xvelocity;
	    y += (float)yvelocity;
	
	    xSpeed = x - xprev;
	    ySpeed = y - yprev;
	
	    xprev = x;
	    yprev = y;
		
#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
		long prevTouchId = currentTouchId;
		
		bool onmouseenter = false;
		bool onmouseleave = false;
		bool onclick = false;
		bool onrelease = false;
		
	    if(mouseOver())
	    {
			bool prevMouseOver = mouseover;
	    	if(!mouseover)
	    	{
	    		mouseover=true;
	    		if(eventEnabled(EVENT_MOUSEENTER))
	    		{
	    			onmouseenter = true;
	    		}
	    	}
	    	if(!prevMouseOver && !Application::checkPrevTouchActive(touchId))
	    	{
	    		clicked = true;
	    		if(eventEnabled(EVENT_MOUSECLICK))
	    		{
	    			onclick = true;
	    		}
	    	}
	    }
	    else if(mouseover)
		{
			mouseover=false;
			if(eventEnabled(EVENT_MOUSELEAVE))
			{
	    		onmouseleave = true;
			}
		}
	    if(clicked && prevMouseover && !Application::checkTouchActive(prevTouchId))
	    {
	    	clicked = false;
	    	if(eventEnabled(EVENT_MOUSERELEASE))
			{
	    		onrelease = true;
			}
	    }
		
		if(prevclicked && !Application::checkTouchActive(currentTouchId))
		{
			clicked = false;
		}
		
		prevMouseover = mouseover;
		currentTouchId = touchId;
		
		if(onmouseenter)
		{
			onMouseEnter();
		}
		if(onclick)
		{
			onClick();
		}
		if(onmouseleave)
		{
			onMouseLeave();
		}
		if(onrelease)
		{
			onRelease();
		}
#else
		if(mouseOver())
	    {
	    	if(!mouseover)
	    	{
	    		mouseover=true;
	    		if(eventEnabled(EVENT_MOUSEENTER))
	    		{
	    			onMouseEnter();
	    		}
	    	}
	    	if(Application::MouseState(Mouse::LEFTCLICK) && !Application::PrevMouseState(Mouse::LEFTCLICK))
	    	{
	    		clicked = true;
	    		if(eventEnabled(EVENT_MOUSECLICK))
	    		{
	    			onClick();
	    		}
	    	}
	    }
	    else if(mouseover)
		{
			mouseover=false;
			if(eventEnabled(EVENT_MOUSELEAVE))
			{
	    		onMouseLeave();
			}
		}
	    if(clicked && !Application::MouseState(Mouse::LEFTCLICK))
	    {
	    	clicked = false;
	    	if(eventEnabled(EVENT_MOUSERELEASE))
			{
	    		onRelease();
			}
	    }
#endif
	}
		
	void WireframeActor::Draw(Graphics2D& g,long gameTime) //Draws WireframeActor if setVisible is true
	{
	    drawActor(g,gameTime,x,y,1);
	}
	    
	bool WireframeActor::eventEnabled(unsigned char eventCode)
	{
		if(eventCode>totalEvents)
		{
			Console::WriteLine((String)"Error: EventEnabled(unsigned char). Invalid argument " + eventCode + (String)". Event does not exist");
			return false;
		}
		else
		{
			return enabledEvents[eventCode];
		}
	}
	    
	void WireframeActor::eventEnable(unsigned char eventCode)
	{
	    if(eventCode>totalEvents)
	    {
	    	Console::WriteLine((String)"Error: EventEnable(unsigned char). Invalid argument " + eventCode + (String)". Event does not exist");
	    }
	    else
	    {
	    	enabledEvents[eventCode]=true;
	    }
	}
	    
	void WireframeActor::eventDisable(unsigned char eventCode)
	{
	    if(eventCode>totalEvents)
	    {
	    	Console::WriteLine((String)"Error: EventDisable(unsigned char). Invalid argument " + eventCode + (String)". Event does not exist");
	    }
	    else
	    {
	    	enabledEvents[eventCode]=false;
	    }
	}
	    
	void WireframeActor::onMouseEnter() //When mouse enters Actor
	{
	    //Open for implementation
	}
	    
	void WireframeActor::onMouseLeave() //When mouse enters Actor
	{
	    //Open for implementation
	}
	    
	void WireframeActor::onClick() //when Actor is clicked
	{
	    //Open for implementation
	}
	    
	void WireframeActor::onRelease() //When Actor's click is released
	{
	    //Open for implementation
	}
	    
	bool WireframeActor::mouseOver()
	{
#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
	    if(mouseover)
		{
			if(Application::checkTouchActive(currentTouchId))
			{
				if(checkHover((float)Application::TouchX(currentTouchId), (float)Application::TouchY(currentTouchId)))
				{
					return true;
				}
			}
		}
		ArrayList<TouchPoint> points = Application::getTouchPoints();
		for(int i=0; i<points.size(); i++)
		{
			TouchPoint&point = points.get(i);
			if(checkHover(point.x, point.y))
			{
				touchId = point.ID;
				return true;
			}
		}
		return false;
#else
		if(Application::MouseX()>x && Application::MouseX()<x+width && Application::MouseY()>y && Application::MouseY()<y+height)
	    {
	    	return true;
	    }
	    return false;
#endif
	}
	    
	bool WireframeActor::isClicked()
	{
	    return clicked;
	}

	bool WireframeActor::wasClicked()
	{
		return prevclicked;
	}
	
	void WireframeActor::relativeToView(bool toggle)
	{
		relative = toggle;
	}
	
	long WireframeActor::getTouchId()
	{
		return currentTouchId;
	}
	    
	bool WireframeActor::isOnScreen()
	{
		int left1, left2;
	    int right1, right2;
	    int top1, top2;
	    int bottom1, bottom2;
	
	    left1 = (int)x;
	    left2 = (int)View::x;
	    right1 = (int)x+width;
	    right2 = (int)View::x+(View::ScaleWidth());
	    top1 = (int)y;
	    top2 = (int)View::y;
	    bottom1 = (int)y+height;
	    bottom2 = (int)View::y+(View::ScaleHeight());
	
	    if (bottom1 < top2)
	    {
	        return false;
	    }
	    if (top1 > bottom2)
	    {
	        return false;
	    }
	
	    if (right1 < left2)
	    {
	        return false;
	    }
	    if (left1 > right2)
	    {
	        return false;
	    }
	
	    return true;
	}

	float WireframeActor::getXSpeed()
	{
		return xSpeed;
	}

	float WireframeActor::getYSpeed()
	{
		return ySpeed;
	}
}