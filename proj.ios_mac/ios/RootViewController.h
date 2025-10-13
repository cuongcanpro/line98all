#import <UIKit/UIKit.h>
#import <GoogleMobileAds/GoogleMobileAds.h>
//#import "GoogleMobileAds.framework/Headers/GoogleMobileAds.h"
//@import GoogleMobileAds;
#import <UnityAds/UnityAds.h>
//#import "FBAudienceNetwork.framework/Headers/FBAdSettings.h"
//#import "FBAudienceNetwork.framework/Headers/FBAudienceNetworkAds.h"
#import <FBAudienceNetwork/FBAudienceNetworkAds.h>
#import <FBAudienceNetwork/FBAdView.h>
#import <FBAudienceNetwork/FBAdSettings.h>
#import <FBAudienceNetwork/FBInterstitialAd.h>
#import <FBAudienceNetwork/FBRewardedVideoAd.h>
//#import "IronSource/IronSource.h"
//#import <FBAudienceNetwork/FBAdSettings.h>
//#import <FBAudienceNetwork/FBAudienceNetwork.h>
#import "IronSource/IronSource.h"

static NSString *const gameIdUnity = @"4372806";
static NSString *const InterUnityId = @"Interstitial_iOS";
static NSString *const BannerUnityId = @"Banner_iOS";
static NSString *const RewardUnityId = @"Rewarded_iOS";

static NSString *const InterAdmobId = @"ca-app-pub-9378724246417115/6743567089";
static NSString *const BannerAdmobId = @"ca-app-pub-9378724246417115/6297415346";
static NSString *const RewardAdmobId = @"ca-app-pub-9378724246417115/5430485415";

//test id  ca-app-pub-3940256099942544~1458002511
//static NSString *const InterAdmobId = @"ca-app-pub-9378724246417115/9369295654";
//static NSString *const BannerAdmobId = @"ca-app-pub-3940256099942544/2934735716";
//static NSString *const RewardAdmobId = @"ca-app-pub-9378724246417115/2087471933";

static NSString *const InterFacebookId = @"699896970081935_2841939389211005";
static NSString *const BannerFacebookId = @"699896970081935_2841940332544244";
static NSString *const RewardFacebookId = @"699896970081935_2841944489210495";


static NSString *const GameIronSourceId = @"1f5f2f7ed";
static NSString *const InterIronSourceId = @"whxwqj408b1keplj";
static NSString *const BannerIronSourceId = @"7y37hehjzzt5h6tv";
static NSString *const RewardIronSourceId = @"9k9lswq2ajughvbe";

static int typeLastShow = 0;
static int typeAdsNetwork = 1;
static int typeAdsNetworkInter = 1;
static int kMediationOrdinal = 1;
static int countErrorInter = 0;
static int countErrorBanner = 0;
static bool moveToUnity = false;
static int changeRotation = 0;
static int isLandscape = 0;
@interface RootViewController : UIViewController <GADFullScreenContentDelegate, GADBannerViewDelegate
,UnityAdsDelegate, UnityAdsLoadDelegate, UnityAdsShowDelegate, UnityAdsInitializationDelegate, UnityAdsBannerDelegate, FBAdViewDelegate, FBInterstitialAdDelegate, FBRewardedVideoAdDelegate
, LevelPlayBannerDelegate, ISInitializationDelegate, LevelPlayInterstitialDelegate, LevelPlayRewardedVideoDelegate>{
   
   //     SmartFox2XClient *smartFox;
}

@property(nonatomic, strong) GADInterstitialAd *interstitialAdmob;
@property(nonatomic, strong) GADBannerView *bannerViewAdmob;
@property(nonatomic, strong) GADRewardedAd *rewardAdmob;

@property (strong, nonatomic) UADSBannerView *bannerViewUnity;

@property (nonatomic, strong) FBAdView *bannerViewFacebook;
@property (nonatomic, strong) FBInterstitialAd *interstitialFacebook;
@property (nonatomic, strong) FBRewardedVideoAd *rewardFacebook;

@property (weak, nonatomic) NSString *defaultGameId;
@property (assign, nonatomic) BOOL testMode;
@property (copy, nonatomic) NSString *interstitialPlacementId;
@property (copy, nonatomic) NSString *incentivizedPlacementId;

@property (nonatomic, strong) ISBannerView *bannerViewIS;
//@property (nonatomic, strong) FBAdView *adView;
//@property (nonatomic, strong) FBInterstitialAd *interstitialAd;
- (void) showBanner;
- (void) hideBanner;
- (void) showInsertial;
- (void) showReward;
- (void) showRewardAdmob;
- (void) initAds: (int)adsType initAdsInter:(int) adsTypeInter;
- (void) initAdmob;
- (void) initUnity;
- (void) initFacebook;
- (void) loadRewardAdmob;
- (void) loadInterFacebook;
- (void) showInterFacebook;
- (void) loadRewardFacebook;
- (void) sendEvent: (NSString*)key data: (NSString*)data;
- (void) crashlyticSetString: (NSString*)key data: (NSString*)data;
- (void) addBannerViewToBottomView: (UIView *)bannerView;
- (void) loadForm;
- (void) initIronSource;
- (void) showTracking;
- (void) forceRotateToOrientation:(UIInterfaceOrientation)orientation;

@end

