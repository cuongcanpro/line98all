#import "RootViewController.h"
//#import <GoogleAnalytics/GAI.h>
//#import <GoogleAnalytics/GAIDictionaryBuilder.h>
//#import "NetworkHandler.h"
//#import <Firebase/Firebase.h>
//#import <FirebaseCore/FirebaseCore.h>
#import <AppTrackingTransparency/AppTrackingTransparency.h>
#import <AdSupport/AdSupport.h>
#import <AdSupport/ASIdentifierManager.h>
//#include "Engine/GlobalVar.h"
#import "cocos2d.h"
#import "platform/ios/CCEAGLView-ios.h"
#import "GlobalVar.h"
#import <FirebaseCore/FirebaseCore.h>
#import <FirebaseCore/FIRApp.h>
#import <FirebaseAnalytics/FirebaseAnalytics.h>
#include <UserMessagingPlatform/UserMessagingPlatform.h>
#include "Game/Data/GlobalData.h"
@implementation RootViewController {
   
}

// Override to allow orientations other than the default portrait orientation.
// This method is deprecated on ios6
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return UIInterfaceOrientationIsPortrait( interfaceOrientation );
}



// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations{
#ifdef __IPHONE_6_0
    //return UIInterfaceOrientationMaskAllButUpsideDown;
#endif
    if (isLandscape == 0)
        return UIInterfaceOrientationMaskPortrait;
    else
        return UIInterfaceOrientationMaskLandscape;
}

-(BOOL)shouldAutorotate
{
   if (changeRotation == 0)
        return NO;
    else
        return YES;
}

//fix not hide status on ios7
- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

- (void)loadView
{
    CCEAGLView *eaglView = [CCEAGLView viewWithFrame: [UIScreen mainScreen].bounds
                                         pixelFormat: (__bridge NSString *)cocos2d::GLViewImpl::_pixelFormat
                                         depthFormat: cocos2d::GLViewImpl::_depthFormat
                                  preserveBackbuffer: NO
                                          sharegroup: nil
                                       multiSampling: cocos2d::GLViewImpl::_multisamplingCount > 0 ? YES : NO
                                     numberOfSamples: cocos2d::GLViewImpl::_multisamplingCount ];
    
    // Enable or disable multiple touches
    [eaglView setMultipleTouchEnabled:NO];
    
    // Set EAGLView as view of RootViewController
    self.view = eaglView;
}

- (void)viewDidUnload {
    [super viewDidUnload];
    
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}



- (void)viewDidLoad{
    [super viewDidLoad];
    self.view.multipleTouchEnabled = true;
    
}

- (void)addBannerViewToView:(UIView *)bannerView {
  bannerView.translatesAutoresizingMaskIntoConstraints = NO;
  [self.view addSubview:bannerView];
  [self.view addConstraints:@[
    [NSLayoutConstraint constraintWithItem:bannerView
                               attribute:NSLayoutAttributeBottom
                               relatedBy:NSLayoutRelationEqual
                                  toItem:self.bottomLayoutGuide
                               attribute:NSLayoutAttributeTop
                              multiplier:1
                                constant:0],
    [NSLayoutConstraint constraintWithItem:bannerView
                               attribute:NSLayoutAttributeCenterX
                               relatedBy:NSLayoutRelationEqual
                                  toItem:self.view
                               attribute:NSLayoutAttributeCenterX
                              multiplier:1
                                constant:0]
                                ]];
}

- (void)viewDidLayoutSubviews
{
    CGRect contentFrame = self.view.bounds;
    CGRect bannerFrame = CGRectZero;
#if __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_6_0
    bannerFrame = self._bannerView.frame;
#else
    bannerFrame.size = [self.bannerViewAdmob sizeThatFits:contentFrame.size];
#endif
    
    bannerFrame.origin.x = (contentFrame.size.width - bannerFrame.size.width) / 2;
  //  bannerFrame.origin.x = 0;
    bannerFrame.origin.y = contentFrame.size.height - bannerFrame.size.height;
    if (typeAdsNetwork == 1) {
        if (self.bannerViewAdmob)
            self.bannerViewAdmob.frame = bannerFrame;
    }
    else if (typeAdsNetwork == 2) {
        if (self.bannerViewFacebook)
            self.bannerViewFacebook.frame = bannerFrame;
    }
    else {
        if (self.bannerViewUnity)
            self.bannerViewUnity.frame = bannerFrame;
    }
   // self.bottomBannerView.frame = bannerFrame;
}

- (void)dealloc {
    [super dealloc];
}

- (void) initAds : (int) adsType initAdsInter:(int) adsTypeInter{
    UIView *contentView = [[UIView alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
   // [contentView addSubview: banner._bannerView];
    typeAdsNetwork = adsType;
    typeAdsNetworkInter = adsTypeInter;
   // typeAdsNetwork = 1;
    [self initAdmob];
    [self initUnity];
    [self initIronSource];
    
 //   typeAdsNetwork = 4;
//    if (typeAdsNetwork == 1) {
//        // khoi tao Admob
//        [self initAdmob];
//    }
//    else if (typeAdsNetwork == 2) {
//        // khoi tao Facebook
//        [self initFacebook];
//    }
//    else if (typeAdsNetwork == 4) {
//        // khoi tao Facebook
//        [self initIronSource];
//    }
//    else {
//        // khoi tao Unity
//        [self initUnity];
//    }
}

- (void) initAdmob {
    self.bannerViewAdmob = [[GADBannerView alloc] initWithAdSize: GADAdSizeBanner];
    GADMobileAds *ads = [GADMobileAds sharedInstance];
      [ads startWithCompletionHandler:^(GADInitializationStatus *status) {
        // Optional: Log each adapter's initialization latency.
        NSDictionary *adapterStatuses = [status adapterStatusesByClassName];
        for (NSString *adapter in adapterStatuses) {
          GADAdapterStatus *adapterStatus = adapterStatuses[adapter];
          NSLog(@"Adapter Name: %@, Description: %@, Latency: %f", adapter,
                adapterStatus.description, adapterStatus.latency);
        }
          GADMobileAds.sharedInstance.requestConfiguration.testDeviceIdentifiers = @[ @"bc917989d107ea02825ca8383b5ba418" ];
        // Start loading ads here...
          
          if (adBannerUnit == "")
              self.bannerViewAdmob.adUnitID = BannerAdmobId; //REPLACE WITH YOUR OWN PUBLISHER ID
          else
              self.bannerViewAdmob.adUnitID = [NSString stringWithCString:adBannerUnit.c_str()
                                                                 encoding:[NSString defaultCStringEncoding]];;
          self.bannerViewAdmob.delegate = self;
          self.bannerViewAdmob.rootViewController = self;
          [self.view addSubview:self.bannerViewAdmob];
          [self.view addConstraints:@[
                                      [NSLayoutConstraint constraintWithItem:self.bannerViewAdmob
                                                                   attribute:NSLayoutAttributeBottom
                                                                   relatedBy:NSLayoutRelationEqual
                                                                      toItem:self.bottomLayoutGuide
                                                                   attribute:NSLayoutAttributeTop
                                                                  multiplier:1
                                                                    constant:0],
                                      [NSLayoutConstraint constraintWithItem:self.bannerViewAdmob
                                                                   attribute:NSLayoutAttributeCenterX
                                                                   relatedBy:NSLayoutRelationEqual
                                                                      toItem:self.view
                                                                   attribute:NSLayoutAttributeCenterX
                                                                  multiplier:1
                                                                    constant:0]
                                      ]];
          
          GADRequest *request = [GADRequest request];
          if (typeAdsNetwork == 1)
              [self.bannerViewAdmob loadRequest:request];
          else
              self.bannerViewAdmob.hidden = true;
          if (typeAdsNetworkInter == 1) {
              [self createAndLoadInterstitial];
               [self loadRewardAdmob];
          }
        
        //  [self initUnity];
      }];
    NSLog(@"admob version  %@ " ,[[GADMobileAds sharedInstance] sdkVersion]);
    [FBAdSettings setAdvertiserTrackingEnabled:YES];
}

- (void)bannerViewDidReceiveAd:(GADBannerView *)bannerView {
  NSLog(@"bannerViewDidReceiveAd");
    NSUserDefaults *prefs = [NSUserDefaults standardUserDefaults];
    
        [prefs setInteger:0 forKey:@"loadDataFail"];
}

- (void)bannerView:(GADBannerView *)bannerView didFailToReceiveAdWithError:(NSError *)error {
  NSLog(@"bannerView:didFailToReceiveAdWithError: %@", [error localizedDescription]);
    NSLog(@"adView didFailToReceiveAdWithError");
    if (moveToUnity == false) {
       // [self._bannerView removeFromSuperview];
        moveToUnity = true;
       // [self addBannerViewToBottomView:self.bottomBannerView];
    }
    NSUserDefaults *prefs = [NSUserDefaults standardUserDefaults];
    NSInteger numFail = [prefs integerForKey:@"loadDataFail"];
    
    if (game->isRussia) {
        self.bannerViewAdmob.hidden = true;
      //  idAdsBanner = 3;
        //[self initAds:3];
    }
    numFail++;
    if (numFail <= 3)
        [prefs setInteger:numFail forKey:@"loadDataFail"];
}

- (void)bannerViewDidRecordImpression:(GADBannerView *)bannerView {
  NSLog(@"bannerViewDidRecordImpression");
}

- (void)bannerViewWillPresentScreen:(GADBannerView *)bannerView {
  NSLog(@"bannerViewWillPresentScreen");
}

- (void)bannerViewWillDismissScreen:(GADBannerView *)bannerView {
  NSLog(@"bannerViewWillDismissScreen");
}

- (void)bannerViewDidDismissScreen:(GADBannerView *)bannerView {
  NSLog(@"bannerViewDidDismissScreen");
}

- (GADInterstitialAd *)createAndLoadInterstitial {
    GADRequest *request = [GADRequest request];
    NSString *loadId = InterAdmobId;
    if (adInterUnit == "")
        loadId = InterAdmobId;
    else
        loadId = [NSString stringWithCString:adInterUnit.c_str()
                                    encoding:[NSString defaultCStringEncoding]];
       
        
      [GADInterstitialAd loadWithAdUnitID:loadId
                                  request:request
                        completionHandler:^(GADInterstitialAd *ad, NSError *error) {
        if (error) {
          NSLog(@"Failed to load interstitial ad with error: %@", [error localizedDescription]);
          return;
        }
          self.interstitialAdmob = ad;
          self.interstitialAdmob.fullScreenContentDelegate = self;
      }];
    return self.interstitialAdmob;
}
/// Tells the delegate that the ad failed to present full screen content.
- (void)ad:(nonnull id<GADFullScreenPresentingAd>)ad
didFailToPresentFullScreenContentWithError:(nonnull NSError *)error {
    NSLog(@"Ad did fail to present full screen content.");
    [self createAndLoadInterstitial];
    game->hideGuiWaitting();
}

/// Tells the delegate that the ad presented full screen content.
- (void)adDidPresentFullScreenContent:(nonnull id<GADFullScreenPresentingAd>)ad {
    NSLog(@"Ad did present full screen content.");
    self.interstitialAdmob = nil;
    [self createAndLoadInterstitial];
}

/// Tells the delegate that the ad dismissed full screen content.
- (void)adDidDismissFullScreenContent:(nonnull id<GADFullScreenPresentingAd>)ad {
   NSLog(@"Ad did dismiss full screen content.");
    if (typeLastShow == 0) {
        [self createAndLoadInterstitial];
    }
    else {
        [self loadRewardAdmob];
    }
    game->hideGuiWaitting();
}

- (void) showInsertial{
    typeLastShow = 0;
    if (typeAdsNetworkInter == 1) {
        @try {
            if (self.interstitialAdmob &&
               [self.interstitialAdmob
                   canPresentFromRootViewController:self
                                              error:nil]) {
             [self.interstitialAdmob presentFromRootViewController:self];
                game->hideGuiWaitting();
           } else {
             NSLog(@"Ad wasn't ready");
             [self createAndLoadInterstitial];
             [IronSource showInterstitialWithViewController:self];
           }
        }
        @catch (NSException *exception) {
           // [UnityAds show:self placementId:InterUnityId showDelegate:self];
        }
        @finally {
           NSLog(@"Finally condition");
        }
    }
    else if (typeAdsNetworkInter == 2){
        [self showInterFacebook];
//        if (self.interstitialAd && self.interstitialAd.isAdValid) {
//            // You can now display the full screen ad using this code:
//            [self.interstitialAd showAdFromRootViewController:self];
//        }
    }
    else if (typeAdsNetworkInter == 4){
        [IronSource showInterstitialWithViewController:self];
    }
    else {
        [UnityAds show:self placementId:InterUnityId showDelegate:self];
    }
}

- (void)loadRewardAdmob {
  GADRequest *request = [GADRequest request];
    NSString *loadId = RewardAdmobId;
    if (adRewardUnit == "")
        loadId = RewardAdmobId;
    else
        loadId = [NSString stringWithCString:adRewardUnit.c_str()
                                    encoding:[NSString defaultCStringEncoding]];
  [GADRewardedAd
       loadWithAdUnitID:loadId
                request:request
      completionHandler:^(GADRewardedAd *ad, NSError *error) {
        if (error) {
          NSLog(@"Rewarded ad failed to load with error: %@", [error localizedDescription]);
          return;
        }
        self.rewardAdmob = ad;
      self.rewardAdmob.fullScreenContentDelegate = self;
        NSLog(@"Rewarded ad loaded.");
      }];
}

- (void)showReward {
    typeLastShow = 1;
    if (typeAdsNetworkInter == 1) {
        [self showRewardAdmob];
    }
    else if (typeAdsNetworkInter == 2) {
        [self showRewardFacebook];
    }
    else if (typeAdsNetworkInter == 4) {
        [IronSource showRewardedVideoWithViewController:self];
    }
    else {
        [UnityAds show:self adUnitId:RewardUnityId showDelegate:self];
    }
}

- (void)showRewardAdmob{
  
  if (self.rewardAdmob) {
    [self.rewardAdmob presentFromRootViewController:self
                                  userDidEarnRewardHandler:^{
                                  GADAdReward *reward =
                                      self.rewardAdmob.adReward;
                                  // TODO: Reward the user!
        game->onReward(1);
                                }];
  } else {
    NSLog(@"Ad wasn't ready");
      [self loadRewardAdmob];
      [IronSource showRewardedVideoWithViewController:self];
    //  game->onReward(1);
  }
}

#pragma mark : Init Unity ads here
- (void) initUnity {
    if (![UnityAds isReady]) {
        [UnityAds setDebugMode: false];
        [UnityAds addDelegate: self];
        [UnityAds initialize: gameIdUnity
                          testMode: false
            initializationDelegate: self];
    }
}

#pragma mark : UnityAdsInitializationDelegate
- (void)initializationComplete {
    NSLog(@" - UnityAdsInitializationDelegate initializationComplete" );
    // Pre-load an ad when initialization succeeds, so it is ready to show:
    if (typeAdsNetworkInter == 3)
        [UnityAds load:@"Interstitial_iOS" loadDelegate:self];
    if (typeAdsNetwork == 3) {
        self.bannerViewUnity = [[UADSBannerView alloc] initWithPlacementId: @"Banner_iOS" size: CGSizeMake(320, 50)];
        //  self.bottomBannerView.delegate = self;
        [self.bannerViewUnity load];
    }
}

- (void)initializationFailed:(UnityAdsInitializationError)error withMessage:(NSString *)message {
    NSLog(@" - UnityAdsInitializationDelegate initializationFailed with message: %@", message );
}

// Implement load callbacks to handle success or failure after initialization:
#pragma mark: UnityAdsLoadDelegate
- (void)unityAdsAdLoaded:(NSString *)adUnitId {
    NSLog(@" - UnityAdsLoadDelegate unityAdsAdLoaded %@", adUnitId);
}

- (void)unityAdsAdFailedToLoad:(NSString *)adUnitId
                     withError:(UnityAdsLoadError)error
                   withMessage:(NSString *)message {
    NSLog(@" - UnityAdsLoadDelegate unityAdsAdFailedToLoad %@", adUnitId);
}

// Implement callbacks for events related to the show method:
#pragma mark: UnityAdsShowDelegate
- (void)unityAdsShowComplete:(NSString *)adUnitId withFinishState:(UnityAdsShowCompletionState)state {
    NSLog(@" - UnityAdsShowDelegate unityAdsShowComplete %@ %ld", adUnitId, state);
    game->hideGuiWaitting();
    if ([adUnitId isEqualToString:@"Rewarded_iOS"] && state == kUnityShowCompletionStateCompleted) {
            // Reward the user.
        game->onReward(1);
        [UnityAds load:@"Rewarded_iOS" loadDelegate:self];
        }
    else {
        [UnityAds load:@"Interstitial_iOS" loadDelegate:self];
    }
}

- (void)unityAdsShowFailed:(NSString *)adUnitId withError:(UnityAdsShowError)error withMessage:(NSString *)message {
    NSLog(@" - UnityAdsShowDelegate unityAdsShowFailed %@ %ld", message, error);
    // Optionally execute additional code, such as attempting to load another ad.
    game->hideGuiWaitting();
    if (countErrorInter < 3) {
        [UnityAds load:@"Interstitial_iOS" loadDelegate:self];
        countErrorInter = 0;
    }
    else {
        countErrorInter++;
    }
}

- (void)unityAdsShowStart:(NSString *)adUnitId {
    NSLog(@" - UnityAdsShowDelegate unityAdsShowStart %@", adUnitId);
}

- (void)unityAdsShowClick:(NSString *)adUnitId {
    NSLog(@" - UnityAdsShowDelegate unityAdsShowClick %@", adUnitId);
}

- (void)unityAdsDidError:(UnityAdsError)error withMessage:(nonnull NSString *)message {
    
}

- (void)unityAdsDidFinish:(nonnull NSString *)placementId withFinishState:(UnityAdsFinishState)state {
    
}

- (void)unityAdsDidStart:(nonnull NSString *)placementId {
    
}

- (void)unityAdsReady:(nonnull NSString *)placementId {
    
}

- (void) addBannerViewToBottomView: (UIView *)bannerView {
    bannerView.translatesAutoresizingMaskIntoConstraints = NO;
    [self.view addSubview:bannerView];
    [self.view addConstraints:@[
                               [NSLayoutConstraint constraintWithItem:bannerView
                                                            attribute:NSLayoutAttributeBottom
                                                            relatedBy:NSLayoutRelationEqual
                                                               toItem:self.bottomLayoutGuide
                                                            attribute:NSLayoutAttributeTop
                                                           multiplier:1
                                                             constant:0],
                               [NSLayoutConstraint constraintWithItem:bannerView
                                                            attribute:NSLayoutAttributeCenterX
                                                            relatedBy:NSLayoutRelationEqual
                                                               toItem:self.view
                                                            attribute:NSLayoutAttributeCenterX
                                                           multiplier:1
                                                             constant:0]
                               ]];
}

// Implement the delegate methods:
#pragma mark : UADSBannerViewDelegate

- (void)bannerViewDidLoad:(UADSBannerView *)bannerView {
    // Called when the banner view object finishes loading an ad.
    NSLog(@"Banner loaded for Ad Unit or Placement: %@", bannerView.placementId);
}

- (void)bannerViewDidClick:(UADSBannerView *)bannerView {
    // Called when the banner is clicked.
    NSLog(@"Banner was clicked for Ad Unit or Placement: %@", bannerView.placementId);
}

- (void)bannerViewDidLeaveApplication:(UADSBannerView *)bannerView {
    // Called when the banner links out of the application.
}


- (void)bannerViewDidError:(UADSBannerView *)bannerView error:(UADSBannerError *)error{
    // Called when an error occurs showing the banner view object.
    NSLog(@"Banner encountered an error for Ad Unit or Placement: %@ with error message %@", bannerView.placementId, [error localizedDescription]);
    // Note that the UADSBannerError can indicate no fill (see API documentation).
    if (countErrorBanner < 3) {
        [_bannerViewUnity load];
        countErrorBanner = 0;
    }
    else {
        countErrorBanner++;
    }
}

#pragma mark : Init Unity ads here ************************
- (void) initFacebook {
    [FBAudienceNetworkAds initializeWithSettings:nil completionHandler:nil];

    // Pass user's consent after acquiring it. For sample app purposes, this is set to YES.
    [FBAdSettings setAdvertiserTrackingEnabled:YES];
    self.bannerViewFacebook = [[FBAdView alloc] initWithPlacementID:BannerFacebookId adSize:kFBAdSizeHeight50Banner rootViewController:self];
    self.bannerViewFacebook.frame = CGRectMake(0, 0, 320, 250);
    self.bannerViewFacebook.delegate = self;
    [self.bannerViewFacebook loadAd];
    [self.view addSubview:self.bannerViewFacebook];
    [self.view addConstraints:@[
                                [NSLayoutConstraint constraintWithItem:self.bannerViewFacebook
                                                             attribute:NSLayoutAttributeBottom
                                                             relatedBy:NSLayoutRelationEqual
                                                                toItem:self.bottomLayoutGuide
                                                             attribute:NSLayoutAttributeTop
                                                            multiplier:1
                                                              constant:0],
                                [NSLayoutConstraint constraintWithItem:self.bannerViewFacebook
                                                             attribute:NSLayoutAttributeCenterX
                                                             relatedBy:NSLayoutRelationEqual
                                                                toItem:self.view
                                                             attribute:NSLayoutAttributeCenterX
                                                            multiplier:1
                                                              constant:0]
                                ]];
    
    self.interstitialFacebook = [[FBInterstitialAd alloc] initWithPlacementID:InterFacebookId];

    self.interstitialFacebook.delegate = self;

      // For auto play video ads, it's recommended to load the ad at least 30 seconds before it is shown
    [self.interstitialFacebook loadAd];
    
    self.rewardFacebook = [[FBRewardedVideoAd alloc] initWithPlacementID:RewardFacebookId];
    self.rewardFacebook.delegate = self;
    [self loadRewardFacebook];
    
    [FBAdSettings addTestDevice:@"bc917989d107ea02825ca8383b5ba418"];
    if (NSClassFromString(@"ASIdentifierManager")) {
        NSLog(@"GoogleAdMobAdsSDK ID for testing: %@" ,
              [[[ASIdentifierManager sharedManager] advertisingIdentifier] UUIDString]);
    } else {
       // NSLog(@"GoogleAdMobAdsSDK ID for testing: %@" ,
            //  [[UIDevice currentDevice] uniqueIdentifier]);
    }
}

- (void) loadInterFacebook {
    [self.interstitialFacebook loadAd];
}

- (void) showInterFacebook {
    if (self.interstitialFacebook && self.interstitialFacebook.isAdValid) {
        // You can now display the full screen ad using this code:
        [self.interstitialFacebook showAdFromRootViewController:self];
    }
}

- (void) loadRewardFacebook {
    [self.rewardFacebook loadAd];
}

- (void) showRewardFacebook {
    if (self.rewardFacebook && self.rewardFacebook.isAdValid) {
        [self.rewardFacebook showAdFromRootViewController:self];
    }
    else {
        game->onReward(1);
    }
}

- (void)rewardedVideoAdDidLoad:(FBRewardedVideoAd *)rewardedVideoAd
{
  NSLog(@"Video ad is loaded and ready to be displayed");
}
    
- (void)rewardedVideoAd:(FBRewardedVideoAd *)rewardedVideoAd didFailWithError:(NSError *)error
{
  NSLog(@"Rewarded video ad failed to load");
}

- (void)rewardedVideoAdDidClick:(FBRewardedVideoAd *)rewardedVideoAd
{
  NSLog(@"Video ad clicked");
}
    
- (void)rewardedVideoAdDidClose:(FBRewardedVideoAd *)rewardedVideoAd
{
  NSLog(@"Rewarded Video ad closed - this can be triggered by closing the application, or closing the video end card");
   // game->onReward(0);
}

- (void)rewardedVideoAdVideoComplete:(FBRewardedVideoAd *)rewardedVideoAd;
{
  NSLog(@"Rewarded Video ad video completed - this is called after a full video view, before the ad end card is shown. You can use this event to initialize your reward");
   // game->onReward(1);
}

- (void)interstitialAdWillLogImpression:(FBInterstitialAd *)interstitialAd
{
  NSLog(@"The user sees the ad");
  // Use this function as indication for a user's impression on the ad.
}

- (void)interstitialAdDidClick:(FBInterstitialAd *)interstitialAd
{
  NSLog(@"The user clicked on the ad and will be taken to its destination");
  // Use this function as indication for a user's click on the ad.
}

- (void)interstitialAdWillClose:(FBInterstitialAd *)interstitialAd
{
  NSLog(@"The user clicked on the close button, the ad is just about to close");
  // Consider to add code here to resume your app's flow
}

- (void)interstitialAdDidClose:(FBInterstitialAd *)interstitialAd
{
  NSLog(@"Interstitial had been closed");
  // Consider to add code here to resume your app's flow
    [self.interstitialFacebook loadAd];
}

- (void)adViewDidClick:(FBAdView *)adView
{
  NSLog(@"Ad was clicked.");
}

- (void)adViewDidFinishHandlingClick:(FBAdView *)adView
{
  NSLog(@"Ad did finish click handling.");
}

- (void)adViewWillLogImpression:(FBAdView *)adView
{
  NSLog(@"Ad impression is being captured.");
}

- (void)adView:(FBAdView *)adView didFailWithError:(NSError *)error
{
  NSLog(@"Ad failed to load with error: %@", error);
}

- (void)adViewDidLoad:(FBAdView *)adView
{
  NSLog(@"Ad was loaded and ready to be displayed");
  //[self showAd];
}

- (void)interstitialAd:(FBInterstitialAd *)interstitialAd didFailWithError:(NSError *)error
{
  NSLog(@"Interstitial ad failed to load with error: %@", error);
}

- (void) hideBanner{
    //TODO:
    if (typeAdsNetwork == 1)
        self.bannerViewAdmob.hidden = true;
    else if (typeAdsNetwork == 2)
        self.bannerViewFacebook.hidden = true;
    else if (typeAdsNetwork == 3)
        self.bannerViewUnity.hidden = true;
    else if (typeAdsNetwork == 4)
        self.bannerViewIS.hidden = true;
}

- (void) showBanner{
    //TODO:
   
    if (typeAdsNetwork == 1)
        self.bannerViewAdmob.hidden = false;
    else if (typeAdsNetwork == 2)
        self.bannerViewFacebook.hidden = false;
    else if (typeAdsNetwork == 3)
        self.bannerViewUnity.hidden = false;
    else if (typeAdsNetwork == 4)
        self.bannerViewIS.hidden = false;
}

- (void) sendEvent : (NSString*) key data: (NSString*) data {
    [FIRAnalytics logEventWithName:key parameters:@{
                                    @"data": data
                                    }];

}

- (void) crashlyticSetString : (NSString*) key data: (NSString*) data {
 //   [[FIRCrashlytics crashlytics] setCustomValue:data forKey:key];
}

- (void)loadForm {
  [UMPConsentForm loadWithCompletionHandler:^(UMPConsentForm *form,
                                              NSError *loadError) {
    if (loadError) {
      // Handle the error.
    } else {
      // Present the form. You can also hold on to the reference to present
      // later.
      if (UMPConsentInformation.sharedInstance.consentStatus ==
          UMPConsentStatusRequired) {
        [form
            presentFromViewController:self
                    completionHandler:^(NSError *_Nullable dismissError) {
                      if (UMPConsentInformation.sharedInstance.consentStatus ==
                          UMPConsentStatusObtained) {
                        // App can start requesting ads.
                      }
                        // Handle dismissal by reloading form.
                        [self loadForm];
                    }];
      } else {
        // Keep the form available for changes to user consent.
      }
    }
  }];
}

- (void) initIronSource {
   // [IronSource setAdaptersDebug:YES];
    [IronSource setLevelPlayBannerDelegate:self];
    [IronSource setLevelPlayInterstitialDelegate:self];
    [IronSource setLevelPlayRewardedVideoDelegate:self];
    [IronSource initWithAppKey:GameIronSourceId delegate:self];
   // [IronSource loadBannerWithViewController:self size:ISBannerSize_BANNER];
}
- (void)initializationDidComplete {
 //   [ISIntegrationHelper validateIntegration];
    [IronSource initWithAppKey:GameIronSourceId adUnits:@[BannerIronSourceId]];
    if (typeAdsNetwork == 4)
        [IronSource loadBannerWithViewController:self size:ISBannerSize_BANNER];
    
    [IronSource initWithAppKey:GameIronSourceId adUnits:@[InterIronSourceId]];
    [IronSource initWithAppKey:GameIronSourceId adUnits:@[RewardIronSourceId]];
    [IronSource loadInterstitial];
    [IronSource loadRewardedVideo];
}
/**
 Called after each banner ad has been successfully loaded, either a manual load or banner refresh
 @param adInfo The info of the ad.
 */
- (void)didLoad:(ISBannerView *)bannerView withAdInfo:(ISAdInfo *)adInfo{
    NSLog(@"didload");
    NSLog(@"%s",__PRETTY_FUNCTION__);
     dispatch_async(dispatch_get_main_queue(), ^{
         self.bannerViewIS = bannerView;
         if (@available(iOS 11.0, *)) {
             [self.bannerViewIS setCenter:CGPointMake(self.view.center.x,self.view.frame.size.height - (self.bannerViewIS.frame.size.height/2.0) - self.view.safeAreaInsets.bottom)]; // safeAreaInsets is available from iOS 11.0
         } else {
             [self.bannerViewIS setCenter:CGPointMake(self.view.center.x,self.view.frame.size.height - (self.bannerViewIS.frame.size.height/2.0))];
         }
         [self.view addSubview:self.bannerViewIS];
     });
}
/**
 Called after a banner has attempted to load an ad but failed.
 This delegate will be sent both for manual load and refreshed banner failures.
 @param error The reason for the error
 */
- (void)didFailToLoadWithError:(NSError *)error{
    NSLog(@"didFailToLoadWithError %li", error.code);
    //game->hideGuiWaitting();
   // showInterNow = false;
  //  [IronSource loadInterstitial];
}
/**
 Called after a banner has been clicked.
 @param adInfo The info of the ad.
 */
- (void)didClickWithAdInfo:(ISAdInfo *)adInfo{
    NSLog(@"didClickWithAdInfo");
}
/**
 Called when a user was taken out of the application context.
 @param adInfo The info of the ad.
 */
- (void)didLeaveApplicationWithAdInfo:(ISAdInfo *)adInfo{
    NSLog(@"didLeaveApplicationWithAdInfo");
}
/**
 Called when a banner presented a full screen content.
 @param adInfo The info of the ad.
 */
- (void)didPresentScreenWithAdInfo:(ISAdInfo *)adInfo{
    NSLog(@"didPresentScreenWithAdInfo");
}
/**
 Called after a full screen content has been dismissed.
 @param adInfo The info of the ad.
 */
- (void)didDismissScreenWithAdInfo:(ISAdInfo *)adInfo{
    NSLog(@"didDismissScreenWithAdInfo");
    game->hideGuiWaitting();
    [IronSource loadInterstitial];
}


/**
 Called after an interstitial has been loaded
 @param adInfo The info of the ad.
 */
- (void)didLoadWithAdInfo:(ISAdInfo *)adInfo {
    NSLog(@"didLoadWithAdInfo");
//    if (showInterNow) {
//        [IronSource showInterstitialWithViewController:self];
//        game->hideGuiWaitting();
//    }
}
/**
 Called after an interstitial has attempted to load but failed.
 @param error The reason for the error
 */

/**
 Called after an interstitial has been opened.
 This is the indication for impression.
 @param adInfo The info of the ad.
 */
- (void)didOpenWithAdInfo:(ISAdInfo *)adInfo {
    NSLog(@"didOpenWithAdInfo");
    game->hideGuiWaitting();
}
/**
 Called after an interstitial has been dismissed.
 @param adInfo The info of the ad.
 */
- (void)didCloseWithAdInfo:(ISAdInfo *)adInfo {
    NSLog(@"didCloseWithAdInfo");
    game->hideGuiWaitting();
    [IronSource loadInterstitial];
}
/**
 Called after an interstitial has attempted to show but failed.
 @param error The reason for the error
 @param adInfo The info of the ad.
 */
- (void)didFailToShowWithError:(NSError *)error andAdInfo:(ISAdInfo *)adInfo {
    NSLog(@"didFailToShowWithError");
    game->hideGuiWaitting();
    [IronSource loadInterstitial];
}


/**
 Called after an interstitial has been displayed on the screen.
 This callback is not supported by all networks, and we recommend using it
 only if it's supported by all networks you included in your build.
 @param adInfo The info of the ad.
 */
- (void)didShowWithAdInfo:(ISAdInfo *)adInfo {
   // [adInfo auction_id];
    game->hideGuiWaitting();
    NSLog(@"didShowWithAdInfo");
}

/**
 Called after a rewarded video has changed its availability to true.
 @param adInfo The info of the ad.
 Replaces the delegate rewardedVideoHasChangedAvailability:(true)available
 */
- (void)hasAdAvailableWithAdInfo:(ISAdInfo *)adInfo{
    NSLog(@"hasAdAvailableWithAdInfo");
}
/**
 Called after a rewarded video has changed its availability to false.
 Replaces the delegate rewardedVideoHasChangedAvailability:(false)available
 */
- (void)hasNoAvailableAd{
    game->onReward(1);
    NSLog(@"hasNoAvailableAd");
    [IronSource loadRewardedVideo];
}
/**
 Called after a rewarded video has been viewed completely and the user is eligible for a reward.
 @param placementInfo An object that contains the placement's reward name and amount.
 @param adInfo The info of the ad.
 */
- (void)didReceiveRewardForPlacement:(ISPlacementInfo *)placementInfo withAdInfo:(ISAdInfo *)adInfo {
    game->onReward(1);
    NSLog(@"didReceiveRewardForPlacement");
    [IronSource loadRewardedVideo];
}
/**
 Called after a rewarded video has attempted to show but failed.
 @param error The reason for the error
 @param adInfo The info of the ad.
 */

/**
 Called after a rewarded video has been clicked.
 This callback is not supported by all networks, and we recommend using it
 only if it's supported by all networks you included in your build
 @param adInfo The info of the ad.
 */
- (void)didClick:(ISPlacementInfo *)placementInfo withAdInfo:(ISAdInfo *)adInfo {
    NSLog(@"didClick");
}


- (void)showTracking {
    if (@available(iOS 14, *)) {
        [ATTrackingManager requestTrackingAuthorizationWithCompletionHandler:^(ATTrackingManagerAuthorizationStatus status) {
            // Tracking authorization completed. Start loading ads here.
            // [self loadAd];
        }];
    } else {
        // Fallback on earlier versions
    }
}

- (void)forceRotateToOrientation:(UIInterfaceOrientation)orientation {
    changeRotation = 1;  // Enable rotation temporarily
    
    NSNumber *value = [NSNumber numberWithInt:orientation];
    [[UIDevice currentDevice] setValue:value forKey:@"orientation"];
    if (orientation == UIInterfaceOrientationPortrait)
        isLandscape = 0;
    else
        isLandscape = 1;
    [UIViewController attemptRotationToDeviceOrientation];
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        changeRotation = 0; // Disable rotation again after the change
        });
}
@end
