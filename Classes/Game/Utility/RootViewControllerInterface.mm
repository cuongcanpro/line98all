//
//  RootViewControllerInterface.m
//  cocosViewController
//
//  Created by toni on 25/06/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
//#include "../../Engine/Utility/CCLocalizedString.h"
#import "RootViewControllerInterface.h"
#import <string.h>



@implementation RootViewControllerInterface

@synthesize rootViewController;

#pragma mark -
#pragma mark Singleton Variables
static RootViewControllerInterface *rootViewControllerInterfaceSingletonDelegate = nil;

#pragma mark -
#pragma mark Singleton Methods
+ (RootViewControllerInterface *) rootViewControllerInterfaceSharedInstance {
	@synchronized(self) {
		if (rootViewControllerInterfaceSingletonDelegate == nil) {
			[[self alloc] init]; // assignment not done here
		}
	}
	return rootViewControllerInterfaceSingletonDelegate;
}

+ (id)allocWithZone:(NSZone *)zone {
	@synchronized(self) {
		if (rootViewControllerInterfaceSingletonDelegate == nil) {
			rootViewControllerInterfaceSingletonDelegate = [super allocWithZone:zone];
			// assignment and return on first allocation
			return rootViewControllerInterfaceSingletonDelegate;
		}
	}
	// on subsequent allocation attempts return nil
	return nil;
}

- (id)copyWithZone:(NSZone *)zone {
	return self;
}

- (id)retain {
	return self;
}

- (unsigned)retainCount {
	return UINT_MAX;  // denotes an object that cannot be released
}

- (void)release {
	//do nothing
    
}

- (id)autorelease {
	return self;
}

-(void) presentModalViewController:(UIViewController*)controller animated:(BOOL)animated {
    [rootViewController presentModalViewController:controller animated:animated];
}

-(void) sendEvent:(NSString *)key data:(NSString*)data {
    [rootViewController sendEvent:key data:data];
}

-(void) crashlyticSetString:(NSString *)key data:(NSString*)data {
    [rootViewController crashlyticSetString:key data:data];
}

-(void) initAds:(int)typeAds initAdsInter:(int)typeAdsInter{
    [rootViewController initAds:typeAds initAdsInter:typeAdsInter];
}

-(void)showInsertial
{
    [rootViewController showInsertial];
}

-(void)loadAds
{
    [rootViewController loadAds];
}

-(void)showReward
{
    [rootViewController showReward];
}

-(void) showAds:(BOOL)visible
{
    if (visible)
        [rootViewController showBanner];
    else
        [rootViewController hideBanner];
}

-(void)showTracking
{
	[rootViewController showTracking];
}


-(void)changeToPortrait
{
    [rootViewController forceRotateToOrientation:UIInterfaceOrientationPortrait];
}

-(void)changeToLandscape
{
    [rootViewController forceRotateToOrientation:UIInterfaceOrientationLandscapeRight];
}

@end
