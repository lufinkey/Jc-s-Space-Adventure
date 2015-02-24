
#include "ObjCBridge.h"

#ifdef __APPLE__
#include "TargetConditionals.h"
#import <UIKit/UIKit.h>
#import "ObjC/MailViewController.h"
#import "MessageBoxDelegate.h"
#endif

#include "SDL.h"
#include "SDL_syswm.h"
#include "CPPBridge.h"
#include <math.h>

//static NSDate*startDate = nil;

void GameEngine_init()
{
	/*if(startDate==nil)
	{
		startDate = [[NSDate alloc] initWithTimeInterval:0 sinceDate:[NSDate date]];
	}*/
}

#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
UIViewController*getSDLViewController(SDL_Window*window)
{
	SDL_SysWMinfo systemWindowInfo;
    SDL_VERSION(&systemWindowInfo.version);
    if ( ! SDL_GetWindowWMInfo(window, &systemWindowInfo))
	{
        // consider doing some kind of error handling here 
        return nil;
    }
    UIWindow * appWindow = systemWindowInfo.info.uikit.window;
    UIViewController * rootViewController = appWindow.rootViewController;
    return rootViewController;
}
#endif

void openURL(const char*url)
{
#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:[NSString stringWithUTF8String:url]]];
#endif
}

void writeEmail(SDL_Window*window, const char*recipient, const char*subject, const char*body)
{
#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
	MailViewController *mailer = [[MailViewController alloc] init];
	//SDL_HideWindow(window);
	UIViewController*viewCtrl = getSDLViewController(window);
	if(viewCtrl==nil)
	{
		//NSLogfile://localhost/Users/luis/Documents/Xcode/GameEngine/GameEngine/Image.cpp(@"Error getting SDL ViewController");
		return;
	}
	[mailer openMail:nil viewCtrl:viewCtrl person:[NSString stringWithUTF8String:recipient] subject:[NSString stringWithUTF8String:subject] body:[NSString stringWithUTF8String:body]];
	while([mailer isOpened])
	{
		updateAppEvents();
		SDL_Delay(30);
	}
	[mailer release];
#endif
}

void getDeviceModel(char*deviceString)
{
#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
	if(deviceString!=NULL)
	{
		UIDevice*device = [UIDevice currentDevice];
		strcpy(deviceString, [[device model] UTF8String]);
	}
#endif
}

void getDeviceName(char*nameString)
{
#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
	if(nameString!=NULL)
	{
		UIDevice*device = [UIDevice currentDevice];
		strcpy(nameString, [[device name] UTF8String]);
	}
#endif
}

void SDL_ShowSimpleMessageBoxFixed(const char*title, const char*message)
{
#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
	UIAlertView *alert = [[UIAlertView alloc] initWithTitle:[NSString stringWithUTF8String:title]
													message:[NSString stringWithUTF8String:message]
												   delegate:nil
										  cancelButtonTitle:@"OK"
										  otherButtonTitles:nil];
	[alert show];
	while(alert.visible==YES)
	{
		updateAppEvents();
		SDL_Delay(30);
	}
	[alert release];
#else
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title, message, NULL);
#endif
}

int SDL_ShowMessageBoxFixed(const char*title, const char*message, const char**options, int numOptions)
{
#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
	int i;
	MessageBoxDelegate*messageDelegate = [[MessageBoxDelegate alloc] init];
	[messageDelegate prepare];
	UIAlertView *alert = [[UIAlertView alloc] initWithTitle:[NSString stringWithUTF8String:title]
													message:[NSString stringWithUTF8String:message]
												   delegate:messageDelegate
										  cancelButtonTitle:nil
										  otherButtonTitles:nil];
	for(i=0; i<numOptions; i++)
	{
		[alert addButtonWithTitle:[NSString stringWithUTF8String:options[i]]];
	}
	[alert show];
	while([messageDelegate isClosed] == NO)
	{
		updateAppEvents();
		SDL_Delay(30);
	}
	int result = [messageDelegate getResult];
	[alert release];
	[messageDelegate release];
	return result;
#else
	SDL_MessageBoxButtonData* buttons = new SDL_MessageBoxButtonData[numOptions];
	for(int i=0; i<numOptions; i++)
	{
		SDL_MessageBoxButtonData button;
		button.buttonid = i;
		button.text = options[i];
		buttons[i] = button;
	}
	SDL_MessageBoxData messageboxdata = {SDL_MESSAGEBOX_INFORMATION, NULL, title, message, numOptions, buttons, NULL};
	int buttonid;
	SDL_ShowMessageBox(&messageboxdata, &buttonid);
	delete[] buttons;
	return buttonid;
#endif
}

#ifdef _WIN32
#include <iostream>
#endif

void GameEngine_Log(char*text)
{
#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
	NSLog(@"%@", [NSString stringWithUTF8String:text]);
#else
	std::cout << text;
#endif
}

#ifdef _WIN32
#include "Util/posixtime.h"
#endif

long getUptimeMillis(void)
{
	struct timeval tv;
	gettimeofday(&tv,NULL);
	//return (long)((long)((long)tv.tv_sec*1000) + (long)((long)tv.tv_usec/1000));
	long elapsed = (long)(tv.tv_sec)*1000 + (long)tv.tv_usec/1000;
	return elapsed;
}