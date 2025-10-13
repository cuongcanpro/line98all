/****************************************************************************
 Copyright (c) 2010-2013 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "AppController.h"
#import "cocos2d.h"
#import "AppDelegate.h"
#import "GlobalVar.h"
#import "RootViewController.h"
#import <AppTrackingTransparency/AppTrackingTransparency.h>
#import <AdSupport/AdSupport.h>
#import "RootViewControllerInterface.h"
#import <FirebaseCore/FirebaseCore.h>
#import <FirebaseCore/FIRApp.h>
//#import "TestFireBase_mobile-Swift.h"
#include <UserMessagingPlatform/UserMessagingPlatform.h>
//#import <GoogleAnalytics/GAI.h>
//#import <GoogleAnalytics/GAIDictionaryBuilder.h>
//#import <Firebase/Firebase.h>

@implementation AppController

@synthesize window;

#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    
    cocos2d::Application *app = cocos2d::Application::getInstance();
    
    // Initialize the GLView attributes
    app->initGLContextAttrs();
    cocos2d::GLViewImpl::convertAttrs();
    
    // Override point for customization after application launch.

    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];

    // Use RootViewController to manage CCEAGLView
    _viewController = [[RootViewController alloc]init];
    _viewController.wantsFullScreenLayout = YES;
    

    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: _viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:_viewController];
    }

    [window makeKeyAndVisible];

    [[UIApplication sharedApplication] setStatusBarHidden:true];
    
    // IMPORTANT: Setting the GLView should be done after creating the RootViewController
    cocos2d::GLView *glview = cocos2d::GLViewImpl::createWithEAGLView((__bridge void *)_viewController.view);
    cocos2d::Director::getInstance()->setOpenGLView(glview);
    [FIRApp configure];
    //run the cocos2d-x game scene
    [[RootViewControllerInterface rootViewControllerInterfaceSharedInstance] setRootViewController: _viewController];
    app->run();
    UMPRequestParameters *parameters = [[UMPRequestParameters alloc] init];
   // UMPDebugSettings *debugSettings = [[UMPDebugSettings alloc] init];
    //debugSettings.testDeviceIdentifiers = @[ @"4690C4DA-B9B6-440E-8CCA-733D52BB793E" ];
    //debugSettings.testDeviceIdentifiers = @[ @"7A24A9D2-94F0-4CFD-8C9C-55533F1F7968" ];// iphone qc
    //debugSettings.geography = UMPDebugGeographyEEA;
    //parameters.debugSettings = debugSettings;
    
    // Create a UMPRequestParameters object.
   // UMPRequestParameters *parameters = [[UMPRequestParameters alloc] init];
    // Set tag for under age of consent. Here NO means users are not under age.
  //  parameters.tagForUnderAgeOfConsent = NO;
    
   // [UMPConsentInformation.sharedInstance reset];
    // Request an update to the consent information.
    [UMPConsentInformation.sharedInstance
        requestConsentInfoUpdateWithParameters:parameters
                             completionHandler:^(NSError *_Nullable error) {
                               if (error) {
                                 // Handle the error.
                               } else {
                                 // The consent information state was updated.
                                 // You are now ready to check if a form is
                                 // available.
                                   [_viewController loadForm];
                               }
                             }];
    
   // Test* test = [Test alloc];
   // [test printData];
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
  
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
    // We don't need to call this method any more. It will interrupt user defined game pause&resume logic
    /* cocos2d::Director::getInstance()->resume(); */
//    if (@available(iOS 14, *)) {
//        [ATTrackingManager requestTrackingAuthorizationWithCompletionHandler:^(ATTrackingManagerAuthorizationStatus status) {
//            // Tracking authorization completed. Start loading ads here.
//            // [self loadAd];
//        }];
//    } else {
//        // Fallback on earlier versions
//    }
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    cocos2d::Application::getInstance()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    cocos2d::Application::getInstance()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
}
- (BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options {
    
    // Extract the scheme
    NSString *scheme = [url scheme];
    
    // Extract the host or any other component from the URL
    NSString *host = [url host];
    
    // Extract query parameters (if any)
    NSURLComponents *urlComponents = [NSURLComponents componentsWithURL:url resolvingAgainstBaseURL:NO];
    NSArray<NSURLQueryItem *> *queryItems = [urlComponents queryItems];
    
    // Look for specific query parameters
    NSString *data = nil;
    NSString *username = nil;
    NSString *password = nil;
    NSString *deviceId = nil;
    for (NSURLQueryItem *item in queryItems) {
        if ([item.name isEqualToString:@"data"]) {
            data = item.value;
           // break;
        }
        else if ([item.name isEqualToString:@"username"]) {
            username = item.value;
           // break;
        }
        else if ([item.name isEqualToString:@"password"]) {
            password = item.value;
           // break;
        }
        else if ([item.name isEqualToString:@"deviceId"]) {
            deviceId = item.value;
           // break;
        }
    }
    
    // Handle the URL scheme and data as needed
    if ([scheme isEqualToString:@"blockPuzzelChess"]) {
        if ([host isEqualToString:@"parameter"]) {
            NSLog(@"Received data: %@", data);
            const char *usernameData = [username UTF8String];
            const char *passwordData = [password UTF8String];
            const char *deviceIdData = [deviceId UTF8String];
            game->updateDataFromOld(usernameData, passwordData, deviceIdData);
            // Handle the data appropriately in your app
            // For example, navigate to a specific view controller or process the data
        }
        return YES;
    }
    
    return NO;
}

#if __has_feature(objc_arc)
#else
- (void)dealloc {
    [window release];
    [_viewController release];
    [super dealloc];
}
#endif


@end
