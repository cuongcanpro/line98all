//
//  IOSConnection.cpp
//  ChineseChess
//
//  Created by Dong Truong Quang on 3/5/14.
//
//
//#import "Reachability.h"
#import "IOSConnection.h"
#import <MessageUI/MFMailComposeViewController.h>
#include "RootViewControllerInterface.h"

using namespace std;


void IOSConnection::openURL(std::string url)
{
    NSString* nsURL = [NSString stringWithUTF8String:("" + url).c_str()];
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:nsURL]];
}

std::string IOSConnection::getIMEI()
{
    NSUUID *identify = [[UIDevice currentDevice] identifierForVendor];
    NSString *str = [identify UUIDString];
    return [str UTF8String];
}

std::string IOSConnection::getDeviceModel()
{
    NSString *str = [[UIDevice currentDevice] platformString];
    return [str UTF8String];
}

void IOSConnection::saveData(std::string key, std::string value)
{
    NSString *savingValue = [NSString stringWithUTF8String:value.c_str()];
    NSString *savingKey = [NSString stringWithUTF8String:key.c_str()];
    
    NSUserDefaults *standardUserDefaults = [NSUserDefaults standardUserDefaults];
    if(standardUserDefaults)
    {
        [standardUserDefaults setObject:savingValue forKey:savingKey];
        [standardUserDefaults synchronize];
    }
    
}
