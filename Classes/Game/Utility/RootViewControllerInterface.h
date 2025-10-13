//
//  RootViewControllerInterface.h
//  cocosViewController
//
//  Created by toni on 25/06/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AddressBookUI/AddressBookUI.h>
#import <AddressBook/AddressBook.h>
#import <MessageUI/MessageUI.h>



@interface RootViewControllerInterface : NSObject  <ABPeoplePickerNavigationControllerDelegate, MFMessageComposeViewControllerDelegate> {
    UIViewController *rootViewController;
}

@property (nonatomic, retain) UIViewController *rootViewController;

#pragma mark -
#pragma mark Singleton Methods
+ (RootViewControllerInterface *) rootViewControllerInterfaceSharedInstance;

-(void) presentModalViewController:(UIViewController*)controller animated:(BOOL)animated;
-(void) showInsertial;
-(void) loadAds;
-(void) sendEvent:(NSString*) key data:(NSString*)data;
-(void) crashlyticSetString:(NSString*) key data:(NSString*)data;
-(void) initAds:(int) typeAds initAdsInter:(int) typeAdsInter;
-(void) showReward;
-(void) showAds:(BOOL) visible;
-(void) showTracking;
-(void) changeToLandscape;
-(void) changeToPortrait;
@end
